#include <iostream>
#include <sstream>
#include "JsonNumber.h"

namespace Silhouette{
    namespace Json{
        JsonNumber::JsonNumber(double data):
                Json(JsonType::JS_REAL){
            this->as.real = data;
        }

        JsonNumber::JsonNumber(int data):
                Json(JsonType::JS_INTEGER){
            this->as.integer = data;
        }

        bool JsonNumber::equals(Json* other) {
            if(other->getType() == JsonType::JS_INTEGER && this->getType() == JsonType::JS_INTEGER){
                return this->as.integer == ((JsonNumber*) other)->as.integer;
            } else if(other->getType() == JsonType::JS_REAL && this->getType() == JsonType::JS_REAL){
                return this->as.real == ((JsonNumber*) other)->as.real;
            } else{
                return false;
            }
        }

        bool JsonNumber::equals(double x) {
            if(this->getType() == JsonType::JS_REAL){
                return this->as.real == x;
            }
            return false;
        }

        bool JsonNumber::equals(int x) {
            if(this->getType() == JsonType::JS_INTEGER){
                return this->as.integer == x;
            }
            return false;
        }

        std::string JsonNumber::toString(){
            std::stringstream stream;
            if(this->getType() == JsonType::JS_REAL){
                stream << this->as.real;
            } else{
                stream << this->as.integer;
            }
            return stream.str();
        }
    }
}