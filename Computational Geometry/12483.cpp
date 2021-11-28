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

const double MAX = 1001;
const double EPS = 1e-9;
const double PI = acos(-1);

using T = double;
//bool lt(double a, double b) { return a - EPS < b; };
//bool eq(double a, double b) { return fabs(a - b) < EPS; }

//using T = int;
//bool lt(int a, int b) { return a < b; }
//bool eq(int a, int b) { return a == b; }

struct pt {
   T x,y;
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

// PRODUCTOS

T dot(pt v, pt w) { return v.x*w.x + v.y*w.y; }

bool isPerp(pt v, pt w) { return dot(v,w) == 0; }

double angle(pt v, pt w) {
   double cosTheta = dot(v,w) / abs(v) / abs(w);
   return acos(max(-1.0, min(1.0, cosTheta)));
}

T cross(pt v, pt w) { return v.x*w.y - v.y*w.x; }

// positivo/cero/negativo: c a la izquieda/sobre/derecha de a-b
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

bool inAngle(pt a, pt b, pt c, pt p) {
   assert(orient(a,b,c) != 0);
   if (orient(a,b,c) < 0) swap(b,c);
   return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

double orientedAngle(pt a, pt b, pt c) {
   if (orient(a, b, c) >= 0)
      return angle(b - a, c - a);
   else
      return 2*PI - angle(b - a, c - a);
}
// TRANSFORMACIONES

pt translate(pt v, pt p) { return p + v; }

// scale p by a certain factor around a center c
pt scale(pt c, double factor, pt p) {
   return c + (p - c)*factor;
}

// rotate p by a certain angle a counter-clockwise around origin
pt rotate(pt p, double a) {
   return { p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a) };
}

// rotate 90º counterclockwise
pt perp(pt p) { return {-p.y, p.x}; }



struct line {
   pt v; T c;
   // from direction vector v and offset c
   line(pt v, T c) : v(v), c(c) {}
   // from equation ax + by = c
   line(T a, T b, T c) : v({b,-a}), c(c) {}
   // from points p and q
   line(pt p, pt q) : v(q-p), c(cross(v,p)) {}
   
   T side(pt p) { return cross(v,p) - c; }
   
   double dist(pt p) { return abs(side(p)) / abs(v); }
   
   line translate(pt t) { return {v, c + cross(v,t)}; }
   
   pt proj(pt p) { return p - perp(v)*side(p)/sq(v); }
};

bool inter(line l1, line l2, pt & out) {
   T d = cross(l1.v, l2.v);
   if (d == 0) return false;
   out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
   return true;
}





bool r(){
    int n;
    cin >> n;
    if(!cin) return false;
    double l,h;
    cin >> l >> h;
    line izq = line({0,0},{0,h});
    line der = line({l,0},{l,h});
    vector<line> flaps;
    vector<pt> puntos(n);
    double x, y, yy;
    for(int i = 0; i < n; ++i){
        cin >> yy >> x >> y;
        if(i%2 == 0) flaps.push_back(line({0,yy},{x,y}));
        else flaps.push_back(line({l,yy},{l,y}));
        puntos[i] = {x,y};
    }

    double diam = MAX;
    for(int i = 0; i < n; ++i){
        if(i < n-1)
            diam = min(diam,dist(puntos[i], flaps[i+1].proj(puntos[i])));
        //else diam = min(diam, dist(puntos[i], line({0,0},{1,0}).proj(puntos[i])));
        if(i%2 == 0) 
            diam = min(diam, dist(puntos[i], der.proj(puntos[i])));
        else
            diam = min(diam, dist(puntos[i], izq.proj(puntos[i])));
    }
    cout << fixed << setprecision(2) << diam << '\n';

    return true;
}
//cout << fixed << setprecision(2)
int main(){
    while(r());
    return 0;
}