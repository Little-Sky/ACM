#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cstdio>
#include <cmath>
#include "macro.h"

struct Point{
    Flt x, y, z;
    Point (Flt x=0, Flt y=0, Flt z=0) : x(x), y(y), z(z) { }
    inline void Read(FILE * file) { fscanf(file, "%lf%lf%lf", &x, &y, &z); }
};

typedef Point Vector;
typedef Point Color;  //for color, x:R, y:G, z:BI/

//3D basics
#define IsZero(x) (fabs(x) < EPS)
#define Sign(x)   (IsZero(x) ? 0 : (x > 0 ? 1 : -1))
#define Acos(x)   (IsZero(1-(x)) ? 0 : (IsZero(1+(x)) ? PI : acos(x)))
#define Sqrt(x)   (IsZero(x) ? 0 : sqrt(x))

inline Vector operator + (const Vector& A, const Vector& B){
    return Vector (A.x+B.x, A.y+B.y, A.z+B.z);
}
inline Vector operator - (const Point& A, const Point& B){
    return Vector (A.x-B.x, A.y-B.y, A.z-B.z);
}
inline Vector operator * (const Vector& A, const Flt& p){
    return Vector (A.x*p, A.y*p, A.z*p);
}
inline Vector operator / (const Vector& A, const Flt& p){
    return Vector (A.x/p, A.y/p, A.z/p);
}
inline bool operator == (const Vector& A, const Vector& B){
    return IsZero (A.x-B.x) && IsZero (A.y-B.y) && IsZero (A.z-B.z);
}
//Used to compare whether the contribution of any color is larger than min_threshold
inline bool operator < (const Color& A, const Flt& p){
    return max (max (A.x, A.y), A.z) < p;
}

inline Flt Dot (const Vector& A, const Vector& B){
    return A.x*B.x + A.y*B.y + A.z*B.z;
}
inline Vector Cross (const Vector& A, const Vector& B){
    return Vector (A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x);
}
inline Color PiecewiseMulti (const Color& A, const Color& B){
    return Color (A.x*B.x, A.y*B.y, A.z*B.z);
}
inline Flt Length (const Vector& A){
    return Sqrt (Dot (A, A));
}
inline Vector Unitlize (const Vector& A){
    Flt len = Length (A);
    len = IsZero (len) ? 1 : len;
    return A/len;
}

struct Ray{
    Point p;
    Vector v, inv_v;
    Flt eta;
    Point GetPoint (Flt t) { return p + v * t; }
    Ray (Point p, Vector _v) : p (p), v (Unitlize (_v)), eta (1) {
        inv_v.x = IsZero (v.x) ? INF : (1.0f / v.x);  //0: undefined
        inv_v.y = IsZero (v.y) ? INF : (1.0f / v.y);  //0: undefined
        inv_v.z = IsZero (v.z) ? INF : (1.0f / v.z);  //0: undefined
    }
};

//input: incident direction and normal direction; output: reflected direction
inline Vector Reflect (const Vector& I, const Vector& N){
   return I - (N*2*Dot (N, I));
}
inline bool Refract (const Vector& I, const Vector& N, const Flt& eta1, const Flt& eta2, Vector & res){
   double n = eta1 / eta2;
   double n1 = - Dot(N, I);
   double n2 = 1.0f - n*n * (1- n1*n1);
   if (n2 < 0) 
       return 0;
   res = (I * n + N * (n * n1 - Sqrt(n2)));
   return 1;
}

//Tranform point p using matrix m[4][4];
inline Point Transform (const Point& p, Flt m[][4]){
    Point res;
    res.x = p.x * m[0][0] + p.y * m[0][1] + p.z * m[0][2] + m[0][3];
    res.y = p.x * m[1][0] + p.y * m[1][1] + p.z * m[1][2] + m[1][3];
    res.z = p.x * m[2][0] + p.y * m[2][1] + p.z * m[2][2] + m[2][3];
    #ifdef DEBUG
       assert(Sign(p.x * m[3][0] + p.y * m[3][1] + p.z * m[3][2] + m[3][3] - 1) == 0);
    #endif
    return res;
}


#endif
