const { contextBridge, ipcRenderer } = require('electron');

contextBridge.exposeInMainWorld('backend', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySQLAPI', args);
    },
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
    SetCurrentUserID: async (newID) => {
      await ipcRenderer.invoke('SetCurrentUserID', newID);
    }
});