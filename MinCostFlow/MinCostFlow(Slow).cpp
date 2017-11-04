//http://vn.spoj.com/problems/MINCOST/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 444
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

struct edge {
    int u, v, flow, cap, cost;
};
const long long inf = 1e18 + 7;
struct MinCostFlow {
    int n, s, t;
    vector<vector<int> > g;
    vector<edge> e;
    vector<int> bef;
    vector<long long> d;
    queue<int> q;
    vector<bool> inq;
    int res[N][N];

    void reset(int n) {
        this -> n = n;
        e.clear();
        g.clear();
        d.clear();
        bef.clear();
        inq.clear();
        g.resize(n);
        d.resize(n);
        bef.resize(n);
        inq.resize(n);
    }

    void addEdge(int u, int v, int cap, int cost) {
        edge ee = {u, v, 0, cap, cost};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0, -cost};
        g[v].push_back(e.size());
        e.push_back(ee);
    }

    long long Get(int s, int t, int need) {
        this -> s = s; this -> t = t;
        long long res = 0;
        while (bfs()) {
            int x = turn(t, need); // x = pp(cost, flow)
            if (x == 0) break;
            if (x >= need) {
                res += 1ll * need * d[t];
                return res;
            } else res += 1ll * x * d[t];
            need -= x;
        }
        return -1;
    }

    void Trace() {
        memset(res, 0, sizeof res);
        for (edge x : e) {
            if (x.flow > 0) {
                printf("%d %d %d\n", x.u + 1, x.v + 1, x.flow);
            }
        }
        printf("0 0 0");
    }

private:
    bool bfs() {
        while (!q.empty()) q.pop();
        REP(i, n) {
            d[i] = inf;
            inq[i] = false;
        }
        d[s] = 0;
        q.push(s);
        inq[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop(); inq[u] = false;
            for (int id : g[u]) {
                int v = e[id].v;
                int c = e[id].cost;
                edge tmp = e[id];
                if (d[v] <= d[u] + c || e[id].cap <= e[id].flow) continue;
                d[v] = d[u] + c;
                bef[v] = id;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
        return d[t] != inf;
    }
    int turn(int t, int need) {
        int u = t;
        int flow = 1e9;
        while (u != s) {
            int id = bef[u];
            flow = min(flow, e[id].cap - e[id].flow);
            u = e[id].u;
        }
        if (flow > need) flow = need;
        while (t != s) {
            int id = bef[t];
            e[id].flow += flow;
            e[id ^ 1].flow -= flow;
            t = e[id].u;
        }
        return flow;
    }
}MCF;
int n, m, t, s, need;
int dd[N][N], cc[N][N];

int main() {
    IO;
    scanf("%d %d %d %d %d", &n, &m, &need, &s, &t);
    s--;t--;
    MCF.reset(n);
    int u, v, c, d;
    REP(i, n) REP(j, n) cc[i][j] = inf;
    REP(i, m) {
        scanf("%d %d %d %d", &u, &v, &c, &d);
        u--;v--;
        if (u > v) swap(u, v);
        cc[u][v] = c;
        dd[u][v] = d;
    }
    REP(i, n - 1) FOR(j, i + 1, n - 1) if (cc[i][j] != inf) {
        MCF.addEdge(i, j, dd[i][j], cc[i][j]);
        MCF.addEdge(j, i, dd[i][j], cc[i][j]);
    }
    long long ans =  MCF.Get(s, t, need);
    printf("%lld\n", ans);
    if (ans != -1) MCF.Trace();
}
