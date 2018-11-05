/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ArrayWrapperTest.h
 * Author: nh
 *
 * Created on Nov 1, 2018, 10:56:56 PM
 */

#ifndef ARRAYWRAPPERTEST_H
#define ARRAYWRAPPERTEST_H

#include <cppunit/extensions/HelperMacros.h>

class ArrayWrapperTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(ArrayWrapperTest);

    CPPUNIT_TEST(testArray_wrapper_ctor_iterators);
    CPPUNIT_TEST(testArray_wrapper_ctor_size);
    CPPUNIT_TEST(testSize);

    CPPUNIT_TEST_SUITE_END();

public:
    ArrayWrapperTest();
    virtual ~ArrayWrapperTest();
    void setUp();
    void tearDown();

private:
    void testArray_wrapper_ctor_iterators();
    void testArray_wrapper_ctor_size();
    void testSize();

};

#endif /* ARRAYWRAPPERTEST_H */

