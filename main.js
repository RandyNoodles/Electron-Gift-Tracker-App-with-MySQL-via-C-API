//THIS IS BASICALLY SERVER-SIDE CODE

//Load app & BrowserWindow modules
const { app, BrowserWindow, ipcMain } = require('electron/main');
//Load path module to concatenate paths later
const path = require('node:path');

//Create window, apply any config here
const createWindow = () => {
    const win = new BrowserWindow({
      width: 800,
      height: 600,
      //Link the preload script to this window
      webPreferences:{
        preload: path.join(__dirname, 'preload.js')
      }
    })
  
    win.loadFile('index.html')
  }


  //When ready, load up the window
  app.whenReady().then(() => {
    ipcMain.handle('ping', () => 'pong');
    createWindow()


    //This is mac-specific stuff.
    //Apparenly macs don't care whether a window is open or not,
    //they'll just run a program, and this helps fix potential issues
    //with that.
    app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
          createWindow()
        }
      })
    })
    
    app.on('window-all-closed', () => {
      if (process.platform !== 'darwin') {
        app.quit()
      }
  })