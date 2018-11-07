#include "RasterRow.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;

BYTE RunLengthCB(const int count) { return static_cast<BYTE>((256 - (count - 1))); };
BYTE RawCB(const int count) { return static_cast<BYTE>(count-1); }

void PadPackedBits(vector<BYTE> &packed) {
    if (packed.size() % 4 != 0) {
        int padBytes = 4 - (packed.size() % 4);
        for ( ; padBytes > 0; --padBytes) packed.push_back(PAD_);
    }
}

void RasterRow::EncodeRaw(vector<BYTE> &dest, const vector<BYTE> &buf) const {
    if (buf.size() == 0) return;
    dest.emplace_back(RawCB(buf.size()));
    dest.insert(dest.end(), buf.begin(), buf.end());
}

void RasterRow::EncodeRunLength(vector<BYTE> &dest, const BYTE val, const int count) const {
    dest.emplace_back(RunLengthCB(count));
    dest.emplace_back(val);
}

vector<BYTE> RasterRow::Compress() const {
    enum class PackState {
        Run,
        Raw
    };
    
    const ByteArray &d = rasterData_;
    vector<BYTE> res;
    if (d.size() == 0) return res;
    if (d.size() == 1) return { 0x00, d[0] };
    
    PackState state = PackState::Raw;
    int run_count = 1;
    BYTE prev_byte = d[0];
    vector<BYTE> rawBuf;
    for (int i = 1; i < d.size(); ++i) {
        if (d[i] == prev_byte) {
            // continuing Run
            if (state == PackState::Run) {
                ++run_count;
                if (run_count == MAX_RUN_LENGTH) {
                    EncodeRunLength(res, prev_byte, run_count);
                    run_count = 0;
                }
            }
            // encode current Raw buf, and switch to Run
            else {
                EncodeRaw(res, rawBuf);
                rawBuf.clear();
                run_count = 1;
                state = PackState::Run;
            }
        }
        // not match previous byte
        else {
            // end of Run
            if (state == PackState::Run) {
                ++run_count;
                EncodeRunLength(res, prev_byte, run_count);
                run_count = 0;
                state = PackState::Raw;
            }
            // another Raw byte to add
            else {
                if (rawBuf.size() == MAX_RUN_LENGTH) {
                    EncodeRaw(res, rawBuf);
                    rawBuf.clear();
                }
                rawBuf.push_back(prev_byte);
            }
        }
        prev_byte = d[i];
    }
    if (state == PackState::Run) {
        EncodeRunLength(res, prev_byte, ++run_count);
    } else {
        rawBuf.push_back(prev_byte);
        EncodeRaw(res, rawBuf);
        rawBuf.clear();
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