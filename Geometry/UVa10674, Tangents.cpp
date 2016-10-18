#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = acos(-1);

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
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}
//sort()
bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

struct Circle {
  Point o;
  double r;
  Point getPoint (double a){ //in rad
    return Point (o.x + cos(a)*r, o.y + sin(a)*r);
  }
  void read() { scanf("%lf%lf%lf", &o.x, &o.y, &r); }
};

double ACOS(double x){
  if (fabs(1-x) < 1e-8) x = 1;
  if (fabs(1+x) < 1e-8) x = -1;
  return acos(x); //loss precision significantly (10->4, 8->3 and so on). Avoid if possible!
}

double angle(Vector v) { return atan2(v.y, v.x); }

struct tangent{
  Point a;
  Point b;
  bool operator < (const tangent & x) const {
    return a < x.a;
  }
  // tangent():a(0,0), b(0,0) { }
}T[100];

int getTangents(Circle A, Circle B, tangent* t){
  int cnt = 0;
  // if (A.r < B.r) { swap(A, B); swap(a, b); }
  double d = Length(A.o-B.o);
  double rdiff = fabs(A.r - B.r);
  double rsum = A.r + B.r;
  if (dcmp(d-rdiff) < 0) return 0;  //内含
  
  double base = angle(B.o-A.o);
  if (dcmp(d) == 0 && dcmp(A.r-B.r) == 0) return -1;  //重合，无数条切线
  if (dcmp(d-rdiff) == 0){  //内切，1条切线
    t[cnt].a = A.getPoint(base); t[cnt].b = B.getPoint(base); cnt++;
    return 1;
  }
  //有外共切线
  double ang = ACOS( (A.r-B.r) / d );
  t[cnt].a = A.getPoint(base+ang); t[cnt].b = B.getPoint(base+ang); cnt++; 
  t[cnt].a = A.getPoint(base-ang); t[cnt].b = B.getPoint(base-ang); cnt++;
  if (dcmp(d-rsum) == 0){   //一条公切线
    t[cnt].a = A.getPoint(base); t[cnt].b = B.getPoint( PI + base); cnt++;
  }
  else if(dcmp(d-rsum) > 0){  //两条公切线
    double ang = acos((A.r + B.r) / d);
    t[cnt].a = A.getPoint(base+ang); t[cnt].b = B.getPoint( PI + base+ang); cnt++; 
    t[cnt].a = A.getPoint(base-ang); t[cnt].b = B.getPoint( PI + base-ang); cnt++;
  }
  return cnt;
}

int main(){
  Circle x, y;
  while (1){//scanf("%lf%lf%lf%lf%lf%lf", &x.o.x, &x.o.y, &x.r, &y.o.x, &y.o.y, &y.r) != -1 && x.r){
    x.read(); y.read();
    if (dcmp(x.r) == 0)
      break;
    int cnt = getTangents(x, y, T);
    
    sort(T, T+cnt);
    
    printf("%d\n", cnt);
    for (int i=0; i<cnt; i++)
      printf("%.5lf %.5lf %.5lf %.5lf %.5lf\n", T[i].a.x, T[i].a.y, T[i].b.x, T[i].b.y, Length(T[i].a - T[i].b));
  }
  return 0;
}
