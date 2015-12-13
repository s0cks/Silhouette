#include <jni.h>
#include <stdlib.h>
#include <iostream>
#include <core/json/JsonParser.h>
#include <core/json/JsonObject.h>
#include <core/codec/Base64.h>

/*
    JavaVMOption* options = new JavaVMOption[1];
    options[0].optionString = (char*) "-Djava.class.path=.";
    JavaVMInitArgs jvm_args;
    jvm_args.version = JNI_VERSION_1_6;
    jvm_args.nOptions = 1;
    jvm_args.options = options;
    JavaVM* jvm;
    JNIEnv* env;
    jint rc = JNI_CreateJavaVM(&jvm, (void**) &env, &jvm_args);
    delete options;
    if(rc != JNI_OK){
        exit(EXIT_FAILURE);
    }
    jint version = env->GetVersion();
    std::cout << "JVM Loaded Version: " << ((version >> 16) & 0x0F) << "." << (version & 0x0F) << std::endl;
    jvm->DestroyJavaVM();
 */

using namespace Silhouette::Json;

int main(int argc, char** argv){
    JsonObject* doc = (JsonObject*) JsonParser::parse("{\"Hello\":\"World\"}");
    std::cout << doc->get("Hello")->toString() << std::endl;
    std::cout << "Hello World == " << Silhouette::Codec::base64encode("Hello World") << std::endl;
    std::cout << "SGVsbG8gV29ybGQ= == " << Silhouette::Codec::base64decode("SGVsbG8gV29ybGQ=") << std::endl;
    return 0;
}