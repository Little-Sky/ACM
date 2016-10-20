#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 50000 + 10;

struct Point{
  double x, y;
  Point(double a=0, double b=0): x(a), y(b) { }

  void read() { scanf("%lf%lf", &x, &y); }
};

typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Point(A.x+B.x, A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Point(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Point(p*A.x, p*A.y); }
Vector operator / (Vector A, double p) { return Point(A.x/p, A.y/p); }

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point& b){
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

Vector Normal (Vector A) {
  double L = Length(A);
  return Vector(-A.y/L, A.x/L);
}

struct Line{
  Point P;
  Vector v;
  double ang;
  Line() {}
  Line(Point P, Vector v):P(P), v(v) { ang = atan2(v.y, v.x); }
  bool operator < (const Line& L) const {
    return ang < L.ang;
  }
};


Point GetLineIntersection (Point P, Vector v, Point Q, Vector w){
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v*t;
}

bool OnLeft (const Line& L, const Point& p){
  return dcmp(Cross(L.v, p-L.P)) > 0;
}

Point HPIp[maxn];
Line HPIq[maxn];
int HalfplaneIntersection (Line* L, int n){
  sort (L, L+n);
  int first, last;
  Point * p = HPIp;
  Line * q = HPIq;
  q[first=last=0] = L[0];
  for (int i=1; i<n; i++){
    while (first < last && !OnLeft(L[i], p[last-1])) last--;
    while (first < last && !OnLeft(L[i], p[first])) first++;
    q[++last] = L[i];
    if (fabs(Cross(q[last].v, q[last-1].v)) < eps){
      last --;
      if (OnLeft(q[last], L[i].P)) q[last] = L[i];
    }
    if (first < last) p[last-1] = GetLineIntersection (q[last-1].P, q[last-1].v, q[last].P, q[last].v);
  }
  while (first < last && !OnLeft(q[first], p[last-1])) last--;
  if (last - first <= 1) return 0;
  return last-first+1;
}


Line L [maxn];
bool check(Point* p, int n, int k){
  for (int i=0; i<n; i++)
    L[i] = Line(p[i], p[i+1+k]-p[i]);
  int m = HalfplaneIntersection(L, n);
  return m;
}

Point p[2*maxn];
int main(){
  int n;
  while (scanf("%d", &n) != -1 && n){
    for (int i=n-1; i>=0; i--)
      p[i].read();
    for (int i=0; i<n; i++)
      p[n+i] = p[i];
    int l=1, m, r=n;
    while (l != r){
      m = (r+l)/2;
      if (check(p, n, m)) l = m+1;
      else r = m;
    }
    printf("%d\n", l);
  }
  return 0;
}

