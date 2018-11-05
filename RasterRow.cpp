#include "RasterRow.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

const BYTE PAD_ = 0x80;

BYTE RleCB(const int count) { return static_cast<BYTE>((256 - (count - 1))); };
BYTE LitCB(const int count) { return static_cast<BYTE>(count-1); }

void PadPackedBits(vector<BYTE> &packed) {
    if (packed.size() % 4 != 0) {
        int padBytes = 4 - (packed.size() % 4);
        for ( ; padBytes > 0; --padBytes) packed.emplace_back(PAD_);
    }
}

vector<BYTE> RasterRow::Compress() const {
    enum class PackState {
        Run,
        Raw
    };
    
    const ByteArray &d = rasterData_;
    vector<BYTE> res;
    if (d.size() == 0) return res;
    if (d.size() == 1) return { 0x00, d[0], PAD_, PAD_ };
    
//    res.emplace_back(RCB(2));
//    res.emplace_back(d[0]);
//    res.emplace_back(PAD_);
//    res.emplace_back(PAD_);
    
    PackState state = PackState::Raw;
    BYTE prev_byte = d[0];
    vector<BYTE> buf;
    for (int i = 1; i < d.size(); ++i) {
        if (d[i] == prev_byte) {
            // encode and switch to Run
            if (state == PackState::Raw) {
                
                state = PackState::Run;
            } else {
                
            }
        }
    }
    
    return res;
}

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