//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
const { contextBridge, ipcRenderer } = require('electron');

//Hopefully I don't need more than this. This stuff is confusing.
contextBridge.exposeInMainWorld('db', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySQLAPI', args);
    }
});