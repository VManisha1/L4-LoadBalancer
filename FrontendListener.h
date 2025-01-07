#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/address.hpp>
#include "LoadBalancer.h"
#include <iostream>

class FrontendListener
{
private:
    boost::asio::io_context ioContext;
    boost::asio::ip::tcp::acceptor acceptor;
    LoadBalancer& loadBalancer; // Reference to the load balancer

    void acceptConnections() {
        // create socket for incoming connection
        auto socket = std::make_shared<boost::asio::ip::tcp::socket>(ioContext);

        acceptor.async_accept(*socket, [this, socket](const boost::system::error_code& error) {
            if (!error) {
                std::cout << "New client connected";
            }
            else {
                std::cerr << "Accept error: "<<error.message()<< std::endl;
            }
        });

        // Continue accepting new connections
        //acceptConnections();
    }

    void handleClient(std::shared_ptr<boost::asio::ip::tcp::socket> socket) {
        try {
            // Read client request
            boost::asio::streambuf requestBuffer;
            boost::asio::read_until(*socket, requestBuffer, "\n");
            std::istream requestStream(&requestBuffer);
            std::string clientRequest;
            std::getline(requestStream,clientRequest);

            std::cout << "Recieved request: " <<clientRequest<< std::endl;

            // Route request to backend server
            ServerInfo server = loadBalancer.getNextServer();
            std::string response = forwardRequestToServer(server, clientRequest);

            // send response back to client
            boost::asio::write(*socket, boost::asio::buffer(response));
        }
        catch (const std::exception& ex) {
            std::cerr << "Client handling error: " << ex.what() << std::endl;
        }
    }

    std::string forwardRequestToServer(const ServerInfo& server, const std::string& request) {
        try {
            boost::asio::ip::tcp::socket backendSocket(ioContext);
            backendSocket.connect(boost::asio::ip::tcp::endpoint(
                boost::asio::ip::make_address(server.getAddress()),server.getPort()));
             
            // Send the request to the backend server
            boost::asio::write(backendSocket, boost::asio::buffer(request + "\n"));

            // Read the response from the backend server
            boost::asio::streambuf responseBuffer;
            boost::asio::read_until(backendSocket, responseBuffer, "\n");

            std::istream responseStream(&responseBuffer);
            std::string backendResponse;
            std::getline(responseStream, backendResponse);

            return backendResponse;
        }
        catch (std::exception ex) {
            std::cerr << "Forward Request to server error: " << ex.what() << std::endl;
        }
    }

public:
    FrontendListener(LoadBalancer& lb, int port): loadBalancer(lb),
        acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}
    
    void start();
};

