#include "Base64.h"

namespace Silhouette{
    namespace Codec{
        static const std::string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

        static inline bool isBase64(char c){
            return (isalnum(c) || (c == '+') || (c == '/'));
        }

        std::string base64encode(char* bytes, size_t size){
            std::string ret;
            int i = 0;
            int j = 0;
            unsigned char array3[3];
            unsigned char array4[3];

            while(size--){
                array3[i++] = (unsigned char) *(bytes++);
                if(i == 3){
                    array4[0] = (unsigned char) ((array3[0] & 0xFC) >> 2);
                    array4[1] = (unsigned char) (((array3[0] & 0x03) << 4) + ((array3[1] & 0xF0) >> 4));
                    array4[2] = (unsigned char) (((array3[1] & 0x0F) << 2) + ((array3[2] & 0xC0) >> 6));
                    array4[3] = (unsigned char) (array3[2] & 0x3F);

                    for(i = 0; i < 4; i++){
                        ret += base64[array4[i]];
                    }

                    i = 0;
                }
            }

            if(i){
                for(j = i; j < 3; j++){
                    array3[j] = '\0';
                }
                array4[0] = (unsigned char) ((array3[0] & 0xFC) >> 2);
                array4[1] = (unsigned char) (((array3[0] & 0x03) << 4) + ((array3[1] & 0xF0) >> 4));
                array4[2] = (unsigned char) (((array3[1] & 0x0F) << 2) + ((array3[2] & 0xC0) >> 6));
                array4[3] = (unsigned char) (array3[2] & 0x3F);

                for(j = 0; j < i + 1; j++){
                    ret += base64[array4[j]];
                }

                while(i++ < 3){
                    ret += '=';
                }
            }

            return ret;
        }

        std::string base64decode(std::string data){
            int len = (int) data.size();
            int i = 0;
            int j = 0;
            int in = 0;
            unsigned char array4[4];
            unsigned char array3[3];
            std::string ret;

            while(len-- && data[in] != '=' && isBase64(data[in])){
                array4[i++] = (unsigned char) data[in];
                in++;
                if(i == 4){
                    for(i = 0; i < 4; i++){
                        array4[i] = (unsigned char) base64.find(array4[i]);
                    }

                    array3[0] = (unsigned char) ((array4[0] << 2) + ((array4[1] & 0x30) >> 4));
                    array3[1] = (unsigned char) (((array4[1] & 0xF) << 4) + ((array4[2] & 0x3C) >> 2));
                    array3[2] = (unsigned char) (((array4[2] & 0x3) << 6) + array4[3]);

                    for(i = 0; i < 3; i++){
                        ret += array3[i];
                    }
                    i = 0;
                }
            }

            if(i){
                for(j = i; j < 4; j++){
                    array4[j] = 0;
                }

                for(j = 0; j < 4; j++){
                    array4[j] = (unsigned char) base64.find(array4[j]);
                }

                array3[0] = (unsigned char) ((array4[0] << 2) + ((array4[1] & 0x3) >> 4));
                array3[1] = (unsigned char) (((array4[1] & 0xF) << 4) + ((array4[2] & 0x3C) >> 2));
                array3[2] = (unsigned char) (((array4[2] & 0x3) << 6) + array4[3]);

                for(j = 0; j < i - 1; j++){
                    ret += array3[j];
                }
            }

            return ret;
        }
    }
}