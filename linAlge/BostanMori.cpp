#include "bits/stdc++.h"
using namespace std;
using ll=long long;
constexpr ll p=(17LL<<27)|1,R=3,NN=(1<<11);

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
    for(i=1,j=0;i<NN;i++){
        for(k=NN>>1;k<=j;k>>=1)j-=k;
        j+=k;
        if(i<j)swap(a[i],a[j]);
    }
    for(i=1,t=1;i<NN;i<<=1,t++){
        x=po(R,p>>t);
        for(j=0;j<NN;j+=i<<1){
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
    for(i=1,j=0;i<NN;i++){
        for(k=NN>>1;k<=j;k>>=1)j-=k;
        j+=k;
        if(i<j)swap(a[i],a[j]);
    }
    for(i=1,t=1;i<NN;i<<=1,t++){
        x=po(modinvR,p>>t);
        for(j=0;j<NN;j+=i<<1){
            y=1;
            for(k=0;k<i;k++){
                z=a[i|j|k]*y%p;
                a[i|j|k]=(a[j|k]-z+p)%p;
                a[j|k]=(a[j|k]+z)%p;
                y=y*x%p;
            }
        }
    }
    const ll modinvN=po(NN,p-2);
    for(i=0;i<NN;i++)a[i]=a[i]*modinvN%p;
}

vector<ll> operator-(const vector<ll> &ref){
    vector<ll>ret(ref.begin(),ref.end());
    for(int i=1;i<NN;i+=2)ret[i]=-ret[i];
    return ret;
}

vector<ll> operator*(vector<ll> a,vector<ll> b){
    FFT(a);FFT(b);
    for(int i=0;i<NN;i++)a[i]=a[i]*b[i]%p;
    iFFT(a);
    //for(int i=0;i<NN;i++)a[i]%=1999; //BOJ 15572
    return a;
}

vector<ll> BMsub(const vector<ll> &ref,const int isOdd=0){
    vector<ll>ret(NN);
    int k=0;
    for(int i=isOdd;i<NN;i+=2)ret[k++]=ref[i];
    for(;k<NN;k++)ret[k]=0;
    
    return ret;
}

ll BostanMori(ll N,vector<ll>P,vector<ll>Q){
    while(N){
        vector<ll>mQ=-Q;
        vector<ll>U=P*mQ;
        P=BMsub(U,N&1);
        Q=BMsub(Q*mQ);
        N>>=1;
    }
    return P[0]/Q[0];
}

int main(){
    freopen("File","r",stdin);
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    ll N,M;cin>>N>>M;
    vector<ll>P(NN),Q(NN);
    /*
    for(int i=2;i<=N;i++)Q[i]=-1;
    Q[0]=Q[1]=1;
    for(int i=1;i<N;i++){
        P[i]=Q[1];
        Q[1]=(Q[1]<<1)%1999;
    }
    Q[1]=-Q[1];
    P=P*Q;
    for(int i=(int)N;i<NN;i++)P[i]=0;
     */
    Q[0]=1;Q[1]=-2;Q[2]=-1;
    P[1]=1;
    for(int k=1;k<=M;k++)cout<<BostanMori(k, P, Q)<<endl;
    ll ans=BostanMori(M,P,Q);
    cout<<ans<<"\n";
    return 0;
}
