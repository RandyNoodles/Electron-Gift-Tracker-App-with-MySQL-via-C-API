window.addEventListener('load', init);

function init(){
    id('signout').addEventListener('click', SignOut);
}


async function SignOut(event){
    window.backend.SetCurrentUserID(NaN);
    await window.backend.LoadPage('/Pages/Login/Login.html');
}