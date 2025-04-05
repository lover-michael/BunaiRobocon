#include "communication.hpp"

Serial::Serial()
{

}

Serial::~Serial()
{

}

void Serial::Open() {
    return;
}

void Serial::Close() {
    return;
}

size_t Serial::Write() const {
    return 1;
}

size_t Serial::Read() {
    return 1;
}

void Serial::Debug() {
    std::cout << std::to_string(this->decoi) << std::endl;
}