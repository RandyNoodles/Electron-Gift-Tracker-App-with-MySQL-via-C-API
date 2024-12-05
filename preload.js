//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND
const { contextBridge, ipcRenderer } = require('electron');
const fs = require('fs');
const path = require('path');

//Hopefully I don't need more than this. This stuff is confusing.
contextBridge.exposeInMainWorld('backend', {
    CallDB: async (args) => {
      return await ipcRenderer.invoke('MySQLAPI', args);
    },
    LoadHTML: (name) =>{
      try{
        const filePath = "./HTMLSections/".concat(name);
        const fullPath = path.resolve(__dirname, filePath);
        return fs.readFileSync(fullPath, 'utf-8');
      } catch(error){
        console.log("Error reading file: ", error);
        return null;
      }
    }
});