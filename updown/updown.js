const range =100;
const answer = Math.ceil(Math.random()*range);
console.log(answer);

const inputTag = document.getElementById("input");
const resultDiv = document.getElementById("result");
const formBtn = document.getElementById("formBtn");
const displaylife = document.getElementById("lifecnt");

let life = 5; 
formBtn.onclick = (event)=>{
    displaylife.textContent = life;
    const userInput =  Number(inputTag.value);
    const result =document.createElement('h2');
    result.textContent = userInput +"->";

    if(userInput===answer){
        event.preventDefault();
        result.textContent += "Answer";
        alert("You are Correct!"); 
    }
    else {
        if(life>0){
            life -=1;
            event.preventDefault();
            (userInput > answer)?(result.textContent+="Down"):(result.textContent+="Up")
            inputTag.focus();
        }
        else{
            alert("You failed!\nThe answer is "+answer);
        }
    }
    resultDiv.append(result);
    inputTag.value=' ';
}
