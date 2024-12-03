//THIS IS BASICALLY OUR CLIENT-SIDE JS

window.addEventListener("load", init);

function init(){
    document.getElementById('loadGifts').addEventListener('click', LoadGiftTable);
}


async function LoadGiftTable(){
    const response = await window.testJSON.getGifts();
    const tableContainer = document.getElementById('table-container');

    const table = createTableFromJSON(response);
    tableContainer.appendChild(table);
}

function createTableFromJSON(data) {
    const table = document.createElement('table');
    table.border = '1';

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
            td.textContent = row[header];
        });
    });

    return table;
}

