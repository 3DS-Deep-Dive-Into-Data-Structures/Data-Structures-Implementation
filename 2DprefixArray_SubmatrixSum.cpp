#include<bits/stdc++.h>
using namespace std;
#define ll long long 

vector<vector<ll>> build(vector<vector<ll>>&v){
    ll n=v.size();ll m=v[0].size();
    vector<vector<ll>>prefix(n+1,vector<ll>(m+1));
    //prefix[i][j] calculates sum of submatrix from row 0 ->row i+1 and column 0->column j+1 (i*j submatrix)
    //preifx[i][j] ki indexing 1 based hai 
    for(ll i=0;i<=n;i++)prefix[i][0]=0;
    for(ll j=0;j<=m;j++)prefix[0][j]=0;
    for(ll i=1;i<=n;i++){
        for(ll j=1;j<=m;j++){
            prefix[i][j]=v[i-1][j-1]+prefix[i-1][j]+prefix[i][j-1]-prefix[i-1][j-1];
        }
    }
    return prefix;
}
ll query(vector<vector<ll>>&prefix,ll r1,ll c1,ll r2,ll c2){//r1,c1,r2,c2 are 0 based indexed queries
    //remember prefix is 1based indexing
    return prefix[r2+1][c2+1]-prefix[r1][c2+1]-prefix[r2+1][c1]+prefix[r1][c1];
}
int main(){
    ll n,m;cin>>n>>m;
    vector<vector<ll>>v(n,vector<ll>(m));
    for(ll i=0;i<n;i++){
        for(ll j=0;j<m;j++)cin>>v[i][j];
    }
    vector<vector<ll>>prefix=build(v);
    ll q;cin>>q;

    for(ll i=0;i<q;i++){
        ll a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<query(prefix,a,b,c,d)<<endl;
    }
}
