void fwt(int arr[],int n,int type)
{
	if(n==1) return;
	int m=n>>1;
	fwt(arr,m,type);
	fwt(arr+m,m,type);
	for(int i=0;i<m;i++) {
		int a,b;
		switch(type) {
			case 1:
			a=arr[i],b=arr[i+m];
			arr[i]=a+b;
			arr[i+m]=a-b;
			break;
			case 2:
			arr[i]+=arr[i+m];
			break;
			case 3:
			arr[i+m]+=arr[i];
			break;
		}
	}
}

void dfwt(int arr[],int n,int type)
{
	if(n==1) return;
	int m=n>>1;
	dfwt(arr,m,type);
	dfwt(arr+m,m,type);
	for(int i=0;i<m;i++) {
		int a,b;
		switch(type) {
			case 1:
			a=arr[i],b=arr[i+m];
			arr[i]=(a+b)>>1;
			arr[i+m]=(a-b)>>1;
			break;
			case 2:
			arr[i]-=arr[i+m];
			break;
			case 3:
			arr[i+m]-=arr[i];
			break;
		}
	}
}