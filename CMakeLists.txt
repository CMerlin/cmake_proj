project(ZLToolKit)
cmake_minimum_required(VERSION 2.8)

#加载自定义模块
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
#设置库文件路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
#设置可执行程序路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#设置子目录
set(SUB_DIR_LIST "Network" "Poller" "Thread" "Util")

#设置库文件的安装路径
set(INSTALL_PATH_LIB ${PROJECT_SOURCE_DIR}/lib/local_lib)
set(INSTALL_PATH_INCLUDE ${PROJECT_SOURCE_DIR}/include/local_include)
message("INSTALL_PATH_LIB=" ${INSTALL_PATH_LIB})
message("INSTALL_PATH_INCLUDE=" ${INSTALL_PATH_INCLUDE})

foreach(SUB_DIR ${SUB_DIR_LIST})
    #遍历源文件
    aux_source_directory(src/${SUB_DIR} SRC_LIST)
    #安装头文件至系统目录
	message("SUB_DIR=" ${SUB_DIR})
    install(DIRECTORY src/${SUB_DIR} DESTINATION ${INSTALL_PATH_INCLUDE} FILES_MATCHING PATTERN "*.h")
	#install(DIRECTORY src/${SUB_DIR} DESTINATION ${INSTALL_PATH_INCLUDE})
endforeach()

#set(LINK_LIB_LIST WS2_32 Iphlpapi shlwapi)
set(LINK_LIB_LIST ${PROJECT_SOURCE_DIR}/lib)

#打印库文件
message(STATUS "将链接依赖库:${LINK_LIB_LIST}")
#引用头文件路径
include_directories(${PROJECT_SOURCE_DIR}/src)
#使能c++11
add_compile_options(-std=c++11)

if(NOT WIN32)
    add_compile_options(-Wno-deprecated-declarations)
    add_compile_options(-Wno-predefined-identifier-outside-function)
endif()

message("-----42")
#编译动态库
if(NOT IOS AND NOT ANDROID)
    add_library(${CMAKE_PROJECT_NAME}_shared SHARED ${SRC_LIST})
    target_link_libraries(${CMAKE_PROJECT_NAME}_shared ${LINK_LIB_LIST})
    set_target_properties(${CMAKE_PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")
    install(TARGETS ${CMAKE_PROJECT_NAME}_shared  ARCHIVE DESTINATION ${INSTALL_PATH_LIB} LIBRARY DESTINATION ${INSTALL_PATH_LIB})
endif()
message("-----50 SRC_LIST=" ${SRC_LIST})

#编译静态库
add_library(${CMAKE_PROJECT_NAME}_static STATIC ${SRC_LIST})
set_target_properties(${CMAKE_PROJECT_NAME}_static PROPERTIES OUTPUT_NAME "${CMAKE_PROJECT_NAME}")
#安装静态库至系统目录
install(TARGETS ${CMAKE_PROJECT_NAME}_static ARCHIVE DESTINATION ${INSTALL_PATH_LIB})

#测试程序
if(NOT IOS)
    add_subdirectory(tests)
endif()
























