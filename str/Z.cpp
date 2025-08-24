#include "bits/stdc++.h"
using namespace std;
using ll=long long;

vector<int>Z(string s){
    const int n=(int)s.size();
    vector<int>z(n);z[0]=n;
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r){
            l=i;
            r=i+z[i];
        }
    }
    return z;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    string S;cin>>S;
    vector<int>zrr=Z(string(S.rbegin(),S.rend()));
    int M;cin>>M;
    while(M--){
        int i;cin>>i;
        cout<<zrr[S.size()-i]<<"\n";
    }
    return 0;
}
