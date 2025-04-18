const { app, BrowserWindow, ipcMain } = require('electron');
const path = require('path');
const { exec } = require('child_process'); // For executing batch file

function createWindow() {
    const win = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true, // Enable nodeIntegration
            contextIsolation: false, // Disable context isolation (if you're not using preload)
            preload: path.join(__dirname, 'preload.js') // Use if you have a preload.js
        }
    });

    win.loadFile('index.html');
}

app.whenReady().then(() => {
    createWindow();

    // Handle the open-terminal event
    ipcMain.on('open-terminal', (event) => {
        const batchFilePath = 'C:/Users/DELL/OneDrive/Desktop/os_case_study/terminal.bat';
        exec(batchFilePath, (error, stdout, stderr) => {
            if (error) {
                console.error(`exec error: ${error}`);
                return;
            }
            console.log(`stdout: ${stdout}`);
            console.error(`stderr: ${stderr}`);
        });
    });
});

app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});
