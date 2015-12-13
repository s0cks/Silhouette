#ifndef SILHOUETTE_BASE64_H
#define SILHOUETTE_BASE64_H

#include <string>

namespace Silhouette{
    namespace Codec{
        std::string base64encode(char* bytes, size_t len);
        std::string base64decode(std::string data);

        static inline std::string base64encode(std::string data){
            return base64encode((char*) data.c_str(), data.size());
        }
    }
}

#endif