// cp-algorithms.com/graph/dinic.html

#include "bits/stdc++.h"
using namespace std;
using ll=long long;

class Dinitz{
    struct Edge{
        int u,v;
        ll cap,flow;
        Edge(int u=0,int v=0,ll cap=0,ll flow=0):u(u),v(v),cap(cap),flow(flow){}
    };
    
    const ll inf=1e18;
    vector<Edge>edges;
    vector<vector<int> >G;
    int n,m=0;
    int src,sink;
    vector<int>level,ptr;
    queue<int>q;
    
public:
    Dinitz(int n,int src,int sink):n(n),src(src),sink(sink){
        G.resize(n+3);
        level.resize(n+3);
        ptr.resize(n+3);
    }
    
    void addEdge(int u,int v,ll cap){
        edges.push_back(Edge(u,v,cap));
        edges.push_back(Edge(v,u,0));
        G[u].push_back(m);
        G[v].push_back(m+1);
        m+=2;
    }
    
    bool bfs(){
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:G[u]){
                if(edges[v].cap==edges[v].flow||level[edges[v].v]!=-1)continue;
                level[edges[v].v]=level[u]+1;
                q.push(edges[v].v);
            }
        }
        return level[sink]!=-1;
    }
    
    ll dfs(int u,ll pushed){
        if(pushed==0)return 0;
        if(u==sink)return pushed;
        for(int &cid=ptr[u];cid<(int)G[u].size();cid++){
            int cur=G[u][cid];
            int v=edges[cur].v;
            if(level[u]+1!=level[v])continue;
            ll tr=dfs(v,min(pushed,edges[cur].cap-edges[cur].flow));
            if(tr==0)continue;
            edges[cur].flow+=tr;
            edges[cur^1].flow-=tr;
            return tr;
        }
        return 0;
    }
    
    ll flow(){
        ll f=0;
        while(1){
            fill(level.begin(),level.end(),-1);
            level[src]=0;
            q.push(src);
            if(!bfs())break;
            fill(ptr.begin(),ptr.end(),0);
            while(ll pushed=dfs(src,inf))f+=pushed;
        }
        return f;
    }
};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N,M,K;cin>>N>>M>>K;
    int src=2001,sink=2002,dummy=2003;
    Dinitz x(2003,src,sink);
    x.addEdge(src,dummy,K);
    for(int i=1;i<=M;i++){
        x.addEdge(i+1000,sink,1);
    }
    for(int i=1;i<=N;i++){
        int n;cin>>n;
        x.addEdge(src,i,1);
        x.addEdge(dummy,i,1);
        while(n--){
            int a;cin>>a;
            x.addEdge(i,1000+a,1);
        }
    }
    cout<<x.flow()<<"\n";
    
    return 0;
}
