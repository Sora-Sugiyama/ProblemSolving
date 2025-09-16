#include "bits/stdc++.h"
using namespace std;

int SIZE;
vector<int>trie[9000003];
char ch[9000003];
void insert(string s){
    int p=0;
    for(auto c:s){
        for(auto u:trie[p]){
            if(ch[u]==c){
                p=u;
                goto nxt;
            }
        }
        trie[p].push_back(++SIZE);
        ch[SIZE]=c;
        p=SIZE;
        nxt:
    }
}

using ull=uint64_t;
constexpr ull mod=1e9+7;
ull dp[9000003],facto[30]={1};
ull f(int u){
    ull &ret=dp[u];
    dp[u]=1;
    ull cnt=0;
    for(int v:trie[u]){
        ret=ret*f(v)%mod;
        cnt++;
    }
    ret=ret*facto[cnt]%mod;
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    for(ull i=1;i<=27;i++)facto[i]=facto[i-1]*i%mod;
    int N;cin>>N;
    while(N--){
        string s;cin>>s;
        s=s+"@";
        insert(s);
    }
    cout<<f(0)<<"\n";
    return 0;
}
