let openWithDevConsole = true;
let currentUserID = NaN;


//Main electron stuff for spawning window, and inter-process communication
const { app, BrowserWindow, ipcMain } = require('electron');
//Supporting functions
const MySQLAPI = require('./APICalls.js');
//Filesystem
const fs = require('fs');
//Path stuff for grabbing my preload script.
//Helps make it more explicit? Was recommended, idk why relative isn't good enough.
const path = require('path'); 

let mainWindow;

app.on('ready', ()=>{
    mainWindow = new BrowserWindow({
        width: 2000,
        height: 1000,
        //This links it to the preload file
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            enableRemoteModule: false
        },
    });

    //Load the actual window
    mainWindow.loadFile('./Pages/Login/Login.html');
    

    if(openWithDevConsole){
        BrowserWindow.getFocusedWindow().webContents.toggleDevTools();
    }


});//End app.onReady()


    //Attach event handler to client-side API call
    //SEE preload.js
    ipcMain.handle('MySQLAPI', async (event, args) => {
        try {
            const result = await MySQLAPI(args);
            //Edge case where we wrote to stderr but ExitCode was 0
            if(!result.success){
                return {success: false, output: result.api_output};
            }
            //Exit code 0
            return {success: true, output: result.api_output};
        }
        //Exit Code non-zero
        catch (error){
            return {success: false, output: error.api_output};
        }
    });

    ipcMain.handle('LoadPage', (event, htmlFile) =>{

        const currentWindow = BrowserWindow.getFocusedWindow();
        if(currentWindow){
            currentWindow.loadFile(path.join(__dirname, htmlFile));
        }
    });




    ipcMain.handle('GetCurrentUserID', () => currentUserID);
    ipcMain.handle('SetCurrentUserID', (event, newID) =>{
        if (typeof newID === 'number' && newID > 0) {
            currentUserID = newID;
        } 
        else {
            console.warn('Invalid User ID');
        }
    });


    //This is mac-specific stuff.
    //Apparenly macs don't care whether a window is open or not,
    //they'll just run a program, and this helps fix potential issues
    //with that.
app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
    }
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
    app.quit();
    }
})