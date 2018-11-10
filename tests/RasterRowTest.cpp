#include "RasterRowTest.h"
#include "../RasterRow.h"
#include <iterator>
#include <iostream>
#include <algorithm>
#include <utility>
using std::begin;
using std::end;
using std::cout;
using std::endl;
using std::vector;
using std::move;

CPPUNIT_TEST_SUITE_REGISTRATION(RasterRowTest);

RasterRowTest::RasterRowTest() {
}

RasterRowTest::~RasterRowTest() {
}

void RasterRowTest::setUp() {
    std::fill(five_, five_+5, 0x00);
    std::fill(two_, two_+2, 0xff);
    std::fill(three_, three_+3, 0x00);
}

void RasterRowTest::tearDown() {

}

void RasterRowTest::testWriteAtByteOffset() {
    ByteArray two(two_, 2);
    vector<BYTE> five{0x00, 0x00, 0x00, 0x00, 0x00};
    CPPUNIT_ASSERT(WriteAtByteOffset(&five, &two, 3));
    CPPUNIT_ASSERT(five[0] == 0x00);
    CPPUNIT_ASSERT(five[1] == 0x00);
    CPPUNIT_ASSERT(five[2] == 0x00);
    CPPUNIT_ASSERT(five[3] == 0xff);
    CPPUNIT_ASSERT(five[4] == 0xff);
    
    // write past end
    CPPUNIT_ASSERT_ASSERTION_FAIL(CPPUNIT_ASSERT(WriteAtByteOffset(&five, &two, 4)));
}

void RasterRowTest::testRightShiftArrayRange0() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 0);
    CPPUNIT_ASSERT(three[0] == 0xff);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0x00);
}

void RasterRowTest::testRightShiftArrayRange1() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 1);
    CPPUNIT_ASSERT(three[0] == 0b01111111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b10000000);
}

void RasterRowTest::testRightShiftArrayRange2() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 2);
    CPPUNIT_ASSERT(three[0] == 0b00111111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11000000);
}

void RasterRowTest::testRightShiftArrayRange3() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 3);
    CPPUNIT_ASSERT(three[0] == 0b00011111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11100000);
}

void RasterRowTest::testRightShiftArrayRange4() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 4);
    CPPUNIT_ASSERT(three[0] == 0b00001111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11110000);
}

void RasterRowTest::testRightShiftArrayRange5() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 5);
    CPPUNIT_ASSERT(three[0] == 0b00000111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111000);
}

void RasterRowTest::testRightShiftArrayRange6() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 6);
    CPPUNIT_ASSERT(three[0] == 0b00000011);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111100);
}

void RasterRowTest::testRightShiftArrayRange7() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    RightShiftArrayRange(&three, 0, 3, 7);
    CPPUNIT_ASSERT(three[0] == 0b00000001);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111110);
}

void RasterRowTest::testRightShiftArrayRange8_bad_rshift() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    bool success = RightShiftArrayRange(&three, 0, 3, 8);
    CPPUNIT_ASSERT(!success);
}

void RasterRowTest::testRightShiftArrayRange_past_end() {
    vector<BYTE> three{0xff, 0xff, 0x00};
    bool success = RightShiftArrayRange(&three, 1, 3, 0);
    CPPUNIT_ASSERT(!success);
}

// bmWidthBytes: 75
// gTransform.GetGraphicByteWidth: 46 (make all 255)
// gTransform.GetX: 205
void RasterRowTest::testWriteIntoRasterAtPosition_realdata() {
    RasterRow bmRow(vector<BYTE>(75));
    BYTE graphicDataArray[46];
    std::fill(graphicDataArray, graphicDataArray+46, (BYTE)~0);
    ByteArray graphicByteArray(graphicDataArray, 46);
    const int xpos = 205;
    bmRow.WriteIntoRasterAtPosition(graphicByteArray, xpos);
    vector<BYTE> ans_ {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0-9
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 10-19
        0, 0, 0, 0, 0, 0x07, 0xff, 0xff, 0xff, 0xff, // 20-29
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 30-39
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 40-49
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 50-59
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 60-69
        0xff, 0xf8, 0, 0, 0 }; // 70-74
    RasterRow ans(move(ans_));
    CPPUNIT_ASSERT(bmRow == ans);
}

void RasterRowTest::testWriteIntoRasterAtPosition0() {
    RasterRow rr(vector<BYTE>{0xff, 0xff, 0x00});
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 0);
    RasterRow ans(vector<BYTE>{ 0xff, 0xff, 0x00 });
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition3() {
    RasterRow rr(vector<BYTE>{0xff, 0xff, 0x00});
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 3);
    RasterRow ans(vector<BYTE>{ 0b00011111, 0xff, 0b11100000 });
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition8() {
    RasterRow rr(vector<BYTE>{0x00, 0x00, 0x00});
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 8);
    RasterRow ans(vector<BYTE>{ 0x00, 0xff, 0xff });
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition9_bad() {
    RasterRow rr(vector<BYTE>{0xff, 0xff, 0x00});
    ByteArray two(two_, 2);
    bool success = rr.WriteIntoRasterAtPosition(two, 9);
    CPPUNIT_ASSERT(!success);
}
void RasterRowTest::testWriteIntoRasterAtPosition_negative() {
    RasterRow rr(vector<BYTE>{0xff, 0xff, 0x00});
    ByteArray two(two_, 2);
    bool success = rr.WriteIntoRasterAtPosition(two, -1);
    CPPUNIT_ASSERT(!success);
}

void RasterRowTest::testAddNCompressedRows_zero() {
    vector<BYTE> buf;
    long docByteWidth = 0;
    long nrows = 0;
    CPPUNIT_ASSERT(!AddNCompressedBlankRows(&buf, docByteWidth, nrows));
    CPPUNIT_ASSERT(buf.size() == 0);
}

void RasterRowTest::testAddNCompressedRows_128_bytes() {
    vector<BYTE> buf;
    long docByteWidth = 128;
    long nrows = 1;
    CPPUNIT_ASSERT(AddNCompressedBlankRows(&buf, docByteWidth, nrows));
    vector<BYTE> ans{0x81, 0x00};
    CPPUNIT_ASSERT(buf == ans);
}

void RasterRowTest::testAddNCompressedRows_129_bytes() {
    vector<BYTE> buf;
    long docByteWidth = 129;
    long nrows = 1;
    CPPUNIT_ASSERT(AddNCompressedBlankRows(&buf, docByteWidth, nrows));
    vector<BYTE> ans{0x81, 0x00, 0x00, 0x00};
    CPPUNIT_ASSERT(buf == ans);
}

void RasterRowTest::testAddNCompressedRows_130_bytes() {
    vector<BYTE> buf;
    long docByteWidth = 130;
    long nrows = 1;
    CPPUNIT_ASSERT(AddNCompressedBlankRows(&buf, docByteWidth, nrows));
    vector<BYTE> ans{0x81, 0x00, 0xff, 0x00};
    CPPUNIT_ASSERT(buf == ans);
}

void RasterRowTest::testAddNCompressedRows_realworld() {
    vector<BYTE> buf;
    long docByteWidth = 72;
    long nrows = 42;
    CPPUNIT_ASSERT(AddNCompressedBlankRows(&buf, docByteWidth, nrows));
    vector<BYTE> ans;
    vector<BYTE> byte_value_pair{0x81, 0x00};
    for (int i = 0; i < 23; ++i)
        ans.insert(ans.begin(), byte_value_pair.begin(), byte_value_pair.end());
    ans.push_back(0xb1);
    ans.push_back(0x00);
    CPPUNIT_ASSERT(buf == ans);
}