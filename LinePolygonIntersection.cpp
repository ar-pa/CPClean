// In the name of Allah.
// We're nothing and you're everything.
// Ya Ali!
 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 32 + 14;

double INF = 1e100;
double EPS = 1e-12;

struct pt { 
	double x, y; 
	pt() {}
	pt(double x, double y) : x(x), y(y) {}
	pt(const pt &p) : x(p.x), y(p.y)    {}
	pt operator + (const pt &p)  const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt &p)  const { return pt(x-p.x, y-p.y); }
	pt operator * (double c)     const { return pt(x*c,   y*c  ); }
	pt operator / (double c)     const { return pt(x/c,   y/c  ); }
};

double dot(pt p, pt q)     { return p.x*q.x+p.y*q.y; }
double dist2(pt p, pt q)   { return dot(p-q,p-q); }
double cross(pt p, pt q)   { return p.x*q.y-p.y*q.x; }
ostream &operator<<(ostream &os, const pt &p) {
	return os << "(" << p.x << "," << p.y << ")"; 
}

// rotate a point CCW or CW around the origin
pt RotateCCW90(pt p)   { return pt(-p.y,p.x); }
pt RotateCW90(pt p)    { return pt(p.y,-p.x); }
pt RotateCCW(pt p, double t) { 
	return pt(p.x*cos(t)-p.y*sin(t), p.x*sin(t)+p.y*cos(t)); 
}

// project point c onto line through a and b
// assuming a != b
pt ProjectPointLine(pt a, pt b, pt c) {
	return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

// project point c onto line segment through a and b
pt ProjectPointSegment(pt a, pt b, pt c) {
	double r = dot(b-a,b-a);
	if (fabs(r) < EPS) return a;
	r = dot(c-a, b-a)/r;
	if (r < 0) return a;
	if (r > 1) return b;
	return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(pt a, pt b, pt c) {
	return sqrt(dist2(c, ProjectPointSegment(a, b, c)));
}

// compute distance between point (x,y,z) and plane ax+by+cz=d
double DistancePointPlane(double x, double y, double z,
                          double a, double b, double c, double d)
{
	return fabs(a*x+b*y+c*z-d)/sqrt(a*a+b*b+c*c);
}

// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(pt a, pt b, pt c, pt d) { 
	return fabs(cross(b-a, c-d)) < EPS; 
}

bool LinesCollinear(pt a, pt b, pt c, pt d) { 
	return LinesParallel(a, b, c, d)
		&& fabs(cross(a-b, a-c)) < EPS
					   && fabs(cross(c-d, c-a)) < EPS; 
}

// determine if line segment from a to b intersects with 
// line segment from c to d
bool SegmentsIntersect(pt a, pt b, pt c, pt d) {
	if (LinesCollinear(a, b, c, d)) {
		if (dist2(a, c) < EPS || dist2(a, d) < EPS ||
		    dist2(b, c) < EPS || dist2(b, d) < EPS) return true;
		if (dot(c-a, c-b) > 0 && dot(d-a, d-b) > 0 && dot(c-b, d-b) > 0)
			return false;
		return true;
	}
	if (cross(d-a, b-a) * cross(c-a, b-a) > 0) return false;
	if (cross(a-c, d-c) * cross(b-c, d-c) > 0) return false;
	return true;
}

// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if
// segments intersect first
pt ComputeLineIntersection(pt a, pt b, pt c, pt d) {
	b=b-a; d=c-d; c=c-a;
	assert(dot(b, b) > EPS && dot(d, d) > EPS);
	return a + b*cross(c, d)/cross(b, d);
}

// compute center of circle given three points
pt ComputeCircleCenter(pt a, pt b, pt c) {
	b=(a+b)/2;
	c=(a+c)/2;
	return ComputeLineIntersection(b, b+RotateCW90(a-b), c, c+RotateCW90(a-c));
}

// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary
bool PointInPolygon(const vector<pt> &p, pt q) {
	bool c = 0;
	for (int i = 0; i < p.size(); i++){
		int j = (i+1)%p.size();
		if ((p[i].y <= q.y && q.y < p[j].y || 
		     p[j].y <= q.y && q.y < p[i].y) &&
		    q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y))
			c = !c;
	}
	return c;
}

// determine if point is on the boundary of a polygon
bool PointOnPolygon(const vector<pt> &p, pt q) {
	for (int i = 0; i < p.size(); i++)
		if (dist2(ProjectPointSegment(p[i], p[(i+1)%p.size()], q), q) < EPS)
			return true;
	return false;
}

// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<pt> CircleLineIntersection(pt a, pt b, pt c, double r) {
	vector<pt> ret;
	b = b-a;
	a = a-c;
	double A = dot(b, b);
	double B = dot(a, b);
	double C = dot(a, a) - r*r;
	double D = B*B - A*C;
	if (D < -EPS) return ret;
	ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
	if (D > EPS)
		ret.push_back(c+a+b*(-B-sqrt(D))/A);
	return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<pt> CircleCircleIntersection(pt a, pt b, double r, double R) {
	vector<pt> ret;
	double d = sqrt(dist2(a, b));
	if (d > r+R || d+min(r, R) < max(r, R)) return ret;
	double x = (d*d-R*R+r*r)/(2*d);
	double y = sqrt(r*r-x*x);
	pt v = (b-a)/d;
	ret.push_back(a+v*x + RotateCCW90(v)*y);
	if (y > 0)
		ret.push_back(a+v*x - RotateCCW90(v)*y);
	return ret;
}

// This code computes the area or centroid of a (possibly nonconvex)
// polygon, assuming that the coordinates are listed in a clockwise or
// counterclockwise fashion.  Note that the centroid is often known as
// the "center of gravity" or "center of mass".
double ComputeSignedArea(const vector<pt> &p) {
	double area = 0;
	for(int i = 0; i < p.size(); i++) {
		int j = (i+1) % p.size();
		area += p[i].x*p[j].y - p[j].x*p[i].y;
	}
	return area / 2.0;
}

double ComputeArea(const vector<pt> &p) {
	return fabs(ComputeSignedArea(p));
}

pt ComputeCentroid(const vector<pt> &p) {
	pt c(0,0);
	double scale = 6.0 * ComputeSignedArea(p);
	for (int i = 0; i < p.size(); i++){
		int j = (i+1) % p.size();
		c = c + (p[i]+p[j])*(p[i].x*p[j].y - p[j].x*p[i].y);
	}
	return c / scale;
}

// tests whether or not a given polygon (in CW or CCW order) is simple
bool IsSimple(const vector<pt> &p) {
	for (int i = 0; i < p.size(); i++) {
		for (int k = i+1; k < p.size(); k++) {
			int j = (i+1) % p.size();
			int l = (k+1) % p.size();
			if (i == l || j == k) continue;
			if (SegmentsIntersect(p[i], p[j], p[k], p[l])) 
				return false;
		}
	}
	return true;
}

int w, p;
vector<pt> pol[maxn];
pt pat[maxn];
double offset[maxn];
int main(){
	ios::sync_with_stdio(0), cin.tie(0);
	cin >> w >> p;
	for(int i = 0; i < p; i++){
		cin >> pat[i].x >> pat[i].y;
		if(i)
			offset[i] = offset[i - 1] + sqrt(dist2(pat[i - 1], pat[i]));
	}
	for(int i = 0; i < w; i++){
		int m;
		cin >> m;
		pol[i].resize(m);
		for(auto &[x, y] : pol[i])
			cin >> x >> y;	
	}
	vector<pair<double, double> > segs;
	for(int i = 0; i < p - 1; i++)
		for(int j = 0; j < w; j++){
			vector<pt> impos({pat[i], pat[i + 1]});
			for(int k = 0; k < pol[j].size(); k++)
				if(SegmentsIntersect(pat[i], pat[i + 1], pol[j][k], pol[j][(k + 1) % pol[j].size()]))
					impos.push_back(ComputeLineIntersection(pat[i], pat[i + 1], pol[j][k], pol[j][(k + 1) % pol[j].size()]));
			sort(impos.begin(), impos.end(), [&](pt a, pt b){
					return dist2(a, pat[i]) < dist2(b, pat[i]);
				});
			for(int k = 0; k < impos.size() - 1; k++) {
				pt mid = (impos[k] + impos[k + 1]) / 2;
				if(PointInPolygon(pol[j], mid)) 
					segs.emplace_back(offset[i] + sqrt(dist2(pat[i], impos[k])),
						       offset[i] + sqrt(dist2(pat[i], impos[k + 1])));
			}
		}
	double ans = 0;
	int sz = 0;
	for(auto [l, r] : segs)
		if(!sz || l > segs[sz - 1].second + EPS)
			segs[sz++] = {l, r};
		else
			segs[sz - 1].second = max(segs[sz - 1].second, r);
	for(auto [l, r] : segs){
		ans = max(ans, r - l);
	}
	cout << setprecision(9) << fixed << ans << endl;
}
