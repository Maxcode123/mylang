#include "../src/parser/symtable.h"


int main() {
    symbol rhs[] = {S_NT_STM, S_T_EOF};
    Production p = production(S_NT_PROGRAM, rhs, 2);
    LR0_Item i = LR0_item(p, 0);
    LR0_Item i2 = LR0_item(p, 1);
    LR0_Item i3 = LR0_item(p, -1);

    LR0_ItemNode in = LR0_node("key1", i);
    LR0_ItemNode in2 = LR0_node("key2", i2);
    LR0_ItemNode in3 = LR0_node("key3", i3);
    LR0_ItemNode in4 = LR0_node("key3", i3);

    LR0_SymTable st1 = LR0_ST_symtable();
    LR0_SymTable st2 = LR0_ST_symtable();

    LR0_ST_put(st1, in);
    LR0_ST_put(st1, in3);

    LR0_ST_put(st2, in2);
    LR0_ST_put(st2, in4);

    LR0_ST_union(st1, st2);
    LR0_ItemNode n = st1->head;
    while(n != NULL) {
        printf("%s\n", n->k);
        n = n->next;
    }

}