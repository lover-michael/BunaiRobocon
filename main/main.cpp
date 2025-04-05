#include <iostream>
#include "controller.hpp"
#include "communication.hpp"

int main()
{
    std::cout << "Hello World" << std::endl;

    auto ins_1 = Serial{};
    auto ins_2 = Controller{};

    return 0;
}