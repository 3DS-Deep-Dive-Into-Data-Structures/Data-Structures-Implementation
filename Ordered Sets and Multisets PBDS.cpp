#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp> // Common file  
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
#define ordered_multiset tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>  
#define ll long long
// Note->in ordered_multiset ,the lower_bound function will work as upper_bound ,to avoid store it as pairs -ref-https://www.geeksforgeeks.org/policy-based-data-structures-g/
typedef tree<pair<int, int>, null_type, less<pair<int, int> >,rb_tree_tag, tree_order_statistics_node_update>ordered_map;

//The normal set functions sometimes don't quite work well on ordered Multisets ,hence for ordered multisets we have seperately defined the following functions-
void Insert(ordered_multiset &s,int x){ //this function inserts one more occurrence of (x) into the set.
 
     s.insert(x);
 
}
 
 
bool Exist(ordered_multiset &s,int x){ //this function checks weather the value (x) exists in the set or not.
 
     if((s.upper_bound(x))==s.end()){
        return 0;
     }
     return ((*s.upper_bound(x))==x);
 
}
 
 
void Erase(ordered_multiset &s,int x){ //this function erases one occurrence of the value (x).
 
     if(Exist(s,x)){
        s.erase(s.upper_bound(x));
     }
 
}
 
 
int FirstIdx(ordered_multiset &s,int x){ //this function returns the first index of the value (x)..(0 indexing).
 
    if(!Exist(s,x)){
        return -1;
    }
    return (s.order_of_key(x));
 
}
 
 
int Value(ordered_multiset &s,int idx){ //this function returns the value at the index (idx)..(0 indexing).
 
   return (*s.find_by_order(idx));
 
}
 
 
int LastIdx(ordered_multiset &s,int x){ //this function returns the last index of the value (x)..(0 indexing).
 
    if(!Exist(s,x)){
        return -1;
    }
    if(Value(s,(int)s.size()-1)==x){
        return (int)(s.size())-1;
    }
    return FirstIdx(s,*s.lower_bound(x))-1;
 
}
 
 
int Count(ordered_multiset &s,int x){ //this function returns the number of occurrences of the value (x).
 
     if(!Exist(s,x)){
        return 0;
     }
     return LastIdx(s,x)-FirstIdx(s,x)+1;
 
}
 
 
void Clear(ordered_multiset &s){ //this function clears all the elements from the set.
 
     s.clear();
 
}
 
 
int Size(ordered_multiset &s){ //this function returns the size of the set.
 
     return (int)(s.size());
 
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    ll n;
    cin>>n;
    vector<pair<ll,ll>>v(n);
    for(ll i=0;i<n;i++){
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(),v.end());
    ordered_multiset st;
    st.insert(v[0].second);
    ll ans=0;
    //order_of_key is special fxn of set which returns no of elements in ordered set strictly< key value
    //find_by_order(k) returns an iterator to the kth element (counting from zero) in the set in O(logn) time
    //eg of find_by_order(k) ->s : {1, 5, 6, 17, 88}, then :*(s.find_by_order(2)) : 3rd element in the set i.e. 6
    for(ll i=1;i<n;i++){
        ans+=i-st.order_of_key(v[i].first);
        st.insert(v[i].second);
    }
    cout<<ans<<endl;
    return 0;
}
