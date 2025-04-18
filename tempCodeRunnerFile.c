#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>


#define MAX_HISTORY 100

#ifdef _WIN32
    #include <windows.h> // For ShellExecute and SW_SHOWNORMAL
#elif __APPLE__
    #include <string.h>
#endif


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

// Main Function
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
    printf("12. pwd        - Print working directory\n");
    printf("13. cd <dir>   - Change directory\n");
    printf("14. touch <file> - Create empty file\n");
    printf("15. date       - Show current date and time\n");
    printf("16. history    - Show command history\n");
    printf("17. calc       - Open calculator\n");
    printf("18. open <app> - Open an application\n");
    printf("19. runGemini - open gemini\n");
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
    FILE *srcFile = fopen(source, "r");
    if (srcFile == NULL) {
        perror("Error opening source file");
        return;
    }
    FILE *destFile = fopen(destination, "w");
    if (destFile == NULL) {
        perror("Error creating destination file");
        fclose(srcFile);
        return;
    }

    char buffer[1024];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        fwrite(buffer, 1, bytes, destFile);
    }

    printf("File copied from %s to %s\n", source, destination);
    fclose(srcFile);
    fclose(destFile);
}

// Function to move/rename a file
void moveFile(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File moved/renamed from %s to %s\n", source, destination);
    } else {
        perror("Error moving file");
    }
}

// Function to print working directory
void printWorkingDirectory() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd");
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

// Function to create a file
void createFile(const char *fileName) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        perror("Error creating file");
    } else {
        printf("File created: %s\n", fileName);
        fclose(file);
    }
}

//date and time function
void showDateTime() {
    time_t t;
    struct tm *tm_info;

    // Get current time
    time(&t);
    tm_info = localtime(&t);

    // Print current time
    printf("Current time: %02d:%02d:%02d\n",
           tm_info->tm_hour, tm_info->tm_min, tm_info->tm_sec);

    // Print monthly calendar
    printf("\nMonthly calendar for %02d/%04d:\n\n", tm_info->tm_mon + 1, tm_info->tm_year + 1900);
    
    // Days of the week header
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    // Get the first day of the month and the number of days in the month
    int firstDay = tm_info->tm_wday;
    int daysInMonth = 31;

    // Array with number of days in each month (index 0 = January)
    int daysInMonthArray[] = {31, (tm_info->tm_year % 4 == 0 && (tm_info->tm_year % 100 != 0 || tm_info->tm_year % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Get the correct number of days for the current month
    daysInMonth = daysInMonthArray[tm_info->tm_mon];

    // Print leading spaces for the first day
    for (int i = 0; i < firstDay; i++) {
        printf("     ");
    }

    // Print the days of the month
    int day = 1;
    for (int i = firstDay; i < 7; i++) {
        printf(" %3d ", day++);
    }
    printf("\n");

    while (day <= daysInMonth) {
        for (int i = 0; i < 7 && day <= daysInMonth; i++) {
            printf(" %3d ", day++);
        }
        printf("\n");
    }
}


// Function to add command to history
void addHistory(const char *command) {
    if (historyCount < MAX_HISTORY) {
        strcpy(history[historyCount], command);
        historyCount++;
    } else {
        for (int i = 1; i < MAX_HISTORY; i++) {
            strcpy(history[i - 1], history[i]);
        }
        strcpy(history[MAX_HISTORY - 1], command);
    }
}

// Function to print command history
void printHistory() {
    printf("Command history:\n");
    for (int i = 0; i < historyCount; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

// Function to run calculator
void calculator() {
    int num1, num2;
    char operator;
    printf("Enter equation (e.g. 3 + 4): ");
    scanf("%d %c %d", &num1, &operator, &num2);
    switch (operator) {
        case '+': printf("Result: %d\n", num1 + num2); break;
        case '-': printf("Result: %d\n", num1 - num2); break;
        case '*': printf("Result: %d\n", num1 * num2); break;
        case '/': 
            if (num2 != 0) {
                printf("Result: %d\n", num1 / num2);
            } else {
                printf("Error: Division by zero\n");
            }
            break;
        default: printf("Invalid operator\n");
    }
}

// Function to open an app
void openApp(const char *appName) {
    if (strcmp(appName, "camera") == 0) {
#ifdef _WIN32
        ShellExecute(0, "open", "microsoft.windows.camera:", 0, 0, SW_SHOWNORMAL);
#elif __APPLE__
        system("open -a \"Photo Booth\"");
#else
        system("cheese &"); // Common Linux camera app
#endif
        return;
    }
    
    else if (strcmp(appName, "notepad") == 0) {
#ifdef _WIN32
        system("notepad");
#elif __APPLE__
        system("open -a \"TextEdit\"");
#else
        system("gedit &"); // Common Linux text editor
#endif
        return;
    }

    else if (strcmp(appName, "calculator") == 0) {
#ifdef _WIN32
        system("calc");
#elif __APPLE__
        system("open -a \"Calculator\"");
#else
        system("gnome-calculator &"); // Common Linux calculator app
#endif
        return;
    }

    else if (strcmp(appName, "browser") == 0) {
#ifdef _WIN32
        ShellExecute(0, "open", "https://www.google.com", 0, 0, SW_SHOWNORMAL);
#elif __APPLE__
        system("open -a \"Safari\" https://www.google.com");
#else
        system("xdg-open https://www.google.com &"); // Opens default browser in Linux
#endif
        return;
    }

    else if (strcmp(appName, "explorer") == 0 || strcmp(appName, "file explorer") == 0) {
#ifdef _WIN32
        system("explorer");
#elif __APPLE__
        system("open ."); // Opens Finder in current directory
#else
        system("xdg-open . &"); // Opens default file manager in Linux
#endif
        return;
    }

    // If no special case, attempt to open the app with its name as a general command
#ifdef _WIN32
    if ((int)ShellExecute(0, "open", appName, 0, 0, SW_SHOWNORMAL) <= 32) {
        printf("Failed to open the app. Please check the app name or path.\n");
    }
#elif __APPLE__
    char command[512];
    snprintf(command, sizeof(command), "open -a \"%s\"", appName);
    if (system(command) != 0) {
        printf("Failed to open the app. Please check the app name or path.\n");
    }
#else
    char command[512];
    snprintf(command, sizeof(command), "%s &", appName); // For Linux
    if (system(command) != 0) {
        printf("Failed to open the app. Please check the app name or path.\n");
    }
#endif
}





void removeFile(const char *fileName) {
    if (remove(fileName) == 0) {
        printf("File deleted successfully: %s\n", fileName);
    } else {
        perror("Error deleting file");
    }
}


void runGemini() {
    char question[256];
    
    // Ask user for a question
    printf("Please enter a question for Gemini: ");
    fgets(question, sizeof(question), stdin);
    
    // Remove the newline character from the input if it exists
    question[strcspn(question, "\n")] = 0;

    // Prepare the command to run the Python script with the question argument
    char command[512];
    snprintf(command, sizeof(command), "python -u \"c:\\Users\\DELL\\OneDrive\\Desktop\\os_case_study\\google_gemini.py\" \"%s\"", question);

    // Execute the Python script with the question as argument
    system(command);
}
