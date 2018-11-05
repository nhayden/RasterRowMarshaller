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
    vector<BYTE> ans{ 0x00, 0xaa, 0x80, 0x80 };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

void CompressTest::testCompress_two_match() {
    BYTE input_[]{ 0xaa, 0xaa };
    RasterRow rasterRow(ByteArray(input_, 2));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ RleCB(2), 0xaa, 0x80, 0x80 };
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

void CompressTest::testCompress_two_mismatch() {
    BYTE input_[]{ 0xaa, 0xbb };
    RasterRow rasterRow(ByteArray(input_, 2));
    vector<BYTE> result = rasterRow.Compress();
    vector<BYTE> ans{ LitCB(2), 0xaa, 0xbb, 0x80 };
    ppb(ans);
    CPPUNIT_ASSERT(result.size() == ans.size());
    CPPUNIT_ASSERT(std::equal(ans.begin(), ans.end(), result.begin()));
}

