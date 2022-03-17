#include<bits/stdc++.h>

using namespace std;

const int mod=1000000007;
const double pi=acos(-1.0);
bool sf(int &x){return scanf("%d",&x)==1;}
bool sf(ll &x){return scanf("%I64d",&x)==1;}
bool sf(double &x){return scanf("%lf",&x)==1;}
bool sf(char &x){return scanf("%c",&x)==1;}
bool sf(char *x){return scanf("%s",x)==1;}
bool sf(string &x){return cin>>x;}
template<class T>inline void sf2(T&num){
    num=0;T f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')num=num*10+ch-'0',ch=getchar();
    num*=f;
}
void pf(int x,int op){op==0?printf("%d",x):printf("%d%c",x,op==1?' ':'\n');}
void pf(ll x,int op){op==0?printf("%I64d",x):printf("%I64d%c",x,op==1?' ':'\n');}
void pf(char x,int op){op==0?printf("%c",x):printf("%c%c",x,op==1?' ':'\n');}
void pf(char *x,int op){op==0?printf("%s",x):printf("%s%c",x,op==1?' ':'\n');}
void pf(string x,int op){op==0?cout<<x:cout<<x<<(op==1?' ':'\n');}
inline int gcd(int x,int y){if(!x)return y;return gcd(y%x,x);}
inline int power(int x,int k,int p){int res=1;for(;k;k>>=1,x=(ll)x*x%p)if(k&1)res=(ll)res*x%p;return res;}
int n,m,k;
int dp[maxn][maxn],a[maxn][maxn];
int dir[][2]={{0,1},{-1,0},{0,-1},{1,0},{-1,1},{-1,-1},{1,-1},{1,1}};

int main()
{
	
	return 0;
}