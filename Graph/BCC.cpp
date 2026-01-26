#include "bits/stdc++.h"
using namespace std;
using pii = pair<int,int>;

vector<vector<int> > G;
int dfsn[100003], dcnt=0;
vector<vector<pii> > bccs;
stack<pii> stk;
int pos[100003], id=0;

int dfs(int x,int anc){
    dfsn[x] = ++dcnt;
    int ret=dfsn[x];
    for(auto y:G[x]){
        if(y==anc)continue;
        if(dfsn[x]>dfsn[y])stk.push(pii{x,y});
        if(dfsn[y]>0)ret=min(ret,dfsn[y]);
        else{
            const int nxt=dfs(y,x);
            ret=min(nxt,ret);
            if(nxt>=dfsn[x]){
                bccs.emplace_back();
                while(stk.top() != pii{x,y}){
                    bccs.back().push_back(stk.top());
                    stk.pop();
                }
                bccs.back().push_back(stk.top());
                stk.pop();
            }
        }
    }
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int N,M; cin>>N>>M;
    G.resize(N+3);
    while(M--){
        int x,y; cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    
    for(int i=1; i<=N; ++i){
        if(!dfsn[i])dfs(i,-1);
    }
    
    set<int>anc;
    for(auto &bcc:bccs){
        ++id;
        for(auto &e:bcc){
            if(pos[e.first]>0 && pos[e.first]!=id)anc.insert(e.first);
            else pos[e.first]=id;
            if(pos[e.second]>0 && pos[e.second]!=id)anc.insert(e.second);
            else pos[e.second]=id;
        }
    }
    
    cout<<anc.size()<<"\n";
    for(auto x:anc)cout<<x<<" ";
    cout<<"\n";
    
    return 0;
}
