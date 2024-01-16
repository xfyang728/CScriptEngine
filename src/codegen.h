#ifndef CSE_CODEGEN_H
#define CSE_CODEGEN_H

#include <stack>
#include <typeinfo>
#include <map>
#include "../Value.h"
#include <string>
//#include <llvm/IR/Module.h>
//#include <llvm/IR/Function.h>
//#include <llvm/IR/Type.h>
//#include <llvm/IR/DerivedTypes.h>
//#include <llvm/IR/LLVMContext.h>
//#include <llvm/IR/LegacyPassManager.h>
//#include <llvm/IR/Instructions.h>
//#include <llvm/IR/CallingConv.h>
//#include <llvm/IR/IRPrintingPasses.h>
//#include <llvm/IR/IRBuilder.h>
//#include <llvm/Bitcode/BitstreamReader.h>
//#include <llvm/Bitcode/BitstreamWriter.h>
//#include <llvm/Support/TargetSelect.h>
//#include <llvm/ExecutionEngine/ExecutionEngine.h>
//#include <llvm/ExecutionEngine/MCJIT.h>
//#include <llvm/ExecutionEngine/GenericValue.h>
//#include <llvm/Support/raw_ostream.h>
//
#include "Code.h"
using namespace cse;

class NBlock;

//static LLVMContext MyContext;

class CodeGenBlock {
public:
    //BasicBlock *block;
    Value *returnValue;
    std::map<std::string, Value*> locals;
};

class CodeGenContext {
    std::stack<CodeGenBlock *> blocks;
    //Function *mainFunction;
    Code* m_Code;

public:
    //Module *module;
    CodeGenContext();// { module = new Module("main", MyContext); }
    
    void generateCode(NBlock& root);
    void runCode();
    std::map<std::string, Value*>& locals() { return blocks.top()->locals; }
    //BasicBlock *currentBlock() { return blocks.top()->block; }
    //void pushBlock(BasicBlock *block) { blocks.push(new CodeGenBlock()); blocks.top()->returnValue = NULL; blocks.top()->block = block; }
    void popBlock() { CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; }
    void setCurrentReturnValue(Value *value) { blocks.top()->returnValue = value; }
    Value* getCurrentReturnValue() { return blocks.top()->returnValue; }
};

#endif // CSE_CODEGEN_H
