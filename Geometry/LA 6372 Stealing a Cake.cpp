
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

const double eps = 1e-10;
const double PI = acos(-1);
const int INF = 1e9;

int cmp(double a, double b){
  if (fabs(a-b) < eps) return 0;
  if (a-b < 0) return -1;
  return 1;
}

struct P{
  double x;
  double y;
  P operator + (const P& a)const{
    return (P){x+a.x, y+a.y};
  }
  void s(double a, double b){x = a, y = b;}
}R[4], C;   //R[0] takes left-lower && R[1] right-upper
double r;

double dis(P a, P b){
  double c1 = a.x - b.x;
  double c2 = a.y - b.y;
  return sqrt(c1*c1 + c2*c2);
}

double toR(P a){
  if (cmp(a.x, R[1].x) <= 0 && cmp(a.x, R[0].x) >= 0 )
    return min(fabs(a.y - R[0].y), fabs(a.y - R[1].y));
  if (cmp(a.y, R[1].y) <= 0 && cmp(a.y, R[0].y) >= 0)
    return min(fabs(a.x - R[0].x), fabs(a.x - R[1].x));
  double m = INF;
  for (int i=0; i<4; i++)
    m = min(m, dis(a, R[i]));
  // printf("%lf %lf %lf\n", a.x, a.y, m);
  return m;
}

P PoC(double a){
  return (P){C.x + r*cos(a), C.y + r*sin(a)};
}

int main(){
  P s;
  double x1, x2, y1, y2, best;
  while(cin >> s.x >> s.y && (cmp(s.x, 0) || cmp(s.y, 0) ) ){
    cin >> C.x >> C.y >> r;
    cin >> x1 >> y1 >> x2 >> y2;
    if (cmp(x1, x2) > 0) swap(x1, x2);
    if (cmp(y1, y2) > 0) swap(y1, y2);
    R[0].s(x1, y1); R[1].s(x2, y2); 
    R[2].s(x1, y2); R[3].s(x2, y1);
    double a=0, b=2*PI/3, c=4*PI/3, d=2*PI, e, f, g;
    best = INF;
    P i, j, k;
    bool first = true;
    // cout << R[0].x << " " << R[0].y << endl;
    // cout << R[1].x << " " << R[1].y << endl;
    for(;;){
      // cout << a/PI*180 << " " << b/PI*180 << " "<< c/PI*180 << " " << d/PI*180 << " " << best<< endl;
      i = PoC((a+b) / 2);
      j = PoC((b+c) / 2);
      k = PoC((c+d) / 2);
      e = dis(s, i) + toR(i);
      f = dis(s, j) + toR(j);
      g = dis(s, k) + toR(k);
      if (!cmp(dis(i,k), 0) && !cmp(e,g))
        break;
      if (cmp(e,f) < 0 && cmp(e,g) < 0){
        if (first)
          a = (c+d)/2 - 2*PI;
        d = (b+c)/2;
        first = 0;
        best = min (best, e);
        // cout << "1\n"; 
      }else if (cmp(f,g) < 0){
        a = (a+b)/2;
        d = (c+d)/2;
        first = 0;
        best = min (best, f);
        // cout << "2\n";
      }else{
        if (first)
          d = (a+b)/2 + 2*PI;
        a = (b+c)/2;
        best = min (best, g);
        // cout << "3\n";
      }
      b = a+(d-a)/3;
      c = a+(d-a)/3*2;
      // cout << "runned \n";
    }
    printf("%.2lf\n", best);
  }
  return 0; 
}


