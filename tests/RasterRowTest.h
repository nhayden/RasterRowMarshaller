#ifndef RASTERROWTEST_H
#define RASTERROWTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../RasterRow.h"


class RasterRowTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(RasterRowTest);

    CPPUNIT_TEST(testWriteAtByteOffset);
    CPPUNIT_TEST(testRightShiftArrayRange0);
    CPPUNIT_TEST(testRightShiftArrayRange1);
    CPPUNIT_TEST(testRightShiftArrayRange2);
    CPPUNIT_TEST(testRightShiftArrayRange3);
    CPPUNIT_TEST(testRightShiftArrayRange4);
    CPPUNIT_TEST(testRightShiftArrayRange5);
    CPPUNIT_TEST(testRightShiftArrayRange6);
    CPPUNIT_TEST(testRightShiftArrayRange7);
    CPPUNIT_TEST(testRightShiftArrayRange8_bad_rshift);
    CPPUNIT_TEST(testRightShiftArrayRange_past_end);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition_realdata);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition0);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition3);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition8);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition9_bad);
    CPPUNIT_TEST(testWriteIntoRasterAtPosition_negative);

    CPPUNIT_TEST_SUITE_END();

public:
    RasterRowTest();
    virtual ~RasterRowTest();
    void setUp();
    void tearDown();

private:
    void testWriteAtByteOffset();
    void testRightShiftArrayRange0();
    void testRightShiftArrayRange1();
    void testRightShiftArrayRange2();
    void testRightShiftArrayRange3();
    void testRightShiftArrayRange4();
    void testRightShiftArrayRange5();
    void testRightShiftArrayRange6();
    void testRightShiftArrayRange7();
    void testRightShiftArrayRange8_bad_rshift();
    void testRightShiftArrayRange_past_end();
    void testWriteIntoRasterAtPosition_realdata();
    void testWriteIntoRasterAtPosition0();
    void testWriteIntoRasterAtPosition3();
    void testWriteIntoRasterAtPosition8();
    void testWriteIntoRasterAtPosition9_bad();
    void testWriteIntoRasterAtPosition_negative();
    BYTE *five_, *two_, *three_;
};

#endif /* RASTERROWTEST_H */

