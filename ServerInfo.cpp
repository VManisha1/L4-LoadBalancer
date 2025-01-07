#include <string>
#include "ServerInfo.h"

std::string ServerInfo::getAddress() const {
    return ip + ":" + std::to_string(port);
}

bool ServerInfo::getHealthStatus() const {
    return isHealthy;
}

void ServerInfo::setHealthStatus(bool status) {
    isHealthy = status;
}

int ServerInfo::getPort() const {
	return port;
}
