struct Data {
    ll sum;
};

const int N = 2e5+5;
Data segtree[4*N];

Data combine(Data l, Data r) {
    Data res;
    res.sum = l.sum + r.sum;
    return res;
}

Data make_data(int val) {
    Data res;
    res.sum = val;
    return res;
}

void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        segtree[v] = make_data(a[tl]);
    } else {
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        segtree[v] = combine(segtree[v*2], segtree[v*2+1]);
    }
}

void update(int v, int tl, int tr, int pos, int new_val) {
    if( tl>pos or tr<pos) return; 
    if (tl == tr) {
        segtree[v] = make_data(new_val);
    } else {
        int tm = (tl + tr) / 2;
       // if (pos <= tm)
            update(v*2, tl, tm, pos, new_val);
        //else
            update(v*2+1, tm+1, tr, pos, new_val);
        segtree[v] = combine(segtree[v*2], segtree[v*2+1]);
    }
}

Data query(int v, int tl, int tr, int L, int R) {
    if (L > R or tl>tr)
        return make_data(0);
    if (L >= tl && R <= tr)
        return segtree[v];
    int tm = (tl + tr) / 2;
    return combine(query(v*2, tl, tm, L ,R),
                   query(v*2+1, tm+1, tr, L, R));
}

int main(){
    int n,q;
    cin>>n>>q;
    int a[n+1],b[n];
    for(int i=1;i<=n;i++) cin>>a[i];
    build(a,1,1,n);


    while(q--){
        int k,x;
        cin>>k>>x;
        update(1,1,n,k,x);
        cout<<query(1,1,n,1,n).ans<<endl;
    }
}
