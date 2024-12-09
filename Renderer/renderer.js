//THIS IS BASICALLY OUR CLIENT-SIDE JS

window.addEventListener("load", init);

function init(){

}





async function LoadGiftTable(){
    let args = ['100', '1'];
    const response = await window.backend.CallDB(args);
    const tableContainer = document.getElementById('table-container');

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
}

function createTableFromJSON(data) {
    const table = document.createElement('table');

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