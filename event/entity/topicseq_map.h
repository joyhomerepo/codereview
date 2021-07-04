#pragma once
#include <stdint.h>
#include <system_error.h>
#include <map>
#include "property.h"


namespace tec_arch
{

class TopicSeqMap
{
public:
	//
	TopicSeqMap();
    ~TopicSeqMap();

    //property 包含上游业务消息主题信息列表
    std::error_code Init(Property property);
	
	//更新单个主题消息接收进度，管理处理器更新
    std::error_code UpdateReceivedSequence(uint64_t topic, uint64_t sequence);

    //输入topic
    //输出该topic已经经过管理处理器的序号，由EventFramework::switch主备切换时调用
    std::error_code GetReceivedSequence(uint64_t topic, uint64_t* pSequence)

private:
	Property property_;
    std::map<uint64_t, uint64_t> topicSeqMap_;
};

}
