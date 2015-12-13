#ifndef SILHOUETTE_JSONPARSER_H
#define SILHOUETTE_JSONPARSER_H

#include <string>
#include "JsonType.h"

namespace Silhouette{
    namespace Json{
        class JsonParser{
        private:
            std::string content;
            unsigned long pos;

            void skip(size_t len);
            bool isWhitespace(char c);
            char peek();
            char next();
            char nextReal();

            std::string parseName();
            Json* parseString();
            Json* parseNumber(char next);
            Json* parseObject();
            Json* parseArray();
        public:
            JsonParser(std::string content);
            Json* parse();

            static inline Json* parse(std::string str){
                JsonParser* parser = new JsonParser(str);
                Json* parsed = parser->parse();
                delete parser;
                return parsed;
            }
        };
    }
}

#endif