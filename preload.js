//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
import { contextBridge, ipcRenderer } from 'electron';

//Hopefully I don't need more than this. This stuff is confusing.
contextBridge.exposeInMainWorld('db', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySqlAPI', args);
    }
});