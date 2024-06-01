# VMFlex - a custom Virtual Machine implementation on multi-register CPUS

#### Authors: Soham Nandy (VM), Harmit Singh(Compiler)

### Execution Details:
```
// Compiling .cpp file
cd CompFlex
make clean
make all
// insert code in code.cpp
make run


// Passing throught VM
cd ../virtualmachine
cp ../CompFlex/code.txt code.tac
make clean
make 
./main code.tac > log.txt   

```


