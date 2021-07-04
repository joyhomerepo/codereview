#pragma once

#include <stdint.h>
#include <system_error>
#include "struct_define.hpp"

namespace tec_arch
{

class EventAssembler;
class IPublisher
{
public:
    /// 构建函数
    IPublisher();

    /// 析构函数
    virtual ~IPublisher();

    /// 绑定需要操作的EA
    void BondEa(EventAssembler* pEA);

    /// 由派生类调用，内部调用EA的发布接口进行发布
    //publisher在发布前组装header，与真正消息数据和消息长度一并传入
    std::error_code TryPubEvent(EventHeaderT* pEventHeader, const void* pEvent, uint32_t eventLen);
public:
    inline int64_t GetLastPublishedSequence() const;
private:
    EventAssembler* pEA_;
    int64_t lastPublishedSequence_; //发布者发布内部序号（与EA定序序号无关）
};

}
