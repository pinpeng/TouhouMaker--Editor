#ifndef MEMORY_DATA_I_FILE_OPERATOR_H
#define MEMORY_DATA_I_FILE_OPERATOR_H

#include <QString>

namespace MemoryCache{
    class IFileOperator{
        public:
        /**
         * @brief 保存到文件中
         * @param fileName 文件的绝对路径
        */
        virtual bool SaveToFile(const QString& fileName) = 0;
        /**
         * @brief 从文件中读取
         * @param fileName 文件的绝对路径
        */
        virtual bool ReadFromFile(const QString& fileName) = 0;
    };
}

#endif