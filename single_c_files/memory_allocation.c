/*
	@file
	Programming Language Autumn 2017 assignment 1.
	A program that simulates arrangement of a hyper market's cash-points.  
	It open a new cash-point or close an old one based on how many customer in line.
	@author
	Name: 				Uygar Koroglu	
	Student no: 		16011052
	Date: 				09/10/2017
	E-Mail:				korogluygar@gmail.com
	Compiler used:  	GCC
	IDE: 				Dev-C++
	Operating System 	Windows 8.1
	CPU:				Intel i5 4200U 1.60 GHz - 2.30 GHz
	RAM:				6 GB DDR3
	Video Card: 		Nvdia gt 740m 
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

/*
   this function find the minimum value
   from an array and it increase 1 that 
   value.
   @param integer pointer arr for array
   @param integer n for length of array  
*/
   
void min_arr(int *arr,int n){
	int i=0,min=99999,index=n;
	for(;i<n;i++){
		if(arr[i]<min){
			min=arr[i];
			index=i;	
		}
	}
	*(arr+index)+=1;
}
	
	//this function prints the array 
	//and the total of array items 
	//with a good look 
	//@param integer pointer arr as array
	//@param integer cpc as size of array
	//@return total customers in line as integer

int display(int *arr,int cpc){
	int top_c,i;
	//calculation of total customers 
		top_c=0;
		for(i=0;i<cpc;i++)
		{
			printf("Cash-point-%d ---> %d \n",i+1,*(arr+i));
			top_c+=*(arr+i);
		}
		//outputs
		printf("\nCustomer counter: %d",top_c);
		printf("\nCash-point counter: %d\n",cpc);
		return top_c;
	
}

/*
	 Main function gets the number of cash-points 
	 and max how many  people can stand in one line
	 than it start an infinite loop and do controls
	 for cash-point arrangement than it arrange ne-
	 cessary number of cash-points with dynamic me-
	 mory allocation.
 
 */
int main(){
	srand(time(NULL));
	
	int i,max_cp,x,top_c=0,cpc=1;
	//i for loop count 
	//max_cp for maximum number of cash-points
	//x for maximum people for one line
	//top_c for customers total number
	//cpc for cash-point counter
	 
	printf("How many cash-point do you have? ");
	scanf("%d",&max_cp);//input for number of cashpoints
	printf("Max how many people can wait in line? ");
	scanf("%d",&x);//input for length of max line can be
	int *arr=(int*)malloc(sizeof(int)*cpc);
	if(!arr){
		printf("\nThere is no enough space!\n");
		exit(1);
	} 
	// arr used as an array and it represent cash-points
	*arr=0;
	//initial value for first index of array
	
	while(1==1){//start of infinite loop 
			
		int come=rand()%10+1,go=rand()%5+1;
		//come for people who get in the line
		//go for people who exit the line
		
		if(top_c-go<0)go=0;
		//control for never having negative number customer score
		
		
		//decrease 1 from a random element of array
		//for 'go' times
		//and decrease one cash point 
		//if any one of cash-points have 0 customer
		for(i=0;i<go;i++){
			int t=rand()%cpc;
			if(arr[t]>1)arr[t]--;
			else{
				int j=t;
				for(;j<cpc-1;j++){
					arr[j]=arr[j+1];
				}
				arr[j+1]=0;
				if(cpc!=1){
					cpc--;
					arr=(int*)realloc(arr,sizeof(int)*cpc);
				}
			
			}
			//output of array's situation
			if(cpc>=max_cp){
				printf("\tAll cash-points are available.\n");
			}
			top_c=display(arr,cpc);
			Sleep(300);
			system("cls");//clear screen command for a better look
		}
	
	     
		//increase 1 from minimum element of array
		//for 'come' times
		//and add cash-point if all cash-points have more than or equal x customer
		for(i=0;i<come;i++){
			min_arr(arr,cpc);
			int j=0;
			while(j<cpc && arr[j]>=x)j++;   // control for 'are all cash-points full?'
			if(j==cpc && cpc<max_cp){
				cpc++;                                 //increase of cash-point counter 
				arr=(int*)realloc(arr,sizeof(int)*cpc);//reallocation off arr array
				if(!arr){							   //control of reallocation
					printf("\nThere is no enough space!\n");
					exit(1);
				} 
				*(arr+cpc-1)=0;
				
			}
			//output of array's situation
			if(cpc>=max_cp){
				printf("\tAll cash-points are available.\n");
		    }
			top_c=display(arr,cpc);
			Sleep(300);
			system("cls");//clear screen command for a better look
		}
		
		
	/*	Note: This part of code is mented to output
		just one time after total increase and dec-
		rease and it doesn't show the change of 
		cash-points clearly
		
		//calculation of total customers
		top_c=0;
		for(i=0;i<cpc;i++)
		{
			printf("Cash-point-%d ---> %d \n",i+1,*(arr+i));
			top_c+=*(arr+i);
		}
		//outputs
		printf("\nCustomer counter: %d",top_c);
		printf("\nCash-point counter: %d\n",cpc);
		
		Sleep(1000);
		system("cls");//clear screen command for a better look
		
	*/
	}
	
	return 0;
}
