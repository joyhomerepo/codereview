#pragma once

#include <stdint.h>
#include "./thirdparty/timer.hpp"
namespace tec_arch
{

enum TimeMode
{
    Remote = 0,      //远端时间模式
    Local_realtime = 1,       //本地真实时间模式
    Local_interval = 2,       //时间间隔叠加模式
};

///本地-时间刷新-处理类
class Timer;
class LocalTimeUpdater : public ITimerProc
{
    LocalTimeUpdater(TimeSource* timesource)
    {
        timesource_ = timesource_;
    }
    ~LocalTimeUpdater(){};

    void void TimerProc(int cnt)
    {
        //获取本地时间
        //timesource_->UpdateTime
    }
private:
    TimeSource* timesource_;
}

///时间源实体类
class TimeSource
{
public:
    // 构建函数, 在管理处理出创建时创建, 入参含义为时间戳类型
    TimeSource()
    {

    }
    // 析构函数
    virtual ~TimeSource();

    std::error_code Init(Property property);
    //判断property中的时间模式，如果为本地则：
    //new localTimer_
    //new localTimeUpdater_(this)
    //localTimer_->RegCallBack(LocalTimeUpdater)

    //启动定时器，开始更新时间，可以反复启停
    std::error_code Start();
    // localTimer_->Start

    //停止定时器，停止更新时间
    std::error_code Stop();
    // localTimer_->Stop

    // 获取当前截取时间
    uint64_t GetTime();

public:
    // 更新刷新时间戳, 由LocalTimeUpdater调用
    void UpdateTime(uint64_t newTime);

private:
    int64_t nowTime_;                      //不断被本地/远端刷新的时间
    
    TimeMode timeMode_;                     //时间模式，本地/远端
    
    LocalTimeUpdater* localTimeUpdater_;    
    Timer* localTimer_;                     //本地时间刷新定时器
};


}
