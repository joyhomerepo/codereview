#pragma once
#include <unistd.h>
#include <stdint.h>
#include <chrono>
#include <unordered_map>
#include "ata_common.h"
#include "processor.h"
//#include "event_assembler.h"

class TailProcessor : public Processor
{
public:
    /// 构建函数，tailSequence本节点处理完成的最大序号
	TailProcessor(int64_t* tailSequence);
    // 析构函数
    ~TailProcessor();

    //获取新消息
    //更新本节点处理序号
    void Task();

private:
    int64_t* tailSequence_;
};
