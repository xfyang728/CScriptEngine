.\bison.exe -d -o parser.cpp parser.y
.\flex.exe -o tokens.cpp tokens.l
xcopy tokens.cpp D:\MyCode\CScriptEngine\src\flex_bison /Y
xcopy parser.hpp D:\MyCode\CScriptEngine\src\flex_bison /Y
xcopy parser.cpp D:\MyCode\CScriptEngine\src\flex_bison /Y
