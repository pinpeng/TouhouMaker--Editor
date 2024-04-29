#ifndef MEMORY_CACHE_PROJECT_INFO
#define MEMORY_CACHE_PROJECT_INFO

#include "memoryCache/interface/IFileOperator.h"
#include "memoryCache/interface/IMemoryData.h"
namespace MemoryCache{
    class ProjectInfo:public IFileOperator,public IMemoryData{

    };
}

#endif