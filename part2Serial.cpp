#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

int main() {
    std::ifstream inFile("locations.txt");
    std::string line;
    int fileCounter = 1;  // Counter for file naming

    if (!inFile) {
        std::cerr << "Unable to open locations file." << std::endl;
        return 1;
    }

    while (getline(inFile, line)) {
        std::istringstream iss(line);
        double latitude, longitude;
        if (!(iss >> latitude >> longitude)) {
            continue;  // Skip malformed lines
        }

        // Format the filename and curl command
        std::string filename = "serial_file" + std::to_string(fileCounter++) + ".json";
        std::string command = "/usr/bin/curl -o " + filename + 
                              " \"https://api.open-meteo.com/v1/forecast?latitude=" +
                              std::to_string(latitude) + "&longitude=" +
                              std::to_string(longitude) + "&current_weather=True\"";

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }
        else if (pid == 0) { // Child process
            std::cout << "Child PID: " << getpid() << " Parent PID: " << getppid() << std::endl;
            std::cout << "UID: " << getuid() << " GID: " << getgid() << std::endl;

            // Execute curl command
            execl("/bin/sh", "sh", "-c", command.c_str(), (char *) NULL);
            perror("execl");
            exit(1);
        }
        else { // Parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child to complete

            if (WIFEXITED(status)) {
                std::cout << "Child " << pid << " finished with status: " << WEXITSTATUS(status) << std::endl;
            }
        }
    }

    inFile.close();
    return 0;
}
