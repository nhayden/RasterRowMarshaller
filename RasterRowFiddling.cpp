#include <cstdlib>
#include <iostream>
#include "RasterRow.h"
#include "array_wrapper.h"

using namespace std;

int main(int argc, char** argv) {

    BYTE a_[]{0xff, 0xff, 0x00};
    ByteArray a(a_, 3);
    RightShiftArrayRange(&a, 0, 3, 1);
    RasterRow rr(a);
    rr.print();
    return 0;
}

