#include "../src/parser/operations.h"


int main() {
    LR0_inititems();
    LR0_Item *allitems = LR0_getallitems();
    
    LR0_SymTable I = LR0_ST_symtable();
    LR0_ItemNode in = LR0_ST_node(allitems[4]);

    LR0_ST_put(I, in);

    LR0_O_closure(I);

}