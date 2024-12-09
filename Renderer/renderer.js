//THIS IS BASICALLY OUR CLIENT-SIDE JS

window.addEventListener("load", init);

function init(){
    id('nav_Account').addEventListener('click', LoadPage_Account);
    id('nav_Events').addEventListener('click', LoadPage_Events);
    id('nav_LovedOnes').addEventListener('click', LoadPage_LovedOnes);
    id('nav_Gifts').addEventListener('click', LoadPage_Gifts);
}

function LoadPage_Account(event){

}
function LoadPage_Events(event){

}
function LoadPage_LovedOnes(event){

}
function LoadPage_Gifts(event){

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
