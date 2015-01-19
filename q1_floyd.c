
#include<stdio.h>
#include<stdlib.h>
#define maximum 100
int path[100][100] ;// defined a adjacency matrix of the order 100 x 100
int spath[100] ;// array is defined to store the shortest path
 
//Floyd algorithm is defined below
void functionFloyd(int arr[100][100],int num, int src, int destination)// declared variables to  find the source and destination
{
 
	int i,j,k, x;

    for (i = 0; i < num; i++)  {
		for (j = 0; j < num ; j++)  {
			path[i][j] = -1;		
		}
	}

    for (i = 0; i < num; i++)  {
		spath[i] = -1;		
	}

	x = 0 ;
	for(k = 0;k < num ; k++)
	{
		for(i = 0;i < num; i++)
		{
		for(j = 0;j < num ; j++)
		{
			if ((arr[i][k] + arr[k][j]) < 	arr[i][j]) {		
				arr[i][j] =  arr[i][k] + arr[k][j] ;
				if (i != j)  {
					path[i][j] = k;
					if (i == src && j == destination) {
						spath[x] = k ;					
						x++ ;
					}
					
				}
			}
		}
	}
}
 
} // end of function Floyd
 
 
 
int shortest(int x, int y){
 
	if(x < y){
		return x;
	}
	else{
		return y;
	}
} // end of function shortest

void matrix(int arr[100][100], int num)
{
 
	int i,j;
	for(i = 0;i < num; i++)//defining a matrix having initial value 0.
	{
		for(j = 0;j <= num; j++)
		{
		arr[i][j] = 0;
		}
	 
	}
 
for(i = 1; i < num; i++)// matrix is defined using rand function
{
	for(j=0;j<i;j++)
	{
		arr[i][j] = arr[j][i] = rand()%50;// rand function is used to create random values from 1 to 50.
	}
}
}
 
 
int main()
{
int arr[100][100];
int num,i,j, src, destination ;

printf("\n\t Enter nodes in graph  \n\t");
scanf("%d",&num);

matrix(arr,num);
printf("\t  adjacent matrix  \n"); // generating an adjacency matrix by asking the number of nodes to the user.

for(i = 0;i < num; i++)
{
	for(j = 0;j < num; j++)
	{
		printf("\t%d",arr[i][j]);
		if(arr[i][j] != 0)
	{

	}
}
printf("\n");
}

printf("\n\t Enter source node  \n\t");// asking the user a source node to calculate the shortest path
scanf("%d",&src);

if ((src >= num) || src < 0) {
	printf("Source node must be greater than 0 and less than %i " , num) ;// Source should be less than the destination
	return 0;
	
}
printf("\n\t Enter destination node \n\t”); //asking the user a source node to calculate shortest path
scanf("%d",&destination);
if ((destination >= num) || destination < 0) {
	printf("Source node must be greater than 0 and less than %i " , num) ;// Destination should be greater than source
	return 0;
}

functionFloyd(arr,num, src,destination);


	for(i = 0;i < num; i++) {
	if (i == src ) {
		printf("\n\tNode      Distance \n"); // printing the distance between the source node and destination node
		for(j = 0;j < num; j++)
			if (i == src && j == destination)
				
				printf(" \t %d \t\t %d\n",j, arr[i][j]) ;				
		}
	}

	printf("\n") ;

	printf("\tPATH %d \t", src) ;
	for (i = 0; i < num ; i++) 
{
	  if (spath[i] != -1 )
	  printf("%d ", spath[i]) ; // printing the shortest path for the distance calculated
	}

	printf("%d", destination) ;
	printf("\n") ;
	
return 0;
}