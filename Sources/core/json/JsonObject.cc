#include <sstream>
#include "JsonObject.h"

namespace Silhouette{
    namespace Json{
        struct JsonObjectEntry{
            struct JsonObjectEntry* next;
            struct JsonObjectEntry* prev;
            std::string key;
            Json* value;
        };

        JsonObject::JsonObject():
                Json(JsonType::JS_OBJECT){
            this->root = nullptr;
        }

        JsonObject::~JsonObject() {
            while(this->root){
                JsonObjectEntry* entry = this->root->next;
                delete this->root->value;
                delete this->root;
                this->root = entry;
            }
        }

        void JsonObject::set(std::string key, Json* value){
            JsonObjectEntry* entry = this->root;
            while(entry){
                if(entry->key.compare(key) == 0){
                    entry->value = value;
                    return;
                }
                entry = entry->next;
            }

            entry = new JsonObjectEntry;
            entry->key = key;
            entry->value = value;
            entry->next = this->root;
            if(this->root){
                this->root->prev = entry;
            }
            this->root = entry;
            this->size++;
        }

        Json* JsonObject::get(std::string key) {
            JsonObjectEntry* entry = this->root;
            while(entry){
                if(entry->key.compare(key) == 0){
                    return entry->value;
                }
                entry = entry->next;
            }
            return nullptr;
        }

        bool JsonObject::remove(std::string key) {
            JsonObjectEntry* next = this->root;

            while(next){
                JsonObjectEntry* tmp = next->next;

                if(next->key.compare(key) == 0){
                    if(next->next){
                        next->next->prev = next->prev;
                    }
                    next->prev->next = next->next;
                    delete next->value;
                    delete next;
                    this->size--;
                    return true;
                }

                next = tmp;
            }

            return false;
        }

        bool JsonObject::equals(Json* json) {
            if(json->getType() == JsonType::JS_OBJECT){
                JsonObject* obj = (JsonObject*) json;
                if(obj->size != this->size){
                    return false;
                }
                JsonObjectEntry* entry = this->root;
                JsonObjectEntry* oentry = obj->root;
                while(entry && oentry){
                    if(entry->key.compare(oentry->key) != 0){
                        return false;
                    }

                    if(!entry->value->equals(oentry->value)){
                        return false;
                    }

                    entry = entry->next;
                    oentry = oentry->next;
                }

                return true;
            }

            return false;
        }

        std::string JsonObject::toString() {
            std::stringstream stream;
            stream << "{";
            JsonObjectEntry* entry = this->root;
            while(entry){
                stream << "\"" << entry->key << "\":" << entry->value->toString();
                entry = entry->next;
                if(entry != nullptr){
                    stream << ",";
                }
            }
            stream << "}";
            return stream.str();
        }
    }
}