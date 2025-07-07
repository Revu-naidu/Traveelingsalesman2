#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#include<string.h>

int** array;
int checkdistance(int **arr, int *impath, int n);
void tsp_greedy(int **array, int n,int distribution_points, int efficpoints,float beta,double limit_distance,int range_of_distributionpoints);
void printpath(int path[], int n);
void twoopt(int **array, int *impath, int n);
void reverse1(int *impath, int i, int j);
void thhreeopt(int **array, int *impath, int n);
void optimizeswap(int **array,int *impath,int n,int depo);
void randomswap(int **array,int *path,int n,int depo);
void swap(int*a, int *b);
void itojswap(int **array, int *path, int n, int depo);
void gredy(int **array, int *path, int n, int depo,int greedytotaldistance);

int **malloc2D(int n) {
    int **ipp;
    ipp = (int**)malloc(n * sizeof(int*));
    if (ipp == NULL) {
        printf("Memory not allocated.\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        ipp[i] = (int*)malloc(n * sizeof(int));
        if (ipp[i] == NULL) {
            printf("Memory not allocated.\n");
            exit(1);
        }
    }
    return ipp;
}

void printArray(int **array, int n) {
    printf("The elements are:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}

void free2DIntArray(int **ipp, int dim) {
    for (int i = 0; i < dim; i++) {
        free(ipp[i]);
    }
    free(ipp);
}

int main(int argc, char *argv[]) {
    FILE *pt;
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }
    
    pt = fopen(argv[1], "r");
    if (pt == NULL) {
        printf("File not opened.\n");
        return 1;
    }

    int n, points, effpoints, range_of_points;
    float beta;
    double limit_distance;
    
    if (fscanf(pt, "%d %d %d %f %lf %d", &n, &points, &effpoints, &beta, &limit_distance, &range_of_points) != 6) {
        printf("Error reading file.\n");
        fclose(pt);
        return 1;
    }
    
    printf("%d %d %d %.1f %lf %d\n", n, points, effpoints, beta, limit_distance, range_of_points);
    
    array = malloc2D(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(pt, "%d", &array[i][j]) != 1) {
                printf("Error reading matrix data.\n");
                fclose(pt);
                free2DIntArray(array, n);
                return 1;
            }
        }
    }
    
    fclose(pt);
    printArray(array, n);
    tsp_greedy(array,n,points, effpoints, beta, limit_distance, range_of_points);
    free2DIntArray(array, n);
    
    return 0;
}
void tsp_greedy(int **array, int n,int distribution_points, int efficpoints,float beta,double limit_distance,int range_of_distributionpoints) 
{
    int **distance_matrix = array;
    int path[n + 1];
    bool visited[n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    path[0] = 0;
    visited[0] = true;
    int count=0;
    int no_of_discenters=n-distribution_points +1;
    int distri_cen_array[n];
    for (int i = 1; i < n; ++i) {
        int curr_node = path[i - 1];
        int min_dis = INT_MAX;
        int nearest_node = -1;
        int local_efficpoints=efficpoints;
        bool temp_visited[n];
        memcpy(temp_visited, visited, sizeof(visited)); 
       
        for (int j = 0; j < n; ++j) {
            if (!visited[j] && distance_matrix[curr_node][j] < min_dis) {
            	if(j>=distribution_points && j<n)
            	{
            	printf("courier points: %d\n",j);
            	printf("near cities: ");
             		for(int k=0;k<n;k++)
             		{
             			if(distance_matrix[j][k]<=range_of_distributionpoints && !temp_visited[k] && local_efficpoints!=0)
             			{
             				temp_visited[k]=true;
             				local_efficpoints--;
             				printf("%d ",k);
             				count++;
             			}
             		}
             		printf("\n");
             	}
                min_dis = distance_matrix[curr_node][j];
                nearest_node = j;
            }
        }
        if(nearest_node!=-1){
        memcpy(visited,temp_visited,sizeof(visited));
        path[i] = nearest_node;
        visited[nearest_node] = true;
        }
        else{
        	for(int j=i;j<n;j++)
        	{
        	path[j]=-1;
        	}
        	break;
        }
        
    }
    path[n] = 0;
    
    printf("The greedy path is\n");
    for (int i = 0; i <= n; ++i) {
        printf(" %d", path[i]);
    }
    printf("\n");
    printf("%d \n",count);
    int f=n-count+1;
    printf("\n %d %d\n",f,n);
    int delevered_path[f+1];
    int index=0;
    for(int i=0;i<n;i++)
    {
    	if(path[i]!=-1)
    	{
    		
		delevered_path[index++]=path[i];
	}
    }
    delevered_path[f]=0;
    printf("The greedy path is\n");
    
    for (int i = 0; i <f; ++i) {
        printf(" %d", delevered_path[i]);
    }
    printf("\n");
    printpath(delevered_path,f);
    

    int greedytotaldistance = checkdistance(array, delevered_path, f);
    printf("\nGreedy TOTAL DISTANCE = %d\n", greedytotaldistance);
    printf("%d",f);
    printf("\n\n\n");
    twoopt(array, delevered_path, f);
    printf("\n");

    int t2opt_totaldistance = checkdistance(array, delevered_path, f);
    printf("\n2-opt TOTAL DISTANCE = %d\n", t2opt_totaldistance);
    printf("\nOptimized 2-opt total path: ");
    printpath(delevered_path, f);
    printf("\n");
    
    /*
    
    thhreeopt(array, delevered_path, f);
    int t3opt_totaldistance = checkdistance(array, delevered_path, f);
    printf("\n3-opt TOTAL DISTANCE = %d\n", t3opt_totaldistance);
    printf("Optimized 3-opt path:\n");
    printpath(delevered_path, f);
    
    
    */
    optimizeswap(array,delevered_path, f,0);
    int optimize_finaldistance=checkdistance(array,delevered_path,f);
    printf("\n optimizeswap total distance =");
    printf(" %d ",optimize_finaldistance);
    printf("\n");
    printpath(delevered_path,f);
    itojswap(array, delevered_path, f, 0);
    int itoj_totaldistance = checkdistance(array, delevered_path, f);
    printf("\nitoj TOTAL DISTANCE = %d\n", itoj_totaldistance);
    printf("Optimized itoj path:\n");
    printpath(delevered_path, f);
    randomswap(array,delevered_path, f,0);
    int random_totaldistance = checkdistance(array, delevered_path, f);
    printf("\nrandom TOTAL DISTANCE = %d\n", random_totaldistance);
    printf("Optimized random path:\n");
    printpath(delevered_path, f);
    //gredy(array, delevered_path,  f, 0, greedytotaldistance);
    }

int checkdistance(int **arr, int *impath, int n) 
{
    int **distance_matrix = arr;
    int totaldistance = 0;
    for (int i = 0; i < n - 1; ++i) {
        totaldistance += distance_matrix[impath[i]][impath[i + 1]];
    }
    totaldistance += distance_matrix[impath[n - 1]][impath[0]];
    return totaldistance;
}
void printpath(int path[], int n) {
    for (int i = 0; i < n; i++) {
        printf(" %d", path[i]);
       
        
    }
}
            	
void twoopt(int **array, int *impath, int n) {
    int **distance_matrix = array;
    bool improved = true;
    while (improved) {
        improved = false;
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                int olddistance = distance_matrix[impath[i]][impath[i + 1]] + distance_matrix[impath[j]][impath[(j + 1) % n]];
                int newdistance = distance_matrix[impath[i]][impath[j]] + distance_matrix[impath[i + 1]][impath[(j + 1) % n]];
                if (newdistance < olddistance) {
                    reverse1(impath, i + 1, j);
                    improved = true;
                }
            }
        }
    }
    
}            	
  void reverse1(int *impath, int i, int j) {
    while (i < j) {
        int temp = impath[i];
        impath[i] = impath[j];
        impath[j] = temp;
        i++;
        j--;
    }
}  
void thhreeopt(int **array, int *impath, int n) {
    int **distance_matrix = array;
    bool improved = true;
    int max_iterations = 1000; // Max iterations to prevent infinite loop
    int iteration_count = 0;

    while (improved && iteration_count < max_iterations) {
        improved = false;

        for (int i = 0; i < n - 2; i++) {
            for (int j = i + 2; j < n - 1; j++) {
                for (int k = j + 2; k < n; k++) {
                    int olddistance = distance_matrix[impath[i]][impath[i + 1]] + distance_matrix[impath[j]][impath[j + 1]] + distance_matrix[impath[k]][impath[(k + 1) % n]];
                    int newdistance1 = distance_matrix[impath[i]][impath[j]] + distance_matrix[impath[i + 1]][impath[k]] + distance_matrix[impath[j + 1]][impath[(k + 1) % n]];
                    int newdistance2 = distance_matrix[impath[i]][impath[k]] + distance_matrix[impath[i + 1]][impath[j]] + distance_matrix[impath[j + 1]][impath[(k + 1) % n]];
                    int newdistance3 = distance_matrix[impath[i]][impath[i + 1]] + distance_matrix[impath[j]][impath[k]] + distance_matrix[impath[j + 1]][impath[(k + 1) % n]];

                    if (newdistance1 < olddistance || newdistance2 < olddistance || newdistance3 < olddistance) {
                        if (newdistance1 < olddistance) {
                            reverse1(impath, i + 1, j);
                            reverse1(impath, j + 1, k);
                        } else if (newdistance2 < olddistance) {
                            reverse1(impath, i + 1, k);
                            reverse1(impath, j + 1, k);
                        } else {
                            reverse1(impath, j + 1, k);
                        }
                        improved = true;
                    }
                }
            }
        }
        iteration_count++;
    }

    if (iteration_count == max_iterations) {
        printf("Maximum iterations reached in 3-opt.\n");
    }
}
void optimizeswap(int **array,int *impath,int n,int depo)
{
    
    int i=1;
   int **distance_matrix=array;
   
	
    //int **path=impath;
    int j=i+1;
    while(impath[i]!=depo && j<n && impath[i] != impath[0]) 
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

}
void randomswap(int **array,int *path,int n,int depo)
{
	int itr=10000;
	int lower=1;
	int upper=n-2;
	srand(time(NULL));
	printf("\n\n\n\n");
	printpath(path, n);
	int old_distance=checkdistance(array,path,n);
	for(int k=1;k<itr;k++)
	{
		int i=(rand()%(upper-lower+1))+1;
		int j=(rand()%(upper-lower+1))+1;
		if(i==j || i==depo||j==depo)
		continue;
		swap(&path[i],&path[j]);
		
		int new_dis=checkdistance(array,path,n);
		if(new_dis<old_distance)
		{
			old_distance=new_dis;
		}
		else
		{
			swap(&path[i],&path[j]);
			
		}
	}
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void itojswap(int **array, int *path, int n, int depo) {
    srand(time(NULL));
    int old_distance = checkdistance(array, path, n);
    bool improved = true;

    while (improved) {
        improved = false;
        for (int i = 1; i < n; ++i) {
            int curr_node = path[i];

            for (int j = 1; j < n; ++j) {
                if (i == j || j == depo) continue;

                swap(&path[i], &path[j]);
                int new_distance = checkdistance(array, path, n);

                if (new_distance < old_distance) {
                    old_distance = new_distance;
                    improved = true;
                } else {
                    swap(&path[i], &path[j]); // Revert swap
                }
            }
        }
    }
}
void gredy(int **array, int *path, int n, int depo,int greedytotaldistance)
{
	int minimum_distance=greedytotaldistance;
	int count=0;
	int best_path[n+1];
	int temp_path[n+1];
	for(int i=0;i<=n;i++)
	{
		best_path[i]=path[i];
	}
	while(count<100)
	{
		twoopt(array, best_path, n);
        	//thhreeopt(array, best_path, n);
        	optimizeswap(array, best_path, n, depo);
        	itojswap(array, best_path, n, depo);
        	randomswap(array, best_path, n, depo);
        	
        	int final_distance=checkdistance(array, path, n);
        	if(final_distance<minimum_distance)
        	{
        		minimum_distance=final_distance;
        		for (int i = 0; i <= n; ++i) {
                		temp_path[i] = best_path[i];
            		}
            		count=0;
            	}
            	else
            	{
            		count++;
            	}
            for (int i = 0; i <= n; ++i) {
            best_path[i] = temp_path[i];
        }
    }

    printf("\nBest optimized path found after 100 iterations:\n");
    printpath(best_path, n);
    printf("Total distance: %d\n",minimum_distance);
    
}
            	
            					
