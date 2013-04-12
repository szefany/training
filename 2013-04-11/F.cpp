#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#define N 1100
#define eps 1e-8
using namespace std;

const double PI=acos(-1.0);
int dlcmp(double x) {return x<-eps?-1:x>eps;}

struct Point
{
	double x,y;
	
	Point (){}
	Point (double a,double b):x(a),y(b){}
};

Point pt[N];
vector<double>vec;
int ys;

void work(int n)
{
	int ans,cnt,i,j;
	double ang;
	
	ans=1;
	for (i=0;i<n;i++)
	{
		vec.clear();
		
		for (j=0;j<n;j++)
			if (i!=j)
			{
				ang=atan2(pt[j].y-pt[i].y,pt[j].x-pt[i].x);
				if (dlcmp(ang)>=0)
					vec.push_back(ang);
			}
		
		sort(vec.begin(),vec.end());
		if (!vec.empty())
		{
			cnt=1;
			for (j=1;j<vec.size();j++)
				if (dlcmp(vec[j]-vec[j-1])==0)
					cnt++;
				else
				{
					ans=max(ans,cnt+1);
					cnt=1;
				}
			ans=max(ans,cnt+1);
		}
	}
	
	printf("%d. %d\n",ys,ans);
}
		
		
	
	
int main()
{
	int i,j,n,x,y;
	char str[5000];
	
	ys=0;
	while (scanf("%s",str)!=EOF)
	{
		if (str[0]=='-'&&str[1]=='-')
		{
			if (n==0)
				return 0;
			else
			{
				ys++;
				work(n);
				n=0;
			}
		}
		else
		{
			sscanf(str,"%d",&x);
			scanf("%d",&y);
			pt[n++]=Point((double)x,(double)y);
		}
	}
	
	return 0;
}


