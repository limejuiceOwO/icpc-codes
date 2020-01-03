#include <iostream>
#include <algorithm>
#include <cstring>
#define N 100005
#define LGN 20
#define S 26
using namespace std;

char str[N];
int sa[N],rnk[N],height[N],cnt[N],tmp1[N],tmp2[N],len[N];
int st[LGN][N];
int n;

void sufarr()
{
	int *t1=tmp1,*t2=tmp2;

	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<n;i++)
		cnt[t1[i]=(str[i]-'a')]++;
	for(int i=1;i<S;i++)
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
		for(int i=1;i<n;i++)
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

	memcpy(rnk,t1,sizeof(rnk));

	int p=0;
	for(int i=0;i<n;i++) {
		if(p) p--;
		while(i+p<n&&rnk[i]&&sa[rnk[i]-1]+p<n&&str[i+p]==str[sa[rnk[i]-1]+p]) p++;
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

int qur(int l,int r)
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

	int kase=0;
	while(1) {
		cin>>str;
		if(str[0]=='#') break;

		n=strlen(str);
		sufarr();

		int ans=0,cnt=0;
		for(int l=1;l<n;l++) {
			int lans=0;
			for(int i=0;i+l<n;i+=l) {
				int z=qur(rnk[i],rnk[i+l]);
				int a=z/l+1;
				if(i&&qur(rnk[i-(l-z%l)],rnk[i+z%l])/l+1>a)
					a=qur(rnk[i-(l-z%l)],rnk[i+z%l])/l+1;

				lans=max(lans,a);
			}

			if(lans>ans) {
				cnt=0;
				ans=lans;
				len[cnt++]=l;
			} else if(lans==ans) {
				len[cnt++]=l;
			}
		}

		//cout<<ans<<endl;
		cout<<"Case "<<++kase<<": ";
		for(int i=0;i<n;i++) {
			for(int j=0;j<cnt;j++) {
				if(sa[i]+len[j]>=n) break;
				int l=qur(i,rnk[sa[i]+len[j]])/len[j]+1;
				if(l==ans) {
					for(int p=sa[i];p<sa[i]+len[j]*l;p++)
						cout<<str[p];
					cout<<endl;
					goto end;
				}
			}
		}
		end:while(0);
	}
	return 0;
}