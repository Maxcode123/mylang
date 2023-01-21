#include "checker.h"


void checkuses() {
    Stm stm = (Stm)popASTstk();
    envinit();
    updtstm(stm);
}