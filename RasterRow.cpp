#include "RasterRow.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;

bool RasterRow::WriteIntoRasterAtPosition(const ByteArray& src, const int xpos) {
    if (xpos < 0) return false;
    const int byteOffset = xpos / 8;
    const int byteOffsetBits = byteOffset * 8;
    const int rshift = xpos % 8;
    const int srcSizeBits = src.size() * 8;
    const int arraySizeBits = rasterData_.size() * 8;
    // adequate size for specified range
    if (srcSizeBits + byteOffsetBits + rshift > arraySizeBits) return false;
    if (!WriteAtByteOffset(&rasterData_, &src, byteOffset)) return false;
    return RightShiftArrayRange(&rasterData_, byteOffset, src.size()+1, rshift);
}

bool RasterRow::operator==(const RasterRow &other) const {
    if (rasterData_.size() != other.rasterData_.size()) return false;
    return std::equal(rasterData_.begin(), rasterData_.end(),
            other.rasterData_.begin());
}


bool WriteAtByteOffset(ByteArray *dest, const ByteArray *src, unsigned int byteOffset) {
    if (byteOffset + src->size() > dest->size()) return false;
    std::copy(src->begin(), src->end(), &(*dest)[byteOffset]);
    return true;
}

bool RightShiftArrayRange(ByteArray *array, const int startByte, const int numBytes, int rshift) {
    if (array == nullptr) return false;
    if (startByte + numBytes > array->size()) return false;
    if (rshift < 0 || rshift > 7) return false;
    if (rshift == 0) return true; // OK: no-op
    // OK to perform shift
    ByteArray arrayref = *array;
    for (int i = startByte+numBytes-1; i >= 0; --i) {
        BYTE prev_byte = i > 0 ? arrayref[i-1] : 0;
        arrayref[i] >>= rshift;
        arrayref[i] |= prev_byte << (8 - rshift);
    }
    return true;
}