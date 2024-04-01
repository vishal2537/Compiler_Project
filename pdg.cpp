#include "llvm/Pass.h" // Header files for LLVM Pass infrastructure
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <llvm/Demangle/Demangle.h> // Header for demangling function names
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include <string> // Necessary C++ headers
#include <vector>
#include <list>
#include <map>
using namespace llvm; // Using LLVM namespace

namespace
{
    // Definition of PDG pass
    struct PDG : public ModulePass
    {
        static char ID;                                   // Unique Pass identifier
        std::map<Function *, int> vis;                    // Map to track visited functions
        std::map<Function *, std::set<Function *>> edges; // Map to store edges between functions
        std::map<Function *, int> IDs;                    // Map to assign IDs to functions
        std::queue<Function *> q;                         // Queue for BFS traversal
        int id = 1;                                       // Initial ID

        PDG() : ModulePass(ID) {} // Constructor for PDG pass

        // Function to run on each module
        bool runOnModule(Module &M) override
        {
            // Iterate through each function in the module
            for (auto &F : M)
            {
                // Iterate through each basic block in the function
                for (auto &BB : F)
                {
                    // Initialize visibility and IDs for each function
                    vis[&F] = 0;
                    IDs[&F] = id++;

                    // Iterate through each instruction in the basic block
                    for (auto &I : BB)
                    {
                        // Check if the instruction is a call instruction
                        if (auto *callInst = dyn_cast<CallInst>(&I))
                        {
                            // Get the called function
                            if (auto *calledFunction = callInst->getCalledFunction())
                            {
                                // Add an edge between the current function and the called function
                                edges[&F].insert(calledFunction);

                                // If the current function is in the "Secure" section, add it to the queue
                                if (F.getSection() == "Secure")
                                {
                                    q.push(&F);
                                }
                            }
                        }
                    }
                }
            }

            // Print secured functions
            errs() << "\n****************************************************************************************\n";
            errs() << "Secured Function : (< Function_name , Function_id >)\n";
            while (!q.empty())
            {
                auto *f = q.front();
                q.pop();
                vis[f] = 1;
                errs() << " < " << demangle(f->getName().str()) << " , " << IDs[f] << " > "
                       << "\n";
                // Traverse edges
                for (auto &ff : edges[f])
                {
                    // If the function is not visited and has a valid ID, add it to the queue
                    if (vis[ff] == 0 && IDs[ff] != 0)
                    {
                        q.push(ff);
                    }
                }
            }

            // Print non-secured functions
            errs() << "\n****************************************************************************************\n";
            errs() << "Non-Secured Function : (< Function_name , Function_id >) \n";
            for (auto it : vis)
            {
                if (it.second == 0 && IDs[it.first] != 0)
                {
                    errs() << " < " << demangle(it.first->getName().str()) << " , " << IDs[it.first] << " > "
                           << "\n";
                }
            }

            // Print the graph representation of the module
            errs() << "\n****************************************************************************************\n";
            errs() << "Graph : (< Function_name , Function_id >) \n";
            for (auto &e : edges)
            {
                errs() << " < " << demangle(e.first->getName().str()) << " , " << IDs[e.first] << " > "
                       << " : ";

                // Print edges
                for (auto s : e.second)
                {
                    errs() << " < " << demangle(s->getName().str()) << " , " << IDs[s] << " > , ";
                }
                errs() << "\n";
            }

            // Return false to indicate that the module was not modified
            errs() << "\n****************************************************************************************\n";
            return false;
        }
    };
}

char PDG::ID = 0; // Initialize static member ID

// Register the PDG pass with LLVM Pass Manager
static RegisterPass<PDG> X("pdg", "PDG Pass");