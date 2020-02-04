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
#define fastIO()            ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
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

int GCD(int &a, int &b){
    return abs(__gcd(a, b));
}

#define MX 100005

struct Pole{
    int x;
    int y;
    int h;
};

int cnt = 0;
map <pii, int> group;
vector<Pole> poles[MX];

bool cmp(Pole &a, Pole &b){
    return abs(a.x) < abs(b.x);
}

void reset(int n){
    n += 2;
    cnt = 0;
    group.clear();
    FOR(i, n) poles[i].clear();
}

int main()
{
    //READ("in.txt");

    int n, cs = 1;
    while(scanf("%d", &n) && n > 0){
        reset(n);
        FOR(i, n){
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            int g = GCD(x, y);

            // grouping points based on co-linearity with origin
            pii p = mp(x/g, y/g);
            if (!group[p]) group[p] = ++cnt;
            int idx = group[p];
            poles[idx].pb({x, y, z});
        }

        vector<pii> ans;

        for (int i = 1; i <= cnt; i++){
            sort(poles[i].begin(), poles[i].end(), cmp);
            int mx_so_far = poles[i][0].h;
            for (int j = 1; j < poles[i].size(); j++){
                Pole cur = poles[i][j];
                if (cur.h <= mx_so_far){
                    //cout << "max: " << mx_so_far << " (" <<cur.x << " " << cur.y << ") " << cur.h << endl;
                    ans.pb(mp(cur.x, cur.y));
                }
                else mx_so_far = cur.h;
            }
        }

        sort(ans.begin(), ans.end());
        printf("Data set %d:\n", cs++);
        if (ans.size() == 0) puts("All the lights are visible.");
        else{
            puts("Some lights are not visible:");
            for (int i = 0; i < ans.size(); i++){
                if (i > 0) puts(";");
                printf("x = %d, y = %d", ans[i].fi, ans[i].se);
            }
            puts(".");
        }
    }
    return 0;
}


