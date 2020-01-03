#include<cstdio>
char* strtok_1(char* str,char delim)
{
	static char* ptr;
	char* p;
	if(str!=NULL) ptr=str;
	if(ptr==NULL) return NULL;
	for(p=ptr;*p!='\0'&&*p!=delim;p++);
	char* t=ptr;
	ptr=(*p=='\0')?NULL:p+1;
	*p='\0';
	return t;
}