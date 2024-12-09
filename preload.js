//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
const { contextBridge, ipcRenderer } = require('electron');


let currentUserID;

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

    GetCurrentUserID: () => currentUserID,
    SetCurrentUserID: (newID) => {
      if(typeof newID === 'number'){
        if(newID <= 0){
          currentUserID = NaN;
        }
        else{
          currentUserID = newID;
        }
      }
      else{
        console.warn("USER ID NOT OF TYPE NUMBER");
      }
    }

});