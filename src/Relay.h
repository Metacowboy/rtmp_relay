//
//  rtmp_relay
//

#pragma once

#include <vector>
#include <memory>
#include "Network.h"
#include "Socket.h"

namespace relay
{
    class Server;
    class Status;

    class Relay
    {
    public:
        Relay(cppsocket::Network& aNetwork);
        ~Relay();
        
        Relay(const Relay&) = delete;
        Relay& operator=(const Relay&) = delete;
        
        Relay(Relay&&);
        Relay& operator=(Relay&&);
        
        bool init(const std::string& config);
        
        void run();

        void printInfo() const;
        
    private:
        cppsocket::Network& network;
        std::vector<std::unique_ptr<Server>> servers;
        std::unique_ptr<Status> status;
        std::chrono::steady_clock::time_point previousTime;
    };
}
