#include <iostream>
#include <algorithm>
#include <cstring>
#define N 1000005
#define LGN 22
#define S 26
using namespace std;

char str[N];
int sa[N],rnk[N],height[N],cnt[N],tmp1[N],tmp2[N];
int st[LGN][N];
int n;

void sufarr()
{
	int *t1=tmp1,*t2=tmp2;

	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;i++)
		cnt[t1[i]=(str[i]-'a')]++;
	for(int i=1;i<max(S,n);i++)
		cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--)
		sa[--cnt[t1[i]]]=i;

	for(int step=1;step<=n;step<<=1) { //t1:-rank,t2:-第二关键字排序后的sa
		int p=0;
		for(int i=n-1;i>=n-step;i--)
			t2[p++]=i;
		//for(int i=n-step;i<n;i++) t2[p++]=i; //lrj写错了？
		for(int i=0;i<n;i++)
			if(sa[i]>=step) t2[p++]=sa[i]-step;

		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++)
			cnt[t1[i]]++;
		for(int i=1;i<max(S,n);i++) //注意最多有n个名次
			cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)
			sa[--cnt[t1[t2[i]]]]=t2[i];

		p=0; //计算新的rank数组,注意下标越界
		t2[sa[0]]=0;
		for(int i=1;i<n;i++)
			t2[sa[i]]=(t1[sa[i-1]]==t1[sa[i]]) && sa[i-1]+step<n && sa[i]+step<n && (t1[sa[i-1]+step]==t1[sa[i]+step]) ? p : ++p;

		swap(t1,t2);
		if(p>=n) break;
	}

	for(int i=0;i<n;i++)
		rnk[sa[i]]=i;

	int p=0;
	for(int i=0;i<n;i++) { //height[i]:-sa[i]与sa[i-1]的最长公共前缀，h[i]:-height[rank[i]]
		if(p) p--;
		while(i+p<n&&rnk[i]&&sa[rnk[i]-1]+p<n&&str[i+p]==str[sa[rnk[i]-1]+p]) p++; //h[i]>=h[i-1]-1
		height[rnk[i]]=p;
	}

	for(int i=0;i<n;i++)
		st[0][i]=height[i];

	int pow=1;
	for(int k=1;k<LGN;k++) {
		for(int i=0;i<n;i++) {
			st[k][i]=st[k-1][i];
			if(i+pow<n)
				st[k][i]=min(st[k][i],st[k-1][i+pow]);
		}

		pow<<=1;
	}
}

int qur(int l,int r) //lcp
{
	int k=0,pow=1;
	if(l==r) return n-r;
	if(r<l) swap(l,r);
	l++;
	while(pow<=r-l+1) {
		k++;
		pow<<=1;
	}
	k--,pow>>=1;
	
	return min(st[k][l],st[k][r-pow+1]);
}

void out(int *p,int n)
{
	for(int i=0;i<n;i++)
		cout<<p[i]<<" ";

	cout<<endl;
}

int main()
{
	cin>>str;
	n=strlen(str);
	cout<<n<<endl;
	sufarr();

	out(sa,n);
	out(rnk,n);
	out(height,n);

	while(1) {
		int l,r;
		cin>>l>>r;
		cout<<qur(l,r)<<endl;
	}

	return 0;
}