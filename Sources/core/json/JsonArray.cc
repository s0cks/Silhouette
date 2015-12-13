#include <sstream>
#include "JsonArray.h"

namespace Silhouette{
    namespace Json{
        JsonArray::JsonArray():
                Json(JsonType::JS_ARRAY){
            this->table = new Json*[16];
            this->size = 0;
            this->asize = 16;
        }

        JsonArray::JsonArray(size_t size):
                Json(JsonType::JS_ARRAY){
            this->table = new Json*[size];
            this->size = 0;
            this->asize = size;
        }

        JsonArray::~JsonArray() {
            delete[] this->table;
        }

        void JsonArray::compact() {
            Json* last  = nullptr;
            for(size_t i = 0; i < this->asize; i++){
                last = this->table[i];
                if(last != nullptr){
                    continue;
                } else{
                    if(i + 1 < this->asize){
                        this->table[i] = this->table[i + 1];
                    }
                }
            }
        }

        bool JsonArray::equals(Json* obj) {
            if(obj->getType() == JsonType::JS_ARRAY){
                JsonArray* array = (JsonArray*) obj;
                if(array->size != this->size || array->asize != this->asize){
                    return false;
                }

                for(size_t i = 0; i < this->asize; i++){
                    if(this->table[i] && this->table[i]->equals(array->table[i])){
                        continue;
                    } else{
                        return false;
                    }
                }
                return true;
            }

            return false;
        }

        std::string JsonArray::toString(){
            std::stringstream stream;
            stream << "[";
            for(size_t i = 0; i < this->asize; i++){
                if(this->table[i] == nullptr){
                    continue;
                }

                stream << this->table[i]->toString();
                if(i + 1 < this->asize && this->table[i + 1] != nullptr){
                    stream << ",";
                }
            }
            stream << "]";
            return stream.str();
        }

        void JsonArray::push(Json* obj) {
            if(this->size + 1 > this->asize){
                Json** tmp = (Json**) realloc(this->table, this->size + 1);
                this->table = tmp;
                this->asize++;
            }

            for(size_t i = 0; i < this->asize; i++){
                if(this->table[i] == nullptr){
                    this->table[i] = obj;
                    this->size++;
                    return;
                }
            }
        }

        bool JsonArray::contains(Json* obj) {
            for(size_t i = 0; i < this->asize; i++){
                if(this->table[i] != nullptr){
                    if(this->table[i]->equals(obj)){
                        return 1;
                    }
                }
            }

            return 0;
        }
    }
}