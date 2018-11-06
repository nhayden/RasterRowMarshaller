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
    CPPUNIT_TEST(testCompress_five_match);
    CPPUNIT_TEST(testCompress_five_mismatch);
    CPPUNIT_TEST(testCompress_twelve_mixed);
    CPPUNIT_TEST(testCompress_alternating_matches);

    CPPUNIT_TEST(testCompress_3byte_run_surrounded_by_literals_of_length1);
    CPPUNIT_TEST(testCompress_3byte_run_surrounded_by_literals_of_length2);
    CPPUNIT_TEST(testCompress_2byte_run_surrounded_by_literals_of_length1);
    CPPUNIT_TEST(testCompress_2byte_run_surrounded_by_literals_of_length2);
    
    // testing 128 match boundary
    CPPUNIT_TEST(testCompress_128_match);
    CPPUNIT_TEST(testCompress_129_match);
    CPPUNIT_TEST(testCompress_128_match_2_match);
    CPPUNIT_TEST(testCompress_128_match_2_mismatch_bbbb);
    CPPUNIT_TEST(testCompress_128_match_2_mismatch_bbcc);
    
    // TODO: 128 mismatch boundary

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
    void testCompress_five_match();
    void testCompress_five_mismatch();
    void testCompress_twelve_mixed();
    void testCompress_alternating_matches();
    
    void testCompress_3byte_run_surrounded_by_literals_of_length1();
    void testCompress_3byte_run_surrounded_by_literals_of_length2();
    void testCompress_2byte_run_surrounded_by_literals_of_length1();
    void testCompress_2byte_run_surrounded_by_literals_of_length2();
    
    void testCompress_128_match();
    void testCompress_129_match();
    void testCompress_128_match_2_match();
    void testCompress_128_match_2_mismatch_bbbb();
    void testCompress_128_match_2_mismatch_bbcc();
    

};

#endif /* COMPRESSTEST_H */

