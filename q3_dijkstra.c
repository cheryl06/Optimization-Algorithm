
#include<stdio.h>
#include<stdlib.h>
#define x 0
#define FALSE 0
#define infinity 99
#define TRUE 1
#define z 1
#define maximum 1000

struct Point
{
	int prev, status, distance; 
};

int **Matrix, array[maximum], array2[maximum];
int valid, n, count2, i, j, cnt, temp  ;

void main()
{
	
	int src,destination, shortDistance;
	
	genrateGraph();
	
	printf("\n\t adjacency  matrix Output \n");
	display();
	
	temp = (n*(n-1))/2; //maximum no of elements in one dimensional array
	
	while(TRUE)
	{
		valid = 0 ;
		while (valid == FALSE) {
			printf("\n\t Enter source Vertex('0' to quit)  \n\t");
			scanf("%d",&src); // input taken from source vertex
			
			if(src < 0 || src > n)
			{
				valid = FALSE ;
			}
			else{
				valid = TRUE;
			}
		} 		
		valid = 0 ;
		
		while (valid == FALSE) {
			printf("\n\t Enter destination vertx('0' to quit)  \n\t");
			scanf("%d",&destination); //input taken from destination vertex 	
	 		
			if(destination < 0 || destination > temp) //Maximum no of elements of one dimensional array
				valid = FALSE ;
			else
				valid = TRUE;
		}	

		if(src==0 && destination==0)
			exit(1);

			
		cnt = calculate(src,destination,array,&shortDistance);
		
			
		if(shortDistance!=0)
		{
			printf("\n\t Shortest distance from %d to %d  =  %d \n", src, destination, shortDistance);
			printf("\n\t PATH : ");
			for(i=cnt;i>1;i--)
			   printf("%d => ",array[i]);
			printf("%d",array[i]);
			printf("   \n");
		}
		else
			printf("\n\t path is not available form %d to %d :\t", src, destination);
		
			
	}  
}


int calculate(int s,int d,int array[maximum],int *sdist)
{
	struct Point ste[maximum];
	int i,min,cnt=0;
	int crnt,ndist,u,v;
	
	*sdist=0;
        //temporary nodes
	 for(i=1;i<=n;i++)
	{
		ste[i].prev=0;
		ste[i].distance = infinity;
		ste[i].status = x;
	}
      
       //fixed source node
	ste[s].prev=0;
	ste[s].distance = 0;
	ste[s].status = z;
	
        //source from destination
	crnt=s;
	while(crnt!=d)
	{
	for(i=1;i<=n;i++)
		{
			if ( Matrix[crnt][i] > 0 && ste[i].status == x )
			{
				ndist=ste[crnt].distance + Matrix[crnt][i];
				
				if( ndist < ste[i].distance )
				{
					ste[i].prev = crnt;
					ste[i].distance = ndist;
				}
			}
		}
		//set current node with minimum distance
		min=infinity;
		crnt=0;
		for(i=1;i<=n;i++)
		{
			if(ste[i].status == x && ste[i].distance < min)
			{
				min = ste[i].distance;
				crnt=i;
			}
		}

		if(crnt==0) 
			return 0;
		ste[crnt].status=z;
	}

	while( crnt!=0 )
	{
		cnt++;
		array[cnt]=crnt;
		crnt=ste[crnt].prev;
	}

	for(i=cnt;i>1;i--)
	{
		u=array[i];
		v=array[i-1];
		*sdist+= Matrix[u][v];
	}
	return (cnt);
}

display()
{
	int i,j;
	//Printing the matrix 
	for(i=1;i<=n;i++)
	{
		printf("\t");
		for(j=1;j<=n;j++)
			printf("%d ", Matrix[i][j]);
		printf("\n");
	}

	
	printf("\n");
	printf("\n\t Lower Diagonal elements array : \n\t");
	
	count2 = 0;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<i;j++)
		{
			array2[count2] = Matrix[i][j];
			printf("%d ", array2[count2]);
			count2++;
		}
	}
	printf("\n\n");
	
}

genrateGraph()
{
        //Variables of Graph declare	
	int i; 
	int edges;
	int a, b, c;

        printf("\n\t Enter number of Node in Graph :   ");
	scanf("%d", &n);
	edges=n*(n-1);
        Matrix = (int **)malloc(n * sizeof (int ));  //allocate memory to matrix row and column 
	for(i = 1; i <= n; i++) {
        Matrix[i] = (int *)malloc(n * sizeof(int));
    }
   
    //define matrix using random values generated through FUNCTION rand()
    for(i = 1; i <= n; i++) 
	{
		int j;
        for(j = 1; j <= n; j++) 
		{
		
	 //used rand function to get random values 
            if ((rand() % 2) && (i != j)) 
			{
				Matrix[i][j] = rand() % 50;    //take random value
				Matrix[j][i] = Matrix[i][j]; //All the diagonal value is 0
			
			} else {
			    Matrix[i][j] = 0; 

            } 

        }
    }
	
}


