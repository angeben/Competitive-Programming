#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>
#include <cmath>
#include <random>
#include <tuple>
#include <cassert>
using namespace std;

const double EPS = 1e-9;
const double PI = acos(-1);
int caso =0;
using T = double;


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
   
};

bool inter(line l1, line l2, pt & out) {
   T d = cross(l1.v, l2.v);
   if (d == 0) return false;
   out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
   return true;
}


// POLIGONOS, el primer y último puntos coinciden

double areaTriangle(pt a, pt b, pt c) {
   return abs(cross(b - a, c - a)) / 2.0;
}

double areaPolygon(vector<pt> const& p) {
   double area = 0.0;
   for (int i = 0, n = int(p.size()) - 1; i < n; ++i) {
      area += cross(p[i], p[i+1]);
   }
   return abs(area) / 2.0;
}


bool isConvex(vector<pt> const& p) {
   bool hasPos=false, hasNeg=false;
   for (int i=0, n=(int)p.size(); i<n; ++i) {
      int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
      if (o > 0) hasPos = true;
      if (o < 0) hasNeg = true;
   }
   return !(hasPos && hasNeg);
}


vector<pt> cutPolygon(pt a, pt b, vector<pt> const& P) {
   vector<pt> R; pt c;
   for (int i = 0; i < int(P.size()) - 1; i++) {
      double left1 = cross(b - a, P[i] - a),
             left2 = cross(b - a, P[i + 1] - a);
      if (left1 >= 0) R.push_back(P[i]);  // P[i] is on the left of ab
      if (left1 * left2 < 0) {  // edge (P[i], P[i+1]) crosses line ab
         inter({P[i], P[i+1]}, {a,b}, c);
         R.push_back(c);
      }
   }
   if (!R.empty())
      R.push_back(R[0]); // make R's first point = R's last point
   return R;
}

bool r(){
    int n;
    double x,y,w,h;
    cin >> n;
    if(!cin) return 0;
    pt p;
    cin >> w >> h >> p.x >> p.y;
    vector<pt> region, aux;
    pt o1 = {0,0}, o2 = {w,0}, o3 = {w,h}, o4 = {0,h};
    region.push_back(o1);
    region.push_back(o2);
    region.push_back(o3);
    region.push_back(o4);
    region.push_back(o1);
    pt a; pt b;
    for(int i = 0; i < n; ++i){
        cin >> a.x >> a.y;
        cin >> b.x >> b.y;
        if(line(a,b).side(p) < 0) 
            aux = cutPolygon(b,a,region);
        else aux = cutPolygon(a,b,region);
        region = (aux.size() != 0) ? aux: region;
    }

    caso++;
    cout << fixed << setprecision(3) << "Case #" << caso << ": " << areaPolygon(region) << '\n';
    return 1;
}

int main(){
    while(r());
    return 0;
}