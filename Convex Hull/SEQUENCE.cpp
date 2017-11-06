#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
#define N 100100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)
template<typename T> inline void read(T &x) {
    char c;
    bool neg = false;
    while (!isdigit(c = getchar()) && c != '-');
    x = 0;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
    if (neg) x = -x;
}
template<typename T> inline void write(T x) {
    if (x < 0) {
        putchar('-');
        write(-x);
        return;
    }
    if (x < 10) putchar(char(x + 48));
    else {
        write(x/10);
        putchar(char(48 + x%10));
    }
}
template<typename T> inline void writeln(T x) {
    write(x);
    putchar('\n');
}
using namespace std;
int n, k;
long long a[N], s[N];

struct ConvexHull {
    vector<long long> a, b;
    vector<double> x;
    int start, last;
    ConvexHull() {}
    void reset(int n) {
        a.resize(n);
        b.resize(n);
        x.resize(n);
        start = 1; last = 0;
    }

    void add(long long aNew, long long bNew) {
        double xNew = -1e18;
        while (start <= last) {
            if (aNew == a[last] && bNew < b[last]) return;
            xNew = (bNew - b[last]) / (a[last] - aNew);
            if (start == last || xNew >= x[last]) break;
            --last;
        }
        a[++last] = aNew;
        b[last] = bNew;
        x[last] = xNew;
    }

    long long Get(long long xQuery) {
        if (start > last) return 0;
        while (start < last && x[start + 1] <= xQuery) ++start;
        return a[start] * xQuery + b[start];
    }

}CH[2];

int main() {
    IO;
    read(n); read(k);
    FOR(i, 1, n) read(a[i]);
    s[0] = 0;
    FOR(i, 1, n) s[i] = s[i - 1] + a[i];
    CH[1].reset(n); CH[0].reset(n);
    int d = 0;
    FOR(i, 1, k + 1) {
        d = 1 - d;
        FOR(i, 1, n) {
            CH[1 - d].add()
        }
    }
}
