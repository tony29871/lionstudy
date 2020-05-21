#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>

#define BUF_SIZE 100
void error_handling(char* message);

int main(int argc, char **argv){ // .txt파일 , 포트번호 입력받기
char buffer[BUF_SIZE];
struct sockaddr_in server_addr, client_addr;
int server_sock, client_sock;
socklen_t client_addr_size = sizeof(client_addr);
int fd;

// txt파일 받아오기
fd = open(argv[1],O_RDONLY);
if(fd<0){
perror(".txt file open() error!");
}
if(read(fd,buffer,sizeof(buffer))<0){
perror(".txt read() error!");
}
close(fd);

if (argc != 3){
printf("Usage: %s [.txt] [port] \n", argv[0]); // 잘못 입력시 하는 법 알려주기
return -1;
}

//소켓 생성
if ((server_sock = socket(PF_INET,SOCK_STREAM, 0)) < 0){ // Socket_stream:TCP/IP 통신, AF_INET: IP4
perror("Socket failed !");
return -1;
}

//소켓 초기화
memset(&server_addr,0,sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(atoi(argv[2]));
server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

//bind 오류처리
if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
perror("bind failed");
return -1;
}

//listen 오류처리, 대기상태
printf("Lisetning...\n");
if(listen(server_sock,3)<0){
perror("Server: Can't listening connect");
return -1;
}

//client와 접속 실패시 오류처리
client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_size);
if (client_sock < 0){
perror("accept failed");
return -1;
}
printf("Server client connected\n");
//버퍼에 저장된 내요을 클라이언트로 전송
write(client_sock, buffer,sizeof(buffer));

//소켓 닫기
close(client_sock);
close(server_sock);
return 0;
}
