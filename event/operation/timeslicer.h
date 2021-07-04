#pragma once

#include <stdint.h>
#include <system_error>
#include "timer.h"
#include "publisher.h"

namespace tec_arch
{

// 时间片发布者
class TimeSlicePublisher : public IPublisher, public ITimerCallback
{
public:
    /// 构建函数
    TimeSlicePublisher();
    /// 析构函数
    ~TimeSlicePublisher();

    void OnTimeEvent()
    {
        //get time
        //make event
        //pEA_->TryPubEvent(event);
    }
};

// 时间片生成器
class EventAssembler;
class TimeSlicer
{
public:
	/// 构建函数
	TimeSlicer();
	/// 析构函数
    ~TimeSlicer();

    // 创建定时器和定时器处理类实例并注册
    std::error_code Init(Property property, EventAssembler* pEa);

	// 开始生成时间片并向事件集合器发布
    std::error_code Start();

    // 停止生成时间片
    std::error_code Stop();

    
private:
    Timer* pTimer_;                              //定时器实例
    TimeSlicePublisher* pTimeSlicePublisher_;    //定时器回调 + 时间片发布者        
};

}
