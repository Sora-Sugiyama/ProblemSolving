#include "bits/stdc++.h"
#define fi first
#define se second
using namespace std;
using ull=unsigned long long;
constexpr ull on64=~0ULL,msb=1ULL<<63;
ull A[30][800],B[800],x[800],y[800];
inline ull mod64(const ull &x){
    return x-((x>>6)<<6);
}
int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    string S,T;cin>>S>>T;
    for(char c='A';c<='Z';c++){
        for(ull i=0;i<(ull)T.size();i++){
            if(T[i]==c){
                A[c-'A'][i>>6]|=1ULL<<mod64(i);
            }
        }
    }
    
    const ull N=(ull)T.size()>>6;
    for(ull i=0;i<(ull)S.size();i++){
        bool a=false,b=false;
        for(ull j=0;j<=N;j++){
            x[j]=A[S[i]-'A'][j]|B[j];
            y[j]=(B[j]<<1)|(j==0||a);
            a=bool(B[j]&msb);
            if(b&&y[j]<on64){
                y[j]+=1ULL;
                b=false;
            }
            if(x[j]<y[j])b=true;
            B[j]=(x[j]^(x[j]&(x[j]-y[j])));
        }
    }
    int ans=0;
    for(ull i=0;i<=N;i++){
        ans+=__builtin_popcountll(B[i]);
    }
    cout<<ans<<"\n";
    return 0;
}
