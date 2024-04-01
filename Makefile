all :
	clang -S -emit-llvm input.c -o input.ll
	clang++ -shared -fPIC pdg.cpp -o input.so `llvm-config --cxxflags --ldflags --libs`
	opt -enable-new-pm=0 -load ./input.so -pdg < input.ll > /dev/null