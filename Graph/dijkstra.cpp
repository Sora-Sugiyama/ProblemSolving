#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
namespace Graph{
using ll=long long;
class graph{
    int i,V;
    struct node{
        ll v,w;
        node(ll V=0,ll W=0){
            v=V;w=W;
        }
        ~node(){};
        bool operator<(const node &ref) const{
            return w>ref.w;
        }
        bool operator>(const node &ref) const{
            return w<ref.w;
        }
    };
    vector<vector<node> >G;
public:
    graph(int N=0){
        V=N;
        G.resize(V+1);
    }
    ~graph(){
        V=0;
        G.clear();
    }
    
    vector<ll>Dijkstra(int src){
        vector<ll>dist(V+1,9e18);
        priority_queue<node>pq;
        pq.push(node(src,0));
        dist[src]=0;
        node x;
        while(!pq.empty()){
            x=pq.top();pq.pop();
            if(dist[x.v]<x.w)continue;
            for(node &y:G[x.v]){
                if(dist[y.v]>y.w+x.w){
                    dist[y.v]=y.w+x.w;
                    pq.push(node(y.v,x.w+y.w));
                }
            }
        }
        return dist;
    }
    
    void add_edge(ll x,ll y,ll w=1){
        G[x].push_back({y,w});
    }
    void add_undirected_edge(ll x,ll y,ll w=1){
        G[x].push_back(node(y,w));
        G[y].push_back(node(x,w));
    }
};
}
