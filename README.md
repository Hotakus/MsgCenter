# MsgCenter
The Msg's framework by cpp.

## How to use?
```shell
git clone git@github.com:Hotakus/MsgCenter.git
```

Copy the "msg_center_conf.h" out to upper level  
if you want to use it in Arduino, modify the "msg_center_conf.h"

## example:
Adding the component directly into your project, and run code below👇
```c++
#include "MsgCenter/MsgCenter.h"
using namespace msgmanager;

int main(int argc, char **argv)
{
    MsgCenter::msg_center_test();
    return 0;
}
```
