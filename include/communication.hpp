#pragma once

#include <iostream>
#include <memory>
#include <array>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string>
#include <functional>
#include <termios.h>

#define MAXDATASIZE 10

using test = std::function<void(void)>;

class Communicate_InterFace{
    public:
        virtual void Open() = 0;
        virtual size_t Write() const = 0;
        virtual size_t Read() = 0;
        virtual void Close() = 0;
};

typedef struct{
    int _sock;
    struct sockaddr _sockAddr;
    struct sockaddr_in from;
    socklen_t fromlen;
}UdpTable;

typedef struct{
    std::string ip;
    uint16_t port;
    UdpTable _table;
}UdpInfo;

class Serial : public Communicate_InterFace {
    protected:
        std::unique_ptr<int16_t> _fd;
        std::string _dev_name;
        uint64_t _speed;
        uint16_t max_data_size;
        void SetDev(std::unique_ptr<int16_t>);
    public:
        std::array<uint8_t, MAXDATASIZE> userdata;
        
        Serial();
        Serial(std::string dev_name, uint64_t speed, uint16_t data_size);
        ~Serial();
        virtual void Open(void) override;
        size_t Write(void) const override;
        size_t Read(void) override;
        void Close(void) override;
        // void Reconnect(std::string dev_name);
};

// class UDP : public Communicate_InterFace {
//     private:
//         std::unique_ptr<UdpInfo> _info;
//     public:
//         std::array<uint8_t, MAXDATASIZE> userdata;
//         UDP(std::string ip, uint16_t port);
//         ~UDP();
//         void Open(void) override;
//         void Open(void) override;
//         size_t Write(void) const override;
//         size_t Read(void) override;
//         void Close(void) override;
//         // void Reconnect(void);
// };

