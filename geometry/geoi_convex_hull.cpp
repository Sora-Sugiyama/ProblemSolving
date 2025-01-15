#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

namespace geoi{
using ll=long long;
class planar{
    struct point{
        ll x,y;
        point(ll X=0,ll Y=0){x=X;y=Y;}
        ~point(){}
        
        point operator+(point ref){
            return point(x+ref.x,y+ref.y);
        }
        
        point operator-(point ref){
            return point(x-ref.x,y-ref.y);
        }
        
        point operator*(ll k){
            return point(x*k,y*k);
        }
        
        ll operator*(point ref){
            return x*ref.x+y*ref.y;
        }
        
        bool operator<(const point &ref)const{
            return x<ref.x||(x==ref.x&&y<ref.y);
        }
        
        bool operator>(const point &ref)const{
            return x>ref.x||(x==ref.x&&y>ref.y);
        }
        
    };
    
    struct line{
        point p,q;
        line(point a=point(),point b=point()){p=a;q=b;}
        ~line(){}
    };
    
    vector<point>P,hull;
    vector<line>L;
    
public:
    planar(){}
    ~planar(){
        P.clear();
        L.clear();
        hull.clear();
    }
    
    ll abs(point ref){
        return (ref*ref);
    }
    
    ll dist(point a, point b){
        return abs(a-b);
    }
    
    ll abs(line a){
        return abs(a.p-a.q);
    }
    
    void add_point(ll x,ll y){
        P.push_back(point(x,y));
    }
    
    void add_line(ll x,ll y,ll X,ll Y){
        L.push_back(line(point(x,y),point(x,y)));
    }
    
    void add_line(point p,point q){
        L.push_back(line(p,q));
    }
    
    int CCW(point a,point b,point c){
        ll ret=a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x;
        if(ret<0)return -1;
        else if(ret>0)return 1;
        else return 0;
    }
    
    void compute_hull(){
        hull.clear();
        const size_t n=(int)P.size();
        hull.resize(n<<1);
        sort(P.begin(),P.end());
        
        int k=0;
        for(point &p:P){
            while(k>=2&&CCW(hull[k-2],hull[k-1],p)<=0)k--;
            hull[k++]=p;
        }
        
        for(size_t i=n-1,t=k+1;i>0;i--){
            while(k>=t&&CCW(hull[k-2],hull[k-1],P[i-1])<=0)k--;
            hull[k++]=P[i-1];
        }
        
        hull.resize(k-1);
    }
    
    size_t hullSize(){
        return hull.size();
    }
    
    size_t number_of_points(){
        return P.size();
    }
    
    size_t number_of_lines(){
        return L.size();
    }
};
}

