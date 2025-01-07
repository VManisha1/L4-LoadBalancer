#include <iostream>
#include <fstream>
#include "FrontendListener.h"
#include "HealthChecker.h"

void parseServerConfig(const std::string& serverConfigFile, LoadBalancer& lb) {
    std::ifstream file(serverConfigFile);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open server config file");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string address;
        int port;
        if (iss >> address >> port) {
            lb.addServer(ServerInfo(address, port));
        }
        else {
            std::cerr << "Invalid server configuration line " << line << std::endl;
        }
    }
    file.close();
}

int main(int argc, char* argv[]) { 
    try {
        // Default configuration values
        int port = 8080;                  // Port for frontend listener
        int healthCheckInterval = 5000;  // Health check interval in milliseconds
        std::string configFile = "D:\\Manisha\\C++ projects\\Manisha_CPP_Proj\\servers.config";

        // Parse command-line arguments
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "--port" && i + 1 < argc) {
                port = std::stoi(argv[++i]);
            }
            else if (arg == "--health-interval" && i + 1 < argc) {
                healthCheckInterval = std::stoi(argv[++i]);
            }
            else if (arg == "--config" && i + 1 < argc) {
                configFile = argv[++i];
            }
            else {
                std::cerr << "Unknown argument: " << arg << std::endl;
                return 1;
            }
        }

        // Initialize the Load Balancer
        LoadBalancer lb;

        // Load server configurations
        parseServerConfig(configFile, lb);

        // Start the health check thread
        HealthChecker healthChecker(lb);
        std::thread healthThread([&healthChecker, healthCheckInterval]() {
            healthChecker.start(healthCheckInterval);
            });

        // Start the Frontend Listener
        FrontendListener listener(lb, port);
        std::cout << "Starting Frontend Listener on port " << port << "..." << std::endl;
        listener.start();

        // Join threads
        healthThread.join();
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
