#include<stdlib.h>
#include<stdio.h>
// #include<conio.h>
#include<math.h>
#include<ctype.h>

#define Linux
#ifdef Linux
	void getch(){}
	#define system(cmd) system("clear")
#endif

float f(float ,int ,float*);
float df(float,int,float*);
void gauss_jordan(float matris[30][30],int n);
void anamenu();
void kokmenu();
void matris();
void gauss();
void integral();
void turev();
void matrisinvers(float a[][50],float b[][50],int n);
int main(){
	
	char a;
	anamenu();
	do{
	system("CLS");
	printf("\n Cikmak istiyormusunuz(e/h)");
	scanf("%c",&a);
	if(a=='e' || a=='E') return 0;
	if(a=='h' || a=='H') anamenu();

}while(a!='e'||a!='E'||a!='H'||a!='h');

}
void turev(){
    system("cls");		 
	int n;
	printf("\n Fonksiyon kacinci dereceden? ");
	scanf("%d",&n);
	
	float A[50];
	
 	for(int i=0;i<=n;i++){
 	 	printf(" x^%d nin katsayiyi giriniz: ",n-i);
  		scanf("%f",&A[i]);

    }      	

    printf("\n\n ");
    for(int j=n;j>0;j--){
   		printf("%fx^%d + ",A[n-j],j);

    }	
    printf("%f",A[n]);
    float x,h;
    printf("\n turevini almak istediginiz deger: ");
    scanf("%f",&x);
    printf("\n h degeri: ");
    scanf("%f",&h);
	float ileritop,geritop,merkezitop;
	
	geritop=(f(x,n,A)-f(x-h,n,A))/h;
	ileritop=(f(x+h,n,A)-f(x,n,A))/h;
	merkezitop=(f(x+h,n,A)-f(x-h,n,A))/(2*h);
	printf("\n\n\tGeriye dogru farklar metodu= %.3f",geritop);
	printf("\n\n\tIleri dogru farklar metodu= %.3f",ileritop);
	printf("\n\n\tMerkezi farklar metodu= %.3f",merkezitop);
	getch();
	anamenu();
	
}
void integral(){
	system("cls");
	int w;
	printf("\n\t\tINTEGRAL ALMA\n\n");
	printf("\n\t1)Trapez metodu");
	printf("\n\t2)Simpson metodu");
	printf("\n\t3)anamenu");
	printf("\n\tTercih: ");
	scanf("%d",&w);
	switch(w){
            case 1:	{
			
			   system("cls");printf("\n TRAPEZ METODU\n\n");
                float dizi[30];
				int i,n;
				printf("\n fonksiyon kacinci dereceden: ");
				scanf("%d",&n);
				for(i=0;i<=n;i++){
					printf(" x^%d nin katsayisi: ",n-i);
					scanf("%f",&dizi[i]);
				}
				float x[1000],fx[1000];
				int ust;
				float h;
				int a,b;
				printf(" h= ");
				scanf("%f",&h);
				printf(" a ve b= ");
				scanf("%d%d",&a,&b);
			
				ust=(abs(b-a))/h+1;
				for(i=0;i<ust;i++){
					x[i]=a+h*i;
				}
				for(i=0;i<ust;i++){
					fx[i]=f(x[i],n,dizi);
				}
				float fxtop=0;
				for(i=1;i<ust-1;i++){fxtop=fxtop+fx[i];
				}
				float top;
				top=h*((fx[0]+fx[ust-1])/2+fxtop);
				printf("\n\n integral= %.4f",top);	getch();
				anamenu;
			break;
		    }
			
			case 2: {system("cls");
				 printf("\n\tSIMPSON METODU\n\n");
				 float dizi1[30];
				int i,n1;
				printf(" fonksiyon kacinci dereceden: ");
				scanf("%d",&n1);
				for(i=0;i<=n1;i++){
					printf(" x^%d nin katsayisi: ",n1-i);
					scanf("%f",&dizi1[i]);
				}
				float x1[1000],fx1[1000];
				int ust1;
				float h1;
				int a1,b1;
				printf(" h= ");
				scanf("%f",&h1);
				printf(" a ve b= ");
				scanf("%d%d",&a1,&b1);
			
				ust1=(abs(b1-a1))/h1+1;
				for(i=0;i<ust1;i++){
					x1[i]=a1+h1*i;
				}
				for(i=0;i<ust1;i++){
					fx1[i]=f(x1[i],n1,dizi1);
				}
				float fxtop1=0,fxtop2=0;
				for(i=1;i<ust1-1;i=i+2){fxtop1=fxtop1+fx1[i];
				}
				for(i=2;i<ust1-1;i=i+2){fxtop2=fxtop2+fx1[i];
				}
				float top1;
				top1=h1/3*(4*fxtop1+2*fxtop2+fx1[0]+fx1[ust1-1]);
				printf("\n\n integral= %.4f",top1);
				getch();
				anamenu();
				
				 break;
			}

			
			case 3: anamenu(); break;
			default: {
				printf("\n hatali giris");
				getch();
				anamenu();
				break;
			}
			  
	}

	
}
void gauss(){
	system("cls");
    int i,j,n;
	float matris[30][30];
	printf("\n GAUSS JORDAN ELEMINASYON\n");
	printf("\n denklem sayisi: ");
	scanf("%d",&n);
	
	for(i=0;i<n;i++){
        printf("\n\n %d. denklem icin: \n\n",i+1);
        for(j=0;j<=n;j++){
	        if(j%(n+1)==n)printf("\n Sonucu giriniz: ");
        	else printf("\n x%d nin katsayisini giriniz: ",j+1);
        	scanf("%f",&matris[i][j]);
		}
	}

	
	gauss_jordan(matris,n);
    printf("\n");	
		
	for(i=0;i<n;i++){
		printf("\n x%d= %.3f",i+1,matris[i][n]);
	}	
	
	
	getch();
	anamenu();
}


void anamenu(){
	system("CLS");
	
	int tercih;
	printf("\n\n\n\n\t...Say%csal Analiz Arac%cna Ho%cgeldiniz...\n",141,141,159);
	printf("\n\n\t\tSe%cenekler \n",135);
	printf("\t\t\t1)K%ck bulma y%cntemleri\n",148,148);
	printf("\t\t\t2)N%cmerik t%crev\n",129,129);
	printf("\t\t\t3)N%cmerik integral\n",129);
	printf("\t\t\t4)Matris inversi alma\n");
	printf("\t\t\t5)Gauss Jordan Eleminasyon\n");
	printf("\t\t\t6)%c%ck%c%c\n",128,141,141,159);
	printf("\n\t\t\tTecihiniz: ");
    scanf("%d",&tercih);
	  
	switch(tercih){
		case 1: kokmenu();break;
		case 2: turev(); break;
		case 3: integral(); break;
		
		case 4:matris(); break;
		case 5:gauss();break;
		case 6: break;break;
		
		default: {
			printf("\n Hatali giris!\n");
			getch();
			anamenu();
			break;
		}
	}
}
void matris(){	system("cls");
	 		  	 printf("\n\n\tMATRIS INVERS ALMA\n\n");
			   	int n;
				float a[50][50],b[50][50];
			
				printf("\tmatrisin satir sayisini giriniz: ");
				scanf("%d",&n);
				for (int i=0;i<n;i++){
			
			 		for(int j=0;j<n;j++){
			 			printf("\n\ta[%d][%d]= ",i+1,j+1);
			 			scanf("%f",&a[i][j]);
			 			if(i==j)b[i][j]=1.0;
			 			else b[i][j]=0.0;
					 }}
					 printf("\n\n\tOrjinal matris\n\n");
				for (int i=0;i<n;i++){
					printf("\n\n\t");	
			 		for(int j=0;j<n;j++){
							printf("%.3f  ",a[i][j]);
					 }}
					 printf("\n\n");
					 
					 matrisinvers(a,b,n);

					 printf("\n\n\tInvers matris\n\n");	 
				for (int i=0;i<n;i++){
					printf("\n\n\t");	
			 		for(int j=0;j<n;j++){
							printf("%.3f  ",b[i][j]);
					 }} getch();anamenu();
}
void kokmenu(){
    system("CLS");
	int tercih;
	
	printf("\n\n\n\t\tSecenekler \n");
	printf("\t\t\t1)Newton-Raphson\n");
	printf("\t\t\t2)Bisection\n");
	printf("\t\t\t3)Grafik\n");
	printf("\t\t\t4)Regula-false\n");
	printf("\t\t\t5)Anamenu\n");
	printf("\n\t\t\tTecihiniz: ");
	scanf("%d",&tercih);

	switch(tercih){
		case 1: system("CLS");
		        printf("\n NEWTON-RAPHSON METODU\n\n");	
				int n1;
				printf("\n Fonksiyon kacinci dereceden? ");
				scanf("%d",&n1);
			
				
				float A1[50];
			 	for(int i=0;i<=n1;i++){
			 	 	printf(" x^%d nin katsayisini giriniz: ",n1-i);
			  		scanf("%f",&A1[i]);
			
			    }
			    printf("\n\n f(x) = ");
			    for(int j=n1;j>0;j--){
			   		printf("%.3fx^%d + ",A1[n1-j],j);
			
			    }	
			    printf("%.3f\n",A1[n1]);
			 	float x1,e1;
				printf(" Baslangic kokunu giriniz: ");
			 	scanf("%f",&x1);
				printf(" epsilon degerini giriniz: ");
			 	scanf("%f",&e1);
			 	while(fabs(f(x1,n1,A1))>e1){
			 		x1=x1-(f(x1,n1,A1)/df(x1,n1,A1));
				 }
				printf(" Denklemin koku= %f",x1); 
				getch();anamenu();
	    break;
		case 2: 
		  	 	system("CLS"); 
		  	 	printf("\n BISECTION METODU\n\n");
		        int n;
				printf(" Fonksiyon kacinci dereceden? ");
				scanf("%d",&n);
			
				
				float A[50];
			 	for(int i=0;i<=n;i++){
			 	 	printf(" x^%d nin katsayiyisini giriniz: ",n-i);
			  		scanf("%f",&A[i]);
			
			    }
			    printf("\n\n f(x) = ");
			    for(int j=n;j>0;j--){
			   		printf("%.3fx^%d + ",A[n-j],j);
			
			    }	
			    printf("%f\n",A[n]);
			   	
				float x,y,z,e,l;
				printf(" Fonksiyonu negatif yapan degeri giriniz: ");
				scanf("%f",&x);
				printf(" Fonksiyonu pozitif yapan degeri giriniz: ");
				scanf("%f",&y);
				printf(" Epsilon degerini giriniz: ");
				scanf("%f",&e);
			     
				for(int i=0;i<1000;i++){
					z=(x+y)/2;
					if (fabs(f(z,n,A)-l)<e)break;
					if(f(z,n,A)<0) x=z;
					if (f(z,n,A)>0)y=z;
					//printf("\n\n x: %.5f\n f(x)=%.5f\nf(x)-f(xb)=%f",z,f(z,n,A),fabs(f(z,n,A)-l));
					l=f(z,n,A);
					}
					//printf("\n\n x: %.5f\n f(x)=%.5f\nf(x)-f(xb)=%f",z,f(z,n,A),fabs(f(z,n,A)-l));
             		printf(" Denklemin koku= %.5f",z);
					getch();
             		anamenu();
		
		break;
		case 3:system("CLS");
		        printf("\n GRAFIK METODU\n\n");
			    int n2;
				printf(" Fonksiyon kacinci dereceden? ");
				scanf("%d",&n2);
			
				
				float A2[50];
			 	for(int i=0;i<=n2;i++){
			 	 	printf(" x^%d nin katsayiyisini giriniz: ",n2-i);
			  		scanf("%f",&A2[i]);
			
			    }
			    printf("\n\n f(x) = ");
			    for(int j=n2;j>0;j--){
			   		printf("%.3fx^%d + ",A2[n2-j],j);
			
			    }	
			    printf("%f\n",A2[n2]);
			   	
				float b,dx,e2;
				printf(" Baslangic degerini giriniz: ");
				scanf("%f",&b);
				printf(" Delta x degerini giriniz: ");
				scanf("%f",&dx);
				printf(" Epsilon degerini giriniz: ");
				scanf("%f",&e2);
				
				while(fabs(dx)>e2){
					
					if (f(b,n2,A2)*f(b+dx,n2,A2)<0) dx=dx/2;
					else b=b+dx;
				}
			     printf(" Denklemin koku= %.5f",b); getch();anamenu(); break;
		
		case 4:  system("CLS"); 
			    printf("\n REGULA-FALSE METODU\n\n");
                int n3;
				printf(" Fonksiyon kacinci dereceden? ");
				scanf("%d",&n3);
			
				
				float A3[50];
			 	for(int i=0;i<=n3;i++){
			 	 	printf(" x^%d nin katsayiyisini giriniz: ",n3-i);
			  		scanf("%f",&A3[i]);
			
			    }
			    printf("\n\n f(x) = ");
			    for(int j=n3;j>0;j--){
			   		printf("%.3fx^%d + ",A3[n3-j],j);
			
			    }	
			    printf("%f\n",A3[n3]);
			   	
				float x3,y3,z3,e3,l3;
				printf(" Fonksiyonu negatif yapan degeri giriniz: ");
				scanf("%f",&x3);
				printf(" Fonksiyonu pozitif yapan degeri giriniz: ");
				scanf("%f",&y3);
				printf(" Epsilon degerini giriniz: ");
				scanf("%f",&e3);
			     
			     while(fabs(f(z3,n3,A3)-l3)>e3){
			     	l3=f(z3,n3,A3);
			     	z3=((f(x3,n3,A3)*y3)-(f(y3,n3,A3)*x3))/(f(x3,n3,A3)-f(y3,n3,A3));
			     	if(f(z3,n3,A3)<0)x3=z3;
			     	else y3=z3;
				 }
				 printf(" Denklemin koku= %f",z3);getch();anamenu();break;
		
		case 5:  anamenu(); break;
		
		default: printf("\n Hatali giris!\n");break;
	}
	}


float f(float x,int n,float *a){
 	float k,top=0;
	for(int i=0;i<=n;i++){
		k=a[i]*pow(x,n-i);
		top = top +k;
		
	}
 
 	return top;
}
	float df(float x,int n,float *z){
		float k,top=0;
		for(int i=0;i<n;i++){
			k=(n-i)*z[i]*pow(x,n-i-1);
			top=top+k;
		}
		return top;
	}
	void matrisinvers(float a[][50],float b[][50],int n){
	float d,c;
	for (int i=0;i<n;i++){
	    d=a[i][i];
 		for(int j=0;j<n;j++){
 			
			 	b[i][j]=b[i][j]/d;
				a[i][j]=a[i][j]/d;	
		                    }	
					 
			for (int k=0;k<n;k++){
 					 if(k!=i){
						 	c=	a[k][i];		  
			 		for(int l=0;l<n;l++){
   		 			 	
 
							b[k][l]=b[k][l] -(b[i][l]*c);
							a[k][l]=a[k][l]-(a[i][l]*c);
					                    }
							
						
							 }  }
					    }
							 
 	                                            	}  
 	                                            	
void gauss_jordan(float matris[30][30],int n){
	float d,c;
	for (int i=0;i<n;i++){
	    d=matris[i][i];
 		for(int j=0;j<=n;j++){
				
				matris[i][j]=matris[i][j]/d;	
        }	
					 
			for (int k=0;k<n;k++){
 					 if(k!=i){
						 	c=	matris[k][i];		  
			 				for(int l=0;l<=n;l++){
   		 			 		matris[k][l]=matris[k][l]-(matris[i][l]*c);
					        
							}
							
						
					 }
		    }
	}
 		
   }   
