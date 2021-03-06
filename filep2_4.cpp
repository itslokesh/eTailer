#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;
int stat=0;
class trie
{
	public:
	char data[27],key[27];
	trie *link[27];
	trie()
	{
		for(int i=0;i<27;i++)
		{
			link[i]=NULL;
			data[i]='\0';
			key[i]='\0';
		}
	}
};
struct file
{
	char name[26];
	int num[26];
};
void recent_search(char *);
void search(trie*);
void search_middle(trie*,char*);
int main()
{
	int ch;//used in do while loop
	file f;//for reading the names and array in file
	trie *ptr=new trie;//used to traverse through trie
	trie *node=new trie;//used as the root of the trie
	trie *head=new trie;//used to traverse through trie
	head=ptr=node;//assumes everything to the root
	int i=0;//counter variable used for the indexing of letters in words
	int j=0;//counter variable for loops
	int c=0;//counter variable for the input of all the words in the database
	int k=0;//index variable for words converted from ascii values to 0,1,2,.. etc..
	int some=0;//counter variable to find the unknonw index of any word
	int ascnum[26];//to store the ascii numbers-97 for every letters in the current given word
	int len=0;//string length for the file name currently in use
	int giv_len=0;//string length for the given name currently in use
	char given[27];//input word
	fstream file1;
	file1.open("names.dat",ios::binary | ios::in);//opening the give file
	k=given[0]-97;//index variable
	for(c=0;c<3;c++)//loop for every input
	{
		ptr=head=node;//assigning everything to root
		file1.read((char*) &f,sizeof(f));
		len=strlen(f.name);
		i=0;
		strcpy(ptr->data,"empty");
		while(f.name[i]!='\0')//creating the word in the existing trie
		{
			k=f.name[i]-97;
			trie *temp=new trie;//used for assigning new address
			for(j=0;j<=i;j++)//copying the data to node's data
				temp->data[j]=f.name[j];
			temp->data[j]='\0';
			if(c==0)//condition for preventing coincidence
			{
				if(i==0)
               	                        node->link[k]=temp;
                                ptr->link[k]=temp;
				ptr=temp;
			}//end if
			else
			{
				if(ptr->link[k]!=NULL)
					ptr=ptr->link[k];
				else
				{
					ptr=ptr->link[k]=temp;
					if(i==0)
						node->link[k]=temp;
				}//end else
			}//end else
			++i;//goes to next letter of the existing word
		}//end while loop
		strcpy(ptr->key,f.name);//ptr->key contains the file words while others contain null in key
	}//end for loop
	file1.close();
	do
	{
		c=5;
		system("clear");
		cout<<"Data uploaded in the trie successfully!"<<endl;
		cout<<"\nEnter the product to search:"; 		             cin>>given;
                while(given[i]!='\0')//converting every input to lowercase
                {
                        given[i]=tolower(given[i]);
                        i++;
                }//end while
		k=given[0]-97;
		ptr=head=node;
		if(k>=0)//check for numbers
		{
			cout<<"\nRelated products:"<<endl;
			ptr=head=node;
			i=0;
			k=given[i]-97;
			while(given[i]!='\0' && ptr->link[k]!=NULL)//traversing through the trie
			{
				k=given[i]-97;
				ptr=ptr->link[k];
				if(strcmp(ptr->data,"\0")==0)
					break;
				i++;
				k=given[i]-97;
			}//end while
/*			if(strcmp(given,ptr->key)==0)//if every letter is located in the present node
			{
				cout<<"Search:\n"<<ptr->data<<endl;
				i=2;
			}*/
			if(i>1)//if the given letters lies at front
			{
				search(ptr);
				if(stat==0)
					cout<<"Product not found!"<<endl;
			}
			else if(i<2)//if the given letters lies at center
			{
				ptr=node;
				search_middle(ptr,given);
				if(stat==0)
					cout<<"Product not found!"<<endl;
			}
			else
				cout<<"Product not found!"<<endl;
			file1.close();
		}
		else
			cout<<"Product not found!"<<endl;
		recent_search(given);//to print recent searches option
		cout<<"\nEnter 1 to continue:";				cin>>ch;
	}while(ch==1);//end do while loop
	file1.close();
	delete ptr;
	delete head;
	delete node;
}//end main
void search(trie *ptr)//recursive function to print all the outputs
{
	int some=0,i;
	stat=0;
	for(i=0;i<26;i++)//to traverse to the leaf nodes
		if(ptr->link[i]!=NULL)
			search(ptr->link[i]);
	if(ptr->key[0]!='\0')//to print the leaf node
	{
		cout<<ptr->key<<endl;
		stat++;
	}
}
void search_middle(trie *ptr,char *given)//recursive function to print all the outputs if the input lies at center
{
	int some=0,i=0,j=0,k=0;
	for(k=0;k<=25;k++)//to traverse to the leaf nodes
		if(ptr->link[k]!=NULL)
			search_middle(ptr->link[k],given);
	i=0;
	while(ptr->key[i]!='\0')//to check whether the given word lies in any of the file words
	{
		j=0;
        	while(given[j]!='\0')
		{
                	if(ptr->key[i]==given[j])
                        	if(ptr->key[i+1]==given[j+1])
                                     	some++;
			++j;
		}
		++i;
	}
     	if(some>0)//if anything present it prints all its children
		search(ptr);
}
void recent_search(char name[20])//function for recent search
{
        static int top=-1;
        static char search[100][20];
        top++;
        strcpy(search[top],name);
        int i=0,count=0;
        i=top;
        if(top>0)
        {
                top--;
                cout<<"\nRecent searches:"<<endl;
                while(top>=0)
                {
                        cout<<search[top];
                        cout<<endl;
                        top--;
                }
        }
        top=i;
}
