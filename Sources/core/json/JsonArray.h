#ifndef SILHOUETTE_JSONARRAY_H
#define SILHOUETTE_JSONARRAY_H

#include "JsonType.h"

namespace Silhouette{
    namespace Json{
        class JsonArray: public Json{
        private:
            Json** table;
            size_t size;
            size_t asize;
        public:
            JsonArray(size_t size);
            JsonArray();
            ~JsonArray();

            void push(Json* obj);
            void compact();
            void set(size_t index, Json* obj);
            bool contains(Json* obj);
            bool equals(Json* obj);
            std::string toString();

            Json* get(size_t index){
                return this->table[index];
            }

            size_t length(){
                return this->size;
            }
        };
    }
}

#endif