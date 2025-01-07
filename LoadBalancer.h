// this class manages the pool of backend servers and implements the routing algorithm

#pragma once

#include<vector>
#include<mutex>
#include"ServerInfo.h"
class LoadBalancer
{
private:
	std::vector<ServerInfo> Servers;
	int currentIndex;
	std::mutex mutexLock;

public:
	LoadBalancer() : currentIndex(0){}

	// obtain the lock on Servers list and add server
	void addServer(const ServerInfo& server);

	// obtain the lock on Servers list and remove server
	void removeServer(const std::string& serverAddress);

	std::vector<ServerInfo> getServers() {
		return Servers;
	}

	// returns next healthy server
	ServerInfo getNextServer();
};

