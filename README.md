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

### 2.2. Production rules
0) program -> Stm $

1) Stm -> Stm ; Stm
2) Stm -> id = Exp
3) Stm -> print ( ExpList )

4) Exp -> id
5) Exp -> num
6) Exp -> Exp BinOp Exp
7) Exp -> ( Stm, Exp )

8) ExpList -> Exp, ExpList
9) ExpList -> Exp

10) BinOp -> +
11) BinOp -> -
12) BinOp -> *
13) BinOp -> /

## 3. Modules

### 3.1. Scanner (lexical analyser)
All modules relevant to lexical analysis are found in the [scanner](https://github.com/Maxcode123/mylang/tree/main/src/scanner) directory.  
Lexical analysis is performed with scanner produced by lex.  
Tokens of the language are defined in header file [tokens.h](https://github.com/Maxcode123/mylang/blob/main/src/scanner/tokens.h).  
[mylang.lex](https://github.com/Maxcode123/mylang/blob/main/src/scanner/mylang.lex) is the configuration file of lex.  
Running `make lexer` produces the scanner and running `src/scanner/lexer test.mylang` prints the sequence of scanned tokens from file test.mylang.  

### 3.2. Parser (syntax analyser)
All modules relevant to syntax analysis are found in the [parser](https://github.com/Maxcode123/mylang/tree/main/src/parser) directory.  
The syntax analyser is an SLR parser, which is a slightly tweaked LR(0) parser.
#### 3.2.1. LR(0) parser
A production rule combined with a dot denoting the position of the parser in the right hand side of the production rule, is called an LR(0) item.
