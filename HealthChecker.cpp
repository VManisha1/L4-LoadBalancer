#include "HealthChecker.h"

void HealthChecker::start(int intervalMs) {
	std::thread([this, intervalMs]() {
		while (true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(intervalMs));
		
			try {
				for (ServerInfo& server : lb.getServers()) {
					checkServerHealth(server);
				}
			}
			catch (std::runtime_error er) {
				std::cerr << "Health check error: " << er.what() << std::endl;
			}
		}
	}).detach();;
}