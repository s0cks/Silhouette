#ifndef SILHOUETTE_JSONSTRING_H
#define SILHOUETTE_JSONSTRING_H

#include "JsonType.h"

namespace Silhouette{
    namespace Json{
        class JsonString : public Json{
        private:
            std::string value;
        public:
            JsonString(std::string value);

            bool equals(Json* json);
            bool equals(std::string value);
            std::string toString();
        };
    }
}

#endif