#pragma once

#include "array_wrapper.h"
#include <vector>
#include <utility>

const BYTE PAD_ = 0x80;

class RasterRow {
public:
    static const int MAX_RUN_LENGTH = 128;
    static const BYTE MAX_RUN_LENGTH_CONTROL_BYTE; // defined in RasterRow.cpp
    enum class Compression {
        PackBits,
        None
    };
    explicit RasterRow(std::vector<BYTE> rdata) : rdata_(std::move(rdata)),
        compression_(Compression::PackBits) { }
    explicit RasterRow(std::vector<BYTE> rdata, Compression compression) :
        rdata_(std::move(rdata)), compression_(compression) { }
    bool WriteIntoRasterAtPosition(const ByteArray& src, const int xpos);
    bool operator==(const RasterRow&other) const;
    std::vector<BYTE> Compress() const;
    
    // *CONST* helpers for accessing underlying storage
    typedef std::vector<BYTE>::const_iterator const_iterator;
    const_iterator begin() const { return rdata_.begin(); }
    const_iterator end() const { return rdata_.end(); }
    typedef std::vector<BYTE>::value_type value_type;
    const value_type *data() const { return rdata_.data(); }
    const std::size_t size() const { return rdata_.size(); }
    

private:
    // raster data
    std::vector<BYTE> rdata_;
    const Compression compression_;
    
    void EncodeRaw(std::vector<BYTE> &dest, const std::vector<BYTE> &buf) const;
    void EncodeRunLength(std::vector<BYTE> &dest, const BYTE val,
        const int count) const;
};

// Run-length/Repeat encoding control byte
BYTE RunLengthCB(const int count);
// Literal run control byte
BYTE RawCB(const int count);

void PadPackedBits(std::vector<BYTE> &packed);
bool WriteAtByteOffset(std::vector<BYTE> *dest, const ByteArray *src, unsigned int byteOffset);
bool RightShiftArrayRange(std::vector<BYTE> *raster_data, const int startByte,
        const int numBytes, int rshift);
bool AddNCompressedBlankRows(std::vector<BYTE> *dest, long docRasterWidthInBytes, long nrows);

