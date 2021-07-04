#pragma once

#include <stdint.h>
#include <system_error>

namespace tech_arch
{

struct OutputDataT
{
	uint32_t len;
	char data[4096];
};

//输出链表节点结构
struct OutputT
{
    uint64_t seqNo;
    OutputT* next;
    OutputT* head;
    OutputT* first;
    OutputT* last;
    OutputDataT data;
};

typedef OutputT* OutputIterator;

class OutputQueue
{
public:
    OutputQueue();
    virtual ~OutputQueue();

public:
    //property包含队列中链表头的最大个数，内存池初始大小和最大可扩容大小
    std::error_code Init(Property property);

    //获取队列第一个元素对应的消息序号
    //如果队列内无元素返回错误码
    std::error_code PeekHead(int64_t* sequence);

    /**
     *  @brief  在特定的输出消息链表头下新增输出消息节点
     *  @param [in]  pData 需发布的内容地址
     *  @param [in]  dataSize 需发布的内容长度
     *  @param [in]  sequence 对应输入消息的序号
     *  @return  如果加入失败返回错误码（队列满了）
     */
    std::error_code AddEvent(const void* pData, uint32_t dataSize, int64_t sequence);

    //获取当前输出队列第一个链表头
    //如果没有输出队列无元素则返回失败
    std::error_code GetFirstEvent(OutputIterator& outputIterator);

    //获取当前输出队列第一个链表中下一个未被发送的消息节点
    //如果没有输出队列无元素则返回失败
    //根据outputIterator找到下一条输出消息，并将用下一条消息的指针覆盖outputIterator
    std::error_code GetNextEvent(OutputIterator& outputIterator, OutputDataT** outputData);

    //将链表头出队，包括清链表头及其节点的清理
    std::error_code Release(int64_t sequence);

private:
    int64_t indexMask_;               //用于快速的计算序号对应的下标，与计算就可以代替%
    int64_t indexShift_;              //用于快速整除
    int64_t size_;                    //数据区大小
    OutputT* entries_;    		      //真正的数据区
    int64_t head_;                    //写指针位置，下一个插入位置
    int64_t tail_;                    //读方最慢序号
    Mempool* mempool_;                //内存池，由outputqueue创建
};

}
