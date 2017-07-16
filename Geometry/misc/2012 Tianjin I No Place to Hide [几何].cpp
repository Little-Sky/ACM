#include <cmath>
#include <cstdio>
#include <set>
#include <algorithm>
// #include <assert>
using namespace std;
//#define REP(i, n) for(int i=0; i<(n); i++)
const double eps = 1e-8;
const double PI = acos(-1.0);
const int INF = 1000000000;
const int maxn = 1000 + 10;

int d(double x, double y){
  if (fabs(y-x) < eps) return 0;
  if (x-y > 0) return 1;
  return -1;
}

struct police{
  double x, y;      //x, y coordinate
  double speed;
  double s, e;      //start, end
  bool operator < (const police a) const{
    return d(s, a.s) < 0;
  }
}p[maxn];

set<police> cand;
int n;
double s0;

void cal(){
  cand.clear();
  for (int i=0; i<n; i++){
    police & c = p[i];
    double cur = atan(c.y/c.x);    //cur is the turning angle from 0
    if (d(c.x, 0) < 0)
      cur += PI;
    if (d(cur, 0) < 0)
      cur += 2*PI;
    
    double rg = asin(c.speed/s0);
    c.s = d(cur, rg) < 0 ? cur-rg+2*PI : cur-rg;      //[0, 2*PI)
    c.e = d(cur+rg, 2*PI) > 0 ? cur+rg-2*PI : cur+rg; //(0, 2*PI]
    // printf("%lf %lf\n", c.s/PI*180, c.e/PI*180);
    if (d(c.s, c.e) > 0 || d(c.s * c.e, 0) == 0)
      cand.insert(p[i]);
  }
  sort(p, p+n);
   // printf("size is %lu\n", cand.size());
  
  int best = INF;
  for (set<police>::iterator itr=cand.begin(); itr!=cand.end(); itr++){
    double s = itr->e, e = itr->s, fur;  //furest end can be reached
    // printf("s is %lf e is %lf\n", s/PI*180, e/PI*180);
    if (d(s, e) > 0)
      e += 2*PI;
    int j=0, cnt=1;
    while(d(s,e) < 0 && j<n){
      fur = s;
      while(j<n){
        double s1 = p[j].s, e1 = p[j].e;
        // printf("s1 is %lf s is %lf\n", s1/PI*180, s/PI*180);
        if (d(s1, s) > 0)
          break;
        if (d(s1, e1) > 0)
          e1 += 2*PI;
        // double cur_e = p[j].e 
        if (d(e1, fur) > 0){
          fur = e1;
        }
        j++;
        // printf(" j is %d\n", j);
        // printf("%lf, %lf\n", p[j].e/PI*180, fur/PI*180);
      }
      if (fur != s){
        s = fur;
        cnt++;
      }else{
        break;
      }
    }
    if (d(s,e) >= 0 && cnt<best)
      best = cnt;
  }
  if (best != INF)
    printf("%d\n", best);
  else{
    printf("0\n");
  }
}

int main(){
  int kase;
  scanf("%d", &kase);
  while(kase--){
    double buf1, buf2;
    scanf("%d", &n);
    scanf("%lf%lf%lf", &s0, &buf1, &buf2);
    bool found = false;
    for (int i=0; i<n; i++){
      scanf("%lf%lf%lf", &p[i].speed, &p[i].x, &p[i].y);
      p[i].x -= buf1, p[i].y -= buf2;
      if (d(p[i].speed, s0) > 0 || (d(p[i].x, 0)==0 && d(p[i].y, 0) == 0))
        found = true;
      if (!d(p[i].speed, 0))
        i--, n--;
    }
    // printf("%d ", ignor);
    if (found)
      printf("1\n");
    else
      cal();
  }
  return 0;
}
