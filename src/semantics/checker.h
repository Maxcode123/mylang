#pragma once

#include "env.h"
#include "../parser/parser.h"

/* Checks the AST for invalid variable usage. 
Currenty, the only semantic error raised by invalid variable usage is the usage
of a variable that has not been assigned a value.*/
void checkuses();