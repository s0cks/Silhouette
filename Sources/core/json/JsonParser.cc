#include <core/json/JsonParser.h>
#include "JsonString.h"
#include "JsonNumber.h"
#include "JsonArray.h"
#include "JsonObject.h"

namespace Silhouette{
    namespace Json{
        JsonParser::JsonParser(std::string content):
                pos(0){
            this->content = content;
        }

        bool JsonParser::isWhitespace(char c) {
            switch(c){
                case '\n':
                case '\t':
                case '\r':
                case ' ': return true;
                default: return false;
            }
        }

        char JsonParser::peek() {
            return this->content.at(this->pos);
        }

        char JsonParser::next() {
            if(this->pos >= this->content.size()){
                return '\0';
            }
            return this->content.at(this->pos++);
        }

        char JsonParser::nextReal() {
            char next;
            while(this->isWhitespace(next = this->next()));
            return next;
        }

        void JsonParser::skip(size_t len){
            for(size_t i = 0; i < len; i++){
                this->next();
            }
        }

        std::string JsonParser::parseName(){
            std::string name;
            char next;
            while((next = this->next()) != '"'){
                name += next;
            }
            return name;
        }

        Json* JsonParser::parseString(){
            std::string buffer;
            char next;
            while((next = this->next()) != '"'){
                switch(next){
                    case '\\':{
                        switch(next = this->next()){
                            case '\\': buffer += '\\'; break;
                            case 't': buffer += '\t'; break;
                            case 'n': buffer += '\n'; break;
                            default: buffer += next; break;
                        }
                        break;
                    }
                    default: buffer += next; break;
                }
            }
            return new JsonString(buffer);
        }

        Json* JsonParser::parseNumber(char next){
            std::string buffer;
            buffer += next;
            bool real = false;
            while((isdigit(next = this->peek())) || (next == '.' && !real)){
                if(next == '.'){
                    real = true;
                }
                buffer += next;
                this->next();
            }

            return new JsonNumber(real ? atof(buffer.c_str()) : atoi(buffer.c_str()));
        }

        Json* JsonParser::parseArray() {
            JsonArray* array = new JsonArray();
            char next;
            while((next = this->nextReal()) != '\0' || next != ']'){
                if(next == '"'){
                    array->push(this->parseString());
                } else if(isdigit(next)){
                    array->push(this->parseNumber(next));
                } else if(next == 't'){
                    this->skip(3);
                    array->push(&JSON_TRUE);
                } else if(next == 'f'){
                    this->skip(4);
                    array->push(&JSON_FALSE);
                } else if(next == 'n'){
                    this->skip(3);
                    array->push(&JSON_NULL);
                } else if(next == '['){
                    array->push(this->parseArray());
                } else if(next == '{'){
                    array->push(this->parseObject());
                } else if(next == ','){
                    continue;
                } else if(next == ']'){
                    break;
                }
            }
            return array;
        }

        Json* JsonParser::parseObject() {
            JsonObject* obj = new JsonObject();
            std::string name;
            char next;
            while(((next = this->nextReal()) != '}' || next != '\0')){
                switch(next){
                    case '"': name = this->parseName(); next = this->nextReal(); break;
                    case ':': next = this->nextReal(); break;
                    case ',': continue;
                    case '{': continue;
                    case '}': goto finished;
                    default: goto finished;
                }

                next = next == ':' ? this->nextReal() : next;

                if(next == '"'){
                    obj->set(name, this->parseString());
                } else if(isdigit(next)){
                    obj->set(name, this->parseNumber(next));
                } else if(next == 'n'){
                    this->skip(3);
                    obj->set(name, &JSON_NULL);
                } else if(next == 't'){
                    this->skip(3);
                    obj->set(name, &JSON_TRUE);
                } else if(next == 'f'){
                    this->skip(4);
                    obj->set(name, &JSON_FALSE);
                } else if(next == '{'){
                    obj->set(name, this->parseObject());
                } else if(next == '['){
                    obj->set(name, this->parseArray());
                }
            }

            finished:
                return obj;
        }

        Json* JsonParser::parse() {
            switch(this->peek()){
                case '[': return this->parseArray();
                case '{': return this->parseObject();
                default: return nullptr;
            }
        }
    }
}