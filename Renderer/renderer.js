//THIS IS BASICALLY OUR CLIENT-SIDE JS

window.addEventListener("load", init);

function init(){
    const information = document.getElementById('info')
    information.innerText = `This app is using Chrome (v${versions.chrome()}), Node.js (v${versions.node()}), and Electron (v${versions.electron()})`
    
    const func = async () => {
        const response = await window.versions.ping()
        console.log(response);
    }
    func();
}


