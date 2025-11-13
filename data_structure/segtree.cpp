#include <iostream>
#include <vector>
#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <limits>

template<typename T>
std::array<T,3> operator|(const std::array<T,3> &lhs,const std::array<T,3> &rhs){
    return {lhs[0]+rhs[0],std::min(lhs[1],rhs[1]),std::max(lhs[2],rhs[2])};
}

template<typename T>
class SegTree{
public:
    using tri=std::array<T,3>;
    
private:
    
    // {sum min max}
    std::vector<tri>arr;
    size_t SIZE;
    
    tri CALC(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos);
public:
    SegTree(size_t sz);
    
    void upd(size_t p,T x_f);
    void add(size_t p,T dx);
    
    tri calc(size_t S,size_t E);
};


int main(){
    freopen("File","r",stdin);
    std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);
    using ll=long long;
    int N,M;std::cin>>N>>M;
    SegTree<ll>seg(N);
    for(int i=1;i<=N;i++){
        ll x;std::cin>>x;
        seg.upd(i,x);
    }
    
    while(M--){
        ll b,c;std::cin>>b>>c;
        if(b>c)std::swap(b,c);
        SegTree<ll>::tri ans=seg.calc(size_t(b),size_t(c));
        std::cout<<ans[1]<<" "<<ans[2]<<"\n";
    }
    
    return 0;
}

template<typename T>
SegTree<T>::SegTree(const size_t sz){
    size_t t=1;
    while(t<sz)t<<=1;
    SIZE=t;
    
    arr.resize((SIZE<<1)|3);
    std::fill(arr.begin(),arr.end(),tri({0,std::numeric_limits<T>::max(),std::numeric_limits<T>::lowest()}));
}

template<typename T>
SegTree<T>::tri SegTree<T>::CALC(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos){
    if(S>e||s>E)return {0,std::numeric_limits<T>::max(),std::numeric_limits<T>::lowest()};
    if(S<=s&&e<=E)return arr[pos];
    
    const size_t mid=(s+e)>>1;
    return CALC(S,E,s,mid,pos<<1)|CALC(S,E,mid+1,e,(pos<<1)|1);
}

template<typename T>
SegTree<T>::tri SegTree<T>::calc(size_t S,size_t E){
    return CALC(S,E,1,SIZE,1);
}

template<typename T>
void SegTree<T>::upd(size_t p,T x_f){
    p+=SIZE-1;
    arr[p]={x_f,x_f,x_f};
    while(p>>=1){
        arr[p]=arr[p<<1]|arr[(p<<1)|1];
    }
}

template<typename T>
void SegTree<T>::add(size_t p,T dx){
    p+=SIZE-1;
    arr[p]={arr[p][0]+dx,arr[p][1]+dx,arr[p][2]+dx};
    while(p>>=1){
        arr[p]=arr[p<<1]|arr[(p<<1)|1];
    }
}
