#include "histogram.h"
#include <vector>
#include <cassert>
using namespace std;

void
test_positive() {
    vector <double> test = {1.0, 2.0, 3.0};
    double min = 0;
    double max = 0;
    find_minmax(test, min, max);
    assert(min == 1.0);
    assert(max == 3.0);
}

int
main() {
    test_positive();
}
