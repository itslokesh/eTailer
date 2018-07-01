#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std;
struct trie
{
	char data[100];
	trie link[27];//={a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
}*root=NULL;
int main()
{
	trie *temp;
	char give[26];
	int i,j,k;
	cout<<"Enter the word:";		cin>>give;
	i=j=0;
	int num;
	trie *ptr=new trie;
	while(give[i]!='\0')
	{
		num=give[i];
		ptr=ptr->link[num];
		i++;
	}
	strcpy(ptr->data,give);
	cout<<ptr->data<<"123"<<endl;
	cout<<"line 1"<<endl;
	i=0;
	cout<<give<<endl;
	while(give[i]!='\0')
	{
		cout<<"2";
		num=give[i]-97;
		temp=temp->link[num];
		i++;
	}
	cout<<"\nthe given word is:"<<temp->data<<endl;
}
