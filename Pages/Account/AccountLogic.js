window.addEventListener('load', init);

function init(){
    id('signout').addEventListener('click', SignOut);
    RefreshAccountDetails();

    id('openModal').addEventListener('click', ShowEditModal);
    id('editUserForm').addEventListener('submit', EditUser);
    id('closeEditModalBtn').addEventListener('click', HideEditModal);
    id('cancelModal').addEventListener('click', HideEditModal);
}

function ShowEditModal(){
  id('editModal').style.display = "flex";

  id('editUsername').value = id('displayUsername').innerText;
  id('editPassword').value = "";
  id('editFirstName').value = id('displayFirstName').innerText;
  id('editLastName').value = id('displayLastName').innerText;
  id('editEmail').value = id('displayEmail').innerText;
  id('editPhoneNum').value = id('displayPhoneNum').innerText;
}

function HideEditModal(){
  id('editModal').style.display = "none";
  id('editUserForm').reset();
}

function EditUser(){

  let



}

async function SignOut(event){
    await window.backend.SetCurrentUserID(NaN);
    await window.backend.LoadPage('/Pages/Login/Login.html');
}

async function RefreshAccountDetails(){

    let userID = await window.backend.GetCurrentUserID();
    let args = [106, userID];

    let response = await window.backend.CallDB(args);
    try{
        const response = await window.backend.CallDB(args);

        if(response.success){
          try{
            parsedOutput = JSON.parse(response.output);
            PopulateAccountDetails(parsedOutput);
          }
          catch(parseError){
            document.getElementById('accountDetailsContainer').innerHTML = "failed to parse account details JSON";
          }
        }
        else{
            document.getElementById('testOutput').innerText = "API error: ".concat(response.output);
        }
    } catch (error){
        document.getElementById('testOutput').innerText = "Failed to call node.js backend: ".concat(response.output);
    }
}

function PopulateAccountDetails(output) {
    if (!output || output.length === 0) {
      console.error('No user data found in the output.');
      return;
    }
  
    const user = output[0];
  
    let phoneNum = (user.PhoneNumber == "null") ? "" : user.PhoneNumber;

    id('displayUsername').innerText = `${user.UserName}`
    id('displayFirstName').innerText = `${user.FirstName}`
    id('displayLastName').innerText = `${user.LastName}`
    id('displayEmail').innerText = `${user.Email}`
    id('displayPhoneNum').innerText = `${phoneNum}`

  }
  