/**
   ***************
   *UYGAR KOROGLU*
   ***************
   
   input format: maze matrix with 0(wall) and 1(road) s
	input.txt
	1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
	1 0 0 0 0 0 0 0 0 0 1 0 0 0 1 0 0 0 1
	1 0 1 1 1 1 1 1 1 0 1 0 1 0 1 1 1 1 1
	1 0 1 0 1 0 0 0 1 0 1 0 1 0 1 0 0 0 1
	1 0 1 0 1 1 1 0 1 0 1 0 1 1 1 1 1 1 0
	1 0 1 0 1 0 1 0 1 0 0 0 1 0 0 0 0 1 1
	1 0 1 0 1 0 1 0 1 1 1 1 1 0 1 1 1 1 1
	1 0 0 0 1 1 1 0 0 0 0 0 0 0 1 1 1 1 0
	1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Linux
#ifdef Linux
#include <unistd.h>
void Sleep(int s){sleep(s);}
#endif

int **matrix;
int row = 0;
int column;
void readFile(char* fname)
{
	FILE* f = fopen(fname, "r");
	if(!f)
	{
		printf("can not open  %s file.\n", fname);
		exit(1);
	}

	char line[1024];
	while(!feof(f))
	{
		fgets(line, 1024, f);
		row++;
	}
	column = strlen(line)/2+3;
	row += 2;
	fseek(f,0,SEEK_SET);	
	int i , j;
	matrix = (int**)malloc(sizeof(int*)*row);
	if(!matrix)
	{
		printf("memory allocation error.\n");
		exit(1);
	}
	for(i = 0; i < row; i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*column);
		if(!matrix[i])
		{
			printf("memory allocation error.\n");
			exit(1);
		}
	}


	for(i = 0; i < row; i++)
	{
		for(j = 0; j < column; j++)
		{
			if(i != 0 && i!= row-1 && j!=0 && j!= column-1)
				fscanf(f,"%d", &matrix[i][j]);
			else
				matrix[i][j] = 0;
			//printf("%d ", matrix[i][j]);
		}
	//	printf("\n");
	}
}


void printMat()
{
	int i, j;
	//printf("\n MATRIX: \n");
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < column; j++)
		{
			if(i == 1 && j==1)
				printf("*");
			else if(i==row-2 && j==column-2)
				printf("X");
			else if(matrix[i][j] == 1)
				printf(" ");
			else if(matrix[i][j] == 3)
				printf("I");
			else if(matrix[i][j]==0)
				printf("%c",219);
			else
				printf("o");
		}
		printf("\n");
	}
}

void clearStucks()
{
	int i , j;
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			if(matrix[i][j]==2)
				matrix[i][j] = 1;
		}
	}
}
void DFS(int x , int y, int* arrived)
{

	//printf("%d %d \n", x, y);
	matrix[x][y] = 2;
		printMat();
		Sleep(250);
		system("cls");
	if(x == row-2 && y == column-2)
		*arrived = 1;
    if(*arrived == 0 && matrix[x][y+1] == 1)
	{
		DFS(x, y+1, arrived);
	}
	if(*arrived == 0 && matrix[x+1][y] == 1)
	{
		DFS(x+1, y, arrived);
	}
	if(*arrived == 0 && matrix[x][y-1] == 1)
	{
		DFS(x, y-1, arrived);
	}
	if(*arrived == 0 && matrix[x-1][y] == 1)
	{
		DFS(x-1, y, arrived);
	}
	if(*arrived == 1)
		matrix[x][y] = 3;
}

void freeMat()
{
	int i = 0;
	for(i = 0; i < row; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

int main(int argc, char **argv)
{
	readFile("input.txt");
	int arrived = 0;
	DFS(1,1,&arrived);
	printMat();
	system("cls");
	clearStucks();
	printMat();
	freeMat();
	return 0;
}

