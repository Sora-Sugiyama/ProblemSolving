#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
namespace data_structure{
using ll=long long;
class disjoint_set{
    vector<int>pos;
    vector<ll>w;
    int i,z,tmp;
public:
    disjoint_set(int n=0){
        pos.resize(n+1);
        w=vector<ll>(n+1,1);
        for(i=1;i<=n;i++)pos[i]=i;
    }
    ~disjoint_set(){
        pos.clear();
        w.clear();
    }
    
    int find(int x){
        if(x==pos[x])return x;
        z=x;
        while(z!=pos[z])z=pos[z];
        while(x!=pos[x]){
            tmp=x;
            x=pos[x];
            pos[tmp]=z;
        }
        pos[x]=z;
        return z;
    }
    
    void uni(int x,int y){
        x=find(x);
        while(y!=pos[y]){
            tmp=y;
            y=pos[y];
            pos[tmp]=x;
        }
        if(x!=y){
            pos[y]=x;
            w[x]+=w[y];
            w[y]=0;
        }
    }
};
}
