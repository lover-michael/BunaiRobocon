#include "communication.hpp"

Serial::Serial() {
    _fd = std::make_unique<int16_t>(int(0));
}

Serial::Serial(std::string dev_name, uint64_t speed, uint16_t data_size)
 : _dev_name(dev_name), _speed(speed)
{
    this->userdata = {0};

    if(data_size > MAXDATASIZE)
        this->max_data_size =  MAXDATASIZE;
    else
        this->max_data_size = data_size;
}

Serial::~Serial()
{
    std::cout << "disposed of this instance" << std::endl;
}

void Serial::Open() {
    //シリアルポートの開放
    int16_t serial_num = open(this->_dev_name.c_str(), this->_speed);
    
    if(serial_num < 0)
    {
        perror("REASON: Open Error On Serial");
        std::terminate();       //異常終了
    }

    std::unique_ptr<int16_t> dummy(&serial_num);

    this->_fd = std::move(dummy);

    struct termios _tio = {};

    /*ボーレートの設定(入力 = 出力)*/
    _tio.c_cflag |= CREAD;  // 受信有効
    _tio.c_cflag |= CLOCAL; // ローカルライン
    _tio.c_cflag |= CS8;    // データビット:8bit

    cfsetispeed(&_tio, this->_speed);
    cfsetospeed(&_tio, this->_speed);

    cfmakeraw(&_tio); // RAWモード

    tcsetattr(*this->_fd, TCSANOW, &_tio); // デバイス設定      

    ioctl(*this->_fd, TCSETS, &_tio); // ポート設定の有効化

    u_long val = 1;
    ioctl(*this->_fd, FIONBIO, &val); // 非同期化

    return;
}

void Serial::Close() {
    close(*this->_fd);
}

size_t Serial::Write() const {
    return write(*this->_fd, this->userdata.begin(), this->max_data_size);
}

size_t Serial::Read() {
    return read(*this->_fd, this->userdata.begin(), this->max_data_size);
}

void Serial::SetDev(std::unique_ptr<int16_t> dev)
{
    this->_fd = std::move(dev);
}