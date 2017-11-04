//http://vn.spoj.com/problems/TAMCAM/
/*Dựng đồ thị có m + n + 2 đỉnh (m + n đỉnh tượng trưng cho hàng hoặc cột và 2 đỉnh source(s) và sink(t))
Chúng ta phát biểu bài toán trờ thành xóa đi một số cạnh sao cho bậc vào mỗi đỉnh bằng bậc ra của mỗi đỉnh (trừ s, t)

Nếu tại ô (i, j) ghi 'G' thì mình tạo cạnh từ đỉnh hàng i đến cột j, còn nếu ghi 'T' thì tạo cạnh từ cột j đến hàng i.
Trọng số mỗi cạnh này là 1.
Gọi DEG[u] là hiệu bán bậc ra với bán bậc vào của đỉnh u thì
  Nếu DEG[u] > 0 thì tạo cạnh (s, u) với trọng số 0.
  Nếu DEG[u] < 0 thì tạo cạnh (u, t) với trọng số 0.
Bài toán trở thành tìm luồng cực đại chi phí cực tiểu từ s -> t.
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 222
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
using namespace std;

struct edge {
    int u, v, cap, flow, cost;
};
int n, m;
string st[N];
int DEG[N * N];

struct MinCostFlow {
    int n, s, t;
    vector<int> d, bef;
    vector<vector<int> > g;
    vector<edge> e;
    priority_queue<pp> heap;
    const int inf = 1e9;

    MinCostFlow(int n) : n(n), d(n), bef(n), g(n) {}

    void addEdge(int u, int v, int cap, int cost) {
        edge ee = {u, v, cap, 0, cost};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0, -cost};
        g[v].push_back(e.size());
        e.push_back(ee);
    }

    int GetMinCost(int s, int t, int mm) {
        this -> s = s;
        this -> t = t;

        while (true) {
            while(!heap.empty()) heap.pop();
            REP(i, n) d[i] = inf;
            d[s] = 0;
            heap.push(pp(0, s));
            while (!heap.empty()) {
                int u = heap.top().second;
                int dis = heap.top().first;
                heap.pop();
                if (-dis != d[u]) continue;
                if (u == t) break;
                for (int id : g[u]) {
                    int v = e[id].v;
                    int c = e[id].cost;
                    if (d[v] > d[u] + c && e[id].cap > e[id].flow) {
                        d[v] = d[u] + c;
                        bef[v] = id;
                        heap.push(pp(-d[v], v));
                    }
                }
            }
            if (d[t] == inf) break;
            int v = t;
            while (v != s) {
                int id = bef[v];
                e[id].flow++;
                e[id ^ 1].flow--;
                v = e[id].u;
            }
        }

        return goTrace(mm);


    }

    int goTrace(int m) {
        int ans = 0;
        for (edge x : e) if (x.u < n - 2 && x.v < n - 2 && x.flow > 0) {
            if (x.u < m) {
                ans++;
                st[x.u][x.v - m] = '.';
            }
            else {
                ans++;
                st[x.v][x.u - m] = '.';
            }
        }
        return ans;
    }
};

int main() {
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    IO;
    cin>>m>>n;
    MinCostFlow MCF(n + m + 2);
    REP(i, m) cin>>st[i];
    REP(i, m) REP(j, n) {
        if (st[i][j] == 'G') {
            MCF.addEdge(i, m + j, 1, 1);
            DEG[i]++;
            DEG[m + j]--;
        }
        if (st[i][j] == 'T') {
            MCF.addEdge(m + j, i, 1, 1);
            DEG[i]--;
            DEG[m + j]++;
        }
    }
    REP(i, m + n) {
        if (DEG[i] > 0) MCF.addEdge(m + n, i, DEG[i], 0);
        if (DEG[i] < 0) MCF.addEdge(i, m + n + 1, -DEG[i], 0);
    }
    int MinCost = MCF.GetMinCost(m + n, m + n + 1, m);
    cout<<MinCost<<'\n';
    REP(i, m) cout<<st[i]<<'\n';
}


