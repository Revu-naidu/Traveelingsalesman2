#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include <limits.h>
int **array;
void tsp_greedy(int **array,int n);
void twoopt(int **array,int *impath,int n);
void printpath(int path[],int n);
int checkdistance(int **arr,int *impath,int n);
void optiswap(int **array,int *impath,int n,int depo);
int **mallocintarray(int n)
{
	int **ipp;
	ipp=(int**)malloc(n*sizeof(int*));
	if(ipp==NULL)
	{
		printf("not allocated memory");
		exit(1);
	}
	for(int i=0;i<n;i++)
	{
	ipp[i]=(int*)malloc(n*sizeof(int));
	}
	return ipp;
}
void printarray(int **array,int n)
{
	printf("the elements are\n");
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			printf("%d ",array[i][j]);
		}
		printf("\n");
	}
}
void free2dintarray(int ** ipp,int dim)
{
	for(int i=0;i<dim;i++)
	{
	free(ipp[i]);
	}
	free(ipp);
}
int main(int argc,char *argv[])
{
	FILE *pt;
	if(argc!=2)
	{
	printf("usage: %s filename\n",argv[0]);
	return 1;
	}
	pt=fopen(argv[1],"r");
	if(pt==NULL)
	{
	printf("file not opened");
	}int n;
	fscanf(pt,"%d",&n);
	printf("%d",n);
	array=mallocintarray(n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			fscanf(pt,"%d\t",&array[i][j]);
		}
	}
	fclose(pt);
	printarray(array,n);
	tsp_greedy(array,n);
	free2dintarray(array,n);
	return 0;
}

void tsp_greedy(int **array,int n)
{
	int **distance_matrix=array;
	int path[n+1];
    bool visited[n];
    for(int i=0;i<=n;i++)
    {
        visited[i]=false;
    }
    path[0]=0;
    visited[0]=true;
    for(int i=1;i<n;++i)
    {
        int curr_node=path[i-1];
        int min_dis=INT_MAX;
        int nearest_node=-1;
        for(int j=0;j<n;++j)
        {
            if(!visited[j]&&distance_matrix[curr_node][j]<min_dis)
            {
                min_dis=distance_matrix[curr_node][j];
                nearest_node=j;
            }
        }
        path[i]=nearest_node;
        visited[nearest_node]=true;
    }
    path[n]=0;
    
    printf("okokokok\n");
    for(int i=0;i<=n;++i)
    {
        printf(" %d",path[i]);
    }
    printf("\n");/*
    int totaldistance=0;
    for(int i=0;i<n;++i)
    {
    totaldistance=totaldistance+distance_matrix[path[i]][path[i+1]];
    }*/
    int greedytotaldistance=checkdistance(array,path,n);
    printf("\ngreedyTOTAL DISTANCE =%d",greedytotaldistance);
	twoopt(array,path,n);
	printf("\n");
	/*
	totaldistance=0;
    for(int i=0;i<n;++i)
    {
    totaldistance=totaldistance+distance_matrix[path[i]][path[i+1]];
    }*/
    int t2opt_totaldistance=checkdistance(array,path,n);
    printf("\n2opt TOTAL DISTANCE =%d",t2opt_totaldistance);
    printf("\n optimized 2opt total path ");
    printpath(path,n);
    //printf("\n2 optTOTAL DISTANCE =%d",totaldistance);
    optiswap(array,path,n,0);
}
void twoopt(int **array,int *impath,int n)
{
	int **distance_matrix=array;
	bool improved=true;
	while(improved)
	{
		improved=false;
		for(int i=0;i<n;i++)
		{
			for(int j=i+2;j<n;j++)
			{
				int olddistance =distance_matrix[impath[i]][impath[i+1]]+distance_matrix[impath[j]][impath[j+1]];
				int newdistance =distance_matrix[impath[i]][impath[j]]+distance_matrix[impath[i+1]][impath[j+1]];
				if(newdistance<olddistance)
				{
					int temp=impath[i+1];
					impath[i+1]=impath[j];
					impath[j]=temp;
					improved=true;
				}


			}
		}
	}
	//impath[n]=0;
	
}
void printpath(int path[],int n)
{
for(int i=0;i<=n;i++)
{
printf(" %d ",path[i]);
}
}
int checkdistance(int **arr,int *impath,int n)
{
int **distance_matrix=arr;
    int totaldistance=0;
    for(int i=0;i<n;++i)
    {
        totaldistance=totaldistance+distance_matrix[impath[i]][impath[i+1]];
    }
    return totaldistance;
}
void optiswap(int **array,int *impath,int n,int depo)
{
    /*int depo;
    int i=0;
    scanf("%d",&depo);*/
    /*
    int i=1;
    int **distance_matrix=array;
    if(impath[i]==depo)
    {
    i++;
        return;
    }
    int olddistance=checkdistance(distance_matrix,impath,n);
    for(int i=depo;i<n;++i)
    {
    int temp=impath[i+1];
    impath[i+1]=impath[(i+2)%n];
    impath[(i+2)%n]=temp;
    int newdistance=checkdistance(distance_matrix,impath,n);
    if(newdistance<olddistance)
    {
        optiswap(array,impath,n,depo);
        break;
    }
    else{
         temp=impath[i+1];
        impath[i+1]=impath[(i+2)%n];
        impath[(i+2)%n]=temp;
    }
    }
    int finaldistance=checkdistance(distance_matrix,impath,n);
    printf("\n swap total distance =");
    printf(" %d ",finaldistance);
    printf("\n");
    printpath(impath,n);*/
    int **distance_matrix=array;
    int i=1;
	
    //int **path=impath;/*
    int j=i+1;
    while(impath[i]!=depo && j<n)
    {
    	int olddistance=checkdistance(distance_matrix,impath,n);
    	//printf("\n\n%d ",olddistance);
	int temp=impath[i];
	impath[i]=impath[j];
	impath[j]=temp;
	int newdistance=checkdistance(distance_matrix,impath,n);
    if(newdistance < olddistance)
    {
        i=i+1;
        if(i==j)j++;
    }
    else{
        temp=impath[i];
	impath[i]=impath[j];
	impath[j]=temp;
	j++;
	if(j==n)
	{
		i++;
		j=i+1;
	}
    }
    }
    int finaldistance=checkdistance(distance_matrix,impath,n);
    printf("\n swap total distance =");
    printf(" %d ",finaldistance);
    printf("\n");
    printpath(impath,n);
    
	

}/*
void randominsert(int **array,int *path,int n)
{
bool visited[n];
int **distance_matrix=array;
for(int i=0;i<=n;i++)
{
visited[i]=false;
}
visited[0]=true;
srand(time(NULL));
int i=rand()%n;
if(!visited[j])
{
int j=rand()%n;
if(i!=j)
{
int temp=
*/
