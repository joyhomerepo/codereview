#pragma once
#include <unistd.h>
#include <chrono>
#include "processor.h"

namespace tec_arch
{

class EventAssembler;
class TimeSource;

class ManagerProcessor : public Processor
{
public:
    /// 构建函数
    ManagerProcessor(TimeSource* timeSource, TopicSeqMap* pTopicSeqMap);
    // 析构函数
    ~ManagerProcessor();

    //获取新消息
    //从timeSource拿时间，授时
    //修改TopicSeqMap进度
    void Task();

private:
    TimeSource* timeSource_;
    TopicSeqMap* pTopicSeqMap_;
};

}
