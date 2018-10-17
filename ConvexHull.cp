Convex hull (C++)

// Compute the 2D convex hull of a set of points using the monotone chain
// algorithm.  Eliminate redundant points from the hull if REMOVE_REDUNDANT is 
// #defined.
//
// Running time: O(n log n)
//
//   INPUT:   a vector of input points, unordered.
//   OUTPUT:  a vector of points in the convex hull, counterclockwise

using namespace std;

#define REMOVE_REDUNDANT

typedef double T;
typedef pair<T,T> PT;
typedef vector<PT> VPT;

const double EPS = 1e-7;

T det (const PT &a, const PT &b){ 
  return a.first * b.second - a.second * b.first; 
}

T area2 (const PT &a, const PT &b, const PT &c){ 
  return det(a,b) + det(b,c) + det(c,a); 
}

#ifdef REMOVE_REDUNDANT

// return true if point b is between points a and c

bool between (const PT &a, const PT &b, const PT &c){
  return (fabs(area2(a,b,c)) < EPS &&
          (a.first - b.first) * (c.first - b.first) <= 0 &&
          (a.second - b.second) * (c.second - b.second) <= 0);
}

#endif

void convex_hull (VPT &pts){
  sort (pts.begin(), pts.end());
  pts.erase (unique (pts.begin(), pts.end()), pts.end());

  VPT up, dn;
  for (int i = 0; i < pts.size(); i++){
    while (up.size() > 1 && area2(up[up.size()-2], up.back(), pts[i]) >= 0) 
      up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size()-2], dn.back(), pts[i]) <= 0) 
      dn.pop_back();
    up.push_back(pts[i]);
    dn.push_back(pts[i]);
  }

  pts = dn;
  for (int i = (int) up.size() - 2; i >= 1; i--) pts.push_back(up[i]);

#ifdef REMOVE_REDUNDANT

  if (pts.size() <= 2) return;
  dn.clear();
  dn.push_back (pts[0]);
  dn.push_back (pts[1]);
  for (int i = 2; i < pts.size(); i++){
    if (between (dn[dn.size()-2], dn[dn.size()-1], pts[i])) dn.pop_back();
    dn.push_back (pts[i]);
  }
  if (dn.size() >= 3 && between (dn.back(), dn[0], dn[1])){
    dn[0] = dn.back();
    dn.pop_back();
  }
  pts = dn;

#endif

}
