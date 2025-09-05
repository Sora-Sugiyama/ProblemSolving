#include "bits/stdc++.h"
using namespace std;
vector<vector<int> >G,GT,SCC;
vector<bool>vis;
stack<int>stk;
vector<int>cn;
int N,M;

void DFS(int x,const bool T){
    vector<int>&g=T?GT[x]:G[x];
    for(int y:g){
        if(vis[y])continue;
        vis[y]=true;
        if(T){
            SCC.back().push_back(y);
            cn[y]=(int)SCC.size();
        }
        DFS(y,T);
    }
    if(!T)stk.push(x);
}

inline int NOT(const int &x){
    return x<=N?x+N:x-N;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    cin>>N>>M;
    G.resize(2*N+2);GT.resize(2*N+2);
    cn.resize(2*N+2);
    for(int i=0;i<M;i++){
        int x,y;cin>>x>>y;
        if(x<0)x=N-x;
        if(y<0)y=N-y;
        G[NOT(x)].push_back(y);
        GT[y].push_back(NOT(x));
        G[NOT(y)].push_back(x);
        GT[x].push_back(NOT(y));
    }
    vis.resize(2*N+2);
    for(int x=1;x<=2*N;x++){
        if(vis[x])continue;
        vis[x]=true;
        DFS(x,false);
    }
    
    fill(vis.begin(),vis.end(),false);
    while(!stk.empty()){
        int x=stk.top();stk.pop();
        if(vis[x])continue;
        vis[x]=true;
        SCC.push_back({x});
        cn[x]=(int)SCC.size();
        DFS(x,true);
    }
    bool ans=true;
    for(int i=1;i<=N;i++)ans&=(cn[i]!=cn[i+N]);
    cout<<ans<<"\n";
    if(ans){
        for(int i=1;i<=N;i++)cout<<(cn[i]>cn[i+N])<<" ";
        cout<<"\n";
    }
    return 0;
}
