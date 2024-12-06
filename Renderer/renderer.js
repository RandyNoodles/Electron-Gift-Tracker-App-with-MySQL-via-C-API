//THIS IS BASICALLY OUR CLIENT-SIDE JS

window.addEventListener("load", init);

function init(){
    document.getElementById('loadGifts').addEventListener('click', LoadGiftTable);
    document.getElementById('testAPI').addEventListener('click', callDatabase);
}

//BASIC ANATOMY OF A HTML LOAD CALL
async function callRouter(){
    //(This would normally be an arg)
    let name = "test.html";

    let response = await window.backend.LoadHTML(name);

    //What to do if it succeeded
    if(response.success){
        document.getElementById('testOutput').innerHTML = response.output;
    }
    //What to do if it failed
    else{
        document.getElementById('testOutput').innerHTML = "ERR: ".concat(response.output);
    }

}

//
//BASIC ANATOMY OF A DB CALL
//
async function callDatabase(){
    let args = ['200', 'TestFromRenderer', 120, 1, null, null, null];//TEST COMMAND
    try{
        //Actual database call
        const response = await window.backend.CallDB(args);

        //response.success means you have good stuff from stdout
        if(response.success){
            document.getElementById('testOutput').innerText = response.output;
        }
        //!response.success means there was something in stderr, OR the exit code was non-zero.
        else{
            document.getElementById('testOutput').innerText = "API error: ".concat(response.output);
        }
    //This will mean the call never reached the backend/MySQLAPI()
    } catch (error){
        document.getElementById('testOutput').innerText = "Failed to call node.js backend: ".concat(response.output);
    }
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

function CreateTableFromJSON(jsonData){
    let table = document.createElement("table");
    let columns = Object.keys(jsonData[0]);

    let tHead = document.createElement("thead");
    let tr = document.createElement("tr");

    columns.forEach((item) => {
        let th = document.createElement("th");
        th.innerText = item;
        tr.appendChild(th);
    });
    tHead.appendChild(tr);
    table.append(tr);

    jsonData.forEach((item) =>{
        let vals = Object.values(item);

        vals.forEach((elem) =>{
            let td = document.createElement("td");
            td.innerText = elem;
            tr.appendChild(td);
        });
        table.appendChild(tr);
    });

    return table;
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
            td.textContent = row[header];
        });
    });

    return table;
}