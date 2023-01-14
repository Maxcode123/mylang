**MYLANG GRAMMAR**

*Terminal symbols*
1) id
2) num
3) ,
4) ;
5) `+`
6) `-`
7) `*`
8) `/`
9) print
10) (
11) )
12) =

*Productions*
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

*Items*

-- 1 program -> Stm $
1) program -> • Stm $
2) program -> Stm • $

-- 2 Stm -> Stm ; Stm\
3) Stm -> • Stm ; Stm\
4) Stm -> Stm • ; Stm\
5) Stm -> Stm ; • Stm\
6) Stm -> Stm ; Stm •

-- 3 Stm -> id = Exp\
7) Stm -> • id = Exp\
8) Stm -> id • = Exp\
9) Stm -> id = • Exp\
10) Stm -> id = Exp •

-- 4 Stm -> print ( ExpList )\
11) Stm -> • print ( ExpList )\
12) Stm -> print • ( ExpList )\
13) Stm -> print ( • ExpList )\
14) Stm -> print ( ExpList • )\
15) Stm -> print ( ExpList ) •

-- 5 Exp -> id\
16) Exp -> • id\
17) Exp -> id •

-- 6 Exp -> num\
18) Exp -> • num\
19) Exp -> num •

-- 7 Exp -> Exp BinOp Exp\
20) Exp -> • Exp BinOp Exp\
21) Exp -> Exp • BinOp Exp\
22) Exp -> Exp BinOp • Exp\
23) Exp -> Exp BinOp Exp •

-- 8 Exp -> ( Stm, Exp )\
24) Exp -> • ( Stm, Exp )\
25) Exp -> ( • Stm, Exp )\
26) Exp -> ( Stm •, Exp )\
27) Exp -> ( Stm, • Exp )\
28) Exp -> ( Stm, Exp • )\
29) Exp -> ( Stm, Exp ) •

-- 9 ExpList -> Exp, ExpList\
30) ExpList -> • Exp, ExpList\
31) ExpList -> Exp •, ExpList\
32) ExpList -> Exp, • ExpList\
33) ExpList -> Exp, ExpList •

-- 10 ExpList -> Exp\
34) ExpList -> • Exp\
35) ExpList -> Exp •

-- 11 BinOp -> +\
36) BinOp -> • +\
37) BinOp -> + •

-- 12 BinOp -> -\
38) BinOp -> • -\
39) BinOp -> - •

-- 13 BinOp -> *\
40) BinOp -> • *\
41) BinOp -> * •

-- 14 BinOp -> /\
42) BinOp -> • /\
43) BinOp -> / •
