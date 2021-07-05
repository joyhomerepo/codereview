#pragma once

#include "msg_listener.h"
#include "processor.h"
namespace atalanta
{


enum SYNC_CMD {
	SYNC_DATA,  // 发送传输数据指令
    SYNC_RETRANS, //发送请求重传指令
    SYNC_ACK, //发送传输ACK指令
};

struct SyncData {
	uint32_t cmd;
    uint32_t msgLen;
    char data[4096];
};

class SyncProcessor : public Processor, public IPublisher, public IEventListener
{
public:
	SyncProcessor();
    virtual ~SyncProcessor();

public:
	// property包含集群各个节点号列表
    std::error_code init(Property property, std::string filename, SyncInfoMap* pSyncInfoMap);

    //重写Processor方法，获取新消息，若自己是主节点则向其他节点发送同步消息
    void Task();

    //IEventListener,收到消息回调
    void OnEvent(uint64_t seqNo, uint32_t length, const char* p_event)
    {
        //make event
        //pEA_->TryPubEvent(event);
    }
    
    void SwitchToLeader(bool isLeader = true);      //review:参数有意义吗
    
private:
    // 用于从持久化文件中读取消息向外同步
    PersistenceFile* pPersistenceFile_;
    //各节点同步序号表
    SyncInfoMap* pSyncInfoMap_;
    EventTrans* pEventTrans_;//把自己注册进去
    TopicPublisher* pTopicPublisher; //向外发布消息的句柄
};

}
