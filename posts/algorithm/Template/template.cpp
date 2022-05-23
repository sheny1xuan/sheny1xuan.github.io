#include<bits/stdc++.h>
using namespace std;

using ll = long long;
void pf(int x,int op){op==0?printf("%d",x):printf("%d%c",x,op==1?' ':'\n');}
void pf(ll x,int op){op==0?printf("%I64d",x):printf("%I64d%c",x,op==1?' ':'\n');}
void pf(char x,int op){op==0?printf("%c",x):printf("%c%c",x,op==1?' ':'\n');}
void pf(char *x,int op){op==0?printf("%s",x):printf("%s%c",x,op==1?' ':'\n');}
void pf(string x,int op){op==0?cout<<x:cout<<x<<(op==1?' ':'\n');}
template <typename T>
void pf(vector<T> v){for(auto&& x: v) {cout<<x<<" ";} cout << endl;}
inline int gcd(int x,int y){if(!x)return y;return gcd(y%x,x);}
inline int power(int x,int k,int p){int res=1;for(;k;k>>=1,x=(ll)x*x%p)if(k&1)res=(ll)res*x%p;return res;}
int dir[][2]={{0,1},{-1,0},{0,-1},{1,0},{-1,1},{-1,-1},{1,-1},{1,1}};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<vector<int>> f(3, vector<int>(3, 0));
	
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> f[i][j];
		}
	}
	
	pf<int>(f[0]);
	return 0;
}