#include <iostream>
#include <algorithm>

using namespace std;
 
#define NMAX 1024
 
int n, m, ind, ssize, nrctc, nrd, a[NMAX][NMAX], b[NMAX][NMAX], s[NMAX], idx[NMAX], lowlink[NMAX], onstack[NMAX];
 
struct nod {
    int inf;
    nod* urm;
} *sol[NMAX];
 
struct drum{
    int x, y;
} d[NMAX];
 
void adaug_nod(nod* &l, int x) {
    nod* p = new nod;
 
    p->inf = x;
    p->urm = l;
    l = p;
}
 
void citire() {
    int x, y;
 
    cin>>n>>m;
    for(int i = 1; i <= m; i++) {
        cin>>x>>y;
        a[x][y] = 1;
    }
}
 
void tarjan(int v) {
    int x;
 
    s[++ssize] = v; onstack[v] = 1;
    idx[v] = lowlink[v] = ++ind;
 
    for(int u = 1; u <= n; u++) {
        if(a[v][u]) {
            if(!idx[u]) {
                tarjan(u);
                lowlink[v] = min(lowlink[v], lowlink[u]);
            }
            else if(onstack[u]) lowlink[v] = min(lowlink[v], lowlink[u]);
        }
    }
 
    if(idx[v] == lowlink[v]) {
        nrctc++;
        do {
            x = s[ssize];
            adaug_nod(sol[nrctc], x);
            onstack[x] = 0; ssize--;
        } while(x != v);
    }
}
 
void uneste_ctc(int i, int j) {
    for(nod* p3 = sol[j]; p3 != NULL; p3 = p3->urm) adaug_nod(sol[i], p3->inf);
    for(int k = j + 1; k <= nrctc; k++) sol[j - 1] = sol[j];
    nrctc--;
}
 
void drum_ctc(int i, int j) {
    for(nod* p1 = sol[i]; p1 != NULL; p1 = p1->urm) {
        int x = p1->inf;
        for(nod* p2 = sol[j]; p2 != NULL; p2 = p2->urm) {
            int y = p2->inf;
            if(a[x][y]) {
                b[i][j] = 1;
                return;
            }
            if(a[y][x]) {
                b[j][i] = 1;
                return;
            }
        }
    }
}
 
void simplifica_graf() {
    for(int i = 1; i < nrctc; i++)
        for(int j = i + 1; j <= nrctc; j++) drum_ctc(i, j);
}
 
void adaug_drumuri() {
    int i, j, grext[NMAX], grint[NMAX], q[NMAX], w[NMAX], nrq = 0, nrw = 0;
 
    for(i = 1; i <= nrctc; i++) {grint[i] = 0; grext[i] = 0;}
    for(i = 1; i <= nrctc; i++)
        for(j = 1; j <= nrctc; j++)
            if(b[i][j]) {grext[i]++; grint[j]++;}
 
    for(i = 1; i <= nrctc; i++) {
        if(!grint[i]) q[++nrq] = i;
        if(!grext[i]) w[++nrw] = i;
    }
 
    nrd = max(nrq, nrw);
    cout << nrd;
 
}
 
int main() {
 
    citire();
 
    for(int i = 1; i <= n; i++)
        if(!idx[i]) tarjan(i);
 
    if(nrctc == 1) cout<<0;
    else {
        simplifica_graf();
        adaug_drumuri();
    }
 
    return 0;
}