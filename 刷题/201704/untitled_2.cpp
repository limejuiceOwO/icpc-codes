//斜堆 逆推+模拟 智商题（？）
//数据范围有误导性
#include <iostream>
#include <algorithm>
#include <cassert>
#define N 55
using namespace std;

int lch[N],rch[N],fa[N];
int ans[N],root;

int main()
{
	int n,cnt=0;
	ios::sync_with_stdio(false);
	cin>>n;
	for(int i=1,val;i<=n;i++) {
		cin>>val;
		if(val>=100) {
			rch[val-100]=i;
			fa[i]=val-100;
		} else {
			lch[val]=i;
			fa[i]=val;
		}
	}
	fa[root=0]=-1;
	n++;
	while(n--) {
		int p;
		for(p=root;lch[p]&&rch[p];p=lch[p]);
		if(lch[p]!=0&&lch[lch[p]]==0) p=lch[p];
		//assert(p!=0);
		//cout<<p<<endl;
		ans[cnt++]=p;
		if(lch[p]) fa[lch[p]]=fa[p];
		if(fa[p]==-1) {
			root=lch[p];
			fa[root]=-1;
		} else {
			lch[fa[p]]=lch[p];
			for(p=fa[p];p!=-1;p=fa[p]) {
				//cout<<p<<endl;
				swap(lch[p],rch[p]);
			}
		}
	}
	while(cnt) {
		cout<<ans[--cnt]<<" ";
	}
	cout<<endl;
	return 0;
}