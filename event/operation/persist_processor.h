#pragma once

#include "processor.h"

namespace tec_arch
{

class PersistProcessor : public Processor
{
public:
    PersistProcessor();
    virtual ~PersistProcessor();

    std::error_code Init(std::string filename);

    void Task();
    //获取新消息
    //持久化到文件
private:
    PersistenceFile *pPersistenceFile = nullptr;
};

}
