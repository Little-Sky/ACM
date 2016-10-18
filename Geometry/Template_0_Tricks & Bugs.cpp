
1. Avoid using unneccessarily acos() & asin(); Use atan2 instead.
acos(0.999999999999999888980)=1.49012e-08;
//14-digit precision suddenly drops to only 7-digit precision!

double Angle(Vector A, Vector B) { return fabs(atan2(Cross(A, B), Dot(A, B)));}
//The precision is about 16 digit for test like A(1000000, 0), B(1000000, 1), where double only guarantees 14-digits



2. Rewrite acos(), asin() & sqrt() to handle case like sqrt(-1e-10), acos(1.000001);
double ACOS(double x){
  if (!dcmp(1-x)) x = 1;
  if (!dcmp(1+x)) x = -1;
  return acos(x);
}
double SQRT(double x){
  if (dcmp(x) < 0) x = 0;
  return sqrt(x);
}



3. Be very careful when copy-paste i,j or such things. 
   They may create super-super tricky bugs.
  for (int i=0; i<m; i++) A[i].read();
  for (int j=0; j<n; j++) B[j].read();
  for (int i=1; i<m; i++) len1 += Length(A[i]-A[i-1]);
  for (int j=1; j<m; j++) len2 += Length(B[j]-B[j-1]);
