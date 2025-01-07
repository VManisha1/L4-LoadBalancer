#include "LoadBalancer.h"

void LoadBalancer::addServer(const ServerInfo& server) {
	std::lock_guard<std::mutex> lock(mutexLock);
	Servers.push_back(server);
}

void LoadBalancer::removeServer(const std::string& serverAddress) {
	std::lock_guard<std::mutex> lock(mutexLock);
	Servers.erase(std::remove_if(
		Servers.begin(), Servers.end(),
		[&](const ServerInfo& server)
		{
			return server.getAddress() == serverAddress;
		}),
		Servers.end());
}

// returns next healthy server
ServerInfo LoadBalancer::getNextServer() {
	std::lock_guard<std::mutex> lock(mutexLock);

	if (Servers.empty()) {
		throw std::runtime_error("No server availble");
	}

	// Loop through the servers to find next healthy server
	int startIndex = currentIndex;
	do {
		ServerInfo& server = Servers[currentIndex];
		currentIndex = (currentIndex + 1) % Servers.size();
		if (server.getHealthStatus()) {
			return server;
		}
	} while (currentIndex != startIndex);

	throw std::runtime_error("No healthy server available");
}
