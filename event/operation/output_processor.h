#pragma once
#include <unistd.h>
#include <stdint.h>
#include <chrono>
#include <unordered_map>
#include "ata_common.h"
#include "processor.h"

namespace atalanta
{
class CMsgTrans;
class OutputProcessor : public Thread
{
public:
    /// 构建函数
    OutputProcessor();
    /// 析构函数
    ~OutputProcessor();

    //property包含输出下游的组播地址，端口号等
    std::error_code Init(Property property, SyncInfoMap* pSyncInfoMap, int64_t* tailSequence, OutputQueue* pOutputQueue);
    // 创建MsgTrans，注册主题等

    void Task()
    {
        //遍历pSyncInfoMap，找最小值,结合tailSequence_判断pOutputQueue_头部的输出消息是否能发送
    	//从pOutputQueue_中获取需要发送的消息
        //pMsgTrans_发送
    }
    
private:
    Property property_;
    OutputQueue* pOutputQueue_;
    int64_t* tailSequence_;
    SyncInfoMap* pSyncInfoMap_;
    MsgTrans* pMsgTrans_;
};

}
