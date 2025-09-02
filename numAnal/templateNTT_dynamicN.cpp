#include "bits/stdc++.h"
using namespace std;
using ll=int_fast64_t;

template<ll p,ll R>
class NTT{
    ll po(ll a,ll b){
        ll ret=1;
        while(b){
            if(b&1)ret=ret*a%p;
            a=a*a%p;b>>=1;
        }
        return ret;
    }
    array<ll,64>w,iw;
    ll modinvR,modinvN;
public:
    ll N;
    NTT(ll n){
        N=1;
        while(N<n)N<<=1;
        modinvR=po(R,p-2);modinvN=po(N,p-2);
        
        ll i=1;
        for(ll t=2;t<p;t<<=1,i++);
        i--;
        w[i]=R; iw[i]=modinvR;
        for(ll t=i+1;t<64;t++){
            w[t]=iw[t]=1;
        }
        i--;
        for(;i>0;i--){
            w[i]=w[i+1]*w[i+1]%p;
            iw[i]=iw[i+1]*iw[i+1]%p;
            if((p>>i)&1){
                w[i]=w[i]*R%p;
                iw[i]=iw[i]*modinvR%p;
            }
        }
    }
    
    void FFT(vector<ll>&a){
        ll i,j,k,x,y,z,t;
        for(i=1,j=0;i<N;i++){
            for(k=N>>1;k<=j;k>>=1)j-=k;
            j+=k;
            if(i<j)swap(a[i],a[j]);
        }
        for(i=1,t=1;i<N;i<<=1,t++){
            x=w[t];
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
            x=iw[t];
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
        for(i=0;i<N;i++)a[i]=a[i]*modinvN%p;
    }
};

constexpr ll po2[]={1,2,4,8,16,32,64,128,256,512,1024,2048,(1<<13),(1<<14),(1<<15),(1<<16),(1<<17),(1<<18),(1<<19),(1<<20),(1<<21),(1<<22)};
constexpr ll primes[]={998244353, 167772161, 469762049};

vector<ll> operator*(vector<ll>a,vector<ll>b){
    const ll p=(17LL<<27)|1;
    NTT<p,3>X(a.size()+b.size());
    a.resize(X.N);b.resize(X.N);
    X.FFT(a);X.FFT(b);
    for(int i=0;i<X.N;i++){
        a[i]=a[i]*b[i]%p;
    }
    X.iFFT(a);
    return a;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int N;cin>>N;
    vector<ll>a(N+N),b(N);
    for(int i=0;i<N;i++){
        cin>>a[i];
        a[N+i]=a[i];
    }
    for(int i=0;i<N;i++)cin>>b[i];
    reverse(b.begin(),b.end());
    a=a*b;
    ll mx=0;
    for(int i=N;i<N+N;i++){
        mx=max(mx,a[i]);
    }
    cout<<mx<<"\n";
    return 0;
}
