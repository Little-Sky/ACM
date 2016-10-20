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
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } 
double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}

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

bool SegmentProperIntersection (Point a1, Point a2, Point b1, Point b2){
  double c1 = Cross (a2-a1, b1-a1), c2 = Cross (a2-a1, b2-a1),
         c3 = Cross (b2-b1, a1-b1), c4 = Cross (b2-b1, a2-b1);
  return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool OnSegment(Point p, Point a1, Point a2){
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
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

int isPointInPolygon (Point p, Point* poly, int n){
  int wn = 0; 
  for (int i=0; i<n; i++){
    if (OnSegment (p, poly[i], poly[(i+1)%n])) return -1;  
    int k = dcmp (Cross (poly[(i+1)%n]-poly[i], p-poly[i]));
    int d1 = dcmp (poly[i].y - p.y);
    int d2 = dcmp (poly[(i+1)%n].y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;    
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;    
  }
  if (wn != 0) return 1; 
  return 0;              
}

Point p1[510], p2[510];
Point ch1[510], ch2[510];

int main(){
  int n1, n2, m1, m2;
  while(scanf("%d %d", &n1, &n2) != -1 && n1 && n2){
    for (int i=0; i<n1; i++)
      p1[i].read();
    for (int i=0; i<n2; i++)
      p2[i].read();
    m1 = ConvexHull(p1, n1, ch1);
    m2 = ConvexHull(p2, n2, ch2);
    
    bool ans = true;
    for (int i=0; i<m1 && ans; i++){
      for (int j=0; j<m2 && ans; j++){
        if (ch1[i] == ch2[j]) ans = false;
        if (m1>1 && m2>1 && SegmentProperIntersection(ch1[i], ch1[(i+1)%m1], ch2[j], ch2[(j+1)%m2])) ans = false;
        if (m2>1 && OnSegment( ch1[i], ch2[j], ch2[(j+1)%m2] )) ans = false;
        if (m1>1 && OnSegment( ch2[j], ch1[i], ch1[(i+1)%m1] )) ans = false;
      }
    }
    
    /* 
       Even is no edges intersect, does that means such line (to divide points into two disjoint set) exists?
       Recall the example of tangents line of two circle:
       If one contains the others, they still have no common tangents yet no intersection!
    
       When doing problme concerning polygons, think about the circle case first! 
    */
    
    for (int i=0; i<m1 && ans; i++)
      if (isPointInPolygon(ch1[i], ch2, m2)) ans = false;
    for (int i=0; i<m2 && ans; i++)
      if (isPointInPolygon(ch2[i], ch1, m1)) ans = false;
    printf("%s\n", ans? "Yes" : "No");
  }
  return 0;
}
