#include "timeoperator.h"
#include <QDateTime>

namespace ToolKit {
QString TimeOperator::GetCurDate(){
    return QDateTime::currentDateTime().toString("yyyy-MM-dd");
}

QString TimeOperator::GetCurTime(){
    return QDateTime::currentDateTime().toString("hh:mm:ss");
}

}
