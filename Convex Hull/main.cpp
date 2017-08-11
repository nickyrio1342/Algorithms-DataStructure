//https://open.kattis.com/problems/convexhull

#include <bits/stdc++.h>

using namespace std;


struct pt {
    long long x, y;
};

vector<pt> s;
int n;

bool cmp(const pt &a, const pt &b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool ccw (pt a, pt b, pt c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) > 0;
}



bool cw (pt a, pt b, pt c) {
    return (b.x - a.x) * (c.y - b.y) - (b.y - a.y) * (c.x - b.x) < 0;
}

void convex_hull(vector<pt> &a) {
    if (a.size() == 1) return;
    vector<pt> CH;
    int n = a.size();
    CH.push_back(a[0]);
    for (int i = 1; i<n; i++) {
        if (a[i].x == a[i - 1].x && a[i].y == a[i - 1].y) continue;
        while (CH.size() >=2 && !ccw(CH[CH.size() - 2], CH.back(), a[i]))
            CH.pop_back();
        CH.push_back(a[i]);
    }
    for (int i = n - 2, t = CH.size() + 1; i>=0; i--) {
        if (a[i].x == a[i + 1].x && a[i].y == a[i + 1].y) continue;
        while (CH.size() >= t && !ccw(CH[CH.size() - 2], CH.back(), a[i]))
            CH.pop_back();
        CH.push_back(a[i]);
    }
    if (CH.size() != 1) CH.pop_back();
    a = CH;
}

#define all(s) s.begin(), s.end()
void solve() {
    s.clear();
    cin>>n;
    if (n == 0) exit(0);
    long long a, b;
    for (int i = 0; i<n; i++) {
        cin>>a>>b;
        s.push_back(pt({a, b}));
    }
    sort(all(s), cmp);
    convex_hull(s);
    cout<<s.size()<<endl;
    for(pt u: s) cout<<u.x<<' '<<u.y<<endl;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    while (true) {
        solve();
    }

}
