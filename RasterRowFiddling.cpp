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

struct Thing {
    int x;
    string y;
    Thing() {cout << "default ctor\n";}
    Thing(int x_, string y_) : x(x_), y(move(y_)) { cout << "regular ctor\n";}
    Thing(const Thing& o) : x(o.x), y(o.y) { cout<<"copy ctor\n";};
    Thing(Thing&& o) : x(o.x), y(move(o.y)) { cout<<"move ctor\n";}
    Thing& operator=(const Thing &o) {
        cout << "copy assign\n";
        if (&o != this) {
            x = o.x;
            y = o.y;
        }
        return *this;
    }
    Thing& operator=(Thing &&o) {
        cout << "move assign\n";
        if (&o != this) {
            swap(x, o.x);
            swap(y, o.y);
        }
        return *this;
    }
    void print() { cout << x << " " << y << endl; }
};

struct ThingOwner {
//    explicit ThingOwner(const Thing &thing) : myThing_(thing) {}
//    explicit ThingOwner(Thing &&thing) : myThing_(move(thing)) {}
    explicit ThingOwner(Thing thing) : myThing_(move(thing)) {}
    Thing myThing_;
};
struct VectorOwner {
    explicit VectorOwner(vector<int> v) : myv(move(v)) {}
    explicit VectorOwner(vector<int> &&v) : myv(move(v)) {}
    vector<int> myv;
};

void dothing(Thing t) { t.print(); }

int main(int argc, char** argv) {
    
//    vector<vector<BYTE>> vv = get_mock_field_image_data();
////    bool all17 = std::all_of(vv.begin(), vv.end(), [](const auto &it){ return it.size() == 17; });
//    print2dvec(vv);
    
//    ThingOwner to({1, "seventy-five"});
    Thing t1(1, "t1");
    ThingOwner to1(move(t1));
    cout << endl;
    
    ThingOwner to2(Thing{33, "thirty-three"});
    
//    Thing t1(1, "seventy");
//    t1.print();
//    Thing t2(move(t1));
//    t1.print();
//    t2.print();
    
//    dothing({33, "eight-seven"});
    
    return 0;
}

