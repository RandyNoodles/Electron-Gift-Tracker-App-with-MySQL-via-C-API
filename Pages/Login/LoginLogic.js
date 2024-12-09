window.addEventListener('load', init);


function init(){
    id('loginButton').addEventListener('click', SignIn);
    id('newUserButton').addEventListener('click', SwitchToCreateAccount);
    id('createAccountButton').addEventListener('click', CreateAccount);
    id('backToLoginButton').addEventListener('click', SwitchToLogin);
    id('nav_signOut').addEventListener('click', SignOut);
    ShowLoginModal();
}



function ShowLoginModal(){
    id('loginModal').style.display = "inline";
    id('navbar').style.display = "none";
    id('newUserForm').style.display = "none";
}

function HideLoginModal(){
    id('loginModal').style.display = "none";
    id('navbar').style.display = "flex";
    SwitchToLogin();
    ClearCreateAccountForm();
    ClearLoginForm();
}

function SwitchToCreateAccount(){
    id('newUserForm').style.display = "inline";
    id('loginForm').style.display = "none";
}

function SwitchToLogin(){
    id('newUserForm').style.display = "none";
    id('loginForm').style.display = "flex";
}

function ClearCreateAccountForm(){
    id('newUserName').value = "";
    id('newUserPassword').value = "";
    id('newUserFirstName').value = "";
    id('newUserLastName').value = "";
    id('newUserEmail').value = "";
    id('newUserPhone').value = "";
    id('newUserError').innerText = "";
}
function ClearLoginForm(){
    id('username').value = "";
    id('password').value = "";
    id('loginError').innerText = "";
}

async function CreateAccount(){
    const userName = argString(id('newUserName').value);
    const password = argString(id('newUserPassword').value);
    const firstName = argString(id('newUserFirstName').value);
    const lastName = argString(id('newUserLastName').value);
    const email = argString(id('newUserEmail').value);
    const phone = argString(id('newUserPhone').value);

    //Optional NULLS
    if(phone === ""){ 
        phone = null;
    }

    let newUserArgs = [205, userName, password, firstName, lastName, email, phone];

    try{
        const response = await window.backend.CallDB(newUserArgs);

        if(response.success){
            id('loginError').innerText = "Account successfully created!";
            SwitchToLogin();
        }
        else{
            displayError(`CreateAccount() failed: ${response.output}`);
        }
    }
    catch(error){
        displayError("CreateAccount() failed to call the MySQL API.");
    }
}


async function SignIn(){
    const userName = argString(id('username').value);
    const password = argString(id('password').value);

    let loginArgs = [0, userName, password];
    let querySuccess = false;
    let parsedResponse;

    try{
        const response = await window.backend.CallDB(loginArgs);

        if(response.success){
            try{
                parsedResponse = JSON.parse(response.output);
                querySuccess = true;

            }
            catch(parseError){
                displayError(`Failed to parse JSON on SignIn(): ${parseError}`);
            }
        }
        else{
            displayError(`Invalid query: ${response.output}`);
        }
    }
    catch(error){
        displayError("SignIn() failed to call the MySQL API.");
    }

    if(querySuccess){

        if(parsedResponse.userID > 0){
            currentUserID = parsedResponse.userID;
            displayUserID();
            HideLoginModal();
        }
        else{
            id('loginError').innerText = "Invalid username or password.";
        }
    }   
}

function SignOut(){

    currentUserID = NaN;
    ShowLoginModal();
    clearDynamicContent();
}
