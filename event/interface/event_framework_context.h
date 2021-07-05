#pragma once

#include <stdint.h>
#include <vector>
#include <system_error>
#include "property.h"

namespace tech_arch
{

enum RunModeE
{
    Cluster = 0,      //集群模式
    Singleton = 1,    //单例模式
    Backup = 2        //跟跑模式
};

enum EventTypeE
{
    Business = 0,     //业务消息
    TimeSlice = 1,    //时间片消息
    Emergency = 2,    //应急消息
};

//递交给业务处理回调的数据信息
struct EventData
{
	EventTypeE ev_type;
    uint32_t length;
    int32_t ea_id; //todo
    int64_t sequence_num;
    int64_t timestamp;
    void* pevent;
};

//递交给业务处理回调的输出句柄，业务处理器依靠此句柄输出消息
class EventDispatcher
{
public:
	/// 针对一条输入消息做一次输出，如果有多条输出则需要多次调用
	std::error_code DispatchEvent(const char* pevent, uint32_t length);
};

//业务处理器处理类，使用方可以继承此类并重写OnEvent，来实现业务逻辑并注册到消息处理框架中
class IProcessor
{
public:
	virtual ~IProcessor();
    
	//eventData为输入的消息
	//pEventOutputHandler为输出时使用的句柄
    virtual void OnEvent(const EventData* event_Data, EventOutputHandler* pevent_dispatcher) = 0;
};

class EventFrameContext
{
public:
    /**
     *  @brief  构造函数
     */
	EventFrameContext();
    // 析构函数
    virtual ~EventFrameContext();

public:
    /** 
     * @brief 初始化
     * @details 外部接口, 由用户调用, 用于初始化消息处理框架
     * @param [in] property: 本节点节点号
     * @param [in] runMode：集群，单例，跟跑
     * @return 0或错误码
     */
    std::error_code Init(Property property, RunModeE run_mode);

    /** 
     * @brief 启动消息处理框架
     * @details 外部接口, 由用户调用, 用于启动消息处理框架。 包含处理器及消息输入输出组件的启动等。
     * @return 成功为0，失败返回错误码
     */
    std::error_code Start();
    
    /**
     * @brief 异步停止消息处理框架
     * @details 外部接口, 由用户调用, 用于停止消息处理框架
     * @return 无
     */
    void Stop();

    //阻塞等待线程结束，释放线程资源
    void Join();

    /**
     * @brief 外部接口, 供用户注册业务处理器，仅能调用一次
     * @details 外部接口, 由用户调用, 用于注册业务处理器
     * @return 成功为0，失败返回错误码（如重复注册）
     */
    std::error_code RegisterProcessor(const IProcessor* pProcessor);
};

}
