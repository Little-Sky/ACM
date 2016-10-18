#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

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

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}

Point GetLineIntersection (Point P, Vector v, Point Q, Vector w){
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P + v*t;
}

//判断两线段有无交点（交点不可以在线段端点）
bool SegmentProperIntersection (Point a1, Point a2, Point b1, Point b2){
  double c1 = Cross (a2-a1, b1-a1), c2 = Cross (a2-a1, b2-a1),
         c3 = Cross (b2-b1, a1-b1), c4 = Cross (b2-b1, a2-b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}
//判断某点 P 是否在另一线段 a1-a2 上（端点在另一个线段上）
bool OnSegment(Point p, Point a1, Point a2){
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

const int maxn = 300 + 10;
Point P[maxn], V[maxn*maxn];
//Face 面数 = 2 + Edge 边数 - Vertex 顶点数;
int main(){
  int n, kase = 1;
  while(scanf("%d", &n) != -1 && n){
    int cnt = 0, e = n-1;
    for (int i=0; i<n; i++){
      P[i].read();
      V[cnt++] = P[i];
    }
    for (int i=0; i<n; i++)
      for (int j=i+1; j<n-1; j++)
        if (SegmentProperIntersection(P[i], P[i+1], P[j], P[j+1]))
          V[cnt++] = GetLineIntersection(P[i], P[i+1]-P[i], P[j], P[j+1]-P[j]);
    sort(V, V+cnt);
    cnt = unique(V, V+cnt) - V;
    // printf("%d %d\n", e, cnt);
    for (int i=0; i<cnt; i++){
      for (int j=0; j<n-1; j++){
        if (OnSegment(V[i], P[j], P[j+1]))
          e++;
      }
    }
    // printf("%d %d\n", e, cnt);
    printf("Case %d: There are %d pieces.\n", kase++, 2+e-cnt);
  }
}