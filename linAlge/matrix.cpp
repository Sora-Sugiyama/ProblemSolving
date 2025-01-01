#include <bits/stdc++.h>
using namespace std;
using ll=long long;

namespace linAlge{
class mat{
    using vv=vector<vector<ll> >;
    using u=unsigned int;
    vv M;
    int i,j,k;
    
public:
    int n,m;
    
    mat(u r,u c){
        M.resize(r);
        for(i=0;i<r;i++)M[i].resize(c);
        n=r;m=c;
    }
    ~mat(){
        n=m=0;
        M.clear();
    }
    
    ll& operator()(u r,u c){return M[r][c];}
    
    mat operator+(mat &ref){
        mat ret(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                ret(i,j)=M[i][j]+ref(i,j);
            }
        }
        return ret;
    }
    
private:
    mat nProduct(mat &A,mat &B){
        const int N=A.n,K=A.m,M=B.m;
        mat ret(N,M);
        for(i=0;i<N;i++){
            for(j=0;j<M;j++){
                for(k=0;k<K;k++){
                    ret(i,j)+=A(i,k)*B(k,j);
                }
            }
        }
        return ret;
    }
    
public:
    mat operator*(mat &ref){
        // This part will improved to more efficiently as soon as possible
        return nProduct(ref,*this);
    }
};
}
