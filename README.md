# mylang compiler  
Compiler for a simple straight-line language.
## 1. Requirements
- [gcc](https://gcc.gnu.org/) used to compile the compiler modules.
- [criterionlib](https://github.com/Snaipe/Criterion) used to run tests.  
Once requirements are met, running `make test` should run all tests.

## 2. Grammar

### 2.1. Terminal symbols
1) id
2) num
3) `,`
4) `;`
5) `+`
6) `-`
7) `*`
8) `/`
9) print
10) `(`
11) `)`
12) `=`

### 2.2. Non-terminal symbols
1) program
2) Stm
3) Exp
4) ExpList
5) BinOp  

### 2.3. Production rules
program -> Stm $  
Stm -> Stm ; Stm  
Stm -> id = Exp  
Stm -> print ( ExpList )  
Exp -> id  
Exp -> num  
Exp -> Exp BinOp Exp  
Exp -> ( Stm, Exp )  
ExpList -> Exp, ExpList  
ExpList -> Exp  
BinOp -> +  
BinOp -> -  
BinOp -> *  
BinOp -> /  

## 3. Modules

### 3.1. Scanner (lexical analyser)
All modules relevant to lexical analysis are found in the [scanner](https://github.com/Maxcode123/mylang/tree/main/src/scanner) directory.  
Lexical analysis is performed with a scanner produced by lex.  
Tokens of the language are defined in header file [tokens.h](https://github.com/Maxcode123/mylang/blob/main/src/scanner/tokens.h).  
[mylang.lex](https://github.com/Maxcode123/mylang/blob/main/src/scanner/mylang.lex) is the configuration file of lex.  
Running `make lexer` produces the scanner and running `src/scanner/lexer test.mylang` prints the sequence of scanned tokens from file test.mylang.  

### 3.2. Parser (syntax analyser)
All modules relevant to syntax analysis are found in the [parser](https://github.com/Maxcode123/mylang/tree/main/src/parser) directory.  
The syntax analyser is an SLR parser, which is a slightly tweaked LR(0) parser.
#### 3.2.1. LR(0) parser
A production rule combined with a dot denoting the position of the parser in the right hand side (rhs) of the production rule, is called an LR(0) item. e.g. `Stm -> Stm • ; Stm` is an item meaning that the parser has parsed the first `Stm` symbol and is now right after it.  
Briefly, the parser is a Deterministic Finite State Automaton where each state is a set of items and edges are grammar symbols (both terminals and non-terminals).  
In order to calculate the set of states and edges the following algorithm [(states.c)](https://github.com/Maxcode123/mylang/blob/main/src/parser/states.c) is used [(tiger book, p. 61)](https://www.goodreads.com/book/show/1190651.Modern_Compiler_Implementation_in_C?from_search=true&from_srp=true&qid=uuB0dsJUgw&rank=1):  
`Let T be the set of states, E the set of edges`  
`Initialize T to {closure({first_item})} where first_item = program -> • Stm $`  
`Initialize E to the empty set {}`  
`for each state SN in T:`  
`    for each item i in SN:`  
`        if dot is in the end of i's rhs: continue`  
`        let X be the symbol after the dot in i's rhs`  
`        J = goto(SN, X)`  
`        if J is empty: continue`  
`        add {J} to T`  
`        add {SN->J, X} to E`  

`closure` adds more items to a set of items when there is a dot to the left of a non-terminal symbol. `goto` moves the dot past the symbol X in all items.  
Here are the algorithms used for `closure` and `goto` [(operations.c)](https://github.com/Maxcode123/mylang/blob/main/src/parser/operations.c):  
`closure(I):`  
`for each item i in I:`  
`    if dot is in the end of i's rhs: continue`  
`    let X be the symbol after the dot in i's rhs`  
`    add X -> •γ to I for each item X -> •γ`  
`    add Y -> •γ to I for each item Y -> •γ where X -> Y`  
`return I`  

`goto(I, X)`  
`Initialize J to the empty set {}`  
`for each item i in I:`   
`    if dot is in the end of i's rhs or dot is not before X: continue`  
`    add A -> α X • β to J where i = A -> α • X β`  
`return closure(J)`  


