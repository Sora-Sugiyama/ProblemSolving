#include "bits/stdc++.h"
using namespace std;

// https://cp-algorithms.com/graph/hungarian-algorithm.html
vector<int>Hungarian(int A[][203],const int &n){
    vector<int>u(n+2),v(n+2),p(n+2),way(n+2),ans(n+2);
    for(int i=1;i<=n;i++){
        p[0]=i;
        int j0=0;
        vector<int>minv(n+2,1e9);
        vector<bool>vis(n+2,false);
        do{
            vis[j0]=true;
            int i0=p[j0],delta=1e9,j1=0;
            for(int j=1;j<=n;j++){
                if(!vis[j]){
                    int cur=A[i0][j]-u[i0]-v[j];
                    if(cur<minv[j]){
                        minv[j]=cur;
                        way[j]=j0;
                    }
                    if(minv[j]<delta){
                        delta=minv[j];
                        j1=j;
                    }
                }
            }
            
            for(int j=0;j<=n;j++){
                if(vis[j]){
                    u[p[j]]+=delta;
                    v[j]-=delta;
                }else{
                    minv[j]-=delta;
                }
            }
            j0=j1;
        }while(p[j0]);
        
        do{
            int j1=way[j0];
            p[j0]=p[j1];
            j0=j1;
        }while(j0);
    }
    
    for(int j=1;j<=n;j++){
        ans[p[j]]=j;
    }
    
    return ans;
}

int arr[203][203];
int main(){
    freopen("File","r",stdin);
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N;cin>>N;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=N;j++)cin>>arr[i][j];
    }
    
    auto res=Hungarian(arr,N);
    
    int ans=0;
    for(int i=1;i<=N;i++){
        ans+=arr[i][res[i]];
    }
    cout<<ans<<"\n";
    return 0;
}
