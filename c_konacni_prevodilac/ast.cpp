#include "ast.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;


LLVMContext TheContext;
IRBuilder<> Builder(TheContext);
Module* TheModule;
map<string, AllocaInst*> NamedValues;
legacy::FunctionPassManager *TheFPM;

Value*  ConstantAST::codegen() const{
	return ConstantInt::get( TheContext , APInt(32,Val));
}
Value* VariableAST::codegen() const{
	AllocaInst* tmp = NamedValues[Name];
	if(tmp == nullptr){
		cerr << "Nepostojeca promenljiva" <<  Name <<endl;
		exit(EXIT_FAILURE);
	}
	
	return Builder.CreateLoad(tmp,Name.c_str());
}
InnerExprAST::InnerExprAST(){
	Vec.resize(0);
}
InnerExprAST::InnerExprAST(ExprAST* v){
	Vec.resize(0);
	Vec.push_back(v);
}
InnerExprAST::InnerExprAST(ExprAST* v1,ExprAST* v2){
	Vec.resize(0);
	Vec.push_back(v1);
	Vec.push_back(v2);
}
InnerExprAST::InnerExprAST(ExprAST *v1,ExprAST *v2,ExprAST *v3){
	Vec.resize(0);
	Vec.push_back(v1);
	Vec.push_back(v2);
	Vec.push_back(v3);
}
InnerExprAST::~InnerExprAST(){
	for(unsigned i = 0; i < Vec.size(); i++)
		delete Vec[i];
}
Value* AddAST::codegen() const{
	Value *l = Vec[0]->codegen();
	Value *r = Vec[1]->codegen();
	if (l == nullptr || r == nullptr)
		return nullptr;
	return Builder.CreateAdd(l, r, "addtmp");
}
Value* SubAST::codegen() const{
	Value *l = Vec[0]->codegen();
	Value *r = Vec[1]->codegen();
	if (l == nullptr || r == nullptr)
		return nullptr;
	return Builder.CreateSub(l, r, "subtmp");
}
Value* MulAST::codegen() const{
	Value *l = Vec[0]->codegen();
	Value *r = Vec[1]->codegen();
	if (l == nullptr || r == nullptr)
		return nullptr;
	return Builder.CreateMul(l, r, "multmp");
}
Value* DivAST::codegen() const{
  Value *l = Vec[0]->codegen();
  Value *r = Vec[1]->codegen();
  if (l == nullptr || r == nullptr)
    return nullptr;
  return Builder.CreateFDiv(l, r, "divtmp");
}
Value* SeqAST::codegen() const {
  Value *l = Vec[0]->codegen();
  Value *r = Vec[1]->codegen();
  if (l == nullptr || r == nullptr)
    return nullptr;
  return r;
}
Value* AssignAST::codegen() const{
	
	AllocaInst *alloca = NamedValues[Name];
	
	if(alloca == nullptr){
		
		return nullptr;
	}
	cerr << Vec.size();
	Value * V = Vec[0]->codegen();
	if(V == nullptr)
		return nullptr;
	
	Builder.CreateStore(V,alloca);

	return V;
}
Value* VarAST::codegen() const {
	
	vector<AllocaInst*> oldAllocas;
	BasicBlock *BB = Builder.GetInsertBlock();
	Function *f = BB->getParent();
	
	for (unsigned i = 0; i < _v.size(); i++) {
		oldAllocas.push_back(NamedValues[_v[i].first]);
		AllocaInst *alloca = CreateEntryBlockAlloca(f, _v[i].first);
		NamedValues[_v[i].first] = alloca;
		Value *V = _v[i].second->codegen();
		
		if (V == nullptr)
			return nullptr;
		Builder.CreateStore(V, alloca);
	}
	

// 	for (unsigned i = 0; i < _v.size(); i++) {
// 		AllocaInst* alloca = oldAllocas[i];
// 		if (alloca == nullptr){
// 			NamedValues.erase(_v[i].first);
// 		}
// 		else
// 		NamedValues[_v[i].first] = alloca;
// 	}

  return NamedValues[_v[0].first];
}
Value* CallAST::codegen() const{
	Function* f = TheModule->getFunction(CallName);
	if(f == nullptr){
		cerr << "Neuspesan poziv fje " << CallName << endl;
		return nullptr;
	}
	
	if (f->arg_size() != Vec.size()) {
		cerr << "Poziv fje " << CallName << " sa neodgovarajucim brojem argumenata" << endl;
		exit(EXIT_FAILURE);
	}
	vector<Value*> v;
	for (unsigned i =0; i < Vec.size(); i++) {
		v.push_back(Vec[i]->codegen());
		if (v.back() == nullptr)
			return nullptr;
  }
  
  return Builder.CreateCall(f,v,"calltmp");
  
}
Value* IfAST::codegen() const{
	Value* CondV = Vec[0]->codegen();
	if (CondV == nullptr)
		return nullptr;
	
	Value *tmp = Builder.CreateFCmpONE(CondV, ConstantInt::get(TheContext, APInt(32,0)), "ifcond");
	 Function *f = Builder.GetInsertBlock()->getParent();
	BasicBlock *ThenBB = BasicBlock::Create(TheContext, "then", f);
	BasicBlock *ElseBB = BasicBlock::Create(TheContext, "else");
	BasicBlock *MergeBB = BasicBlock::Create(TheContext, "ifcont");
	Builder.CreateCondBr(tmp, ThenBB, ElseBB);
	
	
	 Builder.SetInsertPoint(ThenBB);
	Value* ThenV = Vec[1]->codegen();
	if (ThenV == nullptr)
		return nullptr;
	Builder.CreateBr(MergeBB);
	ThenBB = Builder.GetInsertBlock();
	
	 f->getBasicBlockList().push_back(ElseBB);
	Builder.SetInsertPoint(ElseBB);
	Value* ElseV = Vec[2]->codegen();
	if (ElseV == nullptr)
		return nullptr;
	Builder.CreateBr(MergeBB);
	ElseBB = Builder.GetInsertBlock();
	
	 f->getBasicBlockList().push_back(MergeBB);
	Builder.SetInsertPoint(MergeBB);
	PHINode *PHI = Builder.CreatePHI(Type::getInt32Ty(TheContext), 2, "iftmp");
	
	PHI->addIncoming(ThenV, ThenBB);
	PHI->addIncoming(ElseV, ElseBB);
  
	return PHI;
	
}
Function* PrototypeAST::codegen() const{
	vector<Type*> t;
  for (auto s : Args)
    t.push_back(Type::getInt32Ty(TheContext));

  FunctionType* ft = FunctionType::get(Type::getInt32Ty(TheContext), t, false);

  Function *f = Function::Create(ft, Function::ExternalLinkage, Name, TheModule);
  
  unsigned i = 0;
  for (auto &a : f->args())
    a.setName(Args[i++]);

  //cerr << "vratio sam generisan prototip" << endl;
  return f;
}
Function* FunctionAST::codegen() const{
	
	Function* f = TheModule->getFunction(Proto->getName());

  if (f == nullptr){
    f = Proto->codegen();
	
  }
 
  if (f == nullptr){
    return nullptr;
  }
  if (!f->empty()) {
    cerr << "Nije moguca redefinicija fje " << Proto->getName() << endl;
    return nullptr;
  }

  BasicBlock *BB = BasicBlock::Create(TheContext, "entry", f);
  Builder.SetInsertPoint(BB);

  NamedValues.clear();
  for (auto &a : f->args()){
	AllocaInst *alloca = CreateEntryBlockAlloca(f,a.getName());
	Builder.CreateStore(&a,alloca);
    NamedValues[a.getName()] = alloca;
  }
  
   
   Value* v = Body->codegen();
  if (v != nullptr) {
    Builder.CreateRet(v);

    verifyFunction(*f);
	
    return f;
  }
  f->eraseFromParent();
  cerr << "Problem while generating code for function " << Proto->getName() << endl;
  return nullptr;
}

AllocaInst* CreateEntryBlockAlloca(Function *TheFunction, const string &VarName) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(Type::getInt32Ty(TheContext), 0, VarName.c_str());
}
void IntializeModuleAndPassManager() {
  TheModule = new Module("myModul", TheContext);
  
  TheFPM = new legacy::FunctionPassManager(TheModule);
  // Do simple "peephole" optimizations and bit-twiddling optzns.
  TheFPM->add(createInstructionCombiningPass());
  // Reassociate expressions.
  TheFPM->add(createReassociatePass());
  // Eliminate Common SubExpressions.
  TheFPM->add(createNewGVNPass());
  // Simplify the control flow graph (deleting unreachable blocks, etc).
  TheFPM->add(createCFGSimplificationPass());
  TheFPM->add(createPromoteMemoryToRegisterPass());

  TheFPM->doInitialization();
}
void DeleteModuleAndPassManager() {
  delete TheFPM;
  delete TheModule;
}
