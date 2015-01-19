#include<stdio.h>
#include<stdlib.h>
#define maximum 1000
#define infinity 99 

int flag1, flag2;
int array[maximum], path[1000][1000], spath[1000]; //defined an adjacency matrix called path and a array to store the shortest path(spath)
int src, dest ;

//Generating an adjacent matrix
void matrix(int mat[100][100],int n)
{ 

int i,j;
for(i = 0;i < n; i++)
{
	for(j = 0;j <= n; j++)
	{
		mat[i][j] = 0;
	}
 
}
 
// Using rand function to create random variables from 1 to 50
for(i = 1; i < n; i++)
{
	for(j=0;j<i;j++)
	{
		mat[i][j] = mat[j][i] = rand()%50;
	}
}
}
  
 // defined a function shortest to calculate the shortest path
int shortest(int x, int y){
 
if(x < y){
	return x;
}
else{
	return y;
}
}

// Floyd’s algorithm is used below 
void functionFloyd(int arr[100][100],int num, int src, int dest)
{
	int i,j,k, x;
    for (i = 0; i < num; i++)  
{
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
					printf("XX %d \n", k) ;
							if (i == src && j == dest) {
								spath[x] = k ;		
								x++ ;
							}
							else {
								
							}
						
				}
			}
		}
	}
}

	
}// End of Floyd’s function

 
 int main()
{
int mat[100][100];
int n,i,j;
 
 
printf("\n\tEnter node in Graph  \n\t"); 
scanf("%d",&n);
 
matrix(mat,n);
 
printf("\t adjacent matrix \n”);// Printing the adjacent matrix 


for(i = 0;i < n; i++)
{
	for(j = 0;j < n; j++)
	{
		printf("\t%d",mat[i][j]);
		if(mat[i][j] != 0)
		{

		}
	}
printf("\n");
}

	printf("\n\t Enter Source and Destination  \n\t");
	scanf("%d %d", &src, &dest);

 
functionFloyd(mat,n, src, dest);
 
printf("\n\t Floyd's Matrix \n"); //Printing the Floyd’s matrix

flag1 = 0;

// Calculating the one dimensional array and printing the values
for(i = 0;i < n; i++)
{
	for(j = 0;j < n; j++)
	{
		printf("\t%d",mat[i][j]);
	}
	printf("\n");
}

printf("\n\t One dimension array of Matrix \n");
	
        flag1 = 0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<i;j++)
		{
			array[flag1] = mat[i][j];
			printf("\t%d", array[flag1]);
			flag1++;
		}
	}
	printf("\n");
	
// Calculating the node distance and printing the value
	for(i = 0;i < n; i++)
 {
	if (i == src ) {
		printf("\n\tNode      Distance \n");
		for(j = 0;j < n; j++)
			if (i == src && j == dest)
				//printf("\t%d",arr[i][j]);
				printf(" \t %d \t\t %d\n",j, mat[i][j]) ;				
		}
	}

	printf("\n") ;

//Calculating the shortest path and printing the value
	printf("\tPATH %d \t", src) ;
	for (i = 0; i < n ; i++) {
		if (spath[i] != -1 )
		printf("%d ", spath[i]) ;
		}
	      printf("\t%d \t", dest) ;

return 0;
}