struct HI {
	const int mxlen=105;
	char bits[mxlen];
	int len;
	HI(long long val=0) {
		memset(bits,0,sizeof(bits));
		for(len=0;val;len++) {
			bits[len]=val%10;
			val/=10;
		}
	}
	HI operator +(const HI &rhs) {
		HI res;
		int ml=max(len,rhs.len);
		int ovf=0,tmp;
		for(int i=0;i<ml;i++) {
			tmp=ovf+bits[i]+rhs.bits[i];
			ovf=tmp/10;
			res.bits[i]=tmp%10;
		}
		if(ovf) res.bits[ml++]=ovf;
		res.len=ml;
		return res;
	}
	HI operator *(long long x) {
		HI res;
		int l=len;
		long long ovf=0,tmp;
		for(int i=0;i<len;i++) {
			tmp=1LL*bits[i]*x+ovf;
			res.bits[i]=tmp%10;
			ovf=tmp/10;
		}
		while(ovf) {
			res.bits[l++]=ovf%10;
			ovf/=10;
		}
		res.len=l;
		return res;
	}
	void out() {
		for(int i=len-1;i>=0;i--) putchar(bits[i]+'0');
		putchar('\n');
	}
};