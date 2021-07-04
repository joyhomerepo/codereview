#pragma once

#include <string>
#include <fstream>
#include "property.h"

namespace tech_arch
{

class PersistenceFile {
public:
	PersistenceFile();
    virtual ~PersistenceFile();

public:
    //property包含文件名
    std::error_code Open(Property property);

    std::error_code Close();
    /** 
     * @brief 持久化消息，线程不安全
     * @param seqNo   被持久化消息的seq
     * @param pMsg    被持久化消息的指针
     * @param msgLen  被持久化消息的长度
     *
     * @return 返回错误码
     *     FAILED  持久化失败
     *     SUCCESS 持久化成功
     */
    std::error_code Write(int64_t seqNo, const char* pMsg, uint32_t msgLen);

    /** 
     * @brief 按序读取已持久化的消息，线程安全
     * @param pMsg    持久化消息的指针，作为读取消息的返回值
     * @param msgLen  输入时代表pMsg可用长度（可能大小不够），输出时返回实际copy的长度
     * @param pSeq    返回获取到的dump消息中的消息序号（正常情况下递增+1）
     * @return 返回错误码
     *     FAILED  读取信息失败
     *     SUCCESS 读取信息成功
     */
    std::error_code Read(char* pMsg, uint32_t* pMsgLen, int64_t* pSeq);

    /** 
     * @brief 按sequence seek持久化文件，线程安全
     * @param seq     sequence 序列号
     * @param msgLen  持久化文件中消息的长度
     *
     * @return 返回错误码
     *     false  seek失败
     *     true   seek成功
     */
    std::error_code Seek(int64_t seq, uint32_t msgLen);
    
    /** 
     * @brief 按位置 seek持久化文件，线程安全
     * @param position  持久化文件中消息的长度
     *
     * @return 返回
     *     错误码:seek失败
     *     0:seek成功
     */
    std::error_code Seek(int64_t position);

private:
    FILE* file_;             // 持久化文件实例
    int64_t lastSeq_ = 0;    // 上一持久化sequence
};

}
