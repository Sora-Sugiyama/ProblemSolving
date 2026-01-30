#include "bits/stdc++.h"
using namespace std;

vector<vector<int> > G;
vector<int> pU, pV, dist;
bool bfs(const int &n, const int &m){
    queue<int> q;
    for(int u=1; u<=n; ++u){
        if(pU[u]==-1){
            dist[u]=0;
            q.push(u);
        }else{
            dist[u]=1e9;
        }
    }
    
    int found = false;
    while(!q.empty()){
        auto u = q.front(); q.pop();
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
        if(pV[v]==-1 || (dist[pV[v]]==dist[u]+1 && dfs(pV[v]))){
            pV[v]=u;
            pU[u]=v;
            return true;
        }
    }
    
    dist[u]=1e9;
    return false;
}

int HopcraftKarp(const int &n, const int &m){
    pU.resize(n+2);
    pV.resize(m+2);
    dist.resize(n+2);
    fill(pU.begin(), pU.end(), -1);
    fill(pV.begin(), pV.end(), -1);
    
    int ret=0;
    while(bfs(n,m)){
        for(int u=1; u<=n; ++u){
            if(pU[u]==-1 && dfs(u)){
                ++ret;
            }
        }
    }
    
    return ret;
}
