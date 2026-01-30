#include "bits/stdc++.h"
#define fi first
#define se second
using namespace std;

vector<vector<int> >G;
vector<int>pU,pV,dist;
bool bfs(const int &n,const int &m){
    queue<int>q;
    for(int u=1;u<=n;u++){
        if(pU[u]==-1){
            dist[u]=0;
            q.push(u);
        }else{
            dist[u]=1e9;
        }
    }
    
    int found=false;
    while(!q.empty()){
        auto u=q.front();q.pop();
        if(dist[u]>=1e9)continue;
        for(auto v:G[u]){
            if(pV[v]==-1){
                found=true;
            }else if(dist[pV[v]]==1e9){
                dist[pV[v]]=dist[u]+1;
                q.push(pV[v]);
            }
        }
    }
    
    return found;
}

bool dfs(int u){
    for(auto v:G[u]){
        if(pV[v]==-1||(dist[pV[v]]==dist[u]+1&&dfs(pV[v]))){
            pV[v]=u;
            pU[u]=v;
            return true;
        }
    }
    dist[u]=1e9;
    return false;
}

int HopcraftKarp(const int &n,const int &m){
    pU.resize(n+2);
    pV.resize(m+2);
    dist.resize(n+2);
    fill(pU.begin(),pU.end(),-1);
    fill(pV.begin(),pV.end(),-1);
    
    int ret=0;
    while(bfs(n,m)){
        for(int u=1;u<=n;u++){
            if(pU[u]==-1&&dfs(u)){
                ret++;
            }
        }
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    using lf=double;
    using pdd=pair<lf,lf>;
    int N,M;cin>>N>>M;
    lf S,V;cin>>S>>V;
    vector<pdd>mouse(N+2);
    auto distEuc=[](pdd a,pdd b)->lf{
        return sqrt((a.fi-b.fi)*(a.fi-b.fi)+(a.se-b.se)*(a.se-b.se));
    };
    
    G.resize(N+3);
    for(int i=1;i<=N;i++)cin>>mouse[i].fi>>mouse[i].se;
    for(int i=1;i<=M;i++){
        pdd cur;cin>>cur.fi>>cur.se;
        for(int j=1;j<=N;j++){
            if(distEuc(mouse[j],cur)/V+1e-9>S){
                G[j].push_back(i);
            }
        }
    }
    cout<<HopcraftKarp(N, M)<<"\n";
    
    return 0;
}
