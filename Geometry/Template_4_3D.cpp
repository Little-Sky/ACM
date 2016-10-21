struct Point3{
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x), y(y), z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (Vector3 A, Vector3 B){
  return Vector3(A.x+B.x, A.y+B.y, A.z+B.z);
}

Vector3 operator - (Point3 A, Point3 B){
  return Vector3(A.x-B.x, A.y-B.y, A.z-B.z);
}

Vector3 operator * (Vector3 A, double p){
  return Vector3(A.x*p, A.y*p, A.z*p);
}

Vector3 operator / (Vector3 A, double p){
  return Vector3(A.x/p, A.y/p, A.z/p);
}

// Plane (p0, N), N is the normal vector pointing away from the halfspace;
// point on plane : Dot (n, p-p0) = 0


