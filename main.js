//THIS IS BASICALLY SERVER-SIDE CODE

//Load app & BrowserWindow modules
import { app, BrowserWindow, ipcMain } from 'electron/main';
//Load path module to concatenate paths later
import path from 'path';
import { fileURLToPath } from 'url';
//Workaround for ES modules
const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);

import { GiftList } from './MainScripts/testJSON.js';
import { MySQLAPI } from './MainScripts/APICalls.js';



let mainWindow;

app.on('ready', ()=>{
    mainWindow = new BrowserWindow({
        //This links it to the preload file
        webPreferences: {
            preload: path.join(__dirname, 'preload.js'),
            contextIsolation: true,
            enableRemoteModule: false,
            nodeIntegration: false,
        },
    });

    //Load the actual window
    mainWindow.loadFile('index.html');

    //Attach event handlers to server-side functions here
    ipcMain.handle('TestGiftsJSON', () => GiftList());
})



    //This is mac-specific stuff.
    //Apparenly macs don't care whether a window is open or not,
    //they'll just run a program, and this helps fix potential issues
    //with that.
app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
        createWindow()
    }
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
    app.quit()
    }
});