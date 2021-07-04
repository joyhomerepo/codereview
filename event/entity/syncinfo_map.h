#pragma once
#include <stdint.h>
#include <system_error.h>
#include <map>
#include "property.h"


namespace tech_arch
{

class SyncInfoMap
{
public:
    SyncInfoMap();
    ~SyncInfoMap();

	//主备同步模式，n/2+1 或 n, 集群节点号列表
    std::error_code Init(Property property);

	//同步处理器调用, 更新某个节点的同步响应进度
    std::error_code UpdateValue(int32_t nodeId, uint64_t sequence);
	
	//根据map计算出被集群认可的ack进度
    uint64_t GetLastSequence();

private:
	Property property_;
    std::map<int32_t, uint64_t> synInfoMap_;
};

}
