#include "CompressTest.h"
#include "../RasterRow.h"
#include <algorithm>
#include <iterator>
#include <bitset>

CPPUNIT_TEST_SUITE_REGISTRATION(CompressTest);
using std::vector;
using std::begin;
using std::end;
using std::cout;
using std::endl;

void printvec(const vector<BYTE> v) {
    for (int i = 0; i < v.size(); ++i)
        cout << i << ": " << (signed int)v[i] << endl;
}
void ppb(const vector<BYTE> v) {
    for (BYTE b : v) cout << std::hex << (unsigned int)(BYTE)b << endl;
}

CompressTest::CompressTest() {
}

CompressTest::~CompressTest() {
}

void CompressTest::setUp() {
}

void CompressTest::tearDown() {
}

void CompressTest::testPadPackedBits() {
    vector<BYTE> empty;
    PadPackedBits(empty);
    CPPUNIT_ASSERT(empty.size() == 0);
    vector<BYTE> one{0xaa};
    PadPackedBits(one);
    CPPUNIT_ASSERT(one.size() == 4);
    vector<BYTE> two{0xaa, 0xaa};
    PadPackedBits(two);
    CPPUNIT_ASSERT(two.size() == 4);
    vector<BYTE> three{0xaa, 0xaa, 0xaa};
    PadPackedBits(three);
    CPPUNIT_ASSERT(three.size() == 4);
    vector<BYTE> four{0xaa, 0xaa, 0xaa, 0xaa};
    PadPackedBits(four);
    CPPUNIT_ASSERT(four.size() == 4);
    vector<BYTE> five{0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
    PadPackedBits(five);
    CPPUNIT_ASSERT(five.size() == 8);
}

void CompressTest::testCompress_one() {
    BYTE input_[]{0xaa};
    RasterRow rasterRow(ByteArray(input_, 1));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x00, 0xaa, PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

void CompressTest::testCompress_two_match() {
    BYTE input_[]{ 0xaa, 0xaa };
    RasterRow rasterRow(ByteArray(input_, 2));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ RunLengthCB(2), 0xaa, PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

void CompressTest::testCompress_two_mismatch() {
    BYTE input_[]{ 0xaa, 0xbb };
    RasterRow rasterRow(ByteArray(input_, 2));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ RawCB(2), 0xaa, 0xbb, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

// example #1 from p. 43 of manual
void CompressTest::testCompress_five_match() {
    BYTE input_[]{ 0x00, 0x00, 0x00, 0x00, 0x00 };
    RasterRow rasterRow(ByteArray(input_, 5));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0xfc, 0x00, PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

// example #2 from p. 43 of manual (NOTE: with addition of 05)
void CompressTest::testCompress_five_mismatch() {
    BYTE input_[]{ 0x01, 0x02, 0x03, 0x04, 0x05 };
    RasterRow rasterRow(ByteArray(input_, 5));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x04, 0x01, 0x02, 0x03, 0x04, 0x05, PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

// example #3 from p. 43 of manual
void CompressTest::testCompress_twelve_mixed() {
    BYTE input_[]{ 0x00, 0x00, 0x00, 0x00, 
                   0x03, 0x04, 0x05, 0x06, 0x07,
                   0x08, 0x08, 0x08 };
    RasterRow rasterRow(ByteArray(input_, 12));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0xfd, 0x00,
                      0x04, 0x03, 0x04, 0x05, 0x06, 0x07,
                      0xfe, 0x08,
                      PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

// correct split behavior for max count length == 128
void CompressTest::testCompress_128_match() {
    BYTE input_[128];
    std::fill(begin(input_), end(input_), 0xaa);
    RasterRow rasterRow(ByteArray(input_, 128));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x81, 0xaa, 0x80, 0x80 };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

// correct split behavior for length > 128
void CompressTest::testCompress_129_match() {
    BYTE input_[129];
    std::fill(begin(input_), end(input_), 0xaa);
    RasterRow rasterRow(ByteArray(input_, 129));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x81, 0xaa, 0x00, 0xaa };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}
// correct split behavior for max len (128), followed by 2 match
void CompressTest::testCompress_128_match_2_match() {
    BYTE input_[130];
    std::fill(begin(input_), end(input_), 0xaa);
    RasterRow rasterRow(ByteArray(input_, 130));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x81, 0xaa, 0xff, 0xaa };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}
// correct split behavior for max len (128), followed by 2 homgen. mismatches
void CompressTest::testCompress_128_match_2_mismatch_bbbb() {
    BYTE input_[130];
    std::fill(begin(input_), end(input_), 0xaa);
    input_[128] = 0xbb;
    input_[129] = 0xbb;
    RasterRow rasterRow(ByteArray(input_, 130));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x81, 0xaa,
                      0xff, 0xbb };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}
// correct split behavior for max len (128), followed by 2 heterog. mismatches
void CompressTest::testCompress_128_match_2_mismatch_bbcc() {
    BYTE input_[130];
    std::fill(begin(input_), end(input_), 0xaa);
    input_[128] = 0xbb;
    input_[129] = 0xcc;
    RasterRow rasterRow(ByteArray(input_, 130));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ 0x81, 0xaa,
                      0x01, 0xbb, 0xcc,
                      PAD_, PAD_, PAD_ };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}