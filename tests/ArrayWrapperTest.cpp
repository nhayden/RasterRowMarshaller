#include "ArrayWrapperTest.h"
#include "../array_wrapper.h"


CPPUNIT_TEST_SUITE_REGISTRATION(ArrayWrapperTest);

ArrayWrapperTest::ArrayWrapperTest() {
}

ArrayWrapperTest::~ArrayWrapperTest() {
}

void ArrayWrapperTest::setUp() {
}

void ArrayWrapperTest::tearDown() {
}

typedef array_wrapper<BYTE> ByteArray;

void ArrayWrapperTest::testArray_wrapper_ctor_iterators() {
    BYTE array[3]{1, 2, 3};
    ByteArray wrapper(array, array+3);
    CPPUNIT_ASSERT(*wrapper.begin() == 1);
    CPPUNIT_ASSERT(*(wrapper.begin()+1) == 2);
    CPPUNIT_ASSERT(*(wrapper.begin()+2) == 3);
}

void ArrayWrapperTest::testArray_wrapper_ctor_size() {
    BYTE array[3]{1, 2, 3};
    ByteArray wrapper(array, 3);
    CPPUNIT_ASSERT(*wrapper.begin() == 1);
    CPPUNIT_ASSERT(*(wrapper.begin()+1) == 2);
    CPPUNIT_ASSERT(*(wrapper.begin()+2) == 3);
}

void ArrayWrapperTest::testSize() {
    ByteArray w1(nullptr, nullptr);
    CPPUNIT_ASSERT(w1.size() == 0);
    BYTE array[3]{1, 2, 3};
    ByteArray w2(array, array);
    CPPUNIT_ASSERT(w2.size() == 0);
    ByteArray w3(array, array+3);
    CPPUNIT_ASSERT(w3.size() == 3);
}

