#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;
class trie
{
	public:

	char data[30];
	trie *link[27];

	trie()
	{
		for(int i=0;i<27;i++)
			link[i]=NULL;
	}
}node;

main()
{
	trie *ptr=new trie;
	char given[20];
	cout<<"Enter the word:";		cin>>given;
	int i=0,j=0,k=0,count=0;
	trie *head;//=new trie;
	strcpy(ptr->data,"empty");
	head=ptr;
	while(given[i]!='\0')
	{
		k=given[i]-97;
		trie *temp=new trie;
		for(j=0;j<=i;j++)
			temp->data[j]=given[j];
		temp->data[j]='\0';
		ptr->link[k]=temp;
		ptr=temp;
		i++;
	}
	cout<<"the given data is:"<<ptr->data<<endl;
	i=0;
	while(given[i]!='\0')
	{
		k=given[i]-97;
		head=head->link[k];
		i++;
	}
		cout<<head->data<<endl;
}
