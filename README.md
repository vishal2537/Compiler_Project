
---
## Project 
### Design a compiler pass (LLVM) to take a C++ application as input, generate the program dependence graph (function level) for a given program, and partition the program into secure or not secure partitions. Also, print the ID of the desired function. You can use numbers to represent the function ID.
---
### Installing Clang and Running PDG Analysis

This guide provides instructions for installing Clang and running Program Dependence Graph (PDG) analysis using the provided command.

### Installation of Clang

**In Linux:**
   
   You can install Clang on Linux using the package manager of your distribution. For example, on Ubuntu or Debian-based systems, you can use:

   ```bash
   sudo apt-get install clang
   ```

### Building PDG Analysis Tool

1. Clone the PDG analysis tool repository from its source.

   ```bash
   git clone https://github.com/vishal2537/Compiler_Project.git
   ```

2. Navigate to the directory containing the source code.

   ```bash
   cd Compiler_Project
   ```

3. Create .ll file from c/cpp file 

   ```bash
	clang -S -emit-llvm filename.c -o filename.ll
   ```

4. Build the PDG analysis tool.

   ```bash
   clang++ -shared -fPIC pdg.cpp -o input.so `llvm-config --cxxflags --ldflags --libs`
   ```

   This command compiles the PDG analysis tool into a shared library.

## Running PDG Analysis

Once you have installed Clang and built the PDG analysis tool, you can perform PDG analysis on your C/C++ code using the provided command.

```bash
clang -S -emit-llvm input.c -o input.ll
opt -enable-new-pm=0 -load ./input.so -pdg < input.ll > /dev/null
```

Replace `input.c` with the path to your C/C++ source file. This command generates LLVM IR code (`input.ll`) from the source file and performs PDG analysis using the PDG tool.

---


## Alternate way run the PDG Analysis
1. Clone the PDG analysis tool repository from its source.

   ```bash
   git clone https://github.com/vishal2537/Compiler_Project.git
   ```

2. Navigate to the directory containing the source code.
   ```bash
   cd Compiler_Project
   ```

3. Make input.cpp file for which you want to make PDG

   <!-- ```bash
	clang -S -emit-llvm filename.c -o filename.ll
   ``` -->

4. Run 

   ```bash
   make all
   ```
---

