#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>
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

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

//sort()
bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}
//cnt = unique(V, V + size) - V;
bool operator == (const Point& a, const Point& b){
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Area2(Point A, Point B, Point C) { return Cross(B-A, C-A); }
//signed area; obey right-hand rule -> cross > 0

//逆时针转角
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad) - A.y*sin(rad), A.x*sin(rad) + A.y*cos(rad));
}

//多边形的有向面积
double PolygonArea (Point* p, int n){
  double area = 0;
  for (int i = 1; i < n-1; i++)//用 p[0] 划分省去 i=n-1 的特殊处理 (下一个点p[n]其实是p[0])
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}

int ConvexHull(Point* p, int& n, Point* ch){
  sort(p, p+n);
  n = unique(p, p+n) - p;
  int m = 0;
  for (int i=0; i<n; i++){
    while (m > 1 && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for (int i=n-2; i>=0; i--){
    while (m > k && dcmp(Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])) <= 0) m--;
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  //ch.resize(m);
  return m; //number of points on convex hull
}

Point p[4000];
Point ch[4000];
int n, m;

int main(){
  int kase, r;
  double a, b, c, d, e;
  cin >> kase;
  while (kase--){
    double area1 = 0;
    n = m = 0;
    cin >> r;
    while (r--){
      cin >> a >> b >> c >> d >> e;
      area1 += c*d;
      Point in(a, b);
      Vector v1(c/2, d/2), v2(c/2, -d/2);
      v1 = Rotate(v1, -1*e*PI/180);
      v2 = Rotate(v2, -1*e*PI/180);
      p[n++] = in + v1; p[n++] = in + v2;
      v1 = v1 * (-1); v2 = v2 * (-1);
      p[n++] = in + v1; p[n++] = in + v2;
    }
    m = ConvexHull (p, n, ch);
    double area2 = PolygonArea(ch, m);
    printf("%.1lf ", area1/area2*100);
    putchar('%');putchar('\n');
  }
  return 0;
}