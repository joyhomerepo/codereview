#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <cstring>

namespace tech_arch
{

const int32_t MAX_EVENT_LEN = 4096;

struct EventHeaderT
{
    int32_t type;        //事件种类
    uint64_t topic;      //事件来源的主题
    uint64_t seqNo;      //事件来源的主题内编号
    bool isValid;        //事件是否需要被处理
    bool isDump;         //事件是否来自持久化文件
    bool isSyn;          //事件是否来主备同步
    char filler[5];
    uint64_t transId;    //事件在EA中的序号
    int64_t msgTime;     //事件时间
    int32_t msglen;      //数据区长度
    char data[0];
};

const int MAX_DATA_LEN = MAX_EVENT_LEN - sizeof(EventHeaderT);

struct Event
{
    EventHeaderT eventHeader;
    char data[MAX_DATA_LEN];
};

}
