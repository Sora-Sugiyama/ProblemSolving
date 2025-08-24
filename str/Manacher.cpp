#include "bits/stdc++.h"
using namespace std;
using ll=long long;

vector<int>Manacher(string s){
    string T="@";
    for(auto c:s){
        T.push_back(c);
        T.push_back('@');
    }
    const int n=(int)T.size();
    int r=0,p=0;
    vector<int>arr(n+3),ans(s.size());
    for(int i=0;i<n;i++){
        if(i<=r)arr[i]=min(arr[2*p-i],r-i);else arr[i]=0;
        while(i-arr[i]-1>=0&& i+arr[i]+1<n&&T[i-arr[i]-1]==T[i+arr[i]+1])arr[i]++;
        if(arr[i]+i>r){
            r=arr[i]+i;
            p=i;
        }
        if(i&1)ans[i>>1]=arr[i];
    }
    return arr;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    string T;cin>>T;
    vector<int>arr=Manacher(T);
    cout<<*max_element(arr.begin(),arr.end())<<"\n";
    return 0;
}
