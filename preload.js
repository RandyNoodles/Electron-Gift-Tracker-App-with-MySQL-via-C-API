//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
const { contextBridge, ipcRenderer } = require('electron');


let currentUserID;

//Hopefully I don't need more than this. This stuff is confusing.
contextBridge.exposeInMainWorld('backend', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySQLAPI', args);
    },
    //FOR SPA APPROACH
    LoadHTML:  (name) =>{
      return ipcRenderer.invoke('LoadHTML', name);
    },
    //FOR MPA APPROACH
    LoadPage: (htmlFile) => ipcRenderer.invoke('LoadPage', htmlFile),

    getCurrentUserID: () => currentUserID,
    setCurrentUserID: (newID) => {
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