#CMakeLists.txt --- 
# 
# Description: CMake编译、运行程序模板。
# Author: Hongyi Wu(吴鸿毅)
# Email: wuhongyi@qq.com 
# Created: 六 2月 22 19:39:08 2014 (+0800)
# Last-Updated: 四 1月  3 16:52:11 2019 (+0800)
#           By: Hongyi Wu(吴鸿毅)
#     Update #: 116
# URL: http://wuhongyi.cn 

#在当前目录打开终端，输入        cmake .[Enter]   make
#或在build目录下打开终端，输入cmake ..[Enter]   make
#----------------------------------------------------------------------------
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
set(PROJ_NAME pku)
project(${PROJ_NAME})
set(CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated") #支持最新c++11
#c++0x是新的C++意思。而-Wno-deprecated是表示 no-deprecated这类警告忽略。
SET(CMAKE_BUILD_TYPE Debug) #编译调试版本
#----------------------------------------------------------------------------
# Find ROOT (required package)
#find_package(ROOT REQUIRED)
find_package( ROOT COMPONENTS ASImage EG FFTW FitPanel Ged Geom Gui GuiBld GuiHtml GX11 GX11TTF Hbook Hist Html MathMore Minuit Minuit2 MLP Proof RGL RooFit RooFitCore Smatrix Spectrum Table TMVA TreePlayer TreeViewer )#COMPONENTS可选 ，REQUIRED COMPONENTS必须有
#----------------------------------------------------------------------------
include_directories(${PROJECT_SOURCE_DIR}/include  ${ROOT_INCLUDE_DIRS})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*)
file(GLOB libs ${PROJECT_SOURCE_DIR}/lib/* )
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build) #生成可执行文件放在bin文件夹中


set(headerfiles ${PROJECT_SOURCE_DIR}/include/*.hh )
set(linkdefs ${PROJECT_SOURCE_DIR}/include/ggLinkDef.h )

add_custom_command(OUTPUT ggDict.cxx 
                   PRE_BUILD
                   COMMAND rootcint -f  ggDict.cxx -c  ${headerfiles} ${linkdefs} )#COMMENT echo "executing a command -> rootcint "
add_library(ggClassDict SHARED ggDict.cxx)#生成动态链接库
#----------------------------------------------------------------------------
add_executable(${PROJ_NAME} main.cc ${sources} ${headers}) 
target_link_libraries(${PROJ_NAME} ggClassDict ${libs} ${ROOT_LIBRARIES} )
#----------------------------------------------------------------------------
set(CopyFile
    rootlogon.C rootlogoff.C
  )

foreach(copyfile ${CopyFile})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${copyfile}
    ${PROJECT_SOURCE_DIR}/build/${copyfile}
    COPYONLY
    )
endforeach()

###################################
