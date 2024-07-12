#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
ll Log(ll &m){
    return floor(log2(m));
}
ll Powerof2(ll &m){
    ll x=(ll)pow(2,Log(m));
    return x;
}
void create_sparse_table(vector<ll>&v,vector<vector<ll>>&B,vector<vector<ll>>&Bindx,int n,int m){//m=Log(n);
    for(int i=0;i<n;i++){
        B[i][0]=min(v[i],v[i+1]);
        
        if(v[i]<=v[i+1])Bindx[i][0]=i;//we want to store the minimum possible index,better for us
        else Bindx[i][0]=i+1;
    }
    for(int j=0;j<=m;j++){//m=Log(n),so it calculates till i to i+2^Log(m)
        B[n-1][j]=v[n-1];
        
        Bindx[n-1][j]=n-1;
    }
    //observe-B[i][j] gives min from A[i] to A[i+2^j] => i<=n-1-2^j, hence uske aage sparse table fill karne ke zarurat nhi
    for(int j=1;j<=m;j++){
        for(int i=0;i<n-(1<<j);i++){ //1<<j is nothing but pow(2,j),i<=n-1-2^j
            B[i][j]=min(B[i][j-1],B[i+(1<<(j-1))][j-1]);

            
            if(B[i][j-1]<B[i+(1<<(j-1))][j-1])Bindx[i][j]=Bindx[i][j-1];
            else if(B[i][j-1]==B[i+(1<<(j-1))][j-1])Bindx[i][j]=min(Bindx[i][j-1],Bindx[i+(1<<(j-1))][j-1]);
            else Bindx[i][j]=Bindx[i+(1<<(j-1))][j-1];
        }
    }
}
ll Rangeminima(vector<ll>&v,vector<vector<ll>>&B,int i,int j){//call by reference only,else it will be O(nq),not O(qlogn)
    ll L=j-i;//range of the query,actually j-i+1 are the elements btw i and j,but L=j-i,coz B[i][Log(L)]=min from A[i] to A[i+2^Log(j-i)]=A[j]
    if(L==0)return v[i];//don't forget this case
    ll t=Powerof2(L);
    ll k=Log(L);
    if(t==L){//this means L is a perfect power of 2,coz t=2^Log(L);
        return B[i][k];//B[i][k] is min from A[i] to A[i+Log(j-i)]
    }
    else{ //Powerof2(L) is less than actual L
        return min(B[i][k],B[j-t][k]);//min (min{A[i],...,A[i+2^Log(L)]},min{A[j-2^Log(L)],...,A[j]})
        //observe here that A[j-2^Log(L)]<A[i+2^Log(L)],coz i+2^Log(L) just hi j pauchte pauchte reh gya
    }
}
ll Rangeminimaindx(vector<ll>&v,vector<vector<ll>>&B,vector<vector<ll>>&Bindx,ll i,ll j){ //THIS FUNCTION GIVES the minimum index among all the minimum elements from index i to j
    ll L=j-i;
    if(L==0)return i;//dont forget this case
    ll t=Powerof2(L);
    ll k=Log(L);
    if(t==L){//this means L is a perfect power of 2,coz t=2^Log(L);
        return Bindx[i][k];//B[i][k] is min index of min element from A[i] to A[i+Log(j-i)]
    }
    else{ //Powerof2(L) is less than actual L
        if(B[i][k]<B[j-t][k])return Bindx[i][k];
        else if(B[i][k]==B[j-t][k]) return min(Bindx[i][k],Bindx[j-t][k]);
        else return Bindx[j-t][k];

    }
}
int main(){
    ll n,q;
    cin>>n>>q;
    vector<ll>v(n);//original Array
    for(ll i=0;i<n;i++){
        cin>>v[i];
    }
    //Range minima problem-sparse table
    //We create n*log2n matrix B,s.t B[i][k] stores the minimum  of{v[i],v[i+1],v[i+2],v[i+3],...v[i+2^k]}
    ll m=Log(n);
    vector<vector<ll>>B(n,vector<ll>(m+1));
    vector<vector<ll>>Bindx(n,vector<ll>(m+1));
    create_sparse_table(v,B,Bindx,n,m);
    while(q--){
        int a,b;
        cin>>a>>b;
        ll ans=Rangeminima(v,B,a-1,b-1);
        cout<<ans<<endl;
    }
    
    return 0;
}
