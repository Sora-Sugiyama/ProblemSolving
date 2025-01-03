#include <iostream>
#include <vector>
using namespace std;

namespace linAlge{
using ll=long long;
class mat{
    using vv=vector<vector<ll> >;
    vv M;
    int i,j,k;
    
public:
    int n,m;
    
    mat(int r=0,int c=0){
        M.resize(r);
        for(i=0;i<r;i++)M[i].resize(c);
        n=r;m=c;
    }
    ~mat(){
        n=m=0;
        M.clear();
    }
    
    ll& operator()(int r,int c){return M[r][c];}
    
    mat &operator<(mat &ref){
        n=ref.n;m=ref.m;M=ref.M;
        return *this;
    }
    
    mat &operator=(mat ref){
        n=ref.n;m=ref.m;M=ref.M;
        return *this;
    }
    
    mat &operator=(vv ref){
        M=ref;
        n=(int)ref.size();
        m=(int)ref.back().size();
        return *this;
    }
    
    mat &operator-(){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++)M[i][j]=-M[i][j];
        }
        return *this;
    }
    
    mat operator+(mat ref){
        mat ret(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                ret(i,j)=M[i][j]+ref(i,j);
            }
        }
        return ret;
    }
    
    mat operator-(mat ref){
        mat ret(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++){
                ret(i,j)=M[i][j]-ref(i,j);
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
    
    mat Winograd(mat &A,mat &B){
        const int N=A.n,M=A.n>>1;
        mat ret(N,N);
        mat A11(M,M),A12(M,M),A21(M,M),A22(M,M),B11(M,M),B12(M,M),B21(M,M),B22(M,M);
        mat M1,M2,M3,M4,M5,M6,M7,S1,S2,S3,S4,T1,T2;
        for(i=0;i<M;i++){
            for(j=0;j<M;j++){
                A11(i,j)=A(i,j);
                A12(i,j)=A(i,j+M);
                A21(i,j)=A(i+M,j);
                A22(i,j)=A(i+M,j+M);
                B11(i,j)=B(i,j);
                B12(i,j)=B(i,j+M);
                B21(i,j)=B(i+M,j);
                B22(i,j)=B(i+M,j+M);
            }
        }
        
        S1=A21+A22; S2=S1-A11; S3=B12-B11; S4=B22-S3;
        M1=S2*S4; M2=A11*B11; M3=A12*B21; M4=(A11-A21)*(B22-B12); M5=S1*S3; M6=(A12-S2)*B22; M7=A22*(S4-B21);
        T1=M1+M2; T2=T1+M4;
        
        for(i=0;i<M;i++){
            for(j=0;j<M;j++){
                ret(i,j)=M2(i,j)+M3(i,j);
                ret(i,j+M)=T1(i,j)+M5(i,j)+M6(i,j);
                ret(i+M,j)=T2(i,j)-M7(i,j);
                ret(i+M,j+M)=T2(i,j)+M5(i,j);
            }
        }
        return ret;
    }
    
    mat product(mat &A,mat &B){
        const int N=A.n,K=A.m,M=B.m;
        mat ret(N,M);
        int t=min({N,K,M});
        if(t&1)t^=1;
        mat A11(t,t),A12(t,K-t),A21(N-t,t),A22(N-t,K-t),B11(t,t),B12(t,M-t),B21(K-t,t),B22(K-t,M-t);
        for(i=0;i<t;i++){
            for(j=0;j<t;j++)A11(i,j)=A(i,j);
            for(j=0;j<K-t;j++)A12(i,j)=A(i,j+t);
        }
        for(i=0;i<N-t;i++){
            for(j=0;j<t;j++)A21(i,j)=A(i+t,j);
            for(j=0;j<K-t;j++)A22(i,j)=A(i+t,j+t);
        }
        for(i=0;i<t;i++){
            for(j=0;j<t;j++)B11(i,j)=B(i,j);
            for(j=0;j<M-t;j++)B12(i,j)=B(i,j+t);
        }
        for(i=0;i<K-t;i++){
            for(j=0;j<t;j++)B21(i,j)=B(i+t,j);
            for(j=0;j<M-t;j++)B22(i,j)=B(i+t,j+t);
        }
        mat C11,C12,C21,C22;
        C11=A11*B11+A12*B21;
        C12=A11*B12+A12*B22;
        C21=A21*B11+A22*B21;
        C22=A21*B12+A22*B22;
        C11=nProduct(A11,B11)+nProduct(A12,B21);
        C12=nProduct(A11,B12)+nProduct(A12,B22);
        C21=nProduct(A21,B11)+nProduct(A22,B21);
        C22=nProduct(A21,B12)+nProduct(A22,B22);
        for(i=0;i<t;i++){
            for(j=0;j<t;j++)ret(i,j)=C11(i,j);
            for(j=0;j<M-t;j++)ret(i,j+t)=C12(i,j);
        }
        for(i=0;i<N-t;i++){
            for(j=0;j<t;j++)ret(i+t,j)=C21(i,j);
            for(j=0;j<M-t;j++)ret(i+t,j+t)=C22(i,j);
        }

        return ret;
    }
    
public:
    mat operator*(mat ref){
        if(n<=5||m<=5||ref.n<=5||ref.m<=5)return nProduct(*this,ref);
        if(n==m&&ref.n==ref.m&&!(n&1))return Winograd(*this,ref);
        return product(*this,ref);
    }
    
    mat &operator*=(mat &ref){
        if(n<=5||m<=5||ref.n<=5||ref.m<=5)*this=nProduct(*this,ref);
        else if(n==m&&ref.n==ref.m&&!(n&1))*this=Winograd(*this,ref);
        else *this=product(*this,ref);
        return *this;
    }
    
    mat operator%(const ll mod){
        mat ret(n,m);
        for(i=0;i<n;i++){
            for(j=0;j<m;j++)ret(i,j)=M[i][j]%mod;
        }
        return ret;
    }
    
    mat &operator%=(const ll mod){
        for(i=0;i<n;i++){
            for(j=0;j<m;j++)M[i][j]%=mod;
        }
        return *this;
    }
    
    mat T(){
        mat ret(m,n);
        for(i=0;i<m;i++){
            for(j=0;j<n;j++)ret(i,j)=M[j][i];
        }
        return ret;
    }
};
}
