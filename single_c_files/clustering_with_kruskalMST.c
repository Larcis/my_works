
/**
	input format: number of vertex in first line, then the adjacency matrix
	input.txt
	20
	1,7,0,8,0,0,0,10,0,0,0,0,0,10,0,1,0,0,0,10
	7,1,8,6,1,10,0,8,0,7,0,0,9,0,9,0,0,0,2,0
	0,8,1,0,0,2,0,0,0,0,2,0,0,0,10,7,10,9,0,0
	8,6,0,1,10,0,7,0,0,0,10,0,0,0,0,0,8,0,0,0
	0,1,0,10,1,0,0,10,0,4,9,6,0,1,0,0,9,0,0,0
	0,10,2,0,0,1,0,8,0,10,1,0,0,0,0,8,0,8,7,0
	0,0,0,7,0,0,1,0,5,0,1,0,0,0,9,0,0,0,0,8
	10,8,0,0,10,8,0,1,0,0,9,10,2,0,0,9,1,0,0,4
	0,0,0,0,0,0,5,0,1,0,0,0,0,0,0,3,0,0,8,0
	0,7,0,0,4,10,0,0,0,1,7,0,0,9,0,0,8,2,0,0
	0,0,2,10,9,1,1,9,0,7,1,0,0,8,0,0,0,0,7,0
	0,0,0,0,6,0,0,10,0,0,0,1,0,10,7,0,1,0,0,0
	0,9,0,0,0,0,0,2,0,0,0,0,1,9,0,0,0,0,0,0
	10,0,0,0,1,0,0,0,0,9,8,10,9,1,0,0,0,7,10,0
	0,9,10,0,0,0,9,0,0,0,0,7,0,0,1,10,0,9,0,0
	1,0,7,0,0,8,0,9,3,0,0,0,0,0,10,1,0,9,10,0
	0,0,10,8,9,0,0,1,0,8,0,1,0,0,0,0,1,0,9,5
	0,0,9,0,0,8,0,0,0,2,0,0,0,7,9,9,0,1,0,0
	0,2,0,0,0,7,0,0,8,0,7,0,0,10,0,10,9,0,1,8
	10,0,0,0,0,0,8,4,0,0,0,0,0,0,0,0,5,0,8,1
**/
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int v1;
	int v2;
	int val;
}edge;

edge *sortedEdge;//sorted edge list
int  *wcluster;//node member of which cluster
int   n;//# vertex
void readFile(char* fname)
{
	FILE* f = fopen(fname, "r");
	if(!f)
	{
		printf("an error occur while trying open the file.\n");
		exit(1);
	}
	int i, j;
	fscanf(f,"%d", &n);
	sortedEdge = (edge*)malloc(sizeof(edge)*n*n/2);
	//clean garbage values from sortedEdge
	for(i = 0; i < n*n/2;i++)
	{
		sortedEdge[i].v1 = -1;
		sortedEdge[i].v2 = -1;
		sortedEdge[i].val = INT_MAX;
	}
	//read all matrix
	for(i = 0; i < n; i++)
	{
		for(j = 0;  j < n; j++)
		{
			int val;
			fscanf(f,"%d,",&val);
			if(j > i && val != 0)//just consider up triangle of matrix and connected edges
			{
				//insertion sort
				//find place of value 
				int k = 0;
				while(sortedEdge[k].val < val) k++;
				//shift array
				int t;
				for(t = n*n/2-1; t > k; t--)
				{
					sortedEdge[t].v1 = sortedEdge[t-1].v1;
					sortedEdge[t].v2 = sortedEdge[t-1].v2;
					sortedEdge[t].val = sortedEdge[t-1].val;
				}
				//add value to array
				sortedEdge[k].v1 = i;
				sortedEdge[k].v2 = j;
				sortedEdge[k].val = val;
			}
		}
	}
}
int* initializeLabelArray()
{
	int i;
	int *label = (int*)malloc(sizeof(int)*n);
	if(!label)
	{
		printf("memory allocation error.\n");
		exit(1);
	}
	for(i = 0; i < n; i++)
		label[i] = 0;
	return label;	
}
//this function creates cluster array from label array
void labelToClusters(int* label, int n)
{
	int i, j, x, cnt=0;
	wcluster = (int*)malloc(sizeof(int)*n);
	if(!wcluster)
	{
		printf("memory allocation error.\n");
		exit(1);
	}
	for(j = 0; j < n; j++)
	{
		if(label[j] != -1)
		{
			x = label[j];
			cnt++;
			for(i = 0; i < n; i++)
			{
				if(label[i] == x)
				{
					wcluster[i] = cnt-1;
					label[i] = -1;
				}
			}
		}
	}
}

void printClusters(int  clusterCount)
{
	int i, j;
	for(i = 0; i < clusterCount; i++)
	{
		printf("%d. cluster: { ", i);
		for(j = 0; j < n; j++)
		{
			if(wcluster[j] == i)
			{
				printf("%d ", j);
			}
		}
		printf("}\n");
	}
}
//this function clusters the data set
void Cluster(int *label, int K)
{
	int i = 0, labelcnt = 0;
	int unLabeled = n; //# unlabeled nodes
	int nofSubtrees = 0;//# sub trees(clusters)
	while( (nofSubtrees + unLabeled) != K && sortedEdge[i].v1 != -1  )
	{
		//current smallest edge's vertexes 
		int u = sortedEdge[i].v1;
		int v = sortedEdge[i].v2;
		if((label[u]+label[v]) == 0)
		{
			labelcnt++;
			label[u] = label[v] = labelcnt;
			unLabeled-=2;
			nofSubtrees++;
		}
		else
		{

			if(label[u] == 0)
			{
				label[u] = label[v];
				unLabeled--;
			}
			else if(label[v] == 0)
			{
				label[v] = label[u];
				unLabeled--;
			}
			else
			{
				if(label[u] != label[v] && K < nofSubtrees)
				{
					int a;
					int ch = label[v];
					for(a = 0; a < n; a++)
						if(label[a] == ch)
							label[a] = label[u];		
					nofSubtrees--;
				}
			}
		}
		i++;
	}
	
	for(i = 0; i < n; i++)
	{
		if(label[i] == 0)
		{
			labelcnt++;
			label[i] = labelcnt;
		}
	}
	//printf("# subtrees: %d\n", nofSubtrees);
	//printf("# unlabeled: %d\n", unLabeled);
} 

void findMinDist(int c1, int c2)
{
	int flag = 1;
	int i = 0;
	while(flag && sortedEdge[i].v1 != -1)
	{
		if(wcluster[sortedEdge[i].v1] == c1 && wcluster[sortedEdge[i].v2] == c2 )
			flag = 0;
		if(wcluster[sortedEdge[i].v1] == c2 && wcluster[sortedEdge[i].v2] == c1)
			flag = 0;
		i++;		
	}
	if(!flag)
	{
		printf("  minimum distance between %d. cluster and %d. cluster is %d.",c1,c2,sortedEdge[i-1].val);
		printf(" And it's between %d. and %d. vertex.\n", sortedEdge[i-1].v1, sortedEdge[i-1].v2);
	}
	else
	{
			printf("  there isn't connection between %d. cluster and %d. cluster.\n",c1,c2);
	}
}
int main(int argc, char **argv)
{
	int i;
	int K;//# clusters
	readFile("input.txt");
	do{
		printf("enter wanted number of cluster: ");
		scanf("%d", &K);
		if(K < 1 || K > n)
			printf("number of clusters must be bigger than 0 and smaller then the number of vertexes. \n"); 
	}while(K < 1 || K > n);

	/*for(i = 0; sortedEdge[i].v1 != -1; i++)
		printf(" v1: %d v2: %d val: %d \n",sortedEdge[i].v1, sortedEdge[i].v2, sortedEdge[i].val);*/
			
	int *label = initializeLabelArray();
	
	Cluster(label, K);//clustering data set with kruskal ish algorithm
	
	labelToClusters(label, n);//creating wcluster(which cluster) array from label array
	printClusters(K);
	printf("\n Cluster s min dist values: \n");
	int j;
	for(i = 0;i < K; i++)
		for(j = i+1; j < K; j++)
			findMinDist(i,j);
	free(wcluster);
	free(sortedEdge);
	free(label);
	return 0;
}

