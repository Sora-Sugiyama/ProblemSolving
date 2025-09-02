#include "bits/stdc++.h"
using namespace std;
using ll=int64_t;

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

constexpr ll nttP[]={998244353, 167772161, 469762049},nttR[]={3,3,3};
constexpr ll nttN=2048;
NTT<nttP[0],nttR[0],nttN>X0;
NTT<nttP[1],nttR[1],nttN>X1;
NTT<nttP[2],nttR[2],nttN>X2;

vector<ll> operator*(const vector<ll>&a,const vector<ll>&b){
    vector<ll>a0(a),a1(a),a2(a),b0(b),b1(b),b2(b);
    X0.FFT(a0);X0.FFT(b0); X1.FFT(a1);X1.FFT(b1); X2.FFT(a2);X2.FFT(b2);
    for(int i=0;i<nttN;i++){
        a0[i]=a0[i]*b0[i]%nttP[0];
        a1[i]=a1[i]*b1[i]%nttP[1];
        a2[i]=a2[i]*b2[i]%nttP[2];
        ll v1=(m)
    }
    vector<ll>ret(nttN);
    return a;
}

int main(){
    freopen("File","r",stdin);
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
