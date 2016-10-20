#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/*
  An interesting question that use integers for input and output. 
  The differences come as change all double to int. 
  Change all comparisons from dcmp() back to common <, >, ==
  Then, delete those division parts, and it is not a hard job.
*/

struct Point{
  int x, y;
  Point(int a=0, int b=0): x(a), y(b) { }
  void read() { scanf("%d%d", &x, &y); }
};

typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Point(A.x+B.x, A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Point(A.x-B.x, A.y-B.y); }

int Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle

bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point& b){
  return a.x == b.x && a.y == b.y;
}

int ConvexHull(Point* p, int n, Point* ch){
  sort(p, p+n);
  n = unique(p, p+n) - p;
  int m = 0;
  for (int i=0; i<n; i++){
    while (m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for (int i=n-2; i>=0; i--){
    while (m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if (n > 1) m--;
  return m; //number of points on convex hull
}

int Dist2(Point A, Point B) {
  return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

int Diameter2(Point* p, int n, Point* ch) {
  int m = ConvexHull(p, n, ch); 
  if(m == 1) return 0;
  if(m == 2) return Dist2(ch[0], ch[1]);
  ch[m+1] = ch[0];
  
  /* 
     But this simplification does not affect the size of m
     Therefore m is unchanged!
     Debugged for about 1h... Stupid...
  */
  
  int ans = 0;
  for(int u = 0, v = 1; u < m; u++) {
    for(;;) {
      int diff = Cross(ch[u+1]-ch[u], ch[v+1]-ch[v]);
      if(diff <= 0) {
        ans = max(ans, Dist2(ch[u], ch[v])); 
        if(diff == 0) ans = max(ans, Dist2(ch[u], ch[v+1])); 
        break;
      }
      v = (v + 1) % m;
    }
  }
  return ans;
}

Point p[500000];
Point ch[500000];

int main(){
  int kase, n, buf;
  scanf("%d", &kase);
  while(kase--){
    scanf("%d", &n);
    for (int i=0; i<4*n; i+=4){
      
      /*
        Nice try!, but then when calling Diameter(), remember to use 4*n. 
        Or multiply the n by 4 after this input loop
      */
      
      p[i].read(); scanf("%d", &buf);
      p[i+1] = p[i] + Point(buf, 0);
      p[i+2] = p[i] + Point(0, buf);
      p[i+3] = p[i] + Point(buf, buf);
    }
    printf("%d\n", Diameter2(p, 4*n, ch));
  }
  return 0;
}
