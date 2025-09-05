#include "bits/stdc++.h"
using namespace std;
vector<vector<int> >G,GT,SCC;
vector<bool>vis;
stack<int>stk;

void DFS(int x,const bool T){
    vector<int>&g=T?GT[x]:G[x];
    for(int y:g){
        if(vis[y])continue;
        vis[y]=true;
        if(T)SCC.back().push_back(y);
        DFS(y,T);
    }
    if(!T)stk.push(x);
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int V,E;cin>>V>>E;
    G.resize(V+2);GT.resize(V+2);
    for(int i=0;i<E;i++){
        int x,y;cin>>x>>y;
        G[x].push_back(y);
        GT[y].push_back(x);
    }
    vis.resize(V+2);
    for(int x=1;x<=V;x++){
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
        DFS(x,true);
    }
    
    cout<<SCC.size()<<"\n";
    for(auto &v:SCC)sort(v.begin(),v.end());
    sort(SCC.begin(),SCC.end());
    for(auto &v:SCC){
        for(int &x:v)cout<<x<<" ";
        cout<<"-1\n";
    }
    
    return 0;
}
