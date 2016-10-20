#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
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

void getLineGeneralEquation(Point p1, Point p2, double& a, double& b, double& c){
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = p2.x * p1.y - p1.x * p2.y;
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
  return m; 
}

Point p[10010];
Point ch[10010];

int main(){
  int T, kase, n, m;
  scanf("%d", &T);
  for (kase=1; kase<=T; kase++){
    scanf("%d", &n);
    for (int i=0; i<n; i++)
      p[i].read();
    double totalx=0, totaly=0, shortest=1e10;
    for (int i=0; i<n; i++)
      totalx += p[i].x, totaly += p[i].y;
    m = ConvexHull(p, n, ch);
    
    
    /*Though the rest code could handle the case for m == 2, but for m == 1, getline() is undefined
      Take degenerated cases seriously!
      
      CuxHull -> a line / a point / empty points
      Check them! When orgranizing your code.*/
    if (m <= 2) shortest = 0;
    else for (int i=0; i<m; i++){
      double a, b, c;
      getLineGeneralEquation(ch[i], ch[(i+1)%m], a, b, c);
      double cur = fabs(a*totalx + b*totaly + c*n) / sqrt(a*a+b*b);
      shortest = min(cur, shortest);
    }
    printf("Case #%d: %.3lf\n", kase, shortest/n);
  }
}
