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
    window.backend.LoadPage('/HTMLSections/Gifts.html');
}