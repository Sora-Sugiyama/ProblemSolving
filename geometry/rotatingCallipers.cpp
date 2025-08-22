#include "bits/stdc++.h"
#define fi first
#define se second
using namespace std;
using ll=long long;
using pii=pair<ll,ll>;
using ppp=pair<pii,pii>;
constexpr pii O(0,0);

inline int ccw(const pii &a,const pii &b,const pii &c){
    ll cp=(b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi);
    return cp>0?1:(cp<0?-1:0);
}

pii operator-(const pii &a,const pii &b){
    return pii(a.fi-b.fi,a.se-b.se);
}

inline ll dist(const pii &a,const pii &b){
    return (a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se);
}

ll rotatingCallipers(vector<pii>arr,const int &n){
    vector<pii>hull(n+n);
    sort(arr.begin(),arr.end());
    
    int k=0;
    for(auto &p:arr){
        while(k>=2&&ccw(hull[k-2],hull[k-1],p)<=0)k--;
        hull[k++]=p;
    }
    for(int i=n-2,t=k+1;i>=0;i--){
        while(k>=t&&ccw(hull[k-2],hull[k-1],arr[i])<=0)k--;
        hull[k++]=arr[i];
    }
    k--;
    
    auto nexti=[k](const int idx)->int{
        return idx+1==k?0:idx+1;
    };
    
    ll ret=0;
    for(int i=0,j=1;i<k;i++){
        pii p=hull[nexti(i)]-hull[i];
        while(ccw(O,p,hull[nexti(j)]-hull[j])>0)j=nexti(j);
        ret=max(ret,dist(hull[i],hull[j]));
    }
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int n;cin>>n;
    vector<pii>arr(n);
    for(int i=0;i<n;i++)cin>>arr[i].fi>>arr[i].se;
    cout<<rotatingCallipers(arr, n)<<"\n";;
    return 0;
}
