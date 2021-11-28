#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
#include <queue>
using namespace std;

int caso = 0;
const double EPS = 1e-9;
const double PI = acos(-1);

using T = long int;
//bool lt(double a, double b) { return a - EPS < b; };
//bool eq(double a, double b) { return fabs(a - b) < EPS; }

//using T = int;
//bool lt(int a, int b) { return a < b; }
//bool eq(int a, int b) { return a == b; }

struct pt {
   T x,y,z;
   pt operator+(pt p) const { return {x+p.x, y+p.y}; }
   pt operator-(pt p) const { return {x-p.x, y-p.y}; }
   pt operator*(T d) const { return {x*d, y*d}; }
   pt operator/(T d) const { return {x/d, y/d}; } // only for floating-point
   
   bool operator==(pt o) const { return x == o.x && y == o.y; }
   bool operator!=(pt o) const { return !(*this == o); }

   bool operator<(pt o) const { // sort points lexicographically
      if (x == o.x) return y < o.y;
      return x < o.x;
   }
};

T sq(pt v) {return v.x*v.x + v.y*v.y;}
double abs(pt v) {return sqrt(sq(v));}

ostream& operator<<(ostream& os, pt p) {
   return os << "("<< p.x << "," << p.y << ")";
}

double dist(pt a, pt b) { // Euclidean distance
   return hypot(a.x - b.x, a.y - b.y);
}
T dist2(pt a, pt b) {
   return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

T cross(pt v, pt w) { return v.x*w.y - v.y*w.x; }
// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool half(pt p) { // true if in blue half
    assert(p.x != 0 || p.y != 0); // the argument of (0,0) is undefined
    return p.y > 0 || (p.y == 0 && p.x < 0);
}

void polarSort(vector<pt> & v) {
   sort(v.begin(), v.end(), [](pt v, pt w) {
      return make_tuple(half(v), 0, sq(v)) < make_tuple(half(w), cross(v,w), sq(w));
   });
}




bool rc(){
    int n,x,y,z;
    cin >> n;
    if(!cin) return false;
    if(n == 0)return false;
    caso++;
    vector<pt> v(n);
    for(int i = 0; i < n;++i) 
        cin >> v[i].x >> v[i].y >> v[i].z;

    polarSort(v);
    vector<pt> f;
    long int m = v[0].z;
    for(int i = 1; i < n; ++i){
        if(orient(v[i-1], v[i], {0,0,0}) == 0){
            if(v[i].z <= m) f.push_back(v[i]);
            m = max(v[i].z, m);
        }
        else m = v[i].z;
    }
    sort(f.begin(), f.end());
    cout << "Data set " << caso << ":\n";
    if(f.empty()){
        cout << "All the lights are visible.\n";
    }
    else {
        cout << "Some lights are not visible:\n";
        for(int i = 0; i < f.size()-1; ++i){
            printf("x = %li, y = %li;\n", f[i].x,f[i].y);
        }
        printf("x = %li, y = %li.\n", f[f.size()-1].x,f[f.size()-1].y);
    }
    return true;
}


int main(){
    while(rc());
    return 0;
}
