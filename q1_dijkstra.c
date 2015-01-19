#include<stdio.h>
#include<stdlib.h>
#define true 1
#define FALSE 0
#define x 0
#define z 1
#define max 1000      // defined maximum value as 1000
#define infinity 99   //defined infinity value as 99


//defined a structure to declare variables to check the status , previous node and the distance.
struct Point
{
	int status, prev, distance;
};



// defined a pointer **Matrix and an array of size 1000
int n, **Matrix, valid, array[max];



void main()
{

     //defined variables shortDistance to find the shortest distance, cnt is the count, src is the source and i and j are the vertices of the matrix.
	
      int shortDistance, cnt, src, i, j, destination; 
	
     // defined a function in order to create the graph after inputing the number of nodes of the graph
       generateGraph();
	
	    printf("\n\t adjacency matrix Output \n");

      // Display function is defined to to display the graph and the shortest path 	
	display();
	
	while(true)
	{
		valid = 0 ;
		while (valid == FALSE) {
			printf("\n\t  Enter source Vertex('0' to quit)  \n\t");
             
            // Input is taken from the source vertex
			scanf("%d",&src);  
			
			if(src < 0 || src > n)
			{
				valid = FALSE ;
			}
			else{
				valid = true;
			}
		} 		
		
		valid = 0 ;
		while (valid == FALSE) {
			printf("\n\t Enter destination vertx('0' to quit)  \n\t");
                 
                    // Input is taken from the destination vertex.

			scanf("%d",&destination);	
			
			if(destination < 0 || destination > n)
				valid = FALSE ;
			else
				valid = true;
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

generateGraph()
{
	// Variables of Graph are  declare
	int i; 
	int edges;
	int a, b, c;

	printf("\n\t Enter number of Node in Graph :   ");
	scanf("%d", &n);
	edges=n*(n-1);
	
	// allocating  memory to matrix row and column
    Matrix = (int **)malloc(n * sizeof (int ));   
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
				Matrix[i][j] = rand() % 50;     // random value from 1 to 50
				Matrix[j][i] = Matrix[i][j];
			
			} else {
			    Matrix[i][j] = 0;                  // Diagonal values will be zero 

            } 

        }
    }
	
}

display()
{
	int i,j;
	for(i=1;i<=n;i++)
	{
		printf("\t");
		for(j=1;j<=n;j++)
			printf("%d ", Matrix[i][j]);
		printf("\n");
	}

}

int calculate(int s,int d,int array[max],int *sdist)
{
	struct Point ste[max];
	int i,min,cnt=0;
	int crnt,ndist,u,v;  //declared variables to calculate the distance
	
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

		//set the current node with minimum distance
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
	return (cnt);// returning the count value to get the distance
}

