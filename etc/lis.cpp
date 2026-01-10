#include "bits/stdc++.h"
#define fi first
#define se second
using namespace std;
using lf=double;
using ll=long long;
using ull=unsigned long long;
using pii=pair<int,int>;
using ppp=pair<pii,pii>;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N;cin>>N;
    vector<int>vi,arr(N+3),anc(N+3),idx(N+3);
    cin>>arr[1];
    vi={arr[1]};
    idx[0]=1;
    anc[1]=-1;
    for(int i=2;i<=N;i++){
        cin>>arr[i];
        if(vi.back()<arr[i]){
            vi.push_back(arr[i]);
            idx[vi.size()-1]=i;
            anc[i]=idx[vi.size()-2];
        }else{
            int pos=int(lower_bound(vi.begin(),vi.end(),arr[i])-vi.begin());
            vi[pos]=arr[i];
            idx[pos]=i;
            if(pos>0){
                anc[i]=idx[pos-1];
            }else{
                anc[i]=-1;
            }
        }
    }
    cout<<vi.size()<<"\n";
    
    stack<int>stk;
    int u=idx[vi.size()-1];
    while(u>=0){
        stk.push(arr[u]);
        u=anc[u];
    }
    while(!stk.empty()){
        cout<<stk.top()<<" ";
        stk.pop();
    }
    cout<<"\n";
    
    return 0;
}
