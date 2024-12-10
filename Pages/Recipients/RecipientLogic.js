window.addEventListener('load', init);

let selectedRow = null;
function SelectRow(event){
    selectedRow = event.target.closest('tr');
}

function init(){
    RefreshRecipientTable();
    id('recipientTableContainer').addEventListener('click', SelectRow);

    id('addRowBtn').addEventListener('click', ShowAddModal);
    id('addRecipientForm').addEventListener('submit', AddRow);
    id('closeAddModalBtn').addEventListener('click', HideAddModal);

    id('editRowBtn').addEventListener('click', ShowEditModal);
    id('editRecipientForm').addEventListener('submit', EditRow);
    id('closeEditModalBtn').addEventListener('click', HideEditModal);

    id('deleteRowBtn').addEventListener('click', DeleteRow);
}

async function DeleteRow(){
    
    if (!selectedRow) {
        alert("Please select a row to delete.");
        return;
    }

    // Display confirmation dialog
    const confirmation = confirm("Are you sure you want to delete this recipient?");
    if (confirmation) {
        let recipientID = selectedRow.cells[0].textContent;

        if(recipientID != null){
            
                let args = [402, recipientID];
            
                const response = await window.backend.CallDB(args);
            
                if(response.success){
                    RefreshRecipientTable();
                }
    
                selectedRow = null;
        }
    }
}



//ADD GIFT STUFF
function ShowAddModal(event){
    id('addModal').style.display = "flex";
    id('addRecipientForm').reset();
}
function HideAddModal(event){
    id('addModal').style.display = "none";
    document.getElementById("addRecipientForm").reset();
}
async function AddRow(event){
    event.preventDefault();

    let firstName = argString(id('addFirstName').value);
    let lastName = argString(id('addLastName').value);
    let dob = argString(id('addDateOfBirth').value);
    let userID = await window.backend.GetCurrentUserID();

    let args = [202, firstName, lastName, dob, userID];


    const response = await window.backend.CallDB(args);

    if(response.success){
        HideAddModal();
        RefreshRecipientTable();
        selectedRow = null;
    }
}


//EDIT GIFT STUFF
//
function ShowEditModal(event){
    if (!selectedRow) {
        alert("Please select a row to edit.");
        return;
    }
    id('editModal').style.display = "flex";
    id('editRecipientForm').reset();

    id('editFirstName').value = selectedRow.cells[1].textContent;
    id('editLastName').value = selectedRow.cells[2].textContent;
    id('editDateOfBirth').value = selectedRow.cells[3].textContent;
    
}
function HideEditModal(event){
    id('editModal').style.display = "none";
    document.getElementById("addRecipientForm").reset();
}
async function EditRow(event){
    event.preventDefault();

    let recipientID = selectedRow.cells[0].textContent;
    let firstName = argString(id('editFirstName').value);
    let lastName = argString(id('editLastName').value);
    let dob = argString(id('editDateOfBirth').value);
    let userID = await window.backend.GetCurrentUserID();

    let args = [302, recipientID, firstName, lastName, dob, userID];

    const response = await window.backend.CallDB(args);

    if(response.success){
        //SOME KIND OF FEEDBACK
        HideEditModal();
        RefreshRecipientTable();
        selectedRow = null;
    }
}


async function RefreshRecipientTable(){
    let userID = await window.backend.GetCurrentUserID();
    let args = ['102', userID];
    const tableContainer = document.getElementById('recipientTableContainer');

    tableContainer.innerHTML = "";

    const response = await window.backend.CallDB(args);

    if(response.success){

        if(response.output == '[]'){
            tableContainer.innerHTML = '<p>No recipients created</p>';
            return;
        }
        
        tableContainer.innerHTML = "";

        if(response.success){
            let table;
            try{
                formattedResponse = JSON.parse(response.output);
                table = createTableFromJSON(formattedResponse);
                tableContainer.appendChild(table);
            }catch(formatErr){
                tableContainer.innerHTML = "Failed to parse response JSON: ".concat(formatErr);
            }
        }
        else{
            tableContainer.innerHTML = "<p>Error loading recipient list: ".concat(response.output);
        }


        //ADD LISTENERS TO MAKE TABLE HIGHLIGHT SELECTED ROW
        const rows = document.querySelectorAll('#table tbody tr');
        rows.forEach((row) => {
            row.addEventListener('click', () => {
                rows.forEach((r) => r.classList.remove('selected'));
                row.classList.add('selected');
                selectedRow = row;
            });
        });

    }   
}
