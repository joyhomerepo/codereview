#pragma once

#include "processor.h"

namespace tec_arch
{

class UserProcessor : public Processor
{
public:
    /// 构建函数
	UserProcessor(EventOutputHandler* pEventOutputHandler);
    // 析构函数
	~UserProcessor();
    //重写，调用pIProcessor_中的回调函数
	void RegCallback(IProcessor* pIProcessor_);

	//获取新消息，调用IProcessor中的处理函数
    void Task();

private:
    IProcessor* pIProcessor_; //处理类，由用户注册
    EventOutputHandler* pEventOutputHandler_;
};

}
