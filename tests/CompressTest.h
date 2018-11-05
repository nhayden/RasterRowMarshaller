#ifndef COMPRESSTEST_H
#define COMPRESSTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../RasterRow.h"

class CompressTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(CompressTest);

    CPPUNIT_TEST(testPadPackedBits);
    CPPUNIT_TEST(testCompress_one);
    CPPUNIT_TEST(testCompress_two_match);
    CPPUNIT_TEST(testCompress_two_mismatch);

    CPPUNIT_TEST_SUITE_END();

public:
    CompressTest();
    virtual ~CompressTest();
    void setUp();
    void tearDown();

private:
    void testPadPackedBits();
    void testCompress_one();
    void testCompress_two_match();
    void testCompress_two_mismatch();

};

#endif /* COMPRESSTEST_H */

