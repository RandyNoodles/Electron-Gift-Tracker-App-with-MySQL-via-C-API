//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
const { contextBridge, ipcRenderer } = require('electron');


var currentUserID;

//Hopefully I don't need more than this. This stuff is confusing.
contextBridge.exposeInMainWorld('backend', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySQLAPI', args);
    },
    //FOR MPA APPROACH
    LoadPage: async (name) => {
      try {
        return await ipcRenderer.invoke('LoadPage', name);
      } catch (error) {
        console.error('Failed to load HTML:', error);
      }
    },
    GetCurrentUserID: async () => {
      return await ipcRenderer.invoke('GetCurrentUserID');
    },
  
    // Asynchronous setter for currentUserID
    SetCurrentUserID: async (newID) => {
      await ipcRenderer.invoke('SetCurrentUserID', newID);
      
    }
});