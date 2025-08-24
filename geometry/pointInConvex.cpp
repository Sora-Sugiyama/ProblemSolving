#include "bits/stdc++.h"
#define fi first
#define se second
using namespace std;
using ll=long long;
using pii=pair<ll,ll>;
using ppp=pair<pii,pii>;

inline int ccw(const pii &a,const pii &b,const pii &c){
    ll cp=(b.fi-a.fi)*(c.se-a.se)-(b.se-a.se)*(c.fi-a.fi);
    return cp>0?1:(cp<0?-1:0);
}

bool pointInConvex(vector<pii>&hull,pii point){
    const int n=(int)hull.size();
    
    if(ccw(hull[0],hull[n-1],point)>0)return false;
    if(ccw(hull[0],hull[1],point)<0)return false;
    
    int le=1,ri=n-2,ans=1;
    while(le<=ri){
        int mid=(le+ri)>>1;
        if(ccw(hull[0],hull[mid],point)>0){
            ans=mid;
            le=mid+1;
        }else ri=mid-1;
    }
    return ccw(hull[ans],hull[ans+1],point)>0;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N,M,K;cin>>N>>M>>K;;
    vector<pii>hullA(N),hullB(M);
    for(auto &p:hullA)cin>>p.fi>>p.se;
    for(auto &p:hullB)cin>>p.fi>>p.se;
    
    int cnt=0;
    for(int i=0;i<K;i++){
        pii cur;cin>>cur.fi>>cur.se;
        cnt+=pointInConvex(hullA, cur)&&!pointInConvex(hullB, cur);
    }
    cout<<(cnt==K?"YES":to_string(K-cnt))<<"\n";
    return 0;
}
