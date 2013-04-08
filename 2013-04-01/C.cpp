#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 200
using namespace std;

const double eps=1e-8;

int dlcmp(double x) {return x<-eps?-1:x>eps;}
double sqr(double x) {return x*x;}

struct Point
{
    double x,y;

    Point(){}
    Point(double a,double b):x(a),y(b){}

    Point operator - (const Point &p) const {return Point(x-p.x,y-p.y);}

    bool operator < (const Point &p) const
    {
        if (dlcmp(x-p.x)==0)
            return y<p.y;
        else
            return x<p.x;
    }

    bool operator == (const Point &p) const
    {
        if (dlcmp(x-p.x)==0&&dlcmp(y-p.y)==0)
            return 1;
        else
            return 0;
    }
};

struct Circle
{
    Point o;
    double r;
    int num[3];


    Circle (){}
    Circle (Point a,double b,int c,int d,int e)
    {
        o=a;
        r=b;
        num[0]=c;
        num[1]=d;
        num[2]=e;
    }

    bool operator < (const Circle & c) const
    {
        if (o==c.o)
            return r<c.r;
        else
            return o<c.o;
    }

    bool operator == (const Circle &c) const
    {
        if (o==c.o&&dlcmp(r-c.r)==0)
            return 1;
        else
            return 0;
    }
};

double cross(Point a,Point b)
{
    return a.x*b.y-b.x*a.y;
}
double dis(Point a,Point b)
{
    return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));
}

Point pt[N];
vector<Circle>cir;
vector<int>vec;

Circle get_circle(int idx1,int idx2,int idx3)
{
    Point p1=pt[idx1];
    Point p2=pt[idx2];
    Point p3=pt[idx3];
    double A1,A2,B1,B2,C1,C2;
    double r;
    Point o;

    A1=2*(p2.x-p1.x);
    A2=2*(p3.x-p2.x);
    B1=2*(p2.y-p1.y);
    B2=2*(p3.y-p2.y);
    C1=sqr(p2.x)+sqr(p2.y)-sqr(p1.x)-sqr(p1.y);
    C2=sqr(p3.x)+sqr(p3.y)-sqr(p2.x)-sqr(p2.y);

    o.x=(C1*B2-C2*B1)/(A1*B2-A2*B1);
    o.y=(C1*A2-C2*A1)/(B1*A2-B2*A1);
    r=dis(o,p1);

    return Circle(o,r,idx1,idx2,idx3);
}

int check(int idx1,int idx2,int idx3)
{
    Point p1=pt[idx1];
    Point p2=pt[idx2];
    Point p3=pt[idx3];

    if (dlcmp(cross(p2-p1,p3-p1))==0)
        return 0;
    else
        return 1;
}

int main()
{
    int n,i,j,k,ans,flag;
    Circle c;

    while (scanf("%d",&n),n)
    {
        cir.clear();
        vec.clear();
        for (i=0;i<n;i++)
            scanf("%lf%lf",&pt[i].x,&pt[i].y);
        for (i=0;i<n;i++)
            for (j=i+1;j<n;j++)
                for (k=j+1;k<n;k++)
                    if (check(i,j,k))
                        cir.push_back(get_circle(i,j,k));
        sort(cir.begin(),cir.end());

        if (n<=2)
        {
            printf("%d\n",n);
            continue;
        }

        if (cir.empty())
        {
            printf("2\n");
            continue;
        }

        ans=0;
        for (i=0;i<3;i++)
            vec.push_back(cir[0].num[i]);
        for (i=1;i<cir.size();i++)
        {
            if (!(cir[i]==cir[i-1]))
            {
                ans=max(ans,(int)vec.size());
                vec.clear();
                for (j=0;j<3;j++)
                    vec.push_back(cir[i].num[j]);
            }
            else
            {
                for (j=0;j<3;j++)
                {
                    flag=1;
                    for (k=0;k<vec.size();k++)
                        if (vec[k]==cir[i].num[j])
                        {
                            flag=0;
                            break;
                        }
                    if (flag)
                        vec.push_back(cir[i].num[j]);
                }
            }
        }
        ans=max(ans,(int)vec.size());

        printf("%d\n",ans);
    }

    return 0;
}









