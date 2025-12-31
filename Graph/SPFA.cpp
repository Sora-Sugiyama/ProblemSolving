#include "bits/stdc++.h"
using namespace std;
using ll=long long;

bool spfa(int N, int src, vector<ll>&dist, vector<vector<pair<int,ll> > >&G){
    vector<int8_t>inQ(N+3);
    vector<int>cnt(N+3);
    queue<int>q; q.push(src);
    inQ[src]=1;
    cnt[src]=1;
    dist[src]=0;
    while(!q.empty()){
        auto u=q.front();q.pop();
        inQ[u]=false;
        for(auto [v,w]:G[u]){
            if(dist[v]>dist[u]+w){
                dist[v]=dist[u]+w;
                if(!inQ[v]){
                    cnt[v]++;
                    if(cnt[v]>=N)return false;
                    q.push(v);
                    inQ[v]=true;
                }
            }
        }
    }
    return true;
}
