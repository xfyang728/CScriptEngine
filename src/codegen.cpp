#include "flex_bison/node.h"
#include "codegen.h"
#include "flex_bison/parser.hpp"
#include "X64Code.h"

using namespace std;

string strBuff = "";
char buff[] =
{
	0xb8, 0x25, 0x00, 0x00, 0x00,   // mov  eax, 0x25
	0xc3                     // int3
};
CodeGenContext::CodeGenContext()
{
	m_Code = new X64Code();
}

/* Compile the AST into a module */
void CodeGenContext::generateCode(NBlock& root)
{
	std::cout << "Generating code...\n";

	///* Create the top level interpreter function to call as entry */
	//vector<Type*> argTypes;
	//FunctionType *ftype = FunctionType::get(Type::getVoidTy(MyContext), makeArrayRef(argTypes), false);
	//mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "main", module);
	//BasicBlock *bblock = BasicBlock::Create(MyContext, "entry", mainFunction, 0);

	/* Push a new variable/block context */
	//pushBlock(bblock);
	root.codeGen(*this); /* emit bytecode for the toplevel block */
	//ReturnInst::Create(MyContext, bblock);
	//popBlock();

	/* Print the bytecode in a human-readable format
	   to see if our program compiled properly
	 */
	std::cout << "Code is generated.\n";
	//// module->dump();

	//legacy::PassManager pm;
	//pm.add(createPrintModulePass(outs()));
	//pm.run(*module);
}

/* Executes the AST by running the main function */
void CodeGenContext::runCode() {
	std::cout << "Running code...\n";
	//ExecutionEngine *ee = EngineBuilder( unique_ptr<Module>(module) ).create();
	//ee->finalizeObject();
	//vector<GenericValue> noargs;
	//GenericValue v = ee->runFunction(mainFunction, noargs);
	std::cout << "Code was run.\n";
	//return v;

	int length = strBuff.size();
	if (length < 6) {
		length = 6;
	}
	//char* buff = new char[length];
	m_Code->AddCode(buff);

	int res = 0;
	int* funaddr = (int*)buff;
	//int* funaddr = m_Code->m_MemBase;
	typedef int (*__stdcall MCodeFun)(int p1, int p2, int p3);
	MCodeFun f = (MCodeFun)funaddr;
	res = f(10, 15, 25);
	printf("eax = 0x%x\nres = %d\n", res, res);

}

///* Returns an LLVM type based on the identifier */
//static Type *typeOf(const NIdentifier& type) 
//{
//	if (type.name.compare("int") == 0) {
//		return Type::getInt64Ty(MyContext);
//	}
//	else if (type.name.compare("double") == 0) {
//		return Type::getDoubleTy(MyContext);
//	}
//	return Type::getVoidTy(MyContext);
//}

/* -- Code Generation -- */

Value* NInteger::codeGen(CodeGenContext& context)
{
	std::cout << "Creating integer: " << value << endl;
	//return ConstantInt::get(Type::getInt64Ty(MyContext), value, true);
	return 0;
}

Value* NDouble::codeGen(CodeGenContext& context)
{
	std::cout << "Creating double: " << value << endl;
	//return ConstantFP::get(Type::getDoubleTy(MyContext), value);
	return 0;
}

Value* NIdentifier::codeGen(CodeGenContext& context)
{
	std::cout << "Creating identifier reference: " << name << endl;
	//if (context.locals().find(name) == context.locals().end()) {
	//	std::cerr << "undeclared variable " << name << endl;
	//	return NULL;
	//}
	//return new LoadInst(context.locals()[name], "", false, context.currentBlock());
	return 0;
}

Value* NMethodCall::codeGen(CodeGenContext& context)
{
	//Function *function = context.module->getFunction(id.name.c_str());
	//if (function == NULL) {
	//	std::cerr << "no such function " << id.name << endl;
	//}
	//std::vector<Value*> args;
	//ExpressionList::const_iterator it;
	//for (it = arguments.begin(); it != arguments.end(); it++) {
	//	args.push_back((**it).codeGen(context));
	//}
	//CallInst *call = CallInst::Create(function, makeArrayRef(args), "", context.currentBlock());
	std::cout << "Creating method call: " << id.name << endl;
	//return call;
	return 0;
}

Value* NBinaryOperator::codeGen(CodeGenContext& context)
{
	std::cout << "Creating binary operation " << op << endl;
	X64Code::BinaryOps instr;
	switch (op) {
	case TPLUS: 	instr = X64Code::Add; goto math;
	case TMINUS: 	instr = X64Code::Sub; goto math;
	case TMUL: 		instr = X64Code::Mul; goto math;
	case TDIV: 		instr = X64Code::SDiv; goto math;

		/* TODO comparison */
	}

	return NULL;
math:
	//return X64Code::Create(instr, lhs.codeGen(context), rhs.codeGen(context), "", context.currentBlock());
	return NULL;
}

Value* NAssignment::codeGen(CodeGenContext& context)
{
	std::cout << "Creating assignment for " << lhs.name << endl;
	//if (context.locals().find(lhs.name) == context.locals().end()) {
	//	std::cerr << "undeclared variable " << lhs.name << endl;
	//	return NULL;
	//}
	//return new StoreInst(rhs.codeGen(context), context.locals()[lhs.name], false, context.currentBlock());
	return 0;
}

Value* NBlock::codeGen(CodeGenContext& context)
{
	StatementList::const_iterator it;
	Value* last = NULL;
	for (it = statements.begin(); it != statements.end(); it++) {
		std::cout << "Generating code for " << typeid(**it).name() << endl;
		last = (**it).codeGen(context);
	}
	std::cout << "Creating block" << endl;
	return last;
}

Value* NExpressionStatement::codeGen(CodeGenContext& context)
{
	std::cout << "Generating code for " << typeid(expression).name() << endl;
	return expression.codeGen(context);
}

Value* NReturnStatement::codeGen(CodeGenContext& context)
{
	std::cout << "Generating return code for " << typeid(expression).name() << endl;
	Value* returnValue = expression.codeGen(context);
	//context.setCurrentReturnValue(returnValue);
	strBuff.append("c3");
	return returnValue;
}

Value* NVariableDeclaration::codeGen(CodeGenContext& context)
{
	std::cout << "Creating variable declaration " << type.name << " " << id.name << endl;
	//AllocaInst *alloc = new AllocaInst(typeOf(type), id.name.c_str(), context.currentBlock());
	//Value* alloc = NULL;
	//context.locals()[id.name] = alloc;
	//if (assignmentExpr != NULL) {
	//	NAssignment assn(id, *assignmentExpr);
	//	assn.codeGen(context);
	//}
	//return alloc;
	strBuff.append("b825000000");
	return 0;
}

Value* NExternDeclaration::codeGen(CodeGenContext& context)
{
	//vector<Type*> argTypes;
	//VariableList::const_iterator it;
	//for (it = arguments.begin(); it != arguments.end(); it++) {
	//    argTypes.push_back(typeOf((**it).type));
	//}
	//FunctionType *ftype = FunctionType::get(typeOf(type), makeArrayRef(argTypes), false);
	//Function *function = Function::Create(ftype, GlobalValue::ExternalLinkage, id.name.c_str(), context.module);
	//return function;
	return 0;
}

Value* NFunctionDeclaration::codeGen(CodeGenContext& context)
{
	//vector<Type*> argTypes;
	VariableList::const_iterator it;
	//for (it = arguments.begin(); it != arguments.end(); it++) {
	//	argTypes.push_back(typeOf((**it).type));
	//}
	//FunctionType *ftype = FunctionType::get(typeOf(type), makeArrayRef(argTypes), false);
	//Function *function = Function::Create(ftype, GlobalValue::InternalLinkage, id.name.c_str(), context.module);
	//BasicBlock *bblock = BasicBlock::Create(MyContext, "entry", function, 0);

	//context.pushBlock(bblock);

	//Function::arg_iterator argsValues = function->arg_begin();
	Value* argumentValue;

	for (it = arguments.begin(); it != arguments.end(); it++) {
		(**it).codeGen(context);

		//argumentValue = &*argsValues++;
		//argumentValue->setName((*it)->id.name.c_str());
	//	StoreInst *inst = new StoreInst(argumentValue, context.locals()[(*it)->id.name], false, bblock);
	}

	block.codeGen(context);
	//ReturnInst::Create(MyContext, context.getCurrentReturnValue(), bblock);

	//context.popBlock();
	std::cout << "Creating function: " << id.name << endl;
	//return function;
	return 0;
}
/****************************************************************************
*   功能：将一个 ASCII 码表示的十六进制字符串转换成十六进制的字节串
*   输入参数：pAscii -- 转换后的 ASCII 码表示的十六进制字符串的首地址
*            pHex   -- 十六进制数字节串首地址
*            nLen   -- 要转换的 ASCII 码表示的十六进制字符串的长度（字节数）
*   输出参数：None
*   注：  要求输入的 ASCII 码表示的十六进制数的字符个数必须为偶数，除了是1 - 9 和 A(a) - F(f) 以外没有别的字符
****************************************************************************/
void AsciiToHex(unsigned char* pAscii, unsigned char* pHex, int nLen)
{
	if (nLen % 2)
		return;
	int nHexLen = nLen / 2;

	for (int i = 0; i < nHexLen; i++)
	{
		unsigned char Nibble[2];
		Nibble[0] = *pAscii++;
		Nibble[1] = *pAscii++;
		for (int j = 0; j < 2; j++)
		{
			if (Nibble[j] <= 'F' && Nibble[j] >= 'A')
				Nibble[j] = Nibble[j] - 'A' + 10;
			else if (Nibble[j] <= 'f' && Nibble[j] >= 'a')
				Nibble[j] = Nibble[j] - 'a' + 10;
			else if (Nibble[j] >= '0' && Nibble[j] <= '9')
				Nibble[j] = Nibble[j] - '0';
			else
				return;
		}   // for (int j = ...)
		pHex[i] = Nibble[0] << 4;   // Set the high nibble
		pHex[i] |= Nibble[1];   //Set the low nibble
	}   // for (int i = ...)
}