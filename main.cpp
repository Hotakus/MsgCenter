/**
* @File main.cpp
* @Author Hotakus@foxmail.com
* @Bref 
* @Details 
* @version 
* @Date 2022/12/01
* @Copyright (c) 2022 Hotakus. All Rights Reserved.
**/

#include <iostream>
#include "MsgCenter.h"

int main (int argc, char *argv[])
{
    msgmanager::MsgCenter mc = msgmanager::MsgCenter();
    mc.msg_center_test();
    std::cout << "Hello" << std::endl;
    return 0;
}

