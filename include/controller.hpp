#pragma once

#include "communication.hpp"
#include <linux/joystick.h>
#include "buttonmap.hpp"

#define X       0
#define Y       1
#define LEFT    0
#define RIGHT   1

typedef struct{
    std::array<bool, 20>button;
    std::array<int16_t, 2>left_stick;
    std::array<int16_t, 2>right_stick;
    std::array<int16_t, 2>trigger_value;
}ControllerData;

class Controller : public Serial{
    public:
        ControllerData controllerdata;

        Controller(std::string dev_name, uint16_t data_size);
        ~Controller();
        void Open(void) override;
        void DecodeRawdataToUserdata(void);
};