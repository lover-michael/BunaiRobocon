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

#define MAXDATASIZE 100

class Communicate_InterFace{
    public:
        virtual void Open() = 0;
        virtual size_t Write() const = 0;
        virtual size_t Read() = 0;
        virtual void Close() =0;
};

typedef struct{
    uint8_t command;
    std::array<uint8_t, MAXDATASIZE> data;
}CommucationData;

class Serial : public Communicate_InterFace {
    protected:
        CommucationData _data;
        std::unique_ptr<uint8_t> _fd;
        uint8_t decoi = 10;
    public:
        Serial();
        ~Serial();
        void Open(void) override;
        size_t Write(void) const override;
        size_t Read(void) override;
        void Close(void) override;
        void Debug(void);
};

