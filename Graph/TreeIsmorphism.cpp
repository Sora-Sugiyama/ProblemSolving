#include "bits/stdc++.h"
using namespace std;

void dfs(int x,vector<vector<int> >&G,vector<int>&dp){
    dp[x]=1;
    for(int y:G[x]){
        dfs(y,G,dp);
        dp[x]+=dp[y];
    }
}

vector<int>findCent(vector<vector<int> >&G,const int &n){
    vector<int>dp(n+2);
    dfs(1,G,dp);
    vector<int>cents;
    for(int x=1;x<=n;x++){
        if(dp[x]<(n>>1))continue;
        for(int y:G[x]){
            if(dp[y]>(n>>1))goto skip;
        }
        cents.push_back(x);
        skip:
    }
    return cents;
}

string AHU(vector<vector<int> >&G,const int root){
    string ret="";
    vector<bool>vis(G.size());
    vis[root]=true;
    function<string(int)>f=[&G,&vis,&f](int x)->string{
        string cur="0";
        vector<string>vs;
        for(int y:G[x]){
            if(!vis[y]){
                vis[y]=true;
                vs.push_back(f(y));
            }
        }
        sort(vs.begin(),vs.end());
        for(auto &s:vs)cur+=s;
        cur+="1";
        return cur;
    };
    return f(root);
}

string treeHash(vector<vector<int> >&G,const int &n){
    auto cents=findCent(G,n);
    {
        vector<bool>vis(G.size());
        queue<int>q;q.push(1);
        vis[1]=true;
        while(!q.empty()){
            int u=q.front();q.pop();
            for(int v:G[u]){
                if(!vis[v]){
                    vis[v]=true;
                    q.push(v);
                    G[v].push_back(u);
                }
            }
        }
    }
    
    string ret="~";
    for(auto cent:cents)ret=min(ret,AHU(G,cent));
    
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int T;cin>>T;cin.ignore();
    while(T--){
        string a,b;
        getline(cin,a);
        getline(cin,b);
        if(a.size()!=b.size()){
            cout<<"0\n";
            continue;
        }
        const int n=(int)a.size()>>1;
        vector<vector<int> >Ga(n+2),Gb(n+2);
        vector<int>anca(n+2),ancb(n+2);
        int cnt,u;
        
        u=1;cnt=1;
        for(auto c:a){
            if(c=='0'){
                Ga[u].push_back(++cnt);
                anca[cnt]=u;
                u=cnt;
            }else{
                u=anca[u];
            }
        }
        u=1;cnt=1;
        for(auto c:b){
            if(c=='0'){
                Gb[u].push_back(++cnt);
                ancb[cnt]=u;
                u=cnt;
            }else{
                u=ancb[u];
            }
        }
        cout<<(treeHash(Ga,n)==treeHash(Gb,n))<<"\n";
    }
    return 0;
}
