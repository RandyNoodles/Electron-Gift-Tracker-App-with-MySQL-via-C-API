window.addEventListener('load', init);

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


