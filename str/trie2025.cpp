#include "bits/stdc++.h"
using namespace std;

int trie[20003][256],SIZE,mp[256],eos[20003],mark[20003];
void insert(string s){
    int p=0;
    for(auto c:s){
        int &u=trie[p][mp[c]];
        if(!u)u=++SIZE;
        p=u;
    }
    eos[p]++;
}

void marking(string s){
    int p=0;
    mark[p]++;
    for(auto c:s){
        int &u=trie[p][mp[c]];
        if(!u)return;
        p=u;
        mark[u]++;
    }
}

int solve5446(){
    queue<int>q;q.push(0);
    
    int ans=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        if(mark[u]==0){
            ans++;
            continue;
        }
        if(eos[u])ans++;
        for(int i=0;i<256;i++){
            int &v=trie[u][i];
            if(v)q.push(v);
        }
    }
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    for(int i=0;i<256;i++)mp[i]=i;
    int T;cin>>T;
    while(T--){
        memset(trie,0,sizeof(trie));
        memset(eos,0,sizeof(eos));
        memset(mark,0,sizeof(mark));
        SIZE=0;
        int N1;cin>>N1;
        while(N1--){
            string s;cin>>s;
            insert(s);
        }
        int N2;cin>>N2;
        while(N2--){
            string s;cin>>s;
            marking(s);
        }
        cout<<solve5446()<<"\n";
    }
    
    return 0;
}
 
