#pragma once

#include <stdint.h>
#include <system_error>
#include "property.h"

namespace tec_arch
{

enum class RoleE
{
	Leader,
	Follower,
	Learner,
};


enum class EaStatuS
{
    Uninitialized,
    Initialized,
    Running,
};

class IProcessor;
class TimeSlicer;
class TimeSource;
class RmbReceiver;
class EventAssembler;
class ManagerProcessor;
class SyncProcessor;
class PersistProcessor;
class OutputProcessor;
class OutputQueue;
class SyncInfoMap;
class TopicSeqMap;

class EventFramework
{
public:
    /**
     *  @brief 构造函数
     */
    EventFramework();
    // 析构函数
    virtual ~EventFramework();

public:
    /** 
     * @brief  初始化
     * @param [in] property: 本节点节点号
     * @return 成功(0)/失败(错误码)
     */
    std::error_code Init(Property property);
    //用传入的节点号去约定的路径找配置文件并读取属于自己的property
    //创建各个rmb主题对应的接收进度表
    //创建各节点同步序号表
    //创建输出模块
    //创建事件集合器
    //创建管理处理器
    //创建同步处理器
    //创建持久化处理器
    //创建时间片生成器
    //创建业务消息RMB接收实例
    //注册内置处理器编排（根据配置文件）
    //阻塞主备切换时调用，根据新主备状态对不同模块做调整
    void Switch(RoleE newRole);

    // 向UserProcessor中注册用户传入的消息处理类
    // 将IProcessor传入UserProcessor
    // 从pOutputContext_得到输出句柄传入UserProcessor
    void RegProcessor(const IProcessor* pProcessor);

    //启动所有processor
    std::error_code StartProcessor();

    //启动TimeSlicer、RmbReceiver
    std::error_code StartReceiver();

    //异步停止消息处理框架
    void Stop();
    
    //阻塞等待各个线程停止
    void Join();

private:
    //从文件中独到的配置
    Property property_;

    //各个rmb主题对应的接收进度
    TopicSeqMap* pTopicSeqMap_;
    //各节点同步序号
    SyncInfoMap* pSyncInfoMap_;
    //本机处理进度，由TailProcessor修改，由OutputProcessor读取
    int64_t tailSequence_;

    //结果输出模块
    OutputContext* pOutputContext_;

    //时间源实例
    TimeSource* pTimeSource_;

    //事件集合器
    EventAssembler* pEventAssembler_;
    //管理处理器
    ManagerProcessor* pManagerProcessor_;
    //同步处理器
    SyncProcessor* pSyncProcessor_;
    //持久化处理器
    PersistProcessor* pPersistProcessor_;
    //用户注册的业务处理器
    UserProcessor* pUserProcessor_;

    //时间片生成器
    TimeSlicer* pTimeSlicer_;
    //rmb接收组件
    RmbReceiver* pRmbReceiver_;

};

}
