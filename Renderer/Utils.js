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