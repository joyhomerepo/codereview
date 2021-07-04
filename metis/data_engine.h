#ifndef _TECHARCH_DATA_ENGINE_H_
#define _TECHARCH_DATA_ENGINE_H_

#include <string.h>
#include <system_error>


#include "table.h"
#include "property.hpp"

namespace techarch
{
    class Table;

    /// 数据引擎实例类，包含数据引擎启动、停止接口
    class DataEngineInstance
    {
    public:
    /**
     * @brief 构造函数
     * 
     * @param instance_name [in] 引擎实例名
     * @param prot [in] 引擎相关配置：
     * [实例配置]
     * 数据表数量上限
     * 内存使用上限
     * 快照文件存放路径
     * 日志文件存放路径
     * 单表最大可支持的行记录数量
     * 单表最大可支持的行记录大小
     * 单表最大可支持索引数量
     * 索引个数上限
     * 索引长度上限
     * 附加索引子字段个数上限
     * 导出快照时是否提升基线
     * 增量数据区数据载体（共享内存或私有内存）
     * 增量数据区最大个数
     * 数据块尺寸
     * [表配置]数组
     * 每张表的表结构描述（记录长度、记录数量上限、预分配记录数）
     * 每张表的索引结构描述（主键：主键起始位置、主键长度；附加唯一索引：每一个子字段的起始位置以及长度；）
     * @return 错误码
     */
        DataEngineInstance(const char *instance_name, const Property &prot);

        /**
     * @brief 初始化数据引擎，内部包括创建资源、createTable等操作
     * 
     * @return 错误码
     */
        std::error_code Start();

        /**
     * @brief 关闭数据引擎
     * @return 错误码
     */
        std::error_code Stop();
    };

    /// 数据引擎会话类，包含连接、断开连接、获取数据表句柄等接口
    class DataEngineSession
    {
    public:
        DataEngineSession(const char *data_engine_name);

        /**
     * @brief 连接数据引擎
     * 
     * @return 错误码
     */
        std::error_code Connect();

        /**
     * @brief 断开与数据引擎连接
     * 
     * @return 错误码
     */
        std::error_code Close();

        /**
     * @brief 根据表名来获得对应的表句柄
     * 
     * @param table_name [in] 数据表名
     * @param table_handle [out] 数据表句柄
     * @return 错误码
     */
        std::error_code GetTable(const char *table_name, Table *table_handle);

        /**
     * @brief 触发引擎中所有表当前状态生成全量快照落地
     * 
     * @param label [out] 应用传入的标签，例如：可为应用的事务版本号
     * @return 错误码
     */
        std::error_code MakeSnapshot(uint64_t label);

        /**
     * @brief 触发表的数据合并，供应急工具使用
     * 
     * @return 错误码
     */
        std::error_code Purge();

        /**
     * @brief 根据表名来获得对应的表句柄
     * 
     * @param table_names [out] 所有的数据表名
     * @return 错误码
     */
        std::error_code GetAllTableNames(std::vector<std::string> &table_names);

        /**
     * @brief 获得数据引擎的监测数据
     * 
     * @param de_stat [out] 数据引擎监测数据
     * @return 错误码
     */
        std::error_code GetStatistics(Property &de_stat);
    };
} // namespace

#endif // _TECHARCH_DATA_ENGINE_H_