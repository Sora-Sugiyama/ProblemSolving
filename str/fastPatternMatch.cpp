#include <iostream>
#include <vector>
#include <string>

// 1 - based string
std::vector<int>computeNext(const std::string &pattern){
    const int m=(int)pattern.size()-1;
    std::vector<int>next(m+1);
    int j=1,t=0; next[1]=0;
    while(j<m){
        while(t>0 && pattern[j]!=pattern[t])t=next[t];
        t++;j++;
        if(pattern[j]==pattern[t])next[j]=next[t];
        else next[j]=t;
    }
    return next;
}

std::vector<int> patternMatching(std::string text,std::string pattern){
    const int n=(int)text.size()-1,m=(int)pattern.size()-1;
    
    char a=pattern[1];
    text.push_back('^'); text.push_back(a);
    pattern.push_back('@');
    auto next=computeNext(pattern);
    
    std::vector<int>matchedPosition;
    
    int j=1,k=1;
    while(k<=n){
        getStarted:{
            while(text[k]!=a)k++;
            if(k>n)return matchedPosition;
        }
        goto loop;
        
        charMatched:{
            j++;k++;
            if(j>m){
                j=next[j];
                matchedPosition.push_back(k-m);
            }
        }
        
        loop:
        do{
            if(text[k]==pattern[j])goto charMatched;
            j=next[j];
            if(j==1){
                goto getStarted;
            }
            if(j==0){
                j=1;k++;
                goto getStarted;
            }
        }while(j>0);
        
    }
    return matchedPosition;
}
