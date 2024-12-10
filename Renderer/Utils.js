function id(elementName){
    return document.getElementById(elementName);
}

function createTableFromJSON(data) {
    const table = document.createElement('table');

    table.id = 'table';

    // Create table header
    const thead = table.createTHead();
    const headerRow = thead.insertRow();
    const headers = Object.keys(data[0]);
    headers.forEach(header => {
        const th = document.createElement('th');
        th.textContent = header;
        if (header === headers[0]) {
            th.classList.add('hiddenCell');
        }
        headerRow.appendChild(th);
    });

    // Create table body
    const tbody = table.createTBody();
    data.forEach(row => {
        const tr = tbody.insertRow();

        headers.forEach(header => {

            const td = tr.insertCell();
            if(row[header] == null){
                td.textContent = "";
            }
            else{
                td.textContent = row[header];
            }
            console.log("row[header]: ".concat(row[header]));
            console.log("headers[0]: ".concat(headers[0]));
            if (header === headers[0]) {
                td.classList.add('hiddenCell');
            }
        });
    });

    return table;
}


function argString(value){
    if(value === ""){
        return null;
    }
    else{
        return "'".concat(value.concat("'"));
    }
}

function displayError(message){
    id('errorOutput').textContent = message;
}

function displayUserID(){
    id('debug_currentUserID').innerText = "Debug::UserID: ".concat(window.backend.GetCurrentUserID());
}

function clearDynamicContent(){
    id('dynamicSection').innerHTML = "";
}


async function PopulateStatusDropdown(dropdown){
    let userID = await window.backend.GetCurrentUserID();
    let args = [103, userID];

    const response = await window.backend.CallDB(args);
    if(response.success){

        let parsedResponse = JSON.parse(response.output);

        parsedResponse.forEach(status => {
            const option = document.createElement("option");
            option.value = status.StatusID;
            option.textContent = `${status.Status}`;
            dropdown.appendChild(option);
        })
    }
}


async function PopulateRecipientDropdown(dropdown){
    let userID = await window.backend.GetCurrentUserID();
    let args = [102, userID];

    const response = await window.backend.CallDB(args);
    if(response.success){
        if(response.output == "[]"){
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        
        dropdown.innerHTML = `<option value="">No recipient selected</option>`;


        parsedResponse.forEach(recipient => {
            const option = document.createElement("option");
            option.value = recipient.recipientID;
            option.textContent = `${recipient.FirstName} ${recipient.LastName}`;
            dropdown.appendChild(option);
        })
    }
}

async function PopulateEventDropdown(dropdown){
    let userID = await window.backend.GetCurrentUserID();
    let args = [101, userID];

    const response = await window.backend.CallDB(args);
    if(response.success){
        if(response.output == "[]"){
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        dropdown.innerHTML = `<option value="">No event selected</option>`;


        parsedResponse.forEach(event => {
            const option = document.createElement("option");
            option.value = event.eventID;
            option.textContent = `${event.Name}`;
            dropdown.appendChild(option);
        })
    }
}

async function PopulatePurchaseLocationDropdown(dropdown) {
    let userID = await window.backend.GetCurrentUserID();
    let args = [104, userID]; // Assuming 104 is the code for purchase locations

    const response = await window.backend.CallDB(args);
    if (response.success) {
        if (response.output === "[]") {
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        dropdown.innerHTML = `<option value="">No purchase location selected</option>`;

        parsedResponse.forEach(location => {
            const option = document.createElement("option");
            option.value = location.LocationID;
            option.textContent = location.LocationName;
            dropdown.appendChild(option);
        });
    }
}
async function PopulateCategoryDropdown(dropdown) {
    let userID = await window.backend.GetCurrentUserID();
    let args = [105, userID]; // Assuming 105 is the code for categories

    const response = await window.backend.CallDB(args);
    if (response.success) {
        if (response.output === "[]") {
            return;
        }

        let parsedResponse = JSON.parse(response.output);

        dropdown.innerHTML = `<option value="">No category selected</option>`;

        parsedResponse.forEach(category => {
            const option = document.createElement("option");
            option.value = category.CategoryID;
            option.textContent = category.Name;
            dropdown.appendChild(option);
        });
    }
}