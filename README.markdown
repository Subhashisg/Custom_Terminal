# 🌟 CGU Custom Terminal

Welcome to the **CGU Custom Terminal**, a beautifully crafted command-line interface (CLI) designed as part of an operating systems case study. This project blends the power of a **C-based terminal backend**, an **Electron-powered GUI** for seamless launching, and a **Tkinter-based Python process viewer** to monitor system resources. Whether you're navigating directories, managing files, launching apps, or exploring system processes, CGU Terminal offers a robust and intuitive experience.

---

## ✨ Features

- **Command-Line Interface (CLI)**:
  - **File & Directory Management**: `ls`, `mkdir`, `rm`, `cat`, `cp`, `mv`, `touch`, `pwd`, `cd`, `cd../`
  - **System Utilities**: `date` (with calendar view), `history`, `calc` (basic arithmetic)
  - **App Launching**: `open <app>` (e.g., notepad, calculator, browser, camera)
  - **Gemini Integration**: `runGemini` to interact with an external Gemini script
  - **Process Monitoring**: `VP` (Windows) for GUI-based process viewing, `viewProcesses` (Unix-like, experimental)

- **Electron GUI**:
  - A sleek interface with a double-clickable terminal logo to launch the CLI.

- **Process Viewer**:
  - A dynamic Tkinter GUI displaying real-time CPU, memory, and swap usage, alongside a detailed list of running processes (PID, Name, User, Memory).

---

## 🚀 Getting Started

### Prerequisites
- **Node.js** and **Electron** for the GUI.
- **C Compiler** (e.g., GCC) for compiling the terminal backend.
- **Python 3** with `psutil` and `tkinter` for the process viewer.
- **Windows** environment (some features, like `VP`, are Windows-specific).
- Missing dependencies (not included in this repo):
  - `google_gemini.py` (for `runGemini`).
  - Header files: `gemini.h`, `calculator.h`, `app.h` (for `terminal1.c`).

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/<your-username>/CGU-Custom-Terminal.git
   cd CGU-Custom-Terminal
   ```

2. Install Node.js dependencies:
   ```bash
   npm install electron
   ```

3. Compile the C terminal:
   ```bash
   gcc src/terminal/terminal.c -o terminal.exe
   ```

4. Install Python dependencies:
   ```bash
   pip install psutil
   ```

5. Update hardcoded paths in `main.js`, `terminal.bat`, and `terminal.c` to match your local environment (e.g., replace `C:/Users/DELL/OneDrive/Desktop/os_case_study/` with relative paths).

### Usage
1. Launch the Electron app:
   ```bash
   npm start
   ```

2. Double-click the terminal logo in the GUI to open the CGU Terminal via `terminal.bat`.

3. Explore the CLI with commands like:
   ```bash
   ls
   mkdir my_folder
   open notepad
   VP
   ```

4. Run the process viewer directly:
   ```bash
   python src/process-viewer/vp.py
   ```

---

## 📜 Available Commands

| Command              | Description                              |
|----------------------|------------------------------------------|
| `hello`              | Print a friendly greeting                |
| `cgu`                | Display the terminal's name              |
| `clear`              | Clear the terminal screen                |
| `exit`               | Exit the terminal                        |
| `ls`                 | List files in the current directory      |
| `mkdir <dir>`        | Create a new directory                   |
| `rm <file>`          | Delete a file                            |
| `run <file>`         | Execute a program                        |
| `cat <file>`         | Display file contents                    |
| `cp <src> <dst>`     | Copy a file                              |
| `mv <src> <dst>`     | Move or rename a file                    |
| `pwd`                | Show the current working directory       |
| `cd <dir>`           | Change to a specified directory          |
| `cd../`              | Move to the parent directory             |
| `touch <file>`       | Create an empty file                     |
| `date`               | Display the current date, time, and calendar |
| `history`            | View command history                     |
| `calc`               | Perform basic arithmetic calculations    |
| `open <app>`         | Launch an application (e.g., notepad, browser) |
| `runGemini`          | Run the Gemini script (requires `google_gemini.py`) |
| `VP`                 | View processes with a GUI (Windows only, `terminal.c`) |
| `viewProcesses`      | View processes dynamically (Unix-like, experimental, `terminal1.c`) |

---

## 🛠️ Project Structure

```
CGU-Custom-Terminal/
├── src/
│   ├── electron/        # Electron GUI files
│   │   ├── main.js
│   │   ├── index.html
│   │   └── terminal.bat
│   ├── terminal/       # C-based CLI backend
│   │   ├── terminal.c
│   │   ├── terminal1.c
│   │   └── tempCodeRunnerFile.c
│   ├── process-viewer/ # Python process viewer
│   │   ├── vp.py
│   │   └── tempCodeRunnerFile.py
│   └── assets/         # Static assets
│       ├── os.css
│       └── img/os2.jpg
├── README.md
├── package.json
└── .gitignore
```

---

## ⚠️ Important Notes

- **Security Warning**: Do not upload `api.py` to a public repository, as it contains sensitive API keys. Use environment variables instead.
- **Hardcoded Paths**: Update paths in `main.js`, `terminal.bat`, and `terminal.c` for portability.
- **Missing Files**: `google_gemini.py`, `gemini.h`, `calculator.h`, and `app.h` are referenced but not included. Ensure they are available for full functionality.
- **Platform Compatibility**: The `viewProcesses` command in `terminal1.c` is Unix-specific and may not work on Windows. Use `VP` in `terminal.c` for Windows.
- **Cleanup**: Exclude `tempCodeRunnerFile.js` from the repository, as it appears incomplete.

---

## 🤝 Contributing

We welcome contributions to enhance the CGU Custom Terminal! To contribute:
1. Fork the repository.
2. Create a feature branch (`git checkout -b feature/my-feature`).
3. Commit your changes (`git commit -m "Add my feature"`).
4. Push to the branch (`git push origin feature/my-feature`).
5. Open a pull request.

Please test changes on a Windows environment, as some features are platform-specific.

---

## 📜 License

This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.

---

## 🙏 Acknowledgments

- **Guidance**: Dr. Ram Chandra Barik
- **Purpose**: Developed as part of an operating systems case study
- **Inspiration**: A passion for building intuitive and powerful CLI tools

---

Thank you for exploring the **CGU Custom Terminal**! We hope you enjoy using this project as much as we enjoyed building it. For questions or feedback, please open an issue on GitHub.

Happy coding! 🚀