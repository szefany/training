#include "iostream"
#include "cstring"
#include "cstdio"
using namespace std;
typedef long long LOL;
const LOL MOD=1000000007ll;
const LOL MOD1=MOD-1;
const int N = 510;
char s1[N],s2[N];
int num[20],tt[20];
LOL pmod[N],psmod[N];
LOL c1[N][N],c2[N][N];
int a[N];
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
	return x<0?x+p:x;
}

LOL getnum(LOL mod)
{
	int sum=0;
	for(int i=1;i<=9;i++){
		sum+=num[i];
	}
	LOL ans=1;
	for(int i=1;i<=9;i++){
		if(mod==MOD){
			ans=(ans*c1[sum][num[i]])%mod;
		}else{
			ans=(ans*c2[sum][num[i]])%mod;
		}
		sum-=num[i];
	}
	return ans;
}
LOL gaonum(int l,LOL mod)
{
	if(l==0)	return 1;
	LOL sum=0;
	for(int i=1;i<a[l];i++){
		num[i]--;
		sum+=getnum(mod);
		num[i]++;
	}
	num[a[l]]--;
	return sum+gaonum(l-1,mod);
}
LOL getsum()
{
	int sum=0;
	for(int i=1;i<=9;i++){
		sum+=num[i];
	}
	LOL ans=1;
	int tmp=sum;
	for(int i=1;i<=9;i++){
		ans=(ans*c1[sum][num[i]])%MOD;
		sum-=num[i];
	}
	sum=tmp;
	LOL now=(psmod[sum]*inverse(sum,MOD))%MOD;
	LOL all_ans=0;
	for(int i=1;i<=9;i++){
		LOL tans=(ans*num[i]*i)%MOD*now;
		tans%=MOD;
		all_ans=(all_ans+tans)%MOD;
	}
	return all_ans;
}
void solve(int l,LOL &ans_num,LOL &ans_sum)
{
	if(l==0){
		ans_num=1,ans_sum=0;
		return ;
	}
	LOL tmp_num=0,tmp_sum=0;
	for(int i=1;i<a[l];i++){
		if(num[i]>0){
			num[i]--;
			LOL tmp=getnum(MOD);
			tmp_num=(tmp_num+tmp)%MOD;
			tmp_sum=(tmp_sum+getsum()+i*pmod[l]*tmp)%MOD;
			num[i]++;
		}
	}
	num[a[l]]--;
	LOL tx=0,ty=0;
	solve(l-1,tx,ty);
	ans_num=(tmp_num+tx)%MOD;
	ans_sum=(tmp_sum+ty+a[l]*pmod[l]*tx)%MOD;
}
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
		c1[i][0]=1;
		c2[i][0]=1;
	}
	for(int i=1;i<=500;i++){
		for(int j=1;j<=i;j++){
			c1[i][j]=(c1[i-1][j-1]+c1[i-1][j])%MOD;
			c2[i][j]=(c2[i-1][j-1]+c2[i-1][j])%MOD1;
		}
	}
	pmod[1]=1;psmod[1]=1;
	for(int i=2;i<=500;i++){
		pmod[i]=(pmod[i-1]*10)%MOD;
		psmod[i]=(psmod[i-1]+pmod[i])%MOD;
	}
	for(int i=1;i<=9;i++){
		scanf("%d",&tt[i]);
	}
	int Q;
	scanf("%d",&Q);
	while(Q--){
		scanf("%s %s",s1,s2);
		int len=strlen(s1);
		LOL num1=0,num2=0,sum1=0,sum2=0,anum=0,sum=0;
		for(int i=len;i>=1;i--){
			a[i]=s1[len-i]-'0';
		}
		for(int i=1;i<=9;i++){
			num[i]=tt[i];
		}
		num1=gaonum(len,MOD1);
		LOL tmp=0;
		for(int i=1;i<=9;i++){
			num[i]=tt[i];
		}
		solve(len,tmp,sum1);
		for(int i=len;i>=1;i--){
			a[i]=s2[len-i]-'0';
		}
		for(int i=1;i<=9;i++){
			num[i]=tt[i];
		}
		num2=gaonum(len,MOD1);
		tmp=0;
		for(int i=1;i<=9;i++){
			num[i]=tt[i];
		}
		solve(len,tmp,sum2);
		anum=num1-num2+1;
		sum=sum1-sum2;
		tmp=0;
		for(int j=0;j<len;j++){
			tmp=tmp*10+s2[j]-'0';
			tmp%=MOD;
		}
		sum+=tmp;
		anum=(anum%MOD1+MOD1)%MOD1;
		anum=qmod(2,anum);
		anum=(anum*inverse(4,MOD)%MOD);
		sum=(sum%MOD+MOD)%MOD;
		
		printf("%lld %lld\n",anum,(anum*sum)%MOD);
	}
	return 0;
}
