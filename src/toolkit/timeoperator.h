#ifndef TIMEOPERATOR_H
#define TIMEOPERATOR_H

#include <QString>

namespace ToolKit{
class TimeOperator
{
public:
    /**
     * @brief 获取当前日期，格式为：1970-08-01
     * @return
     */
    static QString GetCurDate();
    /**
     * @brief 获取当前时间，格式为：18:59:01
     * @return
     */
    static QString GetCurTime();
};

}

#endif // TIMEOPERATOR_H
