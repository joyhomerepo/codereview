#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <vector>
#include <unordered_map>
#include "struct_define.hpp"
#include "property.h"

namespace tec_arch
{

enum class EaStatuS
{
    Uninitialized,
    Initialized,
    Running,
};

class IPublisher;
class IProcessor;
class LockFreeQueue;
class TailProcessor;

class OutputProcessor;
class OutputQueue;
class SyncInfoMap;
class TopicSeqMap;
class TimeSource;

class EventAssembler
{
public:
    /**
     *  @brief 构造函数
     *  @return
     */
    EventAssembler();
    /// 析构函数
    virtual ~EventAssembler();

public:
    // 初始化消息集合器, property包含 消息队列长度，处理器结构
    std::error_code Init(Property property, int64_t* tailSequence);
    // 创建收尾处理器 pTailProcessor_ = new TailProcress(tailSequence);



    // 注册tailprocessor并启动消费方线程
    std::error_code StartProcessor();

    // 停止消费方线程
    std::error_code StopProcessor();

    // 注册消息队列的发布方
    std::error_code RegPublisher(const IPublisher* pPublisher);

    // 注册消息队列的消费者
    std::error_code RegProcessor(const Processor* pProcessor);

    // 注册包含依赖关系的消费者
    std::error_code RegProcessor(std::vector<Processor*> processors, const Processor* pProcessor);

    /// 由IPublisher调用，发布事件
    std::error_code TryPubEvent(EventHeaderT* pEventHeader, const void* pEvent, uint32_t eventLen);

    /**
     *  @brief 查看下一个事件，由消费者调用
     *  @param [in] pProcessor 消费者本身
     *  @param [out] ppEvent 获取到的消息
     *  @return 如果无可消费的新消息，则返回失败
     */
    std::error_code GetEvent(Processor* pProcessor, char** ppEvent);

    //释放序号为消费完成
    std::error_code Release(int64_t sequence);
private:
    Property property;
    //消息队列
    LockFreeQueue* lockFreeQueue_;

    //收束处理器
    TailProcessor* pTailProcessor_;

    //本机处理进度由，tailProcessor修改
    int64_t* tailSequence_;
};

}
