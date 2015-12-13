cmake_minimum_required(VERSION 3.2)
project(Silhouette)

find_package(JNI)

include_directories(Sources)
include_directories(${JNI_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(Silhouette main.cc Sources/core/json/JsonType.h Sources/core/json/JsonNumber.h Sources/core/json/JsonNumber.cc Sources/core/json/JsonString.h Sources/core/json/JsonString.cc Sources/core/json/JsonObject.h Sources/core/json/JsonObject.cc Sources/core/json/JsonArray.h Sources/core/json/JsonArray.cc Sources/core/json/JsonParser.h Sources/core/json/JsonParser.cc Sources/core/codec/Base64.h Sources/core/codec/Base64.cc Sources/core/websocket/WebsocketConnection.h)
target_link_libraries(Silhouette ${JNI_LIBRARIES})