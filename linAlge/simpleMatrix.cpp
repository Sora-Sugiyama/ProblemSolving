#include "bits/stdc++.h"
using namespace std;
using ll=long long;

template<class T,
ll mod>
class mat{
    vector<vector<T> >arr;
    int n;
    
public:
    mat(int N=0):n(N),arr(vector<vector<T> >(N,vector<T>(N))){
        for(int i=0;i<n;i++)arr[i][i]=1;
    }
    
    int size(){
        return n;
    }
    
    const T& operator()(const int i,const int j)const{
        return arr[i][j];
    }
    
    T& operator()(const int i,const int j){
        return arr[i][j];
    }
    
    mat& operator*=(const mat &rhs){
        mat tmp=*this;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tmp(i,j)=0;
                for(int k=0;k<n;k++){
                    tmp(i,j)=(tmp(i,j)+arr[i][k]*rhs(k,j))%mod;
                }
            }
        }
        this->arr=tmp.arr;
        return *this;
    }
    
    mat operator*(const mat &rhs){
        mat tmp=*this;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                tmp(i,j)=0;
                for(int k=0;k<n;k++){
                    tmp(i,j)=(tmp(i,j)+arr[i][k]*rhs(k,j))%mod;
                }
            }
        }
        return tmp;
    }
};

int main(){
    // You can use like
    mat<ll> A(3, 1000);
    A(0,0)=1;
    A(1,1)=1;
    A(2,2)=1;
    A=A*A;
    A*=A;
    
    return 0;
}
