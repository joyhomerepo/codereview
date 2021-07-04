#pragma once
#include <unistd.h>
#include <stdint.h>
#include <chrono>
#include <unordered_map>
#include "ata_common.h"
#include "publisher.h"
#include "msg_trans.h"

namespace tec_arch
{

// Rmb接收回调，同时也是ea的发布者
class RmbEventPublisher : public IPublisher, public IEventListener
{
public:
    /// 构建函数
    RmbEventPublisher();
    /// 析构函数
    ~RmbEventPublisher();

    void OnEvent(uint64_t seqNo, uint32_t length, const char* p_event)
    {
        //make event
        //pEA_->TryPubEvent(event);
    }
};

// 
class EventAssembler;
class EventTrans;
class RmbReceiver
{
public:
	/// 构建函数
	RmbReceiver();
	/// 析构函数
    ~RmbReceiver();

    //property包含上游主题信息（本地ip，topicid，组播地址，端口号）
    std::error_code Init(Property property, EventAssembler* pEa);

	// 开始获取上游业务消息并向ea发布
    std::error_code Start();

    // 异步停止生成时间片
    void Stop();

    // 阻塞等待线程停止
    void Join();

    //在init需要对每一个需要注册的主题进行注册，Property包含组播地址，端口号等
    //创建RmbEventPublisher
    //注册topic&RmbEventPublisher到EventTrans（可靠组播实例）中
    //将topic&RmbEventPublisher维护在vector中
    std::error_code RegisterTopic(uint64_t topic_id, Property property);
    
private:
    EventAssembler* pEa_;
    Property property_;
    EventTrans* pEventTrans_;
    std::vector<RmbEventPublisher*> rmbEventPublishers;//一个topic
};

}
