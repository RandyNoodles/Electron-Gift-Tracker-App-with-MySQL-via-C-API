window.addEventListener('load', init);

let selectedRow = null;
function SelectRow(event){
    selectedRow = event.target.closest('tr');
}

function init(){
    RefreshEventTable();
    id('eventTableContainer').addEventListener('click', SelectRow);

    id('addNewCategoryCheckbox').addEventListener('click', ToggleNewCategoryField);

    id('addRowBtn').addEventListener('click', ShowAddModal);
    id('addEventForm').addEventListener('submit', AddRow);
    id('closeAddModalBtn').addEventListener('click', HideAddModal);
    id('cancelAddModal').addEventListener('click', HideAddModal);

    id('editRowBtn').addEventListener('click', ShowEditModal);
    id('editEventForm').addEventListener('submit', EditRow);
    id('closeEditModalBtn').addEventListener('click', HideEditModal);
    id('cancelEditModal').addEventListener('click', HideEditModal);
    
    id('deleteRowBtn').addEventListener('click', DeleteRow);
}

function ToggleNewCategoryField() {
    const checkbox = document.getElementById('addNewCategoryCheckbox');
    const inputField = document.getElementById('addNewCategory');
    const selectField = document.getElementById('addCategoryId');

    if (checkbox.checked) {
        //turn on input
        inputField.style.display = 'block';
        inputField.required = true;
        //turn off dropdown
        selectField.disabled = true;
        selectField.required = false;
        
    } else {
        //turn off input
        inputField.style.display = 'none';
        inputField.required = false;
        //turn on dropdown
        selectField.disabled = false;
        selectField.required = true;
    }
}



async function DeleteRow(){
    
    if (!selectedRow) {
        alert("Please select a row to delete.");
        return;
    }

    // Display confirmation dialog
    const confirmation = confirm("Are you sure you want to delete this event?");
    if (confirmation) {
        let eventID = selectedRow.cells[0].textContent;

        if(eventID != null){
            
                let args = [401, eventID];
            
                const response = await window.backend.CallDB(args);
            
                if(response.success){
                    RefreshEventTable();
                }
    
                selectedRow = null;
        }
    }
}



//ADD EVENT STUFF
function ShowAddModal(event){
    id('addModal').style.display = "flex";
    id('addEventForm').reset();
    PopulateCategoryDropdown(id('addCategoryId'));
}
function HideAddModal(event){
    id('addModal').style.display = "none";
    document.getElementById("addEventForm").reset();
}
async function AddRow(event){
    event.preventDefault();


    let name = argString(id('addName').value);
    let date = argString(id('addDate').value);
    let categoryID = id('addCategoryId').value;
    let userId = await window.backend.GetCurrentUserID();


    let newCategoryResponse = null;
    const checkbox = id('addNewCategoryCheckbox').checked;
    if(checkbox){
        let newCategory = argString(id('addNewCategory').value);
        let args2 = [203, newCategory];

        newCategoryResponse = await window.backend.CallDB(args2);
        
        if(newCategoryResponse.success){
            newCategoryID = JSON.parse(newCategoryResponse.output);
            categoryID = newCategoryID.AddedItemID;
        }
        else{
            id('addError').innerHTML = `<p>Error adding new category: ${newCategoryResponse.output}</p>`;
            return;
        }

    }

    let args = [201, name, date, categoryID, userId];

    const response = await window.backend.CallDB(args);

    if(response.success){
        HideAddModal();
        RefreshEventTable();
        selectedRow = null;
    }
}

//EDIT EVENT STUFF
//
function ShowEditModal(event){
    if (!selectedRow) {
        alert("Please select a row to edit.");
        return;
    }
    id('editModal').style.display = "flex";
    id('editEventForm').reset();
    id('editName').value = selectedRow.cells[1].textContent;
    PopulateCategoryDropdown(id('editCategoryId'));
}

function HideEditModal(event){
    id('editModal').style.display = "none";
    document.getElementById("editEventForm").reset();
}
async function EditRow(event){
    event.preventDefault();

    let eventID = selectedRow.cells[0].textContent;
    let name = argString(id('editName').value);
    let date = argString(id('editDate').value);
    let categoryID = id('editCategoryId').value;
    let userID = await window.backend.GetCurrentUserID();

    let args = [301, eventID, name, date, categoryID, userID];

    const response = await window.backend.CallDB(args);

    if(response.success){
        HideEditModal();
        RefreshEventTable();
        selectedRow = null;
    }
}


async function RefreshEventTable(){
    let userID = await window.backend.GetCurrentUserID();
    let args = ['101', userID];
    const tableContainer = document.getElementById('eventTableContainer');

    tableContainer.innerHTML = "";

    const response = await window.backend.CallDB(args);

    if(response.success){

        if(response.output == '[]'){
            tableContainer.innerHTML = '<p>No events created</p>';
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
            tableContainer.innerHTML = "<p>Error loading event list: ".concat(response.output);
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