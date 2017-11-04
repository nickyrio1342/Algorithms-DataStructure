//http://vn.spoj.com/problems/HIWAY/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

struct edge {
    int u, v, cap, flow, cost;
};

struct MinCostFlow { //Find min path with Dijkstra
    int n, s, t;
    const long long inf = 1e18;
    vector<long long> d;
    vector<int> bef;
    vector<vector<int> >g;
    vector<edge> e;
    priority_queue<pp> heap;
    queue<int> res;

    MinCostFlow(int n) : n(n), d(n), g(n), bef(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        edge ee = {u, v, cap, 0, cost};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0, -cost};
        g[v].push_back(e.size());
        e.push_back(ee);
    }

    void getMCF(int s, int t) {
        this -> s = s;
        this -> t = t;
        int test = 2;
        while (test) {
            while (!heap.empty()) heap.pop();
            REP(i, n) d[i] = inf;
            d[s] = 0;
            heap.push(pp(0, s));
            while (!heap.empty()) {
                int u = heap.top().second;
                long long dis = heap.top().first;
                heap.pop();
                if (u == t) continue;
                if (dis != -d[u]) continue;
                for (int id : g[u]) {
                    int v = e[id].v;
                    int c = e[id].cost;
                    if (d[v] > d[u] + c && e[id].flow < e[id].cap) {
                        d[v] = d[u] + c;
                        bef[v] = id;
                        heap.push(pp(-d[v], v));
                    }
                }
            }
            //
            if (d[t] == inf) {
                printf("-1");return;
            }
            --test;
            int v = t;
            while (v != s) {
                int id = bef[v];
                e[id].flow++;
                e[id ^ 1].flow--;
                v = e[id].u;
            }
        }
        long long ans = 0;
        for (edge x : e) if (x.flow > 0) ans += x.cost;
        printf("%d\n", ans);
        dfs(s);
    }

    void dfs(int u) {
        res.push(u + 1);
        if (u == t) {
            printf("%d ", res.size());
            while (!res.empty()) {
                printf("%d ", res.front());
                res.pop();
            }
            res.push(s + 1);
            putchar('\n');
            return;
        }
        for (int id : g[u]) {
            int v = e[id].v;
            if (e[id].flow > 0) dfs(v);
        }
    }
};
int n, m, s, t, u, v, c;

int main() {
   // freopen("HIWAY.inp","r",stdin);
   // freopen("HIWAY.out","w",stdout);
    IO;
    scanf("%d %d %d %d", &n, &m, &s, &t);
    MinCostFlow MCF(n);
    REP(i, m) {
        scanf("%d %d %d", &u, &v, &c);
        --u;--v;
        MCF.addEdge(u, v, 1, c);
        MCF.addEdge(v, u, 1, c);
    }
    MCF.getMCF(s - 1, t - 1);
}
