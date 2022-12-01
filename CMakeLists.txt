project(MCC)
cmake_minimum_required(VERSION 3.16)
include_directories(
    ./
    ./chain/
    )

set(APP_SRC
    ./MsgCenter.cpp
    ./chain/Chain.cpp
    ./chain/chain_node_t.cpp
        )



add_library(mcc_static STATIC ${APP_SRC})
add_library(mcc_shared SHARED ${APP_SRC})


    
# 指定静态库的输出名称
set_target_properties(mcc_static PROPERTIES OUTPUT_NAME "mcc")
set_target_properties(mcc_shared PROPERTIES OUTPUT_NAME "mcc")
# 使动态库和静态库同时存在
set_target_properties(mcc_static  PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(mcc_shared  PROPERTIES CLEAN_DIRECT_OUTPUT 1)
 
# 指定动态库版本
# VERSION 动态库版本
# SOVERSION API版本
# set_target_properties( PROPERTIES VERSION 1.0 SOVERSION 1)


