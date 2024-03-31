#ifndef MEMORY_CACHE_TEXT_H
#define MEMORY_CACHE_TEXT_H

#include <QString>

namespace memoryCache{
    class Text{
        public:
        int _id;
        QList<QString> _text;
    };
}

#endif