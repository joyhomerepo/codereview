#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <vector>
#include "sequence.h"

namespace tech_arch
{

class LockFreeQueue
{
public:
    LockFreeQueue();
    virtual ~LockFreeQueue();

public:
    //property包含blockCount和blockSize
    std::error_code Init(Property property);

    /**
     *  @brief  写方使用，申请一个可写序号
     *  @param [out]  sequence 申请到可写入的最大序号
     *  @param [out]  ppBlock  申请到的序号对应的数据区
     *  @return  申请成功为0，失败为错误码
     */
    std::error_code Reserve(int64_t* sequence, char** ppBlock);

    /**
     *  @brief  写方使用，发布序号为可消费序号
     *  @param [in]  sequence 需发布的序号
     *  @return  发布成功为0，失败为错误码
     */
    std::error_code Mark(int64_t sequence);

    //读方使用，获取指定序号对应的数据的指针
    //获取成功返回0，如果指定序号还不能消费则返回错误码
    std::error_code Get(int64_t sequence, char** ppBlock);

    /**
     *  @brief  读方使用，移动尾指针
     *  @param [in]  sequence 消费完成的最大序号
     *  @return
     */
    std::error_code Release(int64_t sequence);

public:
    //获取已经被占位但还未被消费的队列槽位数量
    int64_t GetOccupiedBlockNum();

private:
    int64_t blockCount_;              //环形队列容纳的item个数
    int64_t blockSize_;               //单个item的消息长度
    int64_t indexMask_;               //用于快速的计算序号对应的下标，与计算就可以代替%
    int64_t indexShift_;              //用于快速整除
    int64_t totalSize_;               //entries数据区大小
    char* entries_;      			  //真正的数据区
    int* availableFlags_;             //有效性标识数组
    int64_t head_;                    //写指针位置，下一个插入位置
    int64_t tail_;                    //读方最慢序号
};

}
