#ifndef SILHOUETTE_JSONTYPE_H
#define SILHOUETTE_JSONTYPE_H

#include <stdint.h>
#include <string>

namespace Silhouette{
    namespace Json{
        enum class JsonType : uint8_t{
            JS_OBJECT,
            JS_ARRAY,
            JS_STRING,
            JS_INTEGER,
            JS_REAL,
            JS_TRUE,
            JS_FALSE,
            JS_NULL
        };

        class Json{
        private:
            JsonType type;
        public:
            Json(JsonType t): type(t){}
            virtual ~Json(){}
            virtual bool equals(Json* other){ return false; }
            virtual std::string toString(){ return ""; }

            JsonType getType(){
                return this->type;
            }
        };

        class JsonNull : public Json{
        public:
            JsonNull(): Json(JsonType::JS_NULL){}

            bool equals(Json* other){
                return other->getType() == JsonType::JS_NULL;
            }

            std::string toString(){
                return "null";
            }
        };

        class JsonTrue: public Json{
        public:
            JsonTrue(): Json(JsonType::JS_TRUE){}
            bool equals(Json* other){
                return other->getType() == JsonType::JS_TRUE;
            }

            std::string toString(){
                return "true";
            }
        };

        class JsonFalse: public Json{
        public:
            JsonFalse(): Json(JsonType::JS_FALSE){}
            bool equals(Json* other){
                return other->getType() == JsonType::JS_FALSE;
            }

            std::string toString(){
                return "false";
            }
        };

        static JsonNull JSON_NULL;
        static JsonTrue JSON_TRUE;
        static JsonFalse JSON_FALSE;
    }
}

#endif