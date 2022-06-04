#include "histogram.h"

#include <cassert>

void
test_positive()
{
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 1);
    assert(max == 3);
}

void
test_negative()
{
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == -1);
    return;
}

void
test_identic()
{
    double min = 0;
    double max = 0;
    find_minmax({5, 5, 5}, min, max);
    assert(min == 5);
    assert(max == 5);
    return;
}

void
test_one()
{
    double min = 0;
    double max = 0;
    find_minmax({1}, min, max);
    assert(min == 1);
    assert(max == 1);
    return;
}

void
test_void()
{
    double min=0;
    double max=0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
    return;
}

int
main()
{
    test_positive();
    test_negative();
    test_identic();
    test_one();
    test_void();
}
