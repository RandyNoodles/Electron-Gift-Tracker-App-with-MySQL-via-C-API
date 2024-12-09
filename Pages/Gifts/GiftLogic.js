window.addEventListener('load', init);

let selectedRow = null;

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
function SelectRow(event){
    selectedRow = event.target.closest('tr');
}

//ADD GIFT STUFF
function ShowAddModal(event){
    id('addModal').style.display = "flex";
    id('addGiftForm').reset();
}
function HideAddModal(event){
    id('addModal').style.display = "none";
    document.getElementById("addGiftForm").reset();
}
function AddRow(event){
    event.preventDefault();

}


//EDIT GIFT STUFF
//
function ShowEditModal(event){
    id('editModal').style.display = "flex";
    id('editGiftForm').reset();
    id('editName').value = selectedRow.cells[1].textContent;
    id('editCost').value = selectedRow.cells[2].textContent;
    GetRecipientList();
    GetEventList();
}
function HideEditModal(event){
    id('editModal').style.display = "none";
    document.getElementById("addGiftForm").reset();
}
function EditRow(event){
    event.preventDefault();
}




async function GetRecipientList(){
    let userID = await window.backend.GetCurrentUserID();
    let args = [102, userID];

    const response = await window.backend.CallDB(args);
    if(response.success){
        if(response.output == "[]"){
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        let dropdown = document.getElementById('editRecipientId');
        dropdown.innerHTML = `<option value="">No recipient selected</option>`;


        parsedResponse.forEach(recipient => {
            const option = document.createElement("option");
            option.value = recipient.recipientID;
            option.textContent = `${recipient.FirstName} ${recipient.LastName}`;
            dropdown.appendChild(option);
        })
    }
}

async function GetEventList(){
    let userID = await window.backend.GetCurrentUserID();
    let args = [101, userID];

    const response = await window.backend.CallDB(args);
    if(response.success){
        if(response.output == "[]"){
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        let dropdown = document.getElementById('editEventId');
        dropdown.innerHTML = `<option value="">No event selected</option>`;


        parsedResponse.forEach(event => {
            const option = document.createElement("option");
            option.value = event.eventID;
            option.textContent = `${event.Name}`;
            dropdown.appendChild(option);
        })
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
