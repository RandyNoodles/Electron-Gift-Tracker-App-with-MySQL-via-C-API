//THIS IS A WAY TO EXPOSE SERVER-SIDE STUFF TO OUR FRONTEND

const { contextBridge, ipcRenderer, contentTracing } = require('electron')

contextBridge.exposeInMainWorld('versions', {
  node: () => process.versions.node,
  chrome: () => process.versions.chrome,
  electron: () => process.versions.electron,
  ping: () => ipcRenderer.invoke('ping')
  // we can also expose variables, not just functions
})
contextBridge.exposeInMainWorld('testJSON', {
    getGifts: () => ipcRenderer.invoke('TestGiftsJSON')
})