#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll Log(ll m){
    return ceil(log2(m));
}
ll Power(ll n){//nearest power of 2 greater than or equal to n
    return (ll)pow(2,Log(n));
}
void build(vector<ll>&A,vector<ll>&v){

    ll n=v.size();
    n=Power(n);
    // while(v.size()!=n)v.push_back(0);
    v.resize(n);
    A.resize(2*n-1);
    for(ll i=n-1;i<2*n-1;i++){
        A[i]=v[i-(n-1)];
    }
    for(ll i=2*n-2;i>0;i-=2){
        A[(i-1)/2]=min(A[i],A[i-1]);
    }
}
ll queries(vector<ll>&A,ll i,ll j){
    if(j<i)return -1;
    ll n=(A.size()+1)/2;
    i+=n-1;
    j+=n-1;
    ll ans=A[i];
    if(j>i){
        ans=min(ans,A[j]);
        while(floor((i-1)*1.0/2)!=floor((j-1)*1.0/2)){
            if(i%2==1)ans=min(ans,A[i+1]);
            if(j%2==0)ans=min(ans,A[j-1]);
            i=floor((i-1)*1.0/2);
            j=floor((j-1)*1.0/2);
        }
    }
    return ans;
}
ll update(vector<ll>&A,ll indx,ll val){
    ll n=(A.size()+1)/2;
    indx+=(n-1);
    A[indx]=val;
    indx=floor((indx-1)*1.0/2);
    while(indx>=0){
        A[indx]=min(A[2*indx+1],A[2*indx+2]);
        indx=floor((indx-1)*1.0/2);
    }

    
}
int main(){
    ll n,q;
    cin>>n>>q;
    vector<ll>v(n);
    for(ll i=0;i<n;i++)cin>>v[i];
    vector<ll>A(2*n-1);
    build(A,v);
    for(ll i=0;i<q;i++){
        ll c,a,b;
        cin>>c>>a>>b;
        
        if(c==2){
            b--;
            cout<<queries(A,a,b)<<endl;
        }
        if(c==1)update(A,a,b);
    }
    for(auto x:A)cout<<x<<" ";

}
