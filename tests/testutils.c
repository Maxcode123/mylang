#include <criterion/criterion.h>

#include "../src/utils/util.h"

Test(testutils, testsort)
{
    int a[] = {9, 10, 2, 1, 3, 7, 2};
    sorti(a, 7);
    cr_assert(a[0] == 1);
    cr_assert(a[1] == 2);
    cr_assert(a[2] == 2);
    cr_assert(a[3] == 3);
    cr_assert(a[4] == 7);
    cr_assert(a[5] == 9);
    cr_assert(a[6] == 10);
}