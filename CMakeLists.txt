# CMakeList.txt: CScriptEngine 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_EXE_LINKER_FLAGS "/NXCOMPAT:NO")

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CScriptEngine")
add_definitions(-DYY_NO_UNISTD_H)

# 设置变量，下面的代码都可以用到
set(FLEX_BISON_DIR src/flex_bison)
include_directories(${FLEX_BISON_DIR})
#set(FLEX_BISON "lex.yy.c" "calculator.tab.h" "calculator.tab.c" )


# 编译子文件夹的CMakeLists.txt
add_subdirectory(src/flex_bison)

# 将源代码添加到此项目的可执行文件。
add_executable (CScriptEngine "src/CScriptEngine.cpp" "src/CScriptEngine.h" "src/Value.h" "src/codegen.h" 
"src/codegen.cpp" "src/Code.h" "src/Code.cpp" "src/X64Code.h" "src/X64Code.cpp")
# target_include_directories(CScriptEngine PUBLIC ${FLEX_BISON_DIR})
# 链接操作
target_link_libraries(${PROJECT_NAME} flex_bison)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CScriptEngine PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
