//This class periodically checks the health of backend servers.

#pragma once

#include <iostream>
#include <sstream>
#include"LoadBalancer.h"

class HealthChecker
{
private:
	LoadBalancer &lb;

	void checkServerHealth(ServerInfo& server) {
		std::ostringstream command;

		command << "ping -n 1 " << server.getAddress();

		// Execute the command and get the return status
		int returnCode = system(command.str().c_str());

		// Check the status (0 indicates success, non-zero indicates failure)
		server.setHealthStatus(returnCode == 0); // Replace with actual health check logic
	}

public:
	HealthChecker(LoadBalancer& loadBalancer) : lb(loadBalancer) {}

	// start health check for all the servers with interval time 
	void start(int intervalMs);
};

