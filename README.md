# VMFlex - a custom Virtual Machine implementation on multi-register CPUS

#### Authors: 
  Soham Nandy (VM),  
  Harmit Singh(Compiler)

### Description:
VMFlex is a custom VM suitable for RISC-V architectures, built on top of [CompFlex](https://github.com/harmitsb2122/CompFlex), a custom C++ compiler. CompFlex has been developed on a subset of standard C++ grammar - handling advanced features of modern C++ like lamda functions.  

The Three Address Code (TAC) returned by the compiler has been assigned as an input to the VM, which is then preprocessed by removing dead codes and unused function declarations. The optimized code runs through a heuristic implementaton of a register allocation algorithm, which maps every datatype to a register allocation table and on oversizing assigns them to a memory location on stack. A seperate heap is maintained for dynamic allocation of pointers and custom datatypes. Function calls and recursions are maintained using a standard stack. The heap and stack grows in size from either ends of an assigned array - as it's designed for modern VMs. The final assembly generated has been well custom commented based on the input variables.


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

### Contributions:
  CompFlex - [Harmit Singh](https://github.com/harmitsb2122) - [Repo](https://github.com/harmitsb2122/CompFlex)  
  VM - [Soham Nandy](https://github.com/nandysoham) - [Repo](https://github.com/nandysoham/VMFlex)

### Detailed Slides - [Link](https://docs.google.com/presentation/d/1XmEQ1knqES5wHiDaaaTCQeY4rQ8XP7cEtB3llIzKWNM/edit?usp=sharing)

## Salient Features:



### Dead Code Removal
![image](https://github.com/nandysoham/VMFlex/assets/67374926/18e929e3-809e-4412-b17d-74536470e0f0)

Notice the function by the name soham(), has never been used however the TAC compiled the high level code. VM optimized code removes such dead pieces of code! This has been done smartly, such that no piece of working code shall be deleted.


### Formation of Basic Blocks
<img width="946" alt="image" src="https://github.com/nandysoham/VMFlex/assets/67374926/5a9651cc-9a5c-4a25-ab51-40a0bc42796f">

Parsing for dead code in a code block is not that easy! There can be condition based calls to a function, or calls to a function fn1 within a function fn2 howevr fn2 has never been called! Such complex behavioural analysis is possible by the aid of Basic Blocks and running Graph Connectivity Algorithms on top of the network


### Register Allocation by K Graph Coloring Heuristics
<img width="909" alt="image" src="https://github.com/nandysoham/VMFlex/assets/67374926/f66eb827-8ed6-45e9-ad5d-1d2cff49a601">


Risc V has total of 32 registers - even within which some are bound by the architecture. For a standard file of code, there can be 1000s of varibles - all of which cannot be simulatenously assigned a register. Thus a standard register allocation heuristic has been implemented. (courtesy: G. J. Chaitin. 1982. Register allocation &amp; spilling via graph coloring. SIGPLAN Not. 17, 6 (June 1982), 98–101. https://doi.org/10.1145/872726.806984)

<img width="912" alt="image" src="https://github.com/nandysoham/VMFlex/assets/67374926/942330c9-34a9-4193-812a-b3310e4ec4af">

### Memory Allocation - Stack + Heap Design

<img width="908" alt="image" src="https://github.com/nandysoham/VMFlex/assets/67374926/f5843ef8-d674-4671-a722-f8b1a74b2c64">


The stack and heap shares the same contiguous memory allocated - this helps in efficient use of memory effectively shared. Each function has been assigned a fixed amount of memory - failing which the program will return with a stack overflow signal. This design decision has significantly addressed the problems of recursive functions, the behaviour of the function stack and effective mapping of variables with a register/ memory location.

### Memory allocation to complex pointers

<img width="868" alt="image" src="https://github.com/nandysoham/VMFlex/assets/67374926/92b2ed72-8a59-4ae1-af61-8a1ee4287a8d">

The VM can very efficiently handle complex TACs like `**t1 = ***t2 + ****t3` requiring extensive memloc operations.


### For further information - pls refer to [docs](https://docs.google.com/presentation/d/1XmEQ1knqES5wHiDaaaTCQeY4rQ8XP7cEtB3llIzKWNM/edit#slide=id.gd5b15f0a3_5_26)

