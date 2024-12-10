window.addEventListener('load', init);

let selectedRow = null;
function SelectRow(event){
    selectedRow = event.target.closest('tr');
}

function init(){
    RefreshEventTable();
    id('eventTableContainer').addEventListener('click', SelectRow);

    id('addRowBtn').addEventListener('click', ShowAddModal);
    id('addEventForm').addEventListener('submit', AddRow);
    id('closeAddModalBtn').addEventListener('click', HideAddModal);

    id('editRowBtn').addEventListener('click', ShowEditModal);
    id('editEventForm').addEventListener('submit', EditRow);
    id('closeEditModalBtn').addEventListener('click', HideEditModal);
        //id('deleteRowBtn').addEventListener('click', DeleteRow);

}



//ADD GIFT STUFF
function ShowAddModal(event){
    id('addModal').style.display = "flex";
    id('addEventForm').reset();
}
function HideAddModal(event){
    id('addModal').style.display = "none";
    document.getElementById("addEventForm").reset();
}
function AddRow(event){
    event.preventDefault();
}


//EDIT GIFT STUFF
//
function ShowEditModal(event){
    if(selectedRow != null){
        id('editModal').style.display = "flex";
        id('editGiftForm').reset();
        id('editName').value = selectedRow.cells[1].textContent;
        id('editCost').value = selectedRow.cells[2].textContent;
        PopulateRecipientDropdown(id('editRecipientId'));
        PopulateEventDropdown(id('editEventId'));
        PopulateStatusDropdown(id('editStatusId'));
    }
}
function HideEditModal(event){
    id('editModal').style.display = "none";
    document.getElementById("editEventForm").reset();
}
function EditRow(event){
    event.preventDefault();
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