#include<bits/stdc++.h>
#define CLR(a)              memset(a, 0, sizeof(a))
#define SET(a, x)           memset(a, x, sizeof(a))
#define SORT(v)             sort(v.begin(), v.end())
#define REV(v)              reverse(v.begin(), v.end())
#define FOR(i, n)           for (int i=0; i<n; i++)
#define FOR1(i, n)          for (int i=1; i<=n; i++)
#define ROF(i, n)           for (int i=n-1; i>=0; i--)
#define ROF1(i, n)          for (int i=n; i>=1; i--)
#define LOOP(i, x, n)       for (int i=x; i<=n; i++)
#define READ(x)             freopen(x, "r", stdin);
#define WRITE(x)            freopen(x, "w", stdout);
#define fastIO()            ios_base::sync_with_stdio(0); cin.tie(0);
#define PI                  acos(-1.0)
#define pb                  push_back
#define mp                  make_pair
#define fi                  first
#define se                  second
#define all(v)              v.begin(), v.end()

using namespace std;

typedef long long              ll;
typedef unsigned long long     ull;
typedef vector<int>            vi;
typedef pair<int, int>         pii;
typedef pair<string, int>      psi;
typedef pair<char, int>        pci;

const double eps = 1e-9;

int fx[] = {-1, 1, 0, 0, -1, -1, 1, 1};
int fy[] = {0, 0, -1, 1, -1, 1, -1, 1};

int kx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int ky[] = {2, -2, 1, -1, 2, -2, 1, -1};

double square(double x){
    return (x*x);
}

// 2D point
struct Point{
    double x, y;

    Point() {x = 0, y = 0;}
    Point(double a, double b) {x = a, y = b;}

    Point operator+ (Point that){return {x + that.x, y + that.y};}
    Point operator- (Point that){return {x - that.x, y - that.y};}
    void print(){cout << "(" << x << "," << y << ")" << endl;}
};

// 2D segment
struct Segment{
    Point st;
    Point en;

    Segment() {}
    Segment(Point a, Point b) {st = a, en = b;}

    void print(){cout << "[ (" << st.x << "," << st.y << ") - (" << en.x << "," << en.y << ") ]" << endl;}
};

double dot(Point a, Point b){
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b){
    return a.x * b.y + a.y * b.x;
}

bool onSegment(Segment s, Point p){
    return abs(cross(s.st - p, s.en - p)) < eps
        && min(s.st.x, s.en.x) <= p.x
        && max(s.st.x, s.en.x) >= p.x
        && min(s.st.y, s.en.y) <= p.y
        && max(s.st.y, s.en.y) >= p.y;
}

double areaTriangle(Point a, Point b, Point c){
    return 0.5 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

double polygonArea(vector<Segment> &v){
    double area = 0;
    for (auto s : v) area += areaTriangle(s.st, s.en, Point(0, 0));
    return area;
}

struct Circle{
    Point center;
    double radius;

    Circle(){center = {0,0}, radius = 0;}
    Circle(Point p, double r){
        center = p;
        radius = r;
    }
    bool inside(Point p){
        return square(p.x - center.x) + square(p.y - center.y) < radius * radius;
    }
};

struct Rectangle{
    vector<Segment> sides;
    double area;

    Rectangle(){area = 0;}
    Rectangle(Point a, Point b){
        sides.push_back(Segment({a.x, b.y}, b));
        sides.push_back(Segment(b, {b.x, a.y}));
        sides.push_back(Segment({b.x, a.y}, a));
        sides.push_back(Segment(a, {a.x, b.y}));

        area = abs(polygonArea(sides));
    }
    bool inside(Point &p){
        double cur = 0;
        for (auto s : sides) cur += abs(areaTriangle(s.st, s.en, p));
        return abs(area - cur) < eps;
    }

    bool onBorder(Point &p){
        for (auto s : sides){
            Point &a = s.st;
            Point &b = s.en;

            if (a.x == p.x && p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y)) return true;
            if (a.y == p.y && p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x)) return true;
        }
        return false;
    }
};

struct Triangle{
    vector<Segment> sides;
    double area;

    Triangle(){area = 0;}
    Triangle(Point a, Point b, Point c){
        sides.push_back(Segment(a, b));
        sides.push_back(Segment(b, c));
        sides.push_back(Segment(c, a));
        area = abs(polygonArea(sides));
    }
    bool inside(Point &p){
        double cur = 0;
        for (auto s : sides) cur += abs(areaTriangle(s.st, s.en, p));
        return abs(area - cur) < eps;
    }

    bool onBorder(Point &p){
        for (auto s : sides) if (onSegment(s, p)) return true;
        return false;
    }
};

int main()
{
    //READ("in.txt");

    char c;
    vector<pair<int, Circle>> C;
    vector<pair<int, Rectangle>> R;
    vector<pair<int, Triangle>> T;

    int cnt = 0;
    while(cin >> c && c != '*'){

        if (c == 'c'){
            double x, y, r; cin >> x >> y >> r;
            C.pb(mp(++cnt, Circle({x, y}, r)));
        }
        else if (c == 'r'){
            double a, b, x, y; cin >> a >> b >> x >> y;
            R.pb(mp(++cnt, Rectangle({a, b}, {x, y}))); //cout << cnt << " " << R.back().se.area << endl;
        }
        else{
            double a, b, p, q, x, y; cin >> a >> b >> p >> q >> x >> y;
            T.pb(mp(++cnt, Triangle({a, b}, {p, q}, {x, y}))); //cout << cnt << " " << T.back().se.area << endl;
        }
    }

    Point p;
    int cs = 0;
    while(scanf("%lf%lf", &p.x, &p.y) != EOF){
        if (p.x == 9999.9 && p.y == 9999.9) break;

        vector<int> ans;
        for (auto cur : C) if (cur.se.inside(p)) ans.pb(cur.fi);
        for (auto cur : R) if (!cur.se.onBorder(p) && cur.se.inside(p)) ans.pb(cur.fi);
        for (auto cur : T) if (!cur.se.onBorder(p) && cur.se.inside(p)) ans.pb(cur.fi);

        ++cs;

        sort(all(ans));
        if (ans.size()) for (int i = 0; i < ans.size(); i++) cout << "Point " << cs << " is contained in figure " << ans[i] << "\n";
        else cout << "Point " << cs << " is not contained in any figure\n";
    }

    return 0;
}


