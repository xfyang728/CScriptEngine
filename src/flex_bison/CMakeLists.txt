# CMakeList.txt: CScriptEngine 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)



# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("flex_bison")
add_definitions(-DYY_NO_UNISTD_H)

# 设置变量，下面的代码都可以用到
set(FLEX_BISON "tokens.cpp" "parser.hpp" "parser.cpp" "node.h")

add_library(${PROJECT_NAME} STATIC ${FLEX_BISON})

