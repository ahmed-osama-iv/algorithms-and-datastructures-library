Linear systems, matrix inverse (Stanford) (C++)

// Gauss-Jordan elimination with partial pivoting.
//
// Uses:
//   (1) solving systems of linear equations (AX=B)
//   (2) inverting matrices (AX=I)
//   (3) computing determinants of square matrices
//
// Running time: O(|N|^3)
//
// INPUT:    a[][] = an nxn matrix
//           b[][] = an nxm matrix
//
// OUTPUT:   x[][] = an nxm matrix (stored in b[][])
//           returns determinant of a[][]

const double EPSILON = 1e-7;

typedef vector<double> VD;
typedef vector<VD> VVD;

// Gauss-Jordan elimination with partial pivoting

double GaussJordan (VVD &a, VVD &b){
  double det = 1;
  int i,j,k;
  int n = a.size();
  int m = b[0].size();
  for (k=0;k<n;k++){
    j=k;
    for (i=k+1;i<n;i++) if (fabs(a[i][k])>fabs(a[j][k])) j = i;
    if (fabs(a[j][k])<EPSILON){ cerr << "Matrix is singular." << endl; exit(1); }
    for (i=0;i<n;i++) swap (a[j][i],a[k][i]);
    for (i=0;i<m;i++) swap (b[j][i],b[k][i]);
    if (j!=k) det *= -1;
    
    double s = a[k][k];
    for (j=0;j<n;j++) a[k][j] /= s;
    for (j=0;j<m;j++) b[k][j] /= s;
    det *= s;
    for (i=0;i<n;i++) if (i != k){
      double t = a[i][k];
      for (j=0;j<n;j++) a[i][j] -= t*a[k][j];
      for (j=0;j<m;j++) b[i][j] -= t*b[k][j];
    }
  }
  return det;
}
