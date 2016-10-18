#include <cstdio>
#include <cmath>
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

//sort()
bool operator < (const Point& a, const Point& b){
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

const double eps = 1e-10;
int dcmp(double x){
  if (fabs(x) < eps) return 0; 
  else return x<0 ? -1 : 1;
}

//cnt = unique(V, V + size) - V;
bool operator == (const Point& a, const Point& b){
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; } //2*size of triangle

double DistanceToSegment (Point P, Point A, Point B){
  if (A == B) return Length(P-A);
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return fabs(Cross(v1, v2)) / Length(v1);
}

double dismin, dismax;

void update(Point a, Point b, Vector c){
  double tmp = DistanceToSegment (a, b, b+c);
  dismin = min (dismin, tmp);
  dismax = max (dismax, Length(a-b));
  dismax = max (dismax, Length(a-b-c));
}

const int maxn = 50 + 10;
Point A[maxn], B[maxn];

int main(){
  int T, m, n;
  scanf("%d", &T);
  for (int kase=1; kase<=T; kase++){
    dismin = 1e9;
    dismax = 1e-9;
    double len1 = 0, len2 = 0;
    scanf("%d%d", &m, &n);
    for (int i=0; i<m; i++) A[i].read();
    for (int j=0; j<n; j++) B[j].read();
    for (int i=1; i<m; i++) len1 += Length(A[i]-A[i-1]);
    
    /*Be very careful when copy-paste i,j or such things. 
      They may create super-super tricky bugs.*/
    for (int j=1; j<n; j++) len2 += Length(B[j]-B[j-1]);

    //speed could be viewed as len1 & len2
    Point p1 = A[0], p2 = B[0];
    int s1=0, s2=0;
    double t=0, tn; //next t
    while (s1 != m-1){
      Vector d1 = A[s1+1]-p1, d2 = B[s2+1]-p2;
      tn = min(Length(d1)/len1, Length(d2)/len2);
      Vector v1 = d1/Length(d1) * len1;
      Vector v2 = d2/Length(d2) * len2;
      update(p1, p2, (v2-v1)*tn);
      p1 = p1 + v1 * tn;
      p2 = p2 + v2 * tn;
      if (p1 == A[s1+1]) s1++;
      if (p2 == B[s2+1]) s2++;
      t += tn;
    }
    printf("Case %d: %d\n", kase, (int)(dismax - dismin + 0.5));
  }
  return 0;
}