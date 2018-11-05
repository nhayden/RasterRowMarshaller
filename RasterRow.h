#ifndef RASTERROW_H
#define RASTERROW_H

#include "array_wrapper.h"
#include <iostream>

class RasterRow {
public:
    RasterRow(ByteArray rasterData) : rasterData_(rasterData) { }
    bool WriteIntoRasterAtPosition(const ByteArray& src, const int xpos);
    void print() const {
        using std::cout;
        using std::endl;
        for (const auto &i : rasterData_) cout << (signed int)i << " ";
        cout << endl;
    }
    bool operator==(const RasterRow&other) const;

private:
    ByteArray rasterData_;
};

bool WriteAtByteOffset(ByteArray *dest, const ByteArray *src, unsigned int byteOffset);
bool RightShiftArrayRange(ByteArray *array, const int startByte, const int numBytes, int rshift);

#endif /* RASTERROW_H */

