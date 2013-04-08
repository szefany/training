#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long LOL;
const LOL MOD = 1000000007LL;
const LOL MOD1 = MOD-1;
const int N = 510;
int vis[20];
char s1[N],s2[N];
LOL c[N][N];
int a[N];
LOL pmod[N],psmod[N];
LOL extendGCD(LOL a,LOL b,LOL &x,LOL &y)
{
	if(!b) return x=1,y=0,a;
	LOL res=extendGCD(b,a%b,x,y),tmp=x;
	x=y,y=tmp-(a/b)*y;
	return res;
}
LOL inverse(LOL a,LOL p)
{
	LOL x,y;
	y=extendGCD(a,p,x,y);
	return x<0?x+=p:x;
}
LOL getnum(LOL mod)
{
	int tx=0;
	for(int j=1;j<=9;j++){
		tx+=vis[j];
	}
	LOL tmp=1;
	for(int j=1;j<=9;j++){
		tmp*=c[tx][vis[j]];
		tmp%=mod;
		tx-=vis[j];
	}
	return tmp;
}
LOL gaonum(int l,LOL mod)
{
	if(l==0){
		return 1;
	}
	LOL sum=0;
	for(int i=1;i<a[l];i++){
		if(vis[i]>0){
			vis[i]--;
			sum+=getnum(mod);
			vis[i]++;
		}
	}
	vis[a[l]]--;
	return sum+gaonum(l-1,mod);
}
LOL getsum()
{
	int tx=0;
	for(int i=1;i<=9;i++){
		tx+=vis[i];
	}
	LOL tmp=1;
	int ttx=tx;
	for(int i=1;i<=9;i++){
		tmp=(tmp*c[tx][vis[i]])%MOD;
		tx-=vis[i];
	}
	LOL sum=0;
	for(int i=1;i<=9;i++){
		LOL ty=tmp*vis[i]%MOD;
		ty=(ty*psmod[ttx])%MOD;
		ty=(ty*inverse(ttx,MOD))%MOD;
		ty*=i;
		sum+=ty;
	}
	return sum;
}
LOL gaosum(int l)
{
	if(l==0){
		return 0;
	}
	LOL sum=0;
	for(int i=1;i<a[l];i++){
		if(vis[i]>0){
			vis[i]--;
			sum=sum+getsum()+i*pmod[l]*getnum(MOD);
			sum%=MOD;
			vis[i]++;
			
		}
	}
	vis[a[l]]--;
	sum+=a[l]*pmod[l]*gaonum(l-1,MOD);
	return sum+gaosum(l-1);
}	
bool check()
{
	int len=strlen(s1);
	for(int i=0;i<len;i++){
		if(s1[i]>s2[i]){
			return 1;
		}else if(s1[i]==s2[i]){
			continue;
		}else{
			return 0;
		}
	}
	return 1;
}
int tvis[20];
LOL qmod(LOL a,LOL b)
{
	LOL sum=1;
	while(b!=0){
		if(b%2==1){
			sum=(sum*a)%MOD;
		}
		a=(a*a)%MOD;
		b/=2;
	}
	return sum;
}
int main(void)
{
	for(int i=0;i<=500;i++){
		c[i][0]=1;
	}
	for(int i=1;i<=500;i++){
		for(int j=1;j<=i;j++){
			c[i][j]=(c[i-1][j-1]+c[i-1][j])%MOD;
		}
	}
	pmod[1]=1;psmod[1]=1;
	for(int i=2;i<=500;i++){
		pmod[i]=(pmod[i-1]*10)%MOD;
		psmod[i]=(psmod[i-1]+pmod[i])%MOD;
	}
	for(int i=1;i<=9;i++){
		scanf("%d",&vis[i]);
	}
	for(int i=1;i<=9;i++){
		tvis[i]=vis[i];
	}
	int Q;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++){
		scanf("%s %s",s1,s2);
		LOL num1=0,sum1=0,num2=0,sum2=0,num=0,sum=0;
		int len=strlen(s1);
		for(int j=len;j>=1;j--){
			a[j]=s1[len-j]-'0';
		}		
		for(int i=1;i<=9;i++){
			vis[i]=tvis[i];
		}
		num1+=gaonum(len,MOD1);	
		for(int i=1;i<=9;i++){
			vis[i]=tvis[i];
		}	
		sum1+=gaosum(len);
		for(int j=len;j>=1;j--){
			a[j]=s2[len-j]-'0';
		}		
		for(int i=1;i<=9;i++){
			vis[i]=tvis[i];
		}
		num2+=gaonum(len,MOD1);
		for(int i=1;i<=9;i++){
			vis[i]=tvis[i];
		}
		sum2+=gaosum(len);
		if(check()){
			num=num1-num2+1;
			sum=sum1-sum2;
			LOL tmp=0;
			for(int j=0;j<len;j++){
				tmp=tmp*10+s2[j]-'0';
				tmp%=MOD;
			}
			sum+=tmp;
		}else{
			num=num2-num1+1;
			sum=sum2-sum1;
			LOL tmp=0;
			for(int j=0;j<len;j++){
				tmp=tmp*10+s1[j]-'0';
				tmp%=MOD;
			}
			sum+=tmp;
		}
		num=(num%MOD1+MOD1)%MOD1;
		num=qmod(2,num);
		num=(num*inverse(4,MOD)%MOD);
		sum=(sum%MOD+MOD)%MOD;
		printf("%lld %lld\n",num,(num*sum)%MOD);
	}
	return 0;
}
