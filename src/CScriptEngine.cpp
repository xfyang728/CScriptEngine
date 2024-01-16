// CScriptEngine.cpp: 定义应用程序的入口点。
//

#include "CScriptEngine.h"
#include "flex_bison/node.h"
#include "codegen.h"

using namespace std; 

extern NBlock* programBlock;
extern int yyparse(); 
extern FILE* yyin;

int main()
{
	FILE* fp;
	fopen_s(&fp, "D:/MyCode/CScriptEngine/example.txt", "r");
	//std::cout<<fp;
	if (fp == NULL)
	{
		std::cout << "error";
	}
	yyin = fp;
	yyparse();
	std::cout << programBlock << std::endl;

	CodeGenContext context;
	context.generateCode(*programBlock);
	context.runCode();
	return 0;
}
