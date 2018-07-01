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
	float price;
	char cat[27];
	trie()
	{
		for(int i=0;i<27;i++)
		{
			link[i]=NULL;
			data[i]='\0';
			key[i]='\0';
			cat[i]='\0';
		}
		price=0;
	}
};
struct file
{
	char name[27];
	int num[26];
	float price;
	char cat[50];
};
void search_cat(trie*,char*);
void recent_search(char *);
void search(trie*);
void search_middle(trie*,char*);
int main()
{
	int choice;
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
	file1.seekp(0,ios::beg);
	k=given[0]-97;//index variable
	for(c=0;c<10;c++)//loop for every input
	{
		ptr=head=node;//assigning everything to root
		file1.read((char *)&f,sizeof(f));//loop for every input
		len=strlen(f.name);
		i=0;
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
		ptr->price=f.price;
		strcpy(ptr->cat,f.cat);
	}//end for loop
	file1.close();
	do
	{
		c=5;
		system("clear");
		cout<<"Data uploaded in trie successfully!"<<endl;
		cout<<"1.Print all the items in category order"<<endl;
		cout<<"2.General search"<<endl<<"Enter your choice:";		cin>>choice;
		if(choice==1)
		{
			char incat[20];
			system("clear");
			cout<<"Categories:";
			cout<<"1.Electronics\n2.Men\n3.Women\n4.Home\nEnter your choice:";		cin>>incat;
			system("clear");
			cout<<incat<<":"<<endl;
			search_cat(node,incat);
		}
		else
		{
                	cout<<"Enter the product to search:";              cin>>given;
			cout<<"Searching on progress..."<<endl;
                	while(given[i]!='\0')//converting every input to lowercase
                	{
                	        given[i]=tolower(given[i]);
                	        i++;
                	}//end while
			k=given[0]-97;
			ptr=head=node;
			if(k>=0)
			{
				cout<<"\nRelated products:"<<endl;
				ptr=head=node;
				i=0;
				while(given[i]!='\0' && ptr->link[k]!=NULL)//traversing through the trie
				{
					k=given[i]-97;
					ptr=ptr->link[k];
					if(strcmp(ptr->data,"\0")==0)
						break;
					i++;
					k=given[i]-97;
				}//end while
				if(i>1)//if starting two letters of the given word matches with the file name
				{
					search(ptr);//function call for printing all the leaf nodes
					if(stat==0)
					{
						//stat=0;
						cout<<"Product not found!"<<endl;
					}
					i=1;
				}
				else if(i<2)//if the given word lies in the file name
				{
					for(i=0;given[i];i++)
						ascnum[i]=given[i]-97;
					file1.open("names.dat",ios::binary | ios::in);
					file1.seekp(0,ios::beg);
					while(file1.read((char *)&f,sizeof(f)))
					{
						c=0;
						len=strlen(f.name);
						giv_len=strlen(given);
						for(i=0;i<len-1;i++)
							for(j=0;j<giv_len-1;j++)
								if(f.num[i]==ascnum[j])
									if(f.num[i+1]==ascnum[j+1])
										c++;
						if(c>1)
						{
							k=100;
							cout<<"Category:"<<f.cat<<endl;
							cout<<"Name:"<<f.name<<endl;
							cout<<"Price:"<<f.price<<endl;
						}
					}
					if(k!=100)
        			        	cout<<"Product not found!"<<endl;
				}
				else
					cout<<"Product not found!"<<endl;
				file1.close();
			}
			else
			cout<<"Product not found!"<<endl;
			recent_search(given);
		}
		cout<<"\nEnter 1 to continue:";						cin>>ch;
	}while(ch==1);//end do while loop
	file1.close();
	delete head;
	delete node;
	delete ptr;
}//end main
void search(trie *ptr)//recursive function to print all the outputs
{
	int some=0,i;
	stat=0;
	for(i=0;i<26;i++)//traverses to the leaf nodes
		if(ptr->link[i]!=NULL)
			search(ptr->link[i]);
	if(ptr->key[0]!='\0')//printint the data in the leaf nodes
	{
		cout<<"Name:"<<ptr->key<<endl;
		cout<<"Price:"<<ptr->price<<endl;
		cout<<"Category:"<<ptr->cat<<endl<<endl;
		stat++;
	}
}
void search_cat(trie *ptr,char *abc)//recursive function to print all the outputs
{
        int some=0,i;
        stat=0;
        for(i=0;i<26;i++)//traverses to the leaf nodes
                if(ptr->link[i]!=NULL)
                        search_cat(ptr->link[i],abc);
        if(ptr->key[0]!='\0' && strcmp(ptr->cat,abc)==0)//printint the data in the leaf nodes
        {
                cout<<"Name:"<<ptr->key<<endl;
		cout<<"Price:"<<ptr->price<<endl<<endl;
                stat++;
        }
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
                cout<<"\nRecent product searches:"<<endl;
                while(top>=0)
                {
                        cout<<search[top];
                        cout<<endl;
                        top--;
                }
        }
        top=i;
}

