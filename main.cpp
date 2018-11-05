#include <bits/stdc++.h>
using namespace std;

typedef unsigned char BYTE;

void printbits(int val) {
    cout << std::bitset<8>(val) << endl;
}

//BYTE twoc(int val) {
//    printbits(val);
//    int inverted = ~val; printbits(inverted);
//    int plusone = inverted+1; printbits(plusone);
//    BYTE res = (BYTE)(plusone & 0xff);
//    return res;
//}

//BYTE twoc(int val) {
//    int res = (256 - val);
//    cout << bitset<8>(res) << endl;
//    return (BYTE)(res);
//}

//int rev2c(BYTE val) {
//    char invval = ~val;
//    char res = invval + 1;
//    return res;
//}

// interpret byte as two's complement value
int rev2c(BYTE val) {
    int mask = 128;
    int res = -(val & mask) + (val & ~mask);
    return res;
}

void testrev2c() {
    cout << rev2c(0xff) << endl;
    cout << rev2c(0x81) << endl;
    cout << rev2c(0x00) << endl;
    cout << rev2c(0x7f) << endl;
    cout << rev2c(0x80) << endl;
    cout << rev2c(0x82) << endl;
    cout << endl;
}

// create byte representing two's complement
// (assume systems represents ints with two's complement)
BYTE twoc(int val) {
    BYTE res = val & 0xff;
    return res;
}

void testtwoc() {
    printf("%x\n", twoc(-1));
    printf("%x\n", twoc(-127));
    printf("%x\n", twoc(0));
    printf("%x\n", twoc(127));
    printf("%x\n", twoc(-128));
    printf("%x\n", twoc(-126));
    cout << rev2c(twoc(-126)) << endl;
}

void shiftarray(BYTE *array, int len, int rshift) {
    for (int i = len-1; i >= 0; --i) {
        BYTE prev_byte = i > 0 ? array[i-1] : 0;
        array[i] >>= rshift;
        array[i] |= prev_byte << (8 - rshift);
    }
}

void printarray(BYTE *a, int len) {
    for (int i = 0; i < len; ++i) {
        cout << bitset<8>(a[i]) << " ";
    }
    cout << endl;
}
void printarraynumbered(BYTE *a, int len) {
    for (int i = 0; i < len; ++i) {
        cout << i << ": " << bitset<8>(a[i]) << endl;
    }
}

void testshift1(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b01011100, 0b11000110 };
    copy(a, a+2, test);
    shiftarray(test, 2, 1);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift2(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00101110, 0b01100011 };
    copy(a, a+2, test);
    shiftarray(test, 2, 2);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift3(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00010111, 0b00110001 };
    copy(a, a+2, test);
    shiftarray(test, 2, 3);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift4(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00001011, 0b10011000 };
    copy(a, a+2, test);
    shiftarray(test, 2, 4);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift5(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00000101, 0b11001100 };
    copy(a, a+2, test);
    shiftarray(test, 2, 5);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift6(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00000010, 0b11100110 };
    copy(a, a+2, test);
    shiftarray(test, 2, 6);
    cout << (equal(ans, ans+2, test)) << endl;
}
void testshift7(const BYTE* const a) {
    BYTE test[2];
    BYTE ans[] = { 0b00000001, 0b01110011 };
    copy(a, a+2, test);
    shiftarray(test, 2, 7);
    cout << (equal(ans, ans+2, test)) << endl;
}
void runshifttests() {
    const BYTE ref[] = { 0b10111001, 0b10001100 };
    testshift1(ref);
    testshift2(ref);
    testshift3(ref);
    testshift4(ref);
    testshift5(ref);
    testshift6(ref);
    testshift7(ref);
}

void shiftarrayrange(BYTE *arr, int insertedByteLength, int rshift) {
    shiftarray(arr, insertedByteLength+1, rshift);
}

void example() {
    auto xpos = 205;
    auto total_width_bytes = 75;
    auto graphic_width_bytes = 46;
    BYTE gdata[46] = {};
    fill(gdata, gdata+sizeof(gdata), (BYTE)~0);
    BYTE rowdata[75] = { 0x0 };
    auto startByteIdx = xpos / 8;
    memcpy(&rowdata[startByteIdx], gdata, sizeof(gdata));
    printarraynumbered(rowdata, sizeof(rowdata));
    shiftarrayrange(&rowdata[startByteIdx], sizeof(gdata), xpos % 8);
    printarraynumbered(rowdata, sizeof(rowdata));
    
    BYTE ans[75] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0-9
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 10-19
                   0, 0, 0, 0, 0, 0x07, 0xff, 0xff, 0xff, 0xff, // 20-29
                   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 30-39
                   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 40-49
                   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 50-59
                   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, // 60-69
                   0xff, 0xf8, 0, 0, 0 }; // 70-74
    cout << equal(rowdata, rowdata+sizeof(rowdata), ans) << endl;
}

//int main(int argc, char** argv) {
////    cout << std::boolalpha;
//    
////    BYTE rowdata[] = { 0x0, 0x0, 0x0, 0x0 };
////    BYTE gdata[] = { (BYTE)~0, (BYTE)~0 };
////    printarray(rowdata, sizeof(rowdata));
////    printarray(gdata, sizeof(gdata));
////    const int xpos = 11;
////    int startByteIdx = xpos / 8;
////    memcpy(&rowdata[startByteIdx], gdata, sizeof(gdata));
////    printarray(rowdata, sizeof(rowdata));
////    shiftarrayrange(&rowdata[startByteIdx], sizeof(gdata), xpos % 8);
////    printarray(rowdata, sizeof(rowdata));
//    
////    BYTE *all = new BYTE[75];
////    example();
//    
//    
//
//    
////    return 0;
//}

