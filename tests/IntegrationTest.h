#ifndef ACCEPTANCETEST_H
#define ACCEPTANCETEST_H

#include <cppunit/extensions/HelperMacros.h>
#include "../RasterRow.h"
#include "../array_wrapper.h"
#include <vector>

class IntegrationTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(IntegrationTest);

    CPPUNIT_TEST(testRealWorld_GrahicData);
//    CPPUNIT_TEST(testFailedMethod);

    CPPUNIT_TEST_SUITE_END();

public:
    IntegrationTest();
    virtual ~IntegrationTest();
    void setUp();
    void tearDown();
    std::vector<std::vector<BYTE>> get_graphicdata();

private:
    BYTE **_ppData;
    const int _documentRasterRowWidthInBytes = 72;
    const int printTimePageHeight = 142;
    const int _graphicXPos = 205;
    const int _graphicYPos = 42;
    const int _graphicByteWidth = 17;
    const int _rows = 56;
    
    void testRealWorld_GrahicData();
//    void testFailedMethod();
};

#endif /* ACCEPTANCETEST_H */

