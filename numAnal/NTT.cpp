#include "bits/stdc++.h"
using namespace std;
using ll=long long;
constexpr ll p=(17LL<<27)|1,R=3,N=(1<<21);
ll po(ll a,ll b){
    ll ret=1;
    while(b){
        if(b&1)ret=ret*a%p;
        a=a*a%p;b>>=1;
    }
    return ret;
}

constexpr ll modinvR=760567126; // modinvR=po(R,p-2);
void FFT(vector<ll>&a){
    ll i,j,k,x,y,z,t;
    for(i=1,j=0;i<N;i++){
        for(k=N>>1;k<=j;k>>=1)j-=k;
        j+=k;
        if(i<j)swap(a[i],a[j]);
    }
    for(i=1,t=1;i<N;i<<=1,t++){
        x=po(R,p>>t);
        for(j=0;j<N;j+=i<<1){
            y=1;
            for(k=0;k<i;k++){
                z=a[i|j|k]*y%p;
                a[i|j|k]=(a[j|k]-z+p)%p;
                a[j|k]=(a[j|k]+z)%p;
                y=y*x%p;
            }
        }
    }
}
void iFFT(vector<ll>&a){
    ll i,j,k,x,y,z,t;
    for(i=1,j=0;i<N;i++){
        for(k=N>>1;k<=j;k>>=1)j-=k;
        j+=k;
        if(i<j)swap(a[i],a[j]);
    }
    for(i=1,t=1;i<N;i<<=1,t++){
        x=po(modinvR,p>>t);
        for(j=0;j<N;j+=i<<1){
            y=1;
            for(k=0;k<i;k++){
                z=a[i|j|k]*y%p;
                a[i|j|k]=(a[j|k]-z+p)%p;
                a[j|k]=(a[j|k]+z)%p;
                y=y*x%p;
            }
        }
    }
    const ll modinvN=po(N,p-2);
    for(i=0;i<N;i++)a[i]=a[i]*modinvN%p;
}
