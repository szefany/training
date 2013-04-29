#include "iostream"
#include "cstring"
#include "cstdio"
#include "cmath"
using namespace std;
typedef unsigned long long LOL;
long long gao(LOL x)
{
	LOL v=(LOL)sqrt(x*1.0);
	if(v*v==x) return v;
	if((v+1)*(v+1)==x) return v+1;
	return -1;
}
LOL get(LOL x,int m)
{
	LOL sum=0;
	while(x!=0){
		sum+=x%m;
		x/=m;
	}
	return sum;
}
int main(void)
{
	int T;
	freopen("input","r",stdin);
	scanf("%d",&T);
	LOL n;
	int m;
	while(T--){
		cin>>n>>m;
		int flag=0;
		long long ans=-1;
		for(int i=1;i<=300;i++){
			long long tmp=gao(i*i+4*n);
			if(tmp==-1) continue;
			long long val=-i+tmp;
			if(val%2==1) continue;
			val/=2;
			if(get(val,m)==(LOL)i){
				if(!flag){
					flag=1;ans=val;
				}else{
					ans=min(ans,val);
				}
			}
		}
		if(flag){
			cout<<ans<<'\n';
		}else{
			cout<<-1<<'\n';
		}
	}
	return 0;
}