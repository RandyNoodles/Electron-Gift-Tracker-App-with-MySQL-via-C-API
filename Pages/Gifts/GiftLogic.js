window.addEventListener('load', init);

let selectedRow = null;
function SelectRow(event){
    selectedRow = event.target.closest('tr');
}

function init(){
    RefreshGiftTable();
    id('giftTableContainer').addEventListener('click', SelectRow);

    id('addRowBtn').addEventListener('click', ShowAddModal);
    id('addGiftForm').addEventListener('submit', AddRow);
    id('closeAddModalBtn').addEventListener('click', HideAddModal);

    id('editRowBtn').addEventListener('click', ShowEditModal);
    id('editGiftForm').addEventListener('submit', EditRow);
    id('closeEditModalBtn').addEventListener('click', HideEditModal);

    //id('deleteRowBtn').addEventListener('click', DeleteRow);
}


//ADD GIFT STUFF
function ShowAddModal(event){
    id('addModal').style.display = "flex";
    id('addGiftForm').reset();

    PopulateEventDropdown(id('addEventId'));
    PopulatePurchaseLocationDropdown(id('addPurchaseLocationID'));
    PopulateRecipientDropdown(id('addRecipientId'));
    PopulateStatusDropdown(id('addStatusId'));
}
function HideAddModal(event){
    id('addModal').style.display = "none";
    document.getElementById("addGiftForm").reset();
}
async function AddRow(event){
    event.preventDefault();

    let name = argString(id('addName').value);
    let cost = id('addCost').value;
    if(cost == ""){
        cost = null;
    }

    let statusID = id('addStatusId').value;
    let recipientID = id('addRecipientId').value;
    let eventID = id('addEventId').value;
    let locationID = id('addPurchaseLocationID').value;
    let userID = await window.backend.GetCurrentUserID();

    let args = [200, name, cost, statusID, recipientID, eventID, locationID, userID];


    const response = await window.backend.CallDB(args);

    if(response.success){
        HideAddModal();
        RefreshGiftTable();
        selectedRow = null;
    }
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
    document.getElementById("addGiftForm").reset();
}
async function EditRow(event){
    event.preventDefault();

    let giftID = selectedRow.cells[0].textContent;
    let name = argString(id('editName').value);
    let cost = id('editCost').value;
    let recipientID = id('editRecipientId').value;
    let eventID = id('editEventId').value;
    let statusID = id('editStatusId').value;
    let purchaseLocationID = 1;

    let args = [300, giftID, name, cost, statusID, recipientID, eventID, purchaseLocationID];

    const response = await window.backend.CallDB(args);

    if(response.success){
        //SOME KIND OF FEEDBACK
        HideEditModal();
        RefreshGiftTable();
        selectedRow = null;
    }


}


async function RefreshGiftTable(){
    let userID = await window.backend.GetCurrentUserID();
    let args = ['100', userID];
    const tableContainer = document.getElementById('giftTableContainer');

    tableContainer.innerHTML = "";

    const response = await window.backend.CallDB(args);

    if(response.success){

        if(response.output == '[]'){
            tableContainer.innerHTML = '<p>No gifts created</p>';
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
            tableContainer.innerHTML = "<p>Error loading gift list: ".concat(response.output);
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
