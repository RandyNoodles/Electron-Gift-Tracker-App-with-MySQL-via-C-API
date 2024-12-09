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
// function createTableFromJSON(data) {
//     const table = document.createElement('table');
//     table.id = 'table';

//     // Create table header
//     const thead = table.createTHead();
//     const headerRow = thead.insertRow();

//     const headers = Object.keys(data[0]);
//     headers.forEach(header => {
      
//         const th = document.createElement('th');
//         th.textContent = header;
//         headerRow.appendChild(th);
//     });

//     // Create table body
//     const tbody = table.createTBody();
//     data.forEach(row => {
//         const tr = tbody.insertRow();

//         // Insert a hidden cell for the ID (first key)
//         const firstKey = headers[0];
//         const hiddenCell = tr.insertCell();
//         hiddenCell.textContent = row[firstKey];
        

//         // Insert the rest of the cells
//         headers.forEach(header => {
//             const td = tr.insertCell();
//             td.textContent = row[header] != null ? row[header] : "";
//         });
//     });

//     return table;
// }

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