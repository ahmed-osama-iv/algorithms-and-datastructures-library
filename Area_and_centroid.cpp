Area and centroid (C++)

// This code computes the area or centroid of a polygon,
// assuming that the coordinates are listed in a clockwise
// or counterclockwise fashion.
//
// Running time: O(n)
//
//   INPUT: list of x[] and y[] coordinates
//   OUTPUTS: (signed) area or centroid
//
// Note that the centroid is often known as the
// "center of gravity" or "center of mass".

typedef vector<double> VD;
typedef pair<double,double> PD;

double ComputeSignedArea (const VD &x, const VD &y){
  double area = 0;
  for (int i = 0; i < x.size(); i++){
    int j = (i+1) % x.size();
    area += x[i]*y[j] - x[j]*y[i];
  }
  return area / 2.0;
}

double ComputeArea (const VD &x, const VD &y){
  return fabs (ComputeSignedArea (x, y));
}

PD ComputeCentroid (const VD &x, const VD &y){
  double cx = 0, cy = 0;
  double scale = 6.0 * ComputeSignedArea (x, y);
  for (int i = 0; i < x.size(); i++){
    int j = (i+1) % x.size();
    cx += (x[i]+x[j])*(x[i]*y[j]-x[j]*y[i]);
    cy += (y[i]+y[j])*(x[i]*y[j]-x[j]*y[i]);
  }
  return make_pair (cx/scale, cy/scale);
}
