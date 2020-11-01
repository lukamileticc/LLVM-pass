#include "ast.hpp"
#include <iostream>

using namespace std;

void ConstantAST::codegen() const{
	cout << "Generisem kod za konstanu: " <<
	Val << endl;
}
void VariableAST::codegen() const{
	//TODO
}
InnerExprAST::InnerExprAST(ExprAST* v1,ExprAST* v2){
	Vec.resize(0);
	Vec.push_back(v1);
	Vec.push_back(v2);
}
InnerExprAST::~InnerExprAST(){
	for(unsigned i = 0; i < Vec.size(); i++)
		delete Vec[i];
}
void AddAST::codegen() const{
	cout << "Generisem kod za zbir" << endl;
}
void SubAST::codegen() const{
	//TODO;
}
void MulAST::codegen() const{
	//TODO;
}
void DivAST::codegen() const{
	//TODO;
}
void CallAST::codegen() const{
	//TODO;
}
void PrototypeAST::codegen() const{
	cout << "Genersiem kod za prototip: " << Name << endl;
}
void FunctionAST::codegen() const{
	cout << "Generisem kod za funkciju: " <<
	Proto->getName() << endl;
}
