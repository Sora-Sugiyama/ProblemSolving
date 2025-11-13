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
    std::vector<T>lazy;
    size_t SIZE;
    
    void propagate(const size_t &s,const size_t &e,const size_t &pos){
        T &cur=lazy[pos];
        if(cur){
            const size_t le=pos<<1,ri=(pos<<1)|1;
            if(s<e){
                lazy[le]+=cur;
                lazy[ri]+=cur;
            }
            arr[pos][0]+=cur*(e-s+1);
            arr[pos][1]+=cur;
            arr[pos][2]+=cur;
            lazy[pos]=0;
        }
    }
    
    tri CALC(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos);
    void ADD(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos,const T &dw);
    
public:
    SegTree(const size_t sz);
    SegTree(const size_t sz,const std::vector<T>&init);
    void add(size_t S,size_t E,T dx);
    tri calc(size_t S,size_t E);
};


int main(){
    freopen("File","r",stdin);
    std::ios_base::sync_with_stdio(false);std::cin.tie(NULL);
    using ll=long long;
    int N,M,K;std::cin>>N>>M>>K;
    std::vector<ll>init(N+2);
    for(int i=1;i<=N;i++){
        std::cin>>init[i];
    }
    SegTree<ll>seg(N,init);
    M+=K;
    while(M--){
        ll a,b,c;std::cin>>a>>b>>c;
        if(b>c)std::swap(b,c);
        if(a==1){
            ll d;std::cin>>d;
            seg.add(b,c,d);
        }else{
            SegTree<ll>::tri ans=seg.calc(size_t(b),size_t(c));
            std::cout<<ans[0]<<"\n";
        }
    }
    
    return 0;
}

template<typename T>
SegTree<T>::SegTree(const size_t sz){
    size_t t=1;
    while(t<sz)t<<=1;
    SIZE=t;
    
    lazy.resize((SIZE<<1)|3);
    arr.resize((SIZE<<1)|3);
    std::fill(arr.begin(),arr.end(),tri({0,std::numeric_limits<T>::max(),std::numeric_limits<T>::lowest()}));
}

template<typename T>
SegTree<T>::SegTree(const size_t sz, const std::vector<T>&init){
    size_t t=1;
    while(t<sz)t<<=1;
    SIZE=t;
    
    lazy.resize((SIZE<<1)|3);
    arr.resize((SIZE<<1)|3);
    std::fill(arr.begin(),arr.end(),tri({0,std::numeric_limits<T>::max(),std::numeric_limits<T>::lowest()}));
    
    for(size_t i=1;i<=sz;i++){
        arr[i+SIZE-1]={init[i],init[i],init[i]};
    }
    for(size_t i=SIZE-1;i>0;i--){
        arr[i]=arr[i<<1]|arr[(i<<1)|1];
    }
}

template<typename T>
SegTree<T>::tri SegTree<T>::CALC(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos){
    propagate(s,e,pos);
    if(S>e||s>E)return {0,std::numeric_limits<T>::max(),std::numeric_limits<T>::lowest()};
    if(S<=s&&e<=E)return arr[pos];
    const size_t mid=(s+e)>>1;
    return CALC(S,E,s,mid,pos<<1)|CALC(S,E,mid+1,e,(pos<<1)|1);
}

template<typename T>
void SegTree<T>::ADD(const size_t &S,const size_t &E,size_t s,size_t e,size_t pos,const T &dw){
    propagate(s,e,pos);
    if(S>e||s>E)return;
    if(S<=s&&e<=E){
        lazy[pos]+=dw;
        propagate(s,e,pos);
        return;
    }
    
    const size_t mid=(s+e)>>1;
    ADD(S,E,s,mid,pos<<1,dw);
    ADD(S,E,mid+1,e,(pos<<1)|1,dw);
    
    if(s<e)arr[pos]=arr[pos<<1]|arr[(pos<<1)|1];
}

template<typename T>
SegTree<T>::tri SegTree<T>::calc(size_t S,size_t E){
    return CALC(S,E,1,SIZE,1);
}

template<typename T>
void SegTree<T>::add(size_t S,size_t E,T dx){
    ADD(S,E,1,SIZE,1,dx);
}
