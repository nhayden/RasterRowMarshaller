#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "RasterRow.h"
#include "array_wrapper.h"

using namespace std;

void ppb(const vector<BYTE> v) {
    for (BYTE b : v) cout << std::hex << (unsigned int)(BYTE)b << endl;
}

int main(int argc, char** argv) {

//    BYTE input_[]{ 0xaa, 0xaa };
    BYTE input_[129];
    std::fill(begin(input_), end(input_), 0xaa);
    RasterRow rasterRow(ByteArray(input_, 129));
    vector<BYTE> result = rasterRow.Compress();
    ppb(result);
    return 0;
}

