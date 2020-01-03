#include <iostream>
#include <algorithm>
#include <cstring>
#define N 50005
#define S 26
#define LGN 17
using namespace std;

char str[N];
int sa[2][N],rnk[2][N],cnt[N],tmp1[N],tmp2[N];
int st[2][LGN][N];
int n;

void sufarr(int *sa,int *rnk,int st[][N])
{
	int *t1=tmp1,*t2=tmp2;

	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;i++)
		cnt[t1[i]=(str[i]-'a')]++;
	for(int i=1;i<max(S,n);i++)
		cnt[i]+=cnt[i-1];
	for(int i=n-1;i>=0;i--)
		sa[--cnt[t1[i]]]=i;

	for(int step=1;step<=n;step<<=1) {
		int p=0;
		for(int i=n-1;i>=n-step;i--)
			t2[p++]=i;
		for(int i=0;i<n;i++)
			if(sa[i]>=step) t2[p++]=sa[i]-step;

		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<n;i++)
			cnt[t1[i]]++;
		for(int i=1;i<max(S,n);i++)
			cnt[i]+=cnt[i-1];
		for(int i=n-1;i>=0;i--)
			sa[--cnt[t1[t2[i]]]]=t2[i];

		p=0;
		t2[sa[0]]=0;
		for(int i=1;i<n;i++)
			t2[sa[i]]=(t1[sa[i-1]]==t1[sa[i]]) && sa[i-1]+step<n && sa[i]+step<n && (t1[sa[i-1]+step]==t1[sa[i]+step]) ? p : ++p;

		swap(t1,t2);
		if(p>=n) break;
	}

	for(int i=0;i<n;i++)
		rnk[sa[i]]=i;

	int p=0;
	for(int i=0;i<n;i++) {
		if(p) p--;
		while(i+p<n&&rnk[i]&&sa[rnk[i]-1]+p<n&&str[i+p]==str[sa[rnk[i]-1]+p]) p++;
		st[0][rnk[i]]=p;
	}

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

int qur(int st[][N],int l,int r)
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

int main()
{
	ios::sync_with_stdio(false);

	int t,g,kase=0;
	cin>>t;
	while(t--) {
		cin>>g>>str;
		n=strlen(str);
		sufarr(sa[0],rnk[0],st[0]);
		for(int i=0;i<n/2;i++)
			swap(str[i],str[n-i-1]);
		sufarr(sa[1],rnk[1],st[1]);
		
		long long cnt=0;
		for(int l=1;l<=n/2;l++) {
			for(int i=0;i+l+g<n;i+=l) {
				int frt=min(l,qur(st[0],rnk[0][i],rnk[0][i+l+g])),bak=min(l,qur(st[1],rnk[1][n-1-i],rnk[1][n-1-i-l-g]));
				//cout<<l<<" "<<i<<" "<<frt<<" "<<bak<<endl;
				if(frt+bak>l)
					cnt+=min(l,frt+bak-l);
			}
		}

		cout<<"Case "<<++kase<<": "<<cnt<<endl;
	}

	return 0;
}