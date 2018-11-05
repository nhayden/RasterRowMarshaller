#include "RasterRowTest.h"
#include "../RasterRow.h"
#include <iterator>
#include <iostream>
#include <algorithm>
using std::begin;
using std::end;
using std::cout;
using std::endl;

CPPUNIT_TEST_SUITE_REGISTRATION(RasterRowTest);

RasterRowTest::RasterRowTest() {
}

RasterRowTest::~RasterRowTest() {
}

void RasterRowTest::setUp() {
    five_ = new BYTE[5]{0, 0, 0, 0, 0};
    two_ = new BYTE[2]{0xff, 0xff};
    three_ = new BYTE[3]{ 0x00, 0x00, 0x00 };
}

void RasterRowTest::tearDown() {
    delete [] five_;
    delete [] two_;
    delete [] three_;
}

// bmWidthBytes: 75
// gTransform.GetGraphicByteWidth: 46 (make all 255)
// gTransform.GetX: 205
void RasterRowTest::testWriteIntoRasterAtPosition_realdata() {
    BYTE fullWidthArray[75]{0x00};
    RasterRow bmRow(ByteArray(fullWidthArray, 75));
    BYTE graphicDataArray[46];
    std::fill(graphicDataArray, graphicDataArray+46, (BYTE)~0);
    ByteArray graphicByteArray(graphicDataArray, 46);
    const int xpos = 205;
    bmRow.WriteIntoRasterAtPosition(graphicByteArray, xpos);
    BYTE ans_[75] {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0-9
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 10-19
        0, 0, 0, 0, 0, 0x07, 0xff, 0xff, 0xff, 0xff, // 20-29
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 30-39
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 40-49
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 50-59
        0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 60-69
        0xff, 0xf8, 0, 0, 0 }; // 70-74
    RasterRow ans(ByteArray(ans_, 75));
    CPPUNIT_ASSERT(bmRow == ans);
}

void RasterRowTest::testWriteIntoRasterAtPosition0() {
    RasterRow rr(ByteArray(three_, 3));
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 0);
    BYTE ans_[]{ 0xff, 0xff, 0x00 };
    RasterRow ans(ByteArray(ans_, 3));
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition3() {
    RasterRow rr(ByteArray(three_, 3));
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 3);
    BYTE ans_[]{ 0b00011111, 0xff, 0b11100000 };
    RasterRow ans(ByteArray(ans_, 3));
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition8() {
    RasterRow rr(ByteArray(three_, 3));
    ByteArray two(two_, 2);
    rr.WriteIntoRasterAtPosition(two, 8);
    BYTE ans_[]{ 0x00, 0xff, 0xff };
    RasterRow ans(ByteArray(ans_, 3));
    CPPUNIT_ASSERT(ans == rr);
}

void RasterRowTest::testWriteIntoRasterAtPosition9_bad() {
    RasterRow rr(ByteArray(three_, 3));
    ByteArray two(two_, 2);
    bool success = rr.WriteIntoRasterAtPosition(two, 9);
    CPPUNIT_ASSERT(!success);
}
void RasterRowTest::testWriteIntoRasterAtPosition_negative() {
    RasterRow rr(ByteArray(three_, 3));
    ByteArray two(two_, 2);
    bool success = rr.WriteIntoRasterAtPosition(two, -1);
    CPPUNIT_ASSERT(!success);
}

void RasterRowTest::testWriteAtByteOffset() {
    ByteArray five(five_, 5);
    ByteArray two(two_, 2);
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
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 0);
    CPPUNIT_ASSERT(three[0] == 0xff);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0x00);
}

void RasterRowTest::testRightShiftArrayRange1() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 1);
    CPPUNIT_ASSERT(three[0] == 0b01111111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b10000000);
}

void RasterRowTest::testRightShiftArrayRange2() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 2);
    CPPUNIT_ASSERT(three[0] == 0b00111111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11000000);
}

void RasterRowTest::testRightShiftArrayRange3() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 3);
    CPPUNIT_ASSERT(three[0] == 0b00011111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11100000);
}

void RasterRowTest::testRightShiftArrayRange4() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 4);
    CPPUNIT_ASSERT(three[0] == 0b00001111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11110000);
}

void RasterRowTest::testRightShiftArrayRange5() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 5);
    CPPUNIT_ASSERT(three[0] == 0b00000111);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111000);
}

void RasterRowTest::testRightShiftArrayRange6() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 6);
    CPPUNIT_ASSERT(three[0] == 0b00000011);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111100);
}

void RasterRowTest::testRightShiftArrayRange7() {
    BYTE three_[]{ 0xff, 0xff, 0x00};
    ByteArray three(three_, 3);
    RightShiftArrayRange(&three, 0, 3, 7);
    CPPUNIT_ASSERT(three[0] == 0b00000001);
    CPPUNIT_ASSERT(three[1] == 0xff);
    CPPUNIT_ASSERT(three[2] == 0b11111110);
}

void RasterRowTest::testRightShiftArrayRange8_bad_rshift() {
    BYTE three_[]{ 0xff, 0xff, 0x00 };
    ByteArray three(three_, 3);
    bool success = RightShiftArrayRange(&three, 0, 3, 8);
    CPPUNIT_ASSERT(!success);
}

void RasterRowTest::testRightShiftArrayRange_past_end() {
    BYTE three_[]{ 0xff, 0xff, 0x00 };
    ByteArray three(three_, 3);
    bool success = RightShiftArrayRange(&three, 1, 3, 0);
    CPPUNIT_ASSERT(!success);
}