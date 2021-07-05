#pragma once
#include <unistd.h>
#include <chrono>
#include "processor.h"

namespace tec_arch
{

class EventAssembler;
class TimeSource;

class ManageProcessor : public Processor
{
public:
    /// 构建函数
    ManageProcessor(TimeSource* time_source, TopicSeqMap* pTopicSeqMap);
    // 析构函数
    ~ManageProcessor();

    //获取新消息
    //从timeSource拿时间，授时
    //修改TopicSeqMap进度
    void Task();

private:
    TimeSource* time_Source_;
    TopicSeqMap* pTopicSeqMap_;
};

}
