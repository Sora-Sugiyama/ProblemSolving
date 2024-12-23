#include <bits/stdc++.h>
using namespace std;
namespace str{

/*
 Reference:
 Juha Kärkkäinen, Peter Sanders, and Stefan Burkhardt. 2006. Linear work suffix array construction. J. ACM 53, 6 (November 2006), 918–936. https://doi.org/10.1145/1217856.1217858
 */

inline bool leq(int a1,int a2,int b1,int b2){return a1<b1||(a1==b1&&a2<b2);}
inline bool leq(int a1,int a2,int a3,int b1,int b2,int b3){return a1<b1||(a1==b1&&leq(a2,a3,b2,b3));}

static void radixPass(vector<int>&a,vector<int>&b,vector<int>&r,const int &n,const int &K){
    vector<int>c(K+1);
    int i,sum,tmp;
    for(i=0;i<=K;i++)c[i]=0;
    for(i=0;i<n;i++)c[r[a[i]]]++;
    for(i=0,sum=0;i<=K;i++){tmp=c[i];c[i]=sum;sum+=tmp;}
    for(i=0;i<n;i++)b[c[r[a[i]]]++]=a[i];
}

void suffixArray(vector<int>&T,vector<int>&SA,const int &n,const int &K){
    const int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
    vector<int>R(n02+3);R[n02]=R[n02+1]=R[n02+2]=0;
    vector<int>SA12(n02+3);SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    vector<int>R0(n0);
    vector<int>SA0(n0);
    int i,j,p,t,k;

    for(i=0,j=0;i<n+n0-n1;i++){if(i%3){R[j++]=i;}}
    
    vector<int>T2(T.begin()+2,T.end()),T1(T.begin()+1,T.end());
    radixPass(R,SA12,T2,n02,K);
    radixPass(SA12,R,T1,n02,K);
    radixPass(R,SA12,T,n02,K);
    
    int name=0,c0=-1,c1=-1,c2=-1;
    for(i=0;i<n02;i++){
        if(T[SA12[i]]!=c0||T[SA12[i]+1]!=c1||T[SA12[i]+2]!=c2){name++;c0=T[SA12[i]];c1=T[SA12[i]+1];c2=T[SA12[i]+2];}
        if(SA12[i]%3==1)R[SA12[i]/3]=name;
        else R[SA12[i]/3+n0]=name;
    }
    if(name<n02){
        suffixArray(R,SA12,n02,name);
        for(i=0;i<n02;i++)R[SA12[i]]=i+1;
    }else{
        for(i=0;i<n02;i++)SA12[R[i]-1]=i;
    }
    
    for(i=0,j=0;i<n02;i++){if(SA12[i]<n0){R0[j++]=SA12[i]+SA12[i]+SA12[i];}}
    radixPass(R0,SA0,T,n0,K);
    
    for(p=0,t=n0-n1,k=0;k<n;k++){
        i=SA12[t]<n0?(SA12[t]+SA12[t]+SA12[t]+1):(SA12[t]+SA12[t]+SA12[t]-n0-n0-n0+2);
        j=SA0[p];
        if(SA12[t]<n0?leq(T[i],R[SA12[t]+n0],T[j],R[j/3]):leq(T[i],T[i+1],R[SA12[t]-n0+1],T[j],T[j+1],R[j/3+n0])){
            SA[k]=i;t++;
            if(t==n02){
                for(k++;p<n0;p++,k++)SA[k]=SA0[p];
            }
        }else{
            SA[k]=j;p++;
            if(p==n0){
                for(k++;t<n02;t++,k++)SA[k]=SA12[t]<n0?(SA12[t]+SA12[t]+SA12[t]+1):(SA12[t]+SA12[t]+SA12[t]-n0-n0-n0+2);
            }
        }
    }
}

vector<int>SA(string &T){
    const int n=(int)T.size()+3;
    const int m=n+n/3;
    vector<int>tmp(m),SA(n-3),garSA(m);
    tmp[0]=tmp[1]=tmp[2]=0;
    int i;
    
    /*
    for(i=3;i<n;i++)tmp[i]=T[i-3];
    suffixArray(tmp,garSA,n,255);
     */
    
     // if there are only small letters:
    for(i=3;i<n;i++)tmp[i]=T[i-3]-'a'+1;
    suffixArray(tmp,garSA,n,30);
     
    /*
     // if there are only small and big letters: (eng alphabet only)
     for(i=3;i<n;i++){
        if(tmp[i]>='a')tmp[i]=T[i-3]-'a'+30;
        else tmp[i]=T[i-3]-'A'+1;
     }
     suffixArray(tmp,garSA,n,60);
     */
    
    for(i=3;i<n;i++)SA[i-3]=garSA[i]-2;
    
    return SA;
}

vector<int>LCPA(string &T,vector<int>&SA){
    const int n=(int)SA.size();
    vector<int>lcpA(n),RA(n);
    int clcp=0,i=0,j=0;
    for(i=0;i<n;i++)RA[SA[i]-1]=i;
    lcpA[0]=-1;
    for(i=0;i<n;i++)if(RA[i]){
        j=SA[RA[i]-1]-1;
        while(T[i+clcp]==T[j+clcp])clcp++;
        lcpA[RA[i]]=clcp;
        clcp=max(clcp-1,0);
    }
    return lcpA;
}
}
