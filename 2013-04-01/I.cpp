/*
AC
*/
#include "iostream"
#include "cstring"
#include "cstdio"
#include "vector"
#define PB push_back
using namespace std;
const int N = 100010;
int gcd(int a,int b)
{
	if(b==0){
		return a;
	}
	return gcd(b,a%b);
}
vector<char> ans;
int a[N];
int ab(int a)
{
	return a>0?a:-a;
}
int main(void)
{
	int n,m,x,y;
	while(scanf("%d%d",&n,&m)&&(n||m)){
		int g=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=2;i<=n;i++){
			g=gcd(g,ab(a[i]-a[i-1]));
		}
		ans.clear();
		for(int i=1;i<=m;i++){
			scanf("%d %d",&x,&y);
			if((ab(y)%2)!=(ab(x)%2)){
				ans.PB('N');
				continue;
			}
			if(n==1){
				if(2*a[i]==x+y){
					ans.PB('Y');
				}else{
					ans.PB('N');
				}
			}else{
				if((ab(y-x)/2)%g==0){
					ans.PB('Y');
				}else{
					bool flag=0;
					for(int i=1;i<=n;i++){
						if((ab(y+x-a[i])/2)%g==0){
							flag=1;
							break;
						}
					}
					if(flag){
						ans.PB('Y');
					}else{
						ans.PB('N');
					}
				}
			}
		}
		for(int i=0;i<ans.size();i++){
			printf("%c%c",ans[i],i==ans.size()-1?'\n':' ');
		}
	}
	return 0;
}