window.addEventListener('load', init);


function init(){
    id('nav_account').addEventListener('click', LoadPage_Account);
    id('nav_gifts').addEventListener('click', LoadPage_Gifts);
    id('nav_events').addEventListener('click', LoadPage_Events);
    id('nav_recipients').addEventListener('click', LoadPage_Recipients);

}

async function LoadPage_Account(event){
    await window.backend.LoadPage('/Pages/Account/Account.html');
}
async function LoadPage_Gifts(event){
    await window.backend.LoadPage('/Pages/Gifts/Gifts.html');
}
async function LoadPage_Events(event){
    await window.backend.LoadPage('/Pages/Events/Event.html');
}
async function LoadPage_Recipients(event){
    await window.backend.LoadPage('/Pages/Recipients/Recipients.html');
}