#include "bits/stdc++.h"
using namespace std;
using ll=int_fast64_t;

template<ll p,ll R,ll N>
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
    const ll modinvR,modinvN;
public:
    NTT():modinvR(po(R,p-2)),modinvN(po(N,p-2)){
        w[0]=iw[0]=1;
        w[1]=R;
        iw[1]=modinvR;
        ll i=1;
        for(ll t=2;t<p;t<<=1,i++){
            w[i]=w[i-1]*w[i-1]%p;
            iw[i]=iw[i-1]*iw[i-1]%p;
        }
        for(ll t=i;t<64;t++){
            w[i]=iw[i]=1;
        }
        reverse(w.begin(),w.begin()+i);
        reverse(iw.begin(),iw.begin()+i);
    }
    
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
        for(i=0;i<N;i++)a[i]=a[i]*modinvN%p;
    }
};

constexpr ll po2[]={1,2,4,8,16,32,64,128,256,512,1024,2048,(1<<13),(1<<14),(1<<15),(1<<16),(1<<17),(1<<18),(1<<19),(1<<20),(1<<21),(1<<22)};

vector<ll> operator*(vector<ll>a,vector<ll>b){
    const ll N=po2[17],p=(17LL<<27)|1;
    NTT<p,3,N>X;
    a.resize(N);b.resize(N);
    X.FFT(a);X.FFT(b);
    for(int i=0;i<N;i++){
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
