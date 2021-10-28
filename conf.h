#ifndef MSG_CENTER_CONF_H
#define MSG_CENTER_CONF_H

#include "../msg_center_conf.h"

#if IS_ARDUINO == 0
#include <cstdio>
#include <string>
#include <iostream>

typedef std::string String;

using namespace std;

#define MSG_PRINT(tag, fmt, ...)    printf(fmt"\r\n", ##__VA_ARGS__)
#define MSG_ALLOC                   malloc
#define MSG_REALLOC                 realloc
#define MSG_FREE                    free

#else
#include "../../HgmApp/HotakusMemUtil.h"
#include <Arduino.h>

#define TAG "MsgCenter"
#define HGM_DEBUG 1
#include "../../HgmLogUtil.h"

#define MSG_PRINT       hgm_log_e

#define MSG_ALLOC       hotakusAlloc
#define MSG_REALLOC     hotakusRealloc
#define MSG_FREE        hotakusFree
#endif // IS_ARDUINO == 0

#ifdef __cplusplus
extern "C" {
#endif

/*...*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //MSG_CENTER_CONF_H
