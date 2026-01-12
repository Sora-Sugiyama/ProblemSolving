#include "bits/stdc++.h"
using namespace std;
using ll=long long;
array<ll,3> extgcd(const ll a,const ll b){
    ll r0=a,r=b,s0=1,s=0,t0=0,t=1;
    while(r){
        ll q=r0/r,tmp=r;
        r=r0-q*r;r0=tmp;
        tmp=s; s=s0-q*s; s0=tmp;
        tmp=t; t=t0-q*t; t0=tmp;
    }
    
    return {r0,s0,t0};
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    
    int t;cin>>t;
    while(t--){
        ll K,C; cin>>K>>C;
        auto [GCD,s,t]=extgcd(K,C);
        if(GCD!=1){
            cout<<"IMPOSSIBLE\n";
        }else{
            if(s<0)s+=(-s+C-1)/C*C;
            ll X=C-s;
            if(X<0)X+=(-X+C-1)/C*C;
            ll ans=(X*K+1)/C;
            if(ans>(ll)1e9)cout<<"IMPOSSIBLE\n";
            else cout<<(X*K+1)/C<<"\n";
        }
    }
    return 0;
}
