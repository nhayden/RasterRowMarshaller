#ifndef RASTERROW_H
#define RASTERROW_H

#include "array_wrapper.h"
#include <iostream>
#include <vector>

class RasterRow {
public:
    enum class Compression {
        PackBits,
        None
    };
    explicit RasterRow(ByteArray rasterData) : rasterData_(rasterData),
        compression_(Compression::PackBits) { }
    explicit RasterRow(ByteArray rasterData, Compression compression) :
        rasterData_(rasterData), compression_(compression) { }
    bool WriteIntoRasterAtPosition(const ByteArray& src, const int xpos);
    void print() const {
        using std::cout;
        using std::endl;
        for (const auto &i : rasterData_) cout << (signed int)i << " ";
        cout << endl;
    }
    bool operator==(const RasterRow&other) const;
    std::vector<BYTE> Compress() const;

private:
    ByteArray rasterData_;
    const Compression compression_;
    
};

// Run-length/Repeat encoding control byte
BYTE RleCB(const int count);
// Literal run control byte
BYTE LitCB(const int count);

void PadPackedBits(std::vector<BYTE> &packed);
bool WriteAtByteOffset(ByteArray *dest, const ByteArray *src, unsigned int byteOffset);
bool RightShiftArrayRange(ByteArray *array, const int startByte, const int numBytes, int rshift);

#endif /* RASTERROW_H */

