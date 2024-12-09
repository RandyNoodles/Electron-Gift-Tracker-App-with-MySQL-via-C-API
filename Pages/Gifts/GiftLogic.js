window.addEventListener('load', init);


function init(){
    RefreshGiftTable();
}


async function RefreshGiftTable(){
    let userID = await window.backend.GetCurrentUserID();
    let args = ['100', userID];
    const tableContainer = document.getElementById('giftTableContainer');
    
    
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
    }   
}


