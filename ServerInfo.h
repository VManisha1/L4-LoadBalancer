// Provides basic server details like port number and health status

#pragma once

#include <string>

class ServerInfo
{
private:
	int port;
	std::string ip;
	bool isHealthy;

public:
	ServerInfo(const std::string& ipAddress, int portAddress) : ip(ipAddress), port(portAddress), isHealthy(true)
	{
	}

	std::string getAddress() const;

	bool getHealthStatus() const;

	void setHealthStatus(bool healthStatus);

	int getPort() const;
};

