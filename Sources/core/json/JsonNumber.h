#ifndef SILHOUETTE_JSONNUMBER_H
#define SILHOUETTE_JSONNUMBER_H

#include "JsonType.h"
#include <iostream>

namespace Silhouette{
    namespace Json{
        class JsonNumber : public Json{
        private:
            union{
                int integer;
                double real;
            } as;
        public:
            JsonNumber(int data);
            JsonNumber(double data);

            int asInteger(){
                if(this->getType() == JsonType::JS_INTEGER){
                    return this->as.integer;
                }

                std::cerr << "Not an integer" << std::endl;
                exit(1);
            }

            double asReal(){
                if(this->getType() == JsonType::JS_REAL){
                    return this->as.real;
                }

                std::cerr << "Not a real" << std::endl;
                exit(1);
            }

            bool equals(Json* other);
            bool equals(int x);
            bool equals(double x);
            std::string toString();
        };
    }
}

#endif