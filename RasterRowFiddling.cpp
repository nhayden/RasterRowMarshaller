#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "RasterRow.h"
#include "array_wrapper.h"

#include "mock_field_image_data.h"

using namespace std;

//void ppb(const vector<BYTE> v) {
//    for (BYTE b : v) cout << std::hex << (unsigned int)(BYTE)b << endl;
//}

int main(int argc, char** argv) {
    
    vector<vector<BYTE>> vv = get_mock_field_image_data();
    cout << "hiiiiiiii\n";
//    bool all17 = std::all_of(vv.begin(), vv.end(), [](const auto &it){ return it.size() == 17; });
    
    print2dvec(vv);
    
    return 0;
}

