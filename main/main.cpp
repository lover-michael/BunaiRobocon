#include <iostream>
#include "controller.hpp"
#include "communication.hpp"
#include <iomanip>

int main()
{
    auto ins_1 = Serial {
        "/dev/ttyUSB0",     //デバイス名
        B115200,            //通信スピード
        30                  //通信パケット量
    };
    auto ins_2 = Controller {
        "/dev/input/js0",   //デバイス名
        8                   //通信パケット量
    };

    ins_1.Open();
    ins_2.Open();

    while(1) {

        auto count = ins_2.Read();

        ins_2.DecodeRawdataToUserdata();

        for(auto && it : ins_2.controllerdata.right_stick)
        {
            std::cout << std::setw(7) << std::to_string(it);
        }

        std::cout << std::endl;

        ins_1.Write();
    }

    return 0;
}