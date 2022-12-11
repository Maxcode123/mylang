**GRAMMAR

*Terminal symbols
id, num, (,), ;, +, -, *, /, print, ), ()

*Productions
1) program -> Stm $

2) Stm -> Stm ; Stm
3) Stm -> id = Exp
4) Stm -> print ( ExpList )

5) Exp -> id
6) Exp -> num
7) Exp -> Exp BinOp Exp
8) Exp -> ( Stm, Exp )

9) ExpList -> Exp, ExpList
10) ExpList -> Exp

11) BinOp -> +
12) BinOp -> -
13) BinOp -> *
14) BinOp -> /

*Items
1) program -> Stm $
program -> • Stm $
program -> Stm • $

2) Stm -> Stm ; Stm
Stm -> • Stm ; Stm
Stm -> Stm • ; Stm
Stm -> Stm ; • Stm
Stm -> Stm ; Stm •

3) Stm -> id = Exp
Stm -> • id = Exp
Stm -> id • = Exp
Stm -> id = • Exp
Stm -> id = Exp •

4) Stm -> print ( ExpList )
Stm -> • print ( ExpList )
Stm -> print • ( ExpList )
Stm -> print ( • ExpList )
Stm -> print ( ExpList • )
Stm -> print ( ExpList ) •

5) Exp -> id
Exp -> • id
Exp -> id •

6) Exp -> num
Exp -> • num
Exp -> num •

7) Exp -> Exp BinOp Exp
Exp -> • Exp BinOp Exp
Exp -> Exp • BinOp Exp
Exp -> Exp BinOp • Exp
Exp -> Exp BinOp Exp •

8) Exp -> ( Stm, Exp )
Exp -> • ( Stm, Exp )
Exp -> ( • Stm, Exp )
Exp -> ( Stm •, Exp )
Exp -> ( Stm, • Exp )
Exp -> ( Stm, Exp • )
Exp -> ( Stm, Exp ) •

9) ExpList -> Exp, ExpList
ExpList -> • Exp, ExpList
ExpList -> Exp •, ExpList
ExpList -> Exp, • ExpList
ExpList -> Exp, ExpList •

10) ExpList -> Exp
ExpList -> • Exp
ExpList -> Exp •

11) BinOp -> +
BinOp -> • +
BinOp -> + •

12) BinOp -> -
BinOp -> • -
BinOp -> - •

13) BinOp -> *
BinOp -> • *
BinOp -> * •

14) BinOp -> /
BinOp -> • /
BinOp -> / •
