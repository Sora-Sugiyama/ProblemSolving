#include <bits/stdc++.h>
using namespace std;
namespace str{
vector<int>CPF(string &s){ // Compute Prefix Function
    const int n=(int)s.size();
    vector<int>next(n);
    for(int i=1,j=0;i<n;i++){
        while(j>0&&s[i]!=s[j])j=next[j-1];
        if(s[i]==s[j])next[i]=++j;
    }
    return next;
}

vector<int>KMP(string &T,string &P){
    vector<int>next=CPF(P),ans;
    const int n=(int)T.size(),m=(int)P.size();
    for(int i=0,j=0;i<n;i++){
        while(j>0&&T[i]!=P[j])j=next[j-1];
        if(T[i]==P[j])j++;
        if(j==m)ans.push_back(i-m+2); // Position where P appears in T
    }
    return ans;
}

}
