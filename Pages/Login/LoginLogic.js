window.addEventListener('load', init);

function init(){

    id('loginForm').addEventListener('submit', SignIn);
    id('showCreateAccountForm').addEventListener('click', SwitchToCreateAccount);
    id('newUserForm').addEventListener('submit', CreateAccount);
    id('backToLoginButton').addEventListener('click', SwitchToLogin);
}

function HideNewUserModal(){
    id('newUserModal').style.display = "none";
    SwitchToLogin();
    ClearCreateAccountForm();
}

function SwitchToCreateAccount(){
    id('newUserModal').style.display = "flex";
}

function SwitchToLogin(){
    id('newUserModal').style.display = "none";
    id('loginForm').style.display = "inline";
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

async function CreateAccount(event){
    event.preventDefault();

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
             id('loginError').innerText = `CreateAccount() failed: ${response.output}`;
        }
    }
    catch(error){
        id('loginError').innerText = "CreateAccount() failed to call the MySQL API.";
    }
}


async function SignIn(event){
    event.preventDefault();

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
                 id('loginError').innerText = `Failed to parse JSON on SignIn(): ${parseError}`;                
            }
        }
        else{
             id('loginError').innerText = `Invalid query: ${response.output}`;           
        }
    }
    catch(error){
         id('loginError').innerText = "SignIn() failed to call the MySQL API.";
    }

    if(querySuccess){

        if(parsedResponse.userID > 0){
            await window.backend.SetCurrentUserID(parsedResponse.userID);
            id('debug_currentUserID').innerText = await window.backend.GetCurrentUserID();
            await window.backend.LoadPage('/Pages/Gifts/Gifts.html');
        }
        else{
            id('loginError').innerText = "Invalid username or password.";
        }
    }   
}

function SignOut(){
    currentUserID = NaN;
    ShowLoginModal();
}