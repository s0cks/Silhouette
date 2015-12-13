#ifndef SILHOUETTE_JSONOBJECT_H
#define SILHOUETTE_JSONOBJECT_H

#include "JsonType.h"

namespace Silhouette{
    namespace Json{
        class JsonObject: public Json{
        private:
            struct JsonObjectEntry* root;
            size_t size;
        public:
            JsonObject();
            ~JsonObject();

            bool equals(Json* json);
            std::string toString();

            void set(std::string key, Json* value);
            bool remove(std::string key);
            Json* get(std::string key);

            size_t length(){
                return this->size;
            }
        };
    }
}

#endif