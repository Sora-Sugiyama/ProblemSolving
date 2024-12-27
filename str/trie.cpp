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
    int MAX,SIZE;
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
        MAX=sz;
        SIZE=0;
        ready2match=false;
        T.resize(MAX+3);
        next.resize(MAX+3);
        eos.resize(MAX+3);
        
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
        T.clear();
        next.clear();
        eos.clear();
        mp.clear();
    }
    
    void resize(int sz){
        MAX=sz;
        ready2match=false;
        T.resize(MAX+3);
        next.resize(MAX+3);
        eos.resize(MAX+3);
    }

    void clear(){
        MAX=SIZE=0;
        ready2match=false;
        memset(M,0,sizeof(M));
        T.clear();      T.resize(3);
        next.clear();   next.resize(3);
        eos.clear();    eos.resize(3);
    }

    void insert(string &s){
        ready2match=false;
        int p=0;
        for(char &c:s){
            int &tmp=M[p][mp[c]];
            if(!tmp){
                tmp=++SIZE;
                if(SIZE>MAX){
                    resize((MAX<<1)|1);
                }
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

