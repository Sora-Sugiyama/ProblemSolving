#include "bits/stdc++.h"
using namespace std;
using ll=int64_t;

template<ll p,ll R,ll N>
class NTT{
    const ll modinvR,modinvN;
    
public:
    ll po(ll a,ll b){
        ll ret=1;
        while(b){
            if(b&1)ret=ret*a%p;
            a=a*a%p;b>>=1;
        }
        return ret;
    }
    
    NTT():modinvR(po(R,p-2)),modinvN(po(N,p-2)){}
    
    void FFT(vector<ll>&a){
        ll i,j,k,x,y,z,t;
        for(i=1,j=0;i<N;++i){
            for(k=N>>1;k<=j;k>>=1)j-=k;
            j+=k;
            if(i<j)swap(a[i],a[j]);
        }
        for(i=1,t=1;i<N;i<<=1,++t){
            x=po(R,p>>t);
            for(j=0;j<N;j+=i<<1){
                y=1;
                for(k=0;k<i;++k){
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
        for(i=1,j=0;i<N;++i){
            for(k=N>>1;k<=j;k>>=1)j-=k;
            j+=k;
            if(i<j)swap(a[i],a[j]);
        }
        for(i=1,t=1;i<N;i<<=1,++t){
            x=po(modinvR,p>>t);
            for(j=0;j<N;j+=i<<1){
                y=1;
                for(k=0;k<i;++k){
                    z=a[i|j|k]*y%p;
                    a[i|j|k]=(a[j|k]-z+p)%p;
                    a[j|k]=(a[j|k]+z)%p;
                    y=y*x%p;
                }
            }
        }
        for(i=0;i<N;++i)a[i]=a[i]*modinvN%p;
    }
};

constexpr ll nttP[]={998244353, 167772161, 469762049},nttR[]={3,3,3};
constexpr ll nttN=128;
NTT<nttP[0],nttR[0],nttN>X0;
NTT<nttP[1],nttR[1],nttN>X1;
NTT<nttP[2],nttR[2],nttN>X2;

constexpr ll p=31991;
vector<ll> operator*(const vector<ll>&a,const vector<ll>&b){
    vector<ll>a0(a),a1(a),a2(a),b0(b),b1(b),b2(b);
    X0.FFT(a0);X0.FFT(b0); X1.FFT(a1);X1.FFT(b1); X2.FFT(a2);X2.FFT(b2);
    vector<ll>ret(nttN);
    for(int i=0;i<nttN;++i){
        a0[i]=a0[i]*b0[i]%nttP[0];
        a1[i]=a1[i]*b1[i]%nttP[1];
        a2[i]=a2[i]*b2[i]%nttP[2];
    }
    X0.iFFT(a0); X1.iFFT(a1); X2.iFFT(a2);
    
    for(int i=0;i<nttN;++i){
        ll c1=a0[i];
        ll c2=(a1[i]-c1%nttP[1]+nttP[1])%nttP[1]*X1.po(nttP[0],nttP[1]-2)%nttP[1];
        ll c3=(a2[i]-(c1+c2*nttP[0])%nttP[2]+nttP[2])%nttP[2]*X2.po(nttP[0]*nttP[1]%nttP[2],nttP[2]-2)%nttP[2];
        ret[i]=(c1+c2*nttP[0]%p+c3*nttP[0]%p*nttP[1]%p)%p;
    }
    
    return ret;
}

vector<ll> operator-(const vector<ll> &ref){
    vector<ll>ret(ref.begin(),ref.end());
    for(int i=1;i<nttN;i+=2)ret[i]=(p-ret[i])%p;
    return ret;
}

vector<ll>BMsub(const vector<ll>&ref,const int isOdd=0){
    vector<ll>ret(nttN);
    int k=0;
    for(int i=isOdd;i<nttN;i+=2)ret[k++]=ref[i];
    return ret;
}

NTT<p,1,1>X;
ll BostanMori(ll N,vector<ll>P,vector<ll>Q){
    while(N){
        vector<ll>mQ=-Q;
        vector<ll>U=P*mQ;
        P=BMsub(U,N&1);
        Q=BMsub(Q*mQ);
        N>>=1;
    }
    return P[0]*X.po(Q[0],p-2)%p;
}

ll getNthValue(int k, ll n, vector<ll> initTerms, vector<ll> coeffs){
    vector<ll> P(nttN, 0), Q(nttN, 0);
    
    for(int i=0;i<k;++i){
        P[i]=initTerms[i]%p;
    }
    
    Q[0]=1;
    for(int i=1;i<=k;++i){
        Q[i]=(p-coeffs[i-1]%p)%p;
    }
    
    P=P*Q;
    fill(P.begin()+k,P.end(),0);
    
    return BostanMori(n, P, Q)%p;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int d; cin>>d;
    ll N; cin>>N;
    
    vector<ll>a(d),c(d,1);
    a[0]=1;
    for(int i=1;i<d;++i){
        for(int j=0;j<i;++j){
            a[i]=(a[i]+a[j])%p;
        }
    }
    
    cout<<getNthValue(d,N,a,c)<<"\n";
    return 0;
}
