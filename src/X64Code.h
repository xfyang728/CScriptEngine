#include <iostream>
#include <vector>
#include <map>
#include "Value.h"
#include <string>
#include "codegen.h"
#include "Code.h"

class X64Code : public Code{
public:
	X64Code();
	~X64Code();
	enum BinaryOps { Add, Sub, Mul, SDiv };
	cse::Value* Create(BinaryOps instr, cse::Value* lhs, cse::Value* rhs, std::string str, CodeGenBlock* block);
	void formatCode();
};