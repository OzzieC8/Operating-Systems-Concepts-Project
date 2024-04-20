#include <iostream>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    while (true) {
        std::string input;
        
        // Print the prompt
        std::cout << "cmd> ";
        std::getline(std::cin, input);
        
        // Exit the shell on 'exit' command
        if (input == "exit") {
            std::cout << "Exiting the shell." << std::endl;
            break;
        }

        // Tokenize the input into command and arguments
        std::istringstream iss(input);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) {
            tokens.push_back(token);
        }

        // Prepare arguments for execvp
        std::vector<char*> args;
        for (auto& t : tokens) {
            args.push_back(&t[0]); // Address of the first character of the string
        }
        args.push_back(nullptr); // execvp expects a NULL at the end of args array

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            // Fork failed
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            // Child process
            // Executing the command
            execvp(args[0], args.data());

            // execvp only returns if there is an error
            perror("execvp");
            exit(EXIT_FAILURE);
        }
        else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);  // Wait for the child to complete

            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                std::cout << "Process exited with status: " << exit_status << std::endl;
            }
        }
    }

    return 0;
}
