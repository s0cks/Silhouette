#include "JsonString.h"

namespace Silhouette{
    namespace Json{
        JsonString::JsonString(std::string value):
                Json(JsonType::JS_STRING){
            this->value = value;
        }

        bool JsonString::equals(Json* json) {
            if(json->getType() == JsonType::JS_STRING){
                return ((JsonString*) json)->value.compare(this->value) == 0;
            }
            return false;
        }

        bool JsonString::equals(std::string value) {
            return this->value == value;
        }

        std::string JsonString::toString() {
            return "\"" + this->value + "\"";
        }
    }
}