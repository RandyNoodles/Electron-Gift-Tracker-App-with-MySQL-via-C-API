//ONE OF THE SOLUTIONS TO ADD EVENT LISTENERS TO OUR DYNAMIC SECTIONS



window.addEventListener("load", init);

function init(){
    document.getElementById('dynamicSection').addEventListener('click', dynamicClickListener);
}


function dynamicClickListener(event){

    switch(event.target.id){
       //BIGASS SWITCH STATEMENT FOR ALL EVENT LISTENERS
    }
}
