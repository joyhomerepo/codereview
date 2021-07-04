#ifndef _TECHARCH_TABLE_H_
#define _TECHARCH_TABLE_H_

#include <set>
#include <system_error>

#include "property.hpp"


namespace techarch {

/// 数据表类，包含数据表全部用法与接口
class Table {
public:
    /**
     * @brief 清空对应数据表（清空数据表内容但不删除数据表结构）
     * 
     * @return 错误码
     */
    std::error_code Truncate();

    /// 记录转换函数指针类型定义
    typedef void (*RecordConvFuncT)(const char *, char *);
    /**
     * @brief 从外部数据文件加载数据表
     * 
     * @param file_path [in] 外部数据文件路径
     * @param record_conv_func [in] 记录转换函数指针
     * @return 错误码
     */
    std::error_code Load(const char *file_path, RecordConvFuncT record_conv_func);
    
    /**
     * @brief 触发表当前状态生成全量快照落地
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
     * @brief 向数据表中插入一条数据（插入仅涉及主键索引）
     * 
     * @param tuple [in] 需要插入的数据
     * @return 错误码
     */
    std::error_code Insert(const char *tuple);

    /**
     * @brief 向数据表更新一条数据
     * 
     * @param primary_key [in] 需要更新的数据的主键
     * @param new_tuple [in] 需要插入的数据
     * @param position [in] 修改数据段在记录中的起始位置
     * @param len [in] 修改数据段长度
     * @return 错误码
     */
    std::error_code Update(const char *primary_key, const char *new_tuple, int32_t position, size_t len);

    /// 记录修改函数指针类型定义
    typedef std::error_code (*UpdateFuncT)(char *tuple, int32_t length);
    /**
     * @brief 向数据表更新一条数据
     * 
     * @param primary_key [in] 需要更新的数据的主键
     * @param update_func [in] 需要插入的数据
     * @return 错误码
     */
    std::error_code Update(const char *primary_key, UpdateFuncT update_func);

    /**
     * @brief 通过主键搜索一条数据记录
     * 
     * @param primary_key [in] 数据主键
     * @param tuple [out] 数据记录
     * @return 错误码
     */
    std::error_code SelectByPK(const char *primary_key, char *tuple);

    /**
     * @brief 通过附加唯一索引搜索一条记录
     * 
     * @param index_no [in] 附加索引编号
     * @param index_tuple [in] 包含查找索引值的记录，其中按照索引的偏移填写附加唯一索引的key值
     * @param tuple [out] 查找到的数据
     * @return 错误码
     */
    std::error_code SelectByUniqueIndex(int32_t index_no, const char *index_tuple, 
                    char* tuple);
    

    /**
     * @brief 通过主键删除一条数据记录
     * 
     * @param primary_key [in] 数据主键
     * @return 错误码
     */
    std::error_code Delete(const char *primary_key);

    /**
     * @brief 获得表的监测数据
     * 
     * @param table_stat [in] 数据表监测数据
     * @return 错误码
     */
    std::error_code GetStatistics(Property &table_stat);
};
} // namespace

#endif // _TECHARCH_TABLE_H_
