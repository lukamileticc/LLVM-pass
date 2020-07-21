#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <string>
#include <vector>
#include <iostream>
using namespace std;

//biblioteke za LLVM
#include "llvm/IR/Value.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/FileSystem.h"

using namespace llvm;
using namespace llvm::legacy;

class ExprAST{
public:
	virtual Value* codegen() const = 0;
	virtual ~ExprAST(){
		
	};
};

class ConstantAST : public ExprAST{
public:
	ConstantAST(int x)
	:Val(x)
	{}
	Value* codegen() const;
private:
	int Val;
};
class VariableAST : public ExprAST{
public:
	VariableAST(string s)
	: Name(s)
	{}
	Value* codegen() const;
private:
	string Name;
};

class InnerExprAST : public ExprAST {
public:
	InnerExprAST(vector<ExprAST*> v)
	:Vec(v)
	{}
	InnerExprAST();
	InnerExprAST(ExprAST *v);
	InnerExprAST(ExprAST* v1,ExprAST* v2);
	InnerExprAST(ExprAST *v1,ExprAST *v2,ExprAST * v3);
	~InnerExprAST();
private:
	InnerExprAST(const InnerExprAST&);
	InnerExprAST& operator=(const InnerExprAST&);
protected:
	vector<ExprAST*> Vec;
};
class AddAST : public InnerExprAST{
public:
	AddAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	Value* codegen() const;
};
class SubAST : public InnerExprAST{
public:
	SubAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	Value* codegen() const;
};
class MulAST : public InnerExprAST{
public:
	MulAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	Value* codegen() const;
};
class DivAST : public InnerExprAST{
public:
	DivAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	Value* codegen() const;
};
class SeqAST : public InnerExprAST {
 public:
  SeqAST(ExprAST* l, ExprAST* r)
    :InnerExprAST(l, r)
    {}
  Value* codegen() const;
};
class CallAST : public InnerExprAST{
public:
	CallAST(string s,vector<ExprAST*> v)
	:InnerExprAST(v),CallName(s)
	{}
	Value* codegen() const;
private:
	string CallName;
};

class IfAST : public InnerExprAST {
public:
	IfAST(ExprAST *uslov,ExprAST *e1,ExprAST *e2)
	:InnerExprAST(uslov,e1,e2)
	{}
	
	Value* codegen() const;
};
class AssignAST : public InnerExprAST{
public:
	AssignAST(ExprAST *e,const string& n)
	:InnerExprAST(e),Name(n)
	{}
	Value* codegen() const;
private:
	string Name;
};
class VarAST : public InnerExprAST{
public:
	VarAST(vector<pair<string, ExprAST*> > v)
    : _v(v)
  {}
  Value* codegen() const;
private:
	vector<pair<string, ExprAST*> > _v;
};
// prototip i funkcija
class PrototypeAST {
public:
	PrototypeAST(string s,vector<string> v)
	:Name(s),Args(v)
	{
	//	cout << "napravio sam prototip" << Name << endl;;
	}
	Function* codegen() const;
	string getName() const{
		return Name;
	}
private:
	string Name;
	vector<string> Args;
};
class FunctionAST {
public:
	FunctionAST(PrototypeAST *p,ExprAST* e)
	:Proto(p),Body(e){
	//	cout << "napravio sam telo od " << Proto->getName();
	}
	Function* codegen() const;
private:
	PrototypeAST *Proto;
	ExprAST *Body;
};



AllocaInst* CreateEntryBlockAlloca(Function *TheFunction, const string &VarName);
void IntializeModuleAndPassManager();
void DeleteModuleAndPassManager();

#endif
