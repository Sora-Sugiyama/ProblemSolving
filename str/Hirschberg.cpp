vector<int>A,B;

void dpHirschberg(const string &S,const string &T){
    fill(A.begin(),A.end(),0);
    fill(B.begin(),B.end(),0);
    const int m=(int)T.size();
    for(auto c:S){
        for(int j=1;j<=m;j++){
            B[j]=max({A[j],B[j-1],A[j-1]+(c==T[j-1])});
        }
        swap(A,B);
    }
}

string Hirschberg(const string &S,const string &T){
    const int n=(int)S.size();
    if(n==0)return "";
    if(n==1){
        for(auto c:T){
            if(c==S.front())return string(1,c);
        }
        return "";
    }
    
    int mid=n>>1;
    string le(S.begin(),S.begin()+mid),ri(S.begin()+mid,S.end()),rri(S.rbegin(),S.rbegin()+mid+(n&1));
    string rT(T.rbegin(),T.rend());
    
    vector<int>dpL,dpR;
    dpHirschberg(le,T);
    dpL=A;
    dpHirschberg(rri,rT);
    dpR=A;
    
    const int m=(int)T.size();
    int pos=0,mx=0;
    for(int i=0;i<=m;i++){
        int cur=dpL[i]+dpR[m-i];
        if(cur>mx){
            mx=cur;
            pos=i;
        }
    }
    
    le=Hirschberg(le,T.substr(0,pos));
    ri=Hirschberg(ri,T.substr(pos));
    return le+ri;
}
