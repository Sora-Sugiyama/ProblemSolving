#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

namespace geof{
class planar{
    struct point{
        double x,y;
        point(double X=0,double Y=0){x=X;y=Y;}
        ~point(){}
        
        point operator+(point ref){
            return point(x+ref.x,y+ref.y);
        }
        
        point operator-(point ref){
            return point(x-ref.x,y-ref.y);
        }
        
        point operator*(double k){
            return point(x*k,y*k);
        }
        
        double operator*(point ref){
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
    vector<line>L,hullLine;
    
public:
    planar(){}
    ~planar(){
        P.clear();
        L.clear();
        hull.clear();
        hullLine.clear();
    }
    
    double abs(point ref){
        return sqrt(ref*ref);
    }
    
    double dist(point a, point b){
        return abs(a-b);
    }
    
    double abs(line a){
        return abs(a.p-a.q);
    }
    
    double dist(point v, line b){
        point u=b.q-b.p;
        v=v-b.p;
        return abs(v-(u*((v*u)/(u*u))));
    }
    
    void add_point(double x,double y){
        P.push_back(point(x,y));
    }
    
    void add_line(double x,double y,double X,double Y){
        L.push_back(line(point(x,y),point(x,y)));
    }
    
    void add_line(point p,point q){
        L.push_back(line(p,q));
    }
    
    int CCW(point a,point b,point c){
        double ret=a.x*b.y+b.x*c.y+c.x*a.y-a.y*b.x-b.y*c.x-c.y*a.x;
        if(ret<0)return -1;
        else if(ret>0)return 1;
        else return 0;
    }
    
    void compute_hull(){
        hull.clear();
        const size_t n=(int)P.size();
        hull.resize(n<<1);
        sort(P.begin(),P.end());
        
        size_t k=0;
        for(point &p:P){
            while(k>=2&&CCW(hull[k-2],hull[k-1],p)<=0)k--;
            hull[k++]=p;
        }
        
        for(size_t i=n-1,t=k+1;i>0;i--){
            while(k>=t&&CCW(hull[k-2],hull[k-1],P[i-1])<=0)k--;
            hull[k++]=P[i-1];
        }
        
        const size_t hullsz=k-1;
        hull.resize(hullsz);
        for(size_t i=0;i<hullsz;i++){
            hullLine.push_back(line(hull[i],hull[(i+1)%hullsz]));
        }
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
