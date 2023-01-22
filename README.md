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
Briefly, the parser is a [Deterministic Finite Automaton](https://en.wikipedia.org/wiki/Deterministic_finite_automaton) (DFA) where each state is a set of items and edges are grammar symbols (both terminals and non-terminals).  

LR(0) parsing is performed by consulting what is called a parse table and by keeping one stack for the states and one for the grammar symbols. The parse table is a table where each column corresponds to a grammar symbol, each row corresponds to a state and each cell contains an action. Available actions are: SHIFT, GOTO, REDUCE, ACCEPT and REJECT. SHIFT and GOTO actions transfer the automaton to another state (the difference between them being that SHIFT does so by popping a terminal symbol from the stack whereas GOTO pops a non-terminal symbol from the stack), REDUCE applies a production rule, i.e. it pops the rhs of a production rule from the stack and pushes the lhs, ACCEPT is the action denoting successfull parsing and REJECT is the action related to a syntax error.  

In order to calculate the set of states and edges of the DFA the following algorithm [(states.c)](https://github.com/Maxcode123/mylang/blob/main/src/parser/states.c) is used [(tiger book, p.61)](https://www.goodreads.com/book/show/1190651.Modern_Compiler_Implementation_in_C?from_search=true&from_srp=true&qid=uuB0dsJUgw&rank=1):  
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

`goto(I, X):`  
`Initialize J to the empty set {}`  
`for each item i in I:`   
`    if dot is in the end of i's rhs or dot is not before X: continue`  
`    add A -> α X • β to J where i = A -> α • X β`  
`return closure(J)`  

Edges between states represent SHIFT and GOTO actions; REDUCE actions are calculated as below:  
`Let R be the set of REDUCE actions, T the set of states`  
`Initialize R to the empty set {}`  
`for each state SN in T:`  
`    for each item i in SN:`  
`        if the dot is not last in i's rhs: continue`  
`        let p be the production rule of item i`  
`        add (REDUCE p, SN) in R`  

where `(REDUCE p, SN)` means reduce by production rule `p` when in `SN` and rhs of p is the next symbol.   
Once states, edges and actions are all calculated the parse table is ready to be populated. However we might get what is called a conflict in the parse table, meaning that we might have a cell containing more than one action. Depending on the actions of the cell the conflict is called shift/shift, shift/reduce or reduce/reduce.

#### 3.2.2. SLR parser
To eliminate most conflicts of the LR(0) parsing table, SLR parsing is used (SLR standing for Simple LR). The only difference of SLR parsing from LR(0) is the algorithm by which REDUCE actions are calculated [(`reduces` in automaton.c)](https://github.com/Maxcode123/mylang/blob/main/src/parser/automaton.c):  
`Let R be the set of REDUCE actions, T the set of states`  
`Initialize R to the empty set {}`  
`for each state SN in T:`  
`    for each item i in SN:`  
`        if the dot is not last in i's rhs: continue`  
`        let p be the production rule of item i`  
`        S = follow(A) where A is the lhs of p`  
`        for each token X in S:`  
`            add (REDUCE p, SN, X) in R`  

where `(REDUCE p, SN, X)` means reduce by production rule `p` when in `SN` and `X` is the next symbol.  
`folow(A)`, for non-terminal `A`, is the set of terminals that can come after `A` in some production rule [(MIT OCW notes, p.39)](https://ocw.mit.edu/courses/6-035-computer-language-engineering-spring-2010/resources/mit6_035s10_lec03b/).  
Here is the algorithm used for `follow` [(`follow` in automaton.c)](https://github.com/Maxcode123/mylang/blob/main/src/parser/automaton.c):  
`follow(X)`  
`Initialize S to the empty set {}`  
`for each production p:`  
`    for each symbol s in p's rhs:`  
`        if s != X: continue`  
`        if s is last rhs symbol:`  
`            let A be p's lhs`  
`            if A == X: continue`  
`            S2 = follow(A)`  
`        else S2 = first(a) where a the symbol after s`  
`        S = S union S2`  
`return S`  
