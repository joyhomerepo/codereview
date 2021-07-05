#pragma once

#include <stdint.h>
#include <system_error>
#include "property.h"

namespace tech_arch
{
//输出
class OutputContext
{
public:
    /// 构造函数
	OutputContext();
    /// 析构函数
	~OutputContext();

	//property包含输出队列长度，内存池配置，输出下游的组播地址，端口号等
	std::err_code Init(Property property, SyncInfoMap* pSyncInfoMap, int64_t* tailSequence);

	//启动输出处理器和输出RMB实例
	std::err_code Start();

	//停止输出处理器和输出RMB实例
	void Stop();

	//等待输出处理器和输出RMB实例线程停止
	void Join();

	//获取消息输出句柄
    EventOutputHandler* GetOutputHandler() const;
private：
	//输出队列(元素为链表头的环形队列)
	OutputQueue* pOutputQueue_;

    //针对OutputQueue创建消息输出句柄
    EventOutputHandler* pEventOutputHandler_;

    //输出处理器
    OutputProcessor* pOutputProcessor_;
};

}
