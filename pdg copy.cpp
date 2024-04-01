#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <llvm/Demangle/Demangle.h>
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <string>
#include <vector>
#include <list>
#include <map>
using namespace llvm;

namespace
{

    struct PDG : public ModulePass
    {
        static char ID;
        std::map<Function *, int> vis; 
        std::map<Function *, std::set<Function *>> edges;
        std::map<Function *, int> IDs;
        std::queue<Function *> q;
        int id = 1;
        PDG() : ModulePass(ID) {}

        bool runOnModule(Module &M) override
        {
            for (auto &F : M)
            {
                for (auto &BB : F)
                {
                    vis[&F] = 0;
                    IDs[&F] = id++;
                    for (auto &I : BB)
                    {
                        if (auto *callInst = dyn_cast<CallInst>(&I))
                        {
                            if (auto *calledFunction = callInst->getCalledFunction())
                            {
                                edges[&F].insert(calledFunction);
                                if (F.getSection() == "Secure")
                                {
                                    q.push(&F);
                                }
                            }
                        }
                    }
                }
            }

            errs() << "\n****************************************************************************************\n";
            errs() << "Secured Fuction : (< Function_name , Function_id >)\n";
            while (!q.empty())
            {
                auto *f = q.front();
                q.pop();
                vis[f] = 1;
                errs() << " < " << demangle(f->getName().str()) << " , " << IDs[f] << " > " << "\n";
                for (auto &ff : edges[f])
                {
                    if (vis[ff] == 0 && IDs[ff]!=0)
                    {
                        q.push(ff);
                    }
                }
            }

            errs() << "\n****************************************************************************************\n";
            errs() << "Non-Secured Fuction : (< Function_name , Function_id >) \n";
            for (auto it : vis)
            {
                if (it.second == 0 && IDs[it.first] != 0)
                {
                    errs() << " < "<< demangle(it.first->getName().str()) << " , " << IDs[it.first] << " > "<< "\n";
                }
            }

            errs() << "\n****************************************************************************************\n";
            errs() << "Graph : (< Function_name , Function_id >) \n";
            for (auto &e : edges)
            {
                errs() << " < " << demangle(e.first->getName().str())<<" , "<<IDs[e.first] << " > " << " : ";

                for (auto s : e.second)
                {
                    errs()<< " < " << demangle(s->getName().str()) << " , "<< IDs[s] << " > , "<< " ";
                }
                errs() << "\n";
            }

            errs() << "\n****************************************************************************************\n";
            return false;
        }
    };
}

char PDG::ID = 0;
static RegisterPass<PDG> X("pdg", "PDG Pass");
