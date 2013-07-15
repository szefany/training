#include "iostream"
#include "cstring"
#include "cstdio"
#include "string"
#include "algorithm"
#include "vector"
using namespace std;
const int N = 1100;
string a[N];
int main(void)
{
	int n;
	while(scanf("%d",&n)&&n){
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		sort(a+1,a+1+n);
		string x=a[n/2],y=a[n/2+1];
		string tmp="";
		for(int i=0;i<min(a[n/2].size(),a[n/2+1].size());i++){
			if(a[n/2][i]==a[n/2+1][i]){
				tmp+=a[n/2][i];
			}else{
				break;
			}
		}
		int sz=tmp.size();
		if(x==tmp){
			cout<<tmp<<endl;
		}else{
			if(x[sz]+1<y[sz]){
				if(sz==x.size()-1){
					cout<<tmp+x[sz]<<endl;
				}else{
					cout<<tmp+(char)(x[sz]+1)<<endl;
				}
			}else{
				string ty="",tx="";
				ty+=x[sz];
				for(int j=sz+1;j<x.size();j++){
					if(x[j]!='Z'){
						if(j==x.size()-1){
							ty+=x[j];
						}else{
							ty+=(char)(x[j]+1);
						}
						break;
					}else{
						ty+=x[j];
					}
				}
				if(y.size()-1!=sz){
					tx+=y[sz];
					if(tx.size()<ty.size()){
						ty=tx;
					}
				}
				cout<<tmp+ty<<endl;;
			}
			
		}		
	}
	return 0;
}
