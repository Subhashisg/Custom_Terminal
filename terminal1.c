#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <time.h>
#include "gemini.h"
#include "calculator.h"
#include "app.h"

#define MAX_HISTORY 100
#define MAX_PROCESSES 1000

// Structure to hold process details
typedef struct {
    int pid;
    char name[256];
    float cpu_usage;
    float mem_usage;
} Process;

Process processes[MAX_PROCESSES];
int processCount = 0;

// Global variables for command history
char history[MAX_HISTORY][256];
int historyCount = 0;

// Function prototypes
void printGraphics();
void printHelp();
void clearScreen();
void listFiles();
void createDirectory(const char *dirName);
void removeFile(const char *fileName);
void runProgram(const char *fileName);
void displayFileContents(const char *fileName);
void copyFile(const char *source, const char *destination);
void moveFile(const char *source, const char *destination);
void printWorkingDirectory();
void changeDirectory(const char *path);
void createFile(const char *fileName);
void showDateTime();
void addHistory(const char *command);
void printHistory();
void calculator();
void openApp(const char *appName);
void runGemini();
void openGeminiApp();
void changeToParentDirectory();
void viewProcesses();  // New function for process viewing

// Main function
int main() {
    char input[256];

    // Print CLI graphics on start
    printGraphics();
    printf("Type 'help' to see available commands.\n");

    while (1) {
        // Main prompt loop for user input
        printf("CGU> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;  // Remove trailing newline
        addHistory(input);  // Add to history

        // Command processing
        if (strcmp(input, "runGemini") == 0) {
            runGemini();  // Call the function to run Gemini
        } else if (strcmp(input, "exit") == 0) {
            printf("Exiting CGU Terminal. Goodbye!\n");
            break;  // Exit the loop
        } else if (strcmp(input, "hello") == 0) {
            printf("Hello! Welcome to CGU Terminal.\n");
        } else if (strcmp(input, "cgu") == 0) {
            printf("This is the CGU Terminal!\n");
        } else if (strcmp(input, "clear") == 0) {
            clearScreen();
        } else if (strcmp(input, "help") == 0) {
            printHelp();
        } else if (strcmp(input, "ls") == 0) {
            listFiles();
        } else if (strncmp(input, "mkdir ", 6) == 0) {
            createDirectory(input + 6); // Extract directory name from input
        } else if (strncmp(input, "rm ", 3) == 0) {
            removeFile(input + 3); // Extract file name from input
        } else if (strncmp(input, "run ", 4) == 0) {
            runProgram(input + 4); // Extract file name from input
        } else if (strncmp(input, "cat ", 4) == 0) {
            displayFileContents(input + 4); // Extract file name from input
        } else if (strncmp(input, "cp ", 3) == 0) {
            char *source = strtok(input + 3, " ");
            char *dest = strtok(NULL, " ");
            if (source && dest) {
                copyFile(source, dest);
            } else {
                printf("Usage: cp <source> <destination>\n");
            }
        } else if (strncmp(input, "mv ", 3) == 0) {
            char *source = strtok(input + 3, " ");
            char *dest = strtok(NULL, " ");
            if (source && dest) {
                moveFile(source, dest);
            } else {
                printf("Usage: mv <source> <destination>\n");
            }
        } else if (strcmp(input, "pwd") == 0) {
            printWorkingDirectory();
        } else if (strncmp(input, "cd ", 3) == 0) {
            changeDirectory(input + 3); // Extract directory path from input
        } else if (strcmp(input, "cd../") == 0) {
            changeToParentDirectory();  // Call the function for "cd../"
        } else if (strncmp(input, "touch ", 6) == 0) {
            createFile(input + 6); // Extract file name from input
        } else if (strcmp(input, "date") == 0) {
            showDateTime();
        } else if (strcmp(input, "history") == 0) {
            printHistory();
        } else if (strcmp(input, "calc") == 0) {
            calculator();
        } else if (strncmp(input, "open ", 5) == 0) {
            openApp(input + 5); // Extract app name from input
        } else if (strcmp(input, "viewProcesses") == 0) {
            viewProcesses();  // Call the function to view processes
        } else {
            printf("Unknown command. Type 'help' for a list of commands.\n");
        }
    }

    return 0;
}

// Function to print welcome graphics
void printGraphics() {
    printf("=============================================\n");
    printf("       Welcome to the CGU Custom Terminal    \n");
    printf("=============================================\n");
    printf("          Created by: Your Name Here         \n");
    printf("=============================================\n\n");
}

// Function to print the help menu
void printHelp() {
    printf("Available commands:\n");
    printf("1. hello       - Print a greeting message\n");
    printf("2. cgu         - Display terminal name\n");
    printf("3. clear       - Clear the terminal screen\n");
    printf("4. exit        - Exit the terminal\n");
    printf("5. ls          - List files in current directory\n");
    printf("6. mkdir <dir> - Create a directory\n");
    printf("7. rm <file>   - Remove a file\n");
    printf("8. run <file>  - Execute a program file\n");
    printf("9. cat <file>  - Display contents of a file\n");
    printf("10. cp <src> <dst> - Copy file\n");
    printf("11. mv <src> <dst> - Move/Rename file\n");
    printf("12. pwd        - Present working directory\n");
    printf("13. cd <dir>   - Change directory\n");
    printf("14. touch <file> - Create empty file\n");
    printf("15. date       - Show current date and time\n");
    printf("16. history    - Show command history\n");
    printf("17. calc       - Open calculator\n");
    printf("18. open <app> - Open an application\n");
    printf("19. viewProcesses - View processes in a dynamic way\n");
    printf("20. runGemini - Open Gemini\n");
    printf("21. cd../ - Change to parent directory\n");
}

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to list files in current directory
void listFiles() {
    DIR *dir;
    struct dirent *entry;

    printf("Listing files in current directory:\n");
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

// Function to create a directory
void createDirectory(const char *dirName) {
#ifdef _WIN32
    // Windows version of mkdir (only one argument)
    if (mkdir(dirName) == 0) {
        printf("Directory created: %s\n", dirName);
    } else {
        perror("Error creating directory");
    }
#else
    // Unix version of mkdir (with two arguments)
    if (mkdir(dirName, 0777) == 0) {
        printf("Directory created: %s\n", dirName);
    } else {
        perror("Error creating directory");
    }
#endif
}

// Function to run a program
void runProgram(const char *fileName) {
    if (access(fileName, F_OK) != -1) {
        printf("Running program: %s\n", fileName);
        system(fileName);
    } else {
        printf("File not found: %s\n", fileName);
    }
}

// Function to display the contents of a file
void displayFileContents(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

// Function to copy a file
void copyFile(const char *source, const char *destination) {
    FILE *src = fopen(source, "r");
    FILE *dest = fopen(destination, "w");
    if (!src || !dest) {
        perror("Error copying file");
        return;
    }
    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dest);
    }
    fclose(src);
    fclose(dest);
    printf("File copied from %s to %s\n", source, destination);
}

// Function to move a file
void moveFile(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File moved from %s to %s\n", source, destination);
    } else {
        perror("Error moving file");
    }
}

// Function to print the working directory
void printWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current directory: %s\n", cwd);
    } else {
        perror("getcwd error");
    }
}

// Function to change directory
void changeDirectory(const char *path) {
    if (chdir(path) == 0) {
        printf("Changed directory to: %s\n", path);
    } else {
        perror("Error changing directory");
    }
}

// Function to go to the parent directory
void changeToParentDirectory() {
    if (chdir("..") == 0) {
        printf("Changed to parent directory.\n");
    } else {
        perror("Error changing to parent directory");
    }
}

// Function to create an empty file
void createFile(const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file) {
        fclose(file);
        printf("File created: %s\n", fileName);
    } else {
        perror("Error creating file");
    }
}

// Function to show the current date and time
void showDateTime() {
    time_t now;
    struct tm *tm_info;
    char buffer[26];

    time(&now);
    tm_info = localtime(&now);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Current date and time: %s\n", buffer);
}

// Function to add a command to the history
void addHistory(const char *command) {
    if (historyCount < MAX_HISTORY) {
        strncpy(history[historyCount++], command, sizeof(history[historyCount]));
    } else {
        // Shift all commands up one to make room for the new one
        for (int i = 1; i < MAX_HISTORY; i++) {
            strncpy(history[i-1], history[i], sizeof(history[i-1]));
        }
        strncpy(history[MAX_HISTORY - 1], command, sizeof(history[MAX_HISTORY-1]));
    }
}

// Function to print the command history
void printHistory() {
    printf("Command History:\n");
    for (int i = 0; i < historyCount; i++) {
        printf("%d. %s\n", i+1, history[i]);
    }
}

void removeFile(const char *fileName) {
    if (remove(fileName) == 0) {
        printf("File deleted successfully: %s\n", fileName);
    } else {
        perror("Error deleting file");
    }
}

// New function to view processes
void viewProcesses() {
    DIR *dir;
    struct dirent *entry;
    char statFile[256];
    FILE *fp;
    int pid;
    char name[256];
    float cpuUsage, memUsage;
    int processCount = 0;

    printf("Process Viewer:\n");

    // Read from /proc directory to get process information
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Failed to open /proc directory");
        return;
    }

    // Loop through each directory in /proc
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {  // Check if directory name is a PID
            pid = atoi(entry->d_name);
            snprintf(statFile, sizeof(statFile), "/proc/%d/stat", pid);
            
            fp = fopen(statFile, "r");
            if (fp == NULL) {
                continue;
            }

            // Parse the stat file for process information (pid, name, cpu, mem)
            if (fscanf(fp, "%d %s", &pid, name) == 2) {
                snprintf(statFile, sizeof(statFile), "/proc/%d/stat", pid);
                FILE *fstat = fopen(statFile, "r");
                if (fstat != NULL) {
                    long utime, stime, total_time;
                    int process_id;
                    unsigned long vsize, rss;

                    fscanf(fstat, "%d %s %*c %*d %*d %*d %*d %*d %*d %*d %ld %ld %ld %ld %*d %*d %ld %ld",
                        &process_id, name, &utime, &stime, &vsize, &rss);

                    fclose(fstat);

                    // Store process details in the global array
                    processes[processCount].pid = process_id;
                    strncpy(processes[processCount].name, name, sizeof(processes[processCount].name));
                    processes[processCount].cpu_usage = utime + stime;
                    processes[processCount].mem_usage = rss;

                    processCount++;
                    if (processCount >= MAX_PROCESSES) {
                        break;
                    }
                }
            }
            fclose(fp);
        }
    }

    closedir(dir);

    // Display the collected processes
    printf("%-10s %-20s %-15s %-15s\n", "PID", "Process Name", "CPU Usage", "Memory Usage");
    for (int i = 0; i < processCount; i++) {
        printf("%-10d %-20s %-15.2f %-15.2f\n", processes[i].pid, processes[i].name,
               processes[i].cpu_usage, processes[i].mem_usage);
    }

    // Allow the user to quit the process viewer
    char quit[10];
    printf("\nType 'q' to quit process viewer or press enter to refresh: ");
    fgets(quit, sizeof(quit), stdin);
    if (quit[0] == 'q' || quit[0] == 'Q') {
        return;
    } else {
        viewProcesses();  // Refresh the process list
    }
}
