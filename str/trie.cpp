#include <bits/stdc++.h>
using namespace std;

namespace str{
class trie{
    struct node{
        int pos;
        char c;
        node(const int p=0,const char ch='?'){
            this->pos=p;
            this->c=ch;
        }
    };

    vector<vector<node> >T;
    vector<int>eos,next,mp;
    int M[500003][4];
    size_t MAX;
    int SIZE;
    bool ready2match=false;

    void bfs_AhoCorasic(){
        queue<node>q;
        int p;
        node u;
        for(node &x:T[0])q.push(x);
        while(!q.empty()){
            u=q.front();q.pop();
            for(node &x:T[u.pos]){
                p=next[u.pos];
                while(p&&!M[p][mp[x.c]])p=next[p];
                p=M[p][mp[x.c]];
                next[x.pos]=p;
                if(eos[p])eos[x.pos]=eos[p];
                q.push(x);
            }
        }
    }
public:
    trie(int sz=0){
        mp.resize(256);
        MAX=size_t(sz);
        SIZE=0;
        ready2match=false;
        T=vector<vector<node> >(sz+3);
        // for boj 10256
        next=eos=vector<int>(sz+3);
        
        // for 10256
        mp['A']=0;
        mp['G']=1;
        mp['T']=2;
        mp['C']=3;
        
        /*
         for(int i='A';i<='Z';i++)mp['A']=i-'A';
         */
    }
    ~trie(){
        memset(M,0,sizeof(M));
    }
    void insert(string &s){
        int p=0;
        for(char &c:s){
            int &tmp=M[p][mp[c]];
            if(!tmp){
                tmp=++SIZE;
                T[p].push_back(node(SIZE,c));
            }
            p=tmp;
        }
        eos[p]++;
    }
    
    int ahoCorasic(string &s){
        if(!ready2match){
            ready2match=true;
            bfs_AhoCorasic();
        }
        int p=0,ret=0;
        for(char &x:s){
            while(p&&!M[p][mp[x]])p=next[p];
            p=M[p][mp[x]];
            if(eos[p])ret++;
        }
        return ret;
    }

    bool in(string &s){
        int p=0;
        for(char &c:s){
            if(!M[p][mp[c]])return false;
            p=M[p][mp[c]];
        }
        return eos[p];
    }
};
}
