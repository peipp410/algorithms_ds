#include <cstdio>
#define MAXN 1000001
#define ll long long
ll a[MAXN], ans[MAXN<<2]={0}, tag[MAXN<<2]={0};

int lc(int p){
    return p<<1;
}

int rc(int p){
    return p<<1|1;
}

void push_up(int p){
    ans[p] = ans[lc(p)] + ans[rc(p)];
}

void build(int l, int r, int p){
    if (l == r){
        ans[p] = a[l];
        return;
    }
    int m = (l+r)>>1;
    build(l, m, lc(p));
    build(m+1, r, rc(p));
    push_up(p);
}

void f(int l, int r, int p, int k){
    tag[p] += k;
    ans[p] += (r-l+1)*k;
}

void push_down(int l, int r, int p){
    int m = (l+r)>>1;
    f(l, m, lc(p), tag[p]);
    f(m+1, r, rc(p), tag[p]);
    tag[p] = 0;
}

void change(int cl, int cr, int l, int r, int p, int k){
    if (cl <= l && cr >= r){
        tag[p] += k;
        ans[p] += k*(r-l+1);
        return;
    }
    push_down(l, r, p);
    int m = (l+r)>>1;
    if (m >= cl) change(cl, cr, l, m, lc(p), k);
    if (m < cr) change(cl, cr, m+1, r, rc(p), k);
    push_up(p);
}

ll query(int ql, int qr, int l, int r, int p){
    if (ql <=l && qr >= r) return ans[p];
    ll ret = 0;
    int m = (l+r)>>1;
    push_down(l, r, p);
    if (m >= ql) ret += query(ql, qr, l, m, lc(p));
    if (m < qr) ret += query(ql, qr, m+1, r, rc(p));
    return ret;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++){
        scanf("%lld", &a[i]);
    }
    build(1, n, 1);
    for (int i = 1; i <= m; i++){
        int op, x, y, k;
        scanf("%d", &op);
        if (op == 1){
            scanf("%d %d %d", &x, &y, &k);
            change(x, y, 1, n, 1, k);
        }
        else{
            scanf("%d %d", &x, &y);
            printf("%lld\n", query(x, y, 1, n, 1));
        }
    }
    return 0;
}
