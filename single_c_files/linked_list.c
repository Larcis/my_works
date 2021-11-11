#include <stdio.h>
#include <stdlib.h>

typedef struct s
{
	int val;
	struct s *next;
}node;
node* createNode(int);
void  addElement(node**,node*);
void  printList (char* ,node*);
void  freeList  (char* ,node**);
void  takeInput (char* ,node**);
node* listUnion (node* ,node*);
node* interSect (node* ,node*);
int main(int argc, char** argv)
{
	node *rootA = NULL; 
	node *rootB = NULL; 
	node *rootC = NULL; 
	node *rootD = NULL; 
	
	char *A = "A";		
	char *B = "B";		
	char *C = "C";		
	char *D = "D";		
	
	takeInput(A, &rootA); 
	takeInput(B, &rootB); 
	
	rootC = listUnion(rootA, rootB); 
	printList(C, rootC);             
	
	rootD = interSect(rootA, rootB); 
	printList(D, rootD);			 
	
	freeList(A, &rootA); 
	freeList(B, &rootB); 
	freeList(C, &rootC); 
	freeList(D, &rootD); 
    return 0;
}

node* listUnion (node *rootA ,node *rootB)
{
	node *rootC = NULL; 
	node *i = rootA;    
	node *j = rootB;    
	int last = -1;      
	while(i != NULL && j != NULL)
	{
		if(i->val > j->val)
		{
			if(j->val != last)
			{
				addElement(&rootC, createNode(j->val));
				last = j->val;
			}
			j = j->next;
		}
		else
		{
			if(i->val != last)
			{
				addElement(&rootC, createNode(i->val));
				last = i->val;
			}
			i = i->next;
		}
	}

	if(i != NULL)
	{
		while(i != NULL)
		{
			if(i->val != last)
			{
				addElement(&rootC, createNode(i->val));
				last = i->val;
			}
			i = i->next;
		}
	}
	else
	{
		while(j != NULL)
		{
			if(j->val != last)
			{
				addElement(&rootC, createNode(j->val));
				last = j->val;
			}
			j = j->next;
		}
	}
	return rootC;
}
node* interSect (node *rootA, node *rootB)
{
	node *rootD = NULL; 
	node *i = rootA;    
	node *j = rootB;    
	while(i != NULL && j != NULL)
	{
		if (i->val > j->val)
		{
			j = j->next;
		}
		else if(i->val == j->val)
		{
			addElement(&rootD, createNode(i->val));
			i = i->next;
		}
		else
		{
			i = i->next;
		}
	}
	rootD = listUnion(rootD,rootD);
	return rootD;
}

node* createNode(int val)
{
	node *tmp; 
	tmp = (node*)malloc(sizeof(node));
	if(tmp == NULL)
	{
		printf("bellek ayrilamadi!\n");
		exit(1);
	}
	tmp->val  = val;
	tmp->next = NULL;
	return tmp;
}

void addElement(node **rootPtr, node *newNode)
{
	if( *rootPtr == NULL || (*rootPtr)->val >= newNode->val)
	{
		newNode->next = *rootPtr;
		*rootPtr = newNode;
	}
	else
	{
		node *i;
		i = *rootPtr;
		while(i->next != NULL && i->next->val < newNode->val )
		{
			i = i->next;	
		}
		newNode->next = i->next;
		i->next = newNode;
	}
}

void printList(char *name, node *root)
{
	if(root == NULL)
	{
		printf(" %s listesi bos!", name);
	}
	else
	{
		printf("\n %s listesi:\n", name);
		node *i = root;
		while(i != NULL)
		{
			printf("%d ", i->val);
			i = i->next;
		}
	}
	printf("\n");
}
void freeList(char *name, node **rootPtr)
{
	if(*rootPtr == NULL)
		printf(" %s listesi zaten bos!\n", name);
	else
	{
		node *prev = *rootPtr;
		while(*rootPtr != NULL)
		{
			*rootPtr = (*rootPtr)->next;
			free(prev);
			prev = *rootPtr;	
		}
		printf(" %s listesi bosaltildi!\n", name);	
	}	
	
}
void takeInput(char* name, node **rootPtr)
{
	int input;
	printf("\n %s listesine eklemek istediginiz elemanlari arada \
			 \n bosluk birakarak yaziniz, bitirmek icin sonuna -1 koyunuz.\n",name);
	do
	{
		scanf("%d", &input);
		if(input != -1)
			addElement(rootPtr, createNode(input));
	}while(input != -1);
	printList(name,*rootPtr);
}
