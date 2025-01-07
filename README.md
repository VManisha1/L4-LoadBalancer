# L4-Load Balancer in C++ using Boost 

An L4 load balancer operates at Layer 4 (Transport Layer) of the OSI model. 
This layer focuses on routing traffic based on transport-layer protocols like TCP (Transmission Control Protocol) and UDP (User Datagram Protocol). 
L4 load balancers direct network traffic to servers based on information from the transport layer, such as IP addresses and port numbers.

------------------------------------------
File Structure 
------------------------------------------
/load-balancer/
├── src/
│   ├── LoadBalancer.h
│   ├── LoadBalancer.cpp
│   ├── HealthChecker.h
│   ├── HealthChecker.cpp
│   ├── FrontendListener.h
│   ├── FrontendListener.cpp
│   ├── ServerInfo.h
│   ├── LoadBalancerApplication.cpp

------------------------------------------
Components
------------------------------------------
1. **LoadBalancer**
Manages a list of servers.
Distributes incoming client requests.
Performs health checks on servers.

2. **HealthChecker**
Periodically checks the health of each server.
Marks servers as healthy or unhealthy based on their responses.

3. **FrontendListener**
Listens for incoming client connections.
Forwards client requests to the load balancer.

4. **ServerInfo**
Represents a backend server with details such as IP address, port, and health status.

------------------------------------------
**Configuration**
------------------------------------------
Modify main.cpp to customize the following:
Server List: Add or remove servers with IP and port.
Health Check Interval: Adjust the interval for server health checks.

Example:
loadBalancer.addServer("127.0.0.1", 8080);
loadBalancer.addServer("127.0.0.1", 8081);
