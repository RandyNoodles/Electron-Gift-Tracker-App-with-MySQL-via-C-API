window.addEventListener('load', init);

function init(){
    id('signout').addEventListener('click', SignOut);
    RefreshAccountDetails();
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
  
    // Create the HTML table as a string
    const tableHTML = `
      <table>
        <tr>
          <td colspan="1"><label for="username">Username:</label></td>
          <td colspan="5"><p>${user.UserName}</p></td>
        </tr>
        <tr>
          <td colspan="1"><label for="password">Password:</label></td>
          <td colspan="5"><p>********</p></td>
        </tr>
        <tr>
          <td colspan="1"><label for="firstName">First Name:</label></td>
          <td colspan="5"><p>${user.FirstName}</p></td>
        </tr>
        <tr>
          <td colspan="1"><label for="lastName">Last Name:</label></td>
          <td colspan="5"><p>${user.LastName}</p></td>
        </tr>
        <tr>
          <td colspan="1"><label for="email">Email:</label></td>
          <td colspan="5"><p>${user.Email}</p></td>
        </tr>
        <tr>
          <td colspan="1"><label for="phoneNum">Phone Number:</label></td>
          <td colspan="5"><p>${user.PhoneNumber}</p></td>
        </tr>
        <tr>
          <td colspan="6" style="text-align: center;">
            <button id="openModal" class="navButton">Edit Account</button>
            <button id="signout" class="navButton">Sign Out</button>
          </td>
        </tr>
      </table>
    `;
  
    // Set the innerHTML of the container to the generated table
    document.getElementById('accountDetailsContainer').innerHTML = tableHTML;
  }
  