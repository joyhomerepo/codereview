#pragma once

#include <stdint.h>

namespace tec_arch
{
//处理器实体类
class IProcessor;
class Processor : public Thread //review:名字起得太雷同，怎么使用这个类？
{
public:
    /// 构造函数
    Processor();
    /// 析构函数
    virtual ~Processor();
    /// 绑定Ea，把处理器向ea注册时绑定
    void BindEa(CEventAssembler* pEa); //review:为什么不是注册

    // 线程的主处理函数, 每个processor需要重写，实现自己的处理函数
    virtual void Task() = 0；

public:
    //获取本处理器处理完的最新序号
    inline int64_t GetLastProcessedSeq() const;

    //获取依赖消费者集合中最慢的消费进度
    int64_t GetLastRelySequence();

protected:
    CEventAssembler* pEa_;
    int64_t nowProcessingSeq_; //当前正在处理的消息序号
    int64_t lastProcessedSeq_; //上一条处理完成的消息序号
    bool isEndOfChain_;        //标识是否在链尾
    std::vector<Processor*> relyProcessors;  //前置依赖的processor列表


};

}
