//BASIC ANATOMY OF A HTML LOAD CALL
async function callRouter(){
    //(This would normally be an arg)
    let name = "test.html";

    let response = await window.backend.LoadHTML(name);

    //What to do if it succeeded
    if(response.success){
        document.getElementById('testOutput').innerHTML = response.output;
    }
    //What to do if it failed
    else{
        document.getElementById('testOutput').innerHTML = "ERR: ".concat(response.output);
    }
}

//
//BASIC ANATOMY OF A DB CALL
//
async function callDatabase(){
    let args = ['200', 'TestFromRenderer', 120, 1, null, null, null];//TEST COMMAND
    try{
        //Actual database call
        const response = await window.backend.CallDB(args);

        //response.success means you have good stuff from stdout
        if(response.success){
            document.getElementById('testOutput').innerText = response.output;
        }
        //!response.success means there was something in stderr, OR the exit code was non-zero.
        else{
            document.getElementById('testOutput').innerText = "API error: ".concat(response.output);
        }
    //This will mean the call never reached the backend/MySQLAPI()
    } catch (error){
        document.getElementById('testOutput').innerText = "Failed to call node.js backend: ".concat(response.output);
    }
}