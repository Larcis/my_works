/**
	@file
	Veri Yapýlarý ve Algoritmalar 2017 Bahar Dönemi 1. Ödev:
	Linkli liste yapýsýný kodlayýnýz ve kullanýcýdan okunan 
	iki linkli liste kullanarak küme birleþimi ve küme kesi-
	þimi iþlemlerini gerçekleþtiriniz. 
	@author
	Name: 				Uygar Koroglu	
	Student no: 		16011052
	Date: 				27/02/2018
	E-Mail:				korogluygar@gmail.com
	Compiler used:  	TDM-GCC 4.9.2 64-bit Release
	IDE: 				Dev-C++
	Operating System 	Windows 8.1
	CPU:				Intel i5 4200U 1.60 GHz - 2.30 GHz
	RAM:				6 GB DDR3
	Video Card: 		Nvdia gt 740m 
*/


#include <stdio.h>
#include <stdlib.h>

typedef struct s
{
	int val;
	struct s *next;
}node;//linkli liste oluþturmak için kullandýgým birim yapý

/**
	malloc fonksiyonu ile bir node 
	için yer ayýrýr ve node.val degerine
	parametre olarak verilen int degerini
	atar.
	@param nodun saklayacagý deger
	@return yer ayrýlan nodun adresi
*/
node* createNode(int);
/**
	bu fonksiyon listeye sýralý eleman 
	ekleme iþini gerçekleþtirir. root un
    durumunu kontrol eder,root bos veya ýcýndeký
    data yený ekleyecegýmýz datadan buyukse
	yený node, root olacak sekýlde gereklý 
	atamalar yapýlýr. bunlardan biri degilse
	iterasyon ile listede nodun eklenmesi 
	gereken pozisyonu bulur ve ekler.
	@param root un adresi
	@param yeni eklenecek nod
*/
void  addElement(node**,node*);
/**
	listeyi ve listenin ismini yazdýrýr.
	@param listenin ismi
	@param listenin root u
*/
void  printList (char* ,node*);
/**
	listenin butun elemanlarýný free'ler
	@param listenin adý
	@param listenin rootunun adresi
*/
void  freeList  (char* ,node**);
/**
	kullanýcýdan -1 girdisi gelene kadar 
	ilgili listeye girdileri ekler.
	@param listenin adý
	@param listenin rootunun adresi
*/
void  takeInput (char* ,node**);
/**
	kendisine root u verilen iki listenin
	küme birlesimini geri dondurur. merge
	algoritmasýnýn biraz degistirilmis ver-
	siyonunu kullanýr. ortak listeye eklenen
	son elemaný bir degiskende saklar ve eger
	listeye yeni eklenecek eleman son eklenen
	elemana esit ise bu elemaný listeye eklemez.
	@param root A
	@param root B
	@return root C 
*/
node* listUnion (node* ,node*);
/**
	kendisine root u verilen iki listenin
	küme kesisimini geri dondurur.
	
	referans liste iterasyon elemaný i (A listesi)
	diger liste iterasyon elemaný j    (B listesi)
	
	i>j iken j sonraki elemana gecer.
	i<=j oldugu anda i eger j ye esitse 
	kesisim listesine eklenir ve i,j bir 
	sonraki degere gecer.i veya j den 
	herhangi biri NULL olursa islem sonlanýr. 
	bu sekilde en kotu, uzun olan liste-
	nin uzunlugu kadar bir  iterasyon
    sayýsýyla kesisim kumesi bulunur.
	 worst case comlexity O(n); 
	@param root A
	@param root B
	@return root C 
*/
node* interSect (node* ,node*);
/**
	main fonksiyonunda A,B,C,D listelerinin
	root larýný olusturdum. A ve B listesini
	kullanýcýdan okudum. C = AuB islemini 
	yaptým. D = AnB islemini yaptým ve lis-
	teleri ekrana yazdýrdým.En son butun
	listeleri freeledim.
	@param arguman sayýsý
	@param arguman vektoru
	@return program exit value
*/
int main(int argc, char** argv)
{
	node *rootA = NULL; //A listesi için root elemaný
	node *rootB = NULL; //B listesi için root elemaný
	node *rootC = NULL; //C listesi için root elemaný
	node *rootD = NULL; //D listesi için root elemaný
	
	char *A = "A";		//A listesinin adý
	char *B = "B";		//B listesinin adý
	char *C = "C";		//C listesinin adý
	char *D = "D";		//D listesinin adý
	
	takeInput(A, &rootA); //A listesi kullanýcýdan okundu
	takeInput(B, &rootB); //B listesi kullanýcýdan okundu
	
	rootC = listUnion(rootA, rootB); //C listesine A ve B listesinin birlesimi atandý
	printList(C, rootC);             //C listesi ekrana basýldý
	
	rootD = interSect(rootA, rootB); //D listesine A ve B listesinin kesisimi atandý
	printList(D, rootD);			 //D listesi ekrana basýldý
	
	freeList(A, &rootA); //A listesi freelendi
	freeList(B, &rootB); //B listesi freelendi
	freeList(C, &rootC); //C listesi freelendi
	freeList(D, &rootD); //D listesi freelendi
    return 0;
}

node* listUnion (node *rootA ,node *rootB)
{
	node *rootC = NULL; //C listesinin head(root) elemaný 
	node *i = rootA;    //A listesi için iterasyon elemaný
	node *j = rootB;    //B listesi için iterasyon elemaný
	int last = -1;      //C listesine son eklenen elemanýn deðeri
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
	node *rootD = NULL; //D listesinin head(root) elemaný 
	node *i = rootA;    //A listesi için iterasyon elemaný
	node *j = rootB;    //B listesi için iterasyon elemaný
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
	/* 
	yanlýs input sonrasý olusan tekrar 
	eden elemanlarý kesisim listesinden 
	silmek icin commen acýlabilir.
	rootD = listUnion(rootD, rootD); 
	*/
	return rootD;
}

node* createNode(int val)
{
	node *tmp;  //ayrýlan bellegin adresini dondurebilmek icin gecici pointer
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
