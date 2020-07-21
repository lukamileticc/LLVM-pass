#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
	
	struct InstructionsCounterIR : public Function {
		
		static char ID;
		InstructionsCounterIR():FunctionPass(ID){}

		bool runOnFunction(Function &F) override{
			//pravimo mapu u kojoj cuvamo broj ponavljanja svake instrukcije 
			std::map<std::string,int> instructions_map;
			//ispisujemo hello jer smo usli u neku funkciju
			errs() << "Hello: ";
			errs() << F.getName() << endl;
			//iteriramo kroz sve funkcije u IR
			for(Function::iterator bb = F.begin(), e = F.end(); bb != e; bb++){

				//ispisujemo ime i velicinu svakog basic bloka 
				errs() << "BasicBlock name = " << bb->getName() << endl;
				errs() << "BasicBlock size = " << bb->size() << endl;
				//a sada iteriramo kroz svaki basic block
				for(BasicBlock::iterator i = bb->begin(), i1 = bb->end(); i != i1; i++){
					//u svakom basic bloku prolazimo kroz instrukcije i belizemo njigovo pojavljivanje u mapi
					if(instructions_map.find(i->getOpcodeName()) == instructions_map.end())
						instructions_map.find[i->getOpcodeName()] = 1; //postavljamo na 1 ako ga nema
					else
						instructions_map.find[i->getOpcodeName()]++; //inace uvecavamo za jedan

					errs() << "-----------------" << endl;

				}
			}

				std::map<std::string,int>::iterator begin = instructions_map.begin();
				std::map<std::string,int>::iterator end = instructions_map.end();
				while(begin != end){
					errs() << begin->first << " se pojavljuje: " << begin->end() << " puta." << endl;
					begin++;
				}

				instructions_map.clear();
		}
	};
}

char InstructionsCounterIR::ID = 0;
//registujemo nas prolaz u skup svih prolaza
//prvi argument: ime naseg prolaza
//drugi argument: sta nas prolaz radi
static RegisterPass<InstructionsCounterIR> X("InstructionsCounterIR","Count number of instructions in every block,function in IR");
