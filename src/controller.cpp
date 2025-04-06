#include "controller.hpp"

Controller::Controller(std::string dev_name, uint16_t data_size)
{
    this->_dev_name = dev_name;
    this->controllerdata = {
        {false},        //buttonデータ
        {0},            //左スティック
        {0},            //右スティック
        {0}             //ｔｒｉｇｇｅｒ
    };
    this->userdata = {0};
    this->max_data_size = data_size;
}

Controller::~Controller()
{

}

void Controller::Open(void)
{
    //ユニークポインタの不便なところ
    //値渡しであってもポインタ同士で書かなければいけない(いいやり方を誰か教えてください)
    this->_fd = std::make_unique<int16_t>(open(this->_dev_name.c_str(), O_RDONLY));
    
    if(*this->_fd < 0)
    {
        perror("REASON: Open Error On Controller");
        std::terminate();
    }

    int *axis=NULL, num_of_axis=0, num_of_buttons=0, x;
	char *button=NULL, name_of_joystick[80];

    ioctl( *this->_fd, JSIOCGAXES, &num_of_axis );
	ioctl( *this->_fd, JSIOCGBUTTONS, &num_of_buttons );
	ioctl( *this->_fd, JSIOCGNAME(80), &name_of_joystick );
    
    fcntl( *this->_fd, F_SETFL, O_NONBLOCK );	/* use non-blocking mode */
    
    std::cout << std::to_string(*this->_fd) << std::endl;

    //ユニークポインタの仕様なのか、派生クラスでオーバーライドした関数内でアクセスしたポインタと、基底クラス側の
    //メソッドからアクセスしたポインタに整合性が消えてる。どうして？
    this->SetDev(std::move(this->_fd));
 
    return;
}

#define ARROWCLEAR(x) this->controllerdata.button[x] = false;

void Controller::DecodeRawdataToUserdata() 
{
    auto it = this->userdata.begin();
    auto value = *(it + 4) << 8 | *(it + 5);
    auto key_map = *(it + 7);

    switch( *(it + 6) )
    {
        case 1:
        {
            if(key_map != 6 && key_map != 7)
                this->controllerdata.button[key_map] = value > 0 ? true : false;
        }break;

        case 2:
        {
            switch(key_map)
            {
                case 0:
                case 1:
                {
                    this->controllerdata.left_stick[key_map] = static_cast<int16_t>(value) / 0x81;
                }break;
                
                case 3:
                case 4:
                {
                    this->controllerdata.right_stick[key_map - 3] = static_cast<int16_t>(value) / 0x81;
                }break;

                case 2:
                {
                    this->controllerdata.trigger_value[LEFT] = value;
                }break;
                case 5:
                {
                    this->controllerdata.trigger_value[RIGHT] = value;
                }break;

                case 6:
                case 7:
                {
                    ARROWCLEAR(14);
                    ARROWCLEAR(7);
                    ARROWCLEAR(13);
                    ARROWCLEAR(6);

                    if(value < 0xff00 && value > 0) {
                        this->controllerdata.button[key_map + 7] = true;
                    }
                    else if(value > 0xff00) {
                        this->controllerdata.button[key_map] = true;
                    }
                }
            }
        }break;
    }
}