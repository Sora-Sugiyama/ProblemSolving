#include <iostream>
#include <bit>
#include <cstdint>
#include <array>
using namespace std;

using u64=uint64_t;

constexpr array<array<u64,64>,64>precomPatterns(){
    array<array<u64,64>,64>patterns={{}};
    for(u64 i=2;i<64;i++){
        for(u64 j=0;j<64;j++){
            for(u64 k=1ULL<<j;k;k<<=i){
                patterns[i][j]|=k;
            }
        }
    }
    return patterns;
}

constexpr array<array<u64,64>,64>precomJumper(){
    array<array<u64,64>,64>jumper={{}};
    for(u64 i=2;i<64;i++){
        for(u64 j=0;j<64;j++){
            jumper[i][j]=(64-j+i-1)/i*i;
        }
    }
    return jumper;
}

constexpr u64 targetN=1ULL<<28;
constexpr auto patterns=precomPatterns();
constexpr auto jumper=precomJumper();
u64 sieve[(targetN>>6)+3]={0b11};

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    for(u64 u=2;u<64;u++){
        if(sieve[u>>6]&(1ULL<<(u&63)))continue;
        for(u64 k=u*u;k<=targetN;k+=jumper[u][k&63]){
            sieve[k>>6]|=patterns[u][k&63];
        }
    }
    
    for(u64 u=64;u*u<=targetN;u++){
        if(sieve[u>>6]&(1ULL<<(u&63)))continue;
        for(u64 k=u*u;k<=targetN;k+=u){
            sieve[k>>6]|=1ULL<<(k&63);
        }
    }
    return 0;
}
