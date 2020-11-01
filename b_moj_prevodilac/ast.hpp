#ifndef __AST_HPP__
#define __AST_HPP__ 1

#include <string>
#include <vector>
using namespace std;


class ExprAST{
public:
	virtual void codegen() const = 0;
	virtual ~ExprAST(){
		
	};
};

class ConstantAST : public ExprAST{
public:
	ConstantAST(int x)
	:Val(x)
	{}
	void codegen() const;
private:
	int Val;
};
class VariableAST : public ExprAST{
public:
	VariableAST(string s)
	: Name(s)
	{}
	void codegen() const;
private:
	string Name;
};

class InnerExprAST : public ExprAST {
public:
	InnerExprAST(vector<ExprAST*> v)
	:Vec(v)
	{}
	InnerExprAST(ExprAST* v1,ExprAST* v2);
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
	void codegen() const;
};
class SubAST : public InnerExprAST{
public:
	SubAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	void codegen() const;
};
class MulAST : public InnerExprAST{
public:
	MulAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	void codegen() const;
};
class DivAST : public InnerExprAST{
public:
	DivAST(ExprAST *v1,ExprAST *v2)
	: InnerExprAST(v1,v2)
	{}
	void codegen() const;
};
class CallAST : public InnerExprAST{
public:
	CallAST(string s,vector<ExprAST*> v)
	:InnerExprAST(v),CallName(s)
	{}
	void codegen() const;
private:
	string CallName;
};

// prototip i funkcija
class PrototypeAST {
public:
	PrototypeAST(string s,vector<string> v)
	:Name(s),Args(v)
	{}
	void codegen() const;
	string getName() const{
		return Name;
	}
private:
	string Name;
	vector<string> Args;
};
class FunctionAST : public InnerExprAST {
public:
	FunctionAST(PrototypeAST *p,vector<ExprAST*> v1)
	:InnerExprAST(v1), Proto(p)
	{}
	void codegen() const;
private:
	PrototypeAST *Proto;
};


















#endif
