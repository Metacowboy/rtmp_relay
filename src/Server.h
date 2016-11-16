//
//  rtmp_relay
//

#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <set>
#include <memory>
#include "Acceptor.h"
#include "Receiver.h"
#include "Application.h"

namespace relay
{
    class Application;
    
    class Server
    {
    public:
        Server(cppsocket::Network& aNetwork,
               const std::string& address,
               float aPingInterval,
               const std::vector<ApplicationDescriptor>& aApplicationDescriptors);
        
        Server(const Server&) = delete;
        Server& operator=(const Server&) = delete;
        
        Server(Server&& other) = delete;
        Server& operator=(Server&& other) = delete;
        
        void update(float delta);

        bool connect(const std::string& applicationName);

        void createStream(const std::string& streamName);
        void deleteStream();
        void unpublishStream();

        void sendAudioHeader(const std::vector<uint8_t>& headerData);
        void sendVideoHeader(const std::vector<uint8_t>& headerData);
        void sendAudio(uint64_t timestamp, const std::vector<uint8_t>& audioData);
        void sendVideo(uint64_t timestamp, const std::vector<uint8_t>& videoData);
        void sendMetaData(const amf0::Node& metaData);
        void sendTextData(uint64_t timestamp, const amf0::Node& textData);

        void printInfo() const;
        void getInfo(std::string& str) const;
        
    protected:
        void handleAccept(cppsocket::Socket& clientSocket);
        
        cppsocket::Network& network;
        cppsocket::Acceptor socket;
        const float pingInterval;
        const std::vector<ApplicationDescriptor> applicationDescriptors;
        
        std::vector<std::unique_ptr<Receiver>> receivers;

        std::unique_ptr<Application> application;
    };
}
