#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
#define maxVertices 100
#define  infinity 1000010000

//Declared heap globally so that we do not need to pass it as an argument every time
// Heap used here is Min Heap 

// A structure to represent a node in adjacency list
struct ListNode
{
    int dest;
    int weight;
    struct ListNode* next;
};
 
// Structure to represent an adjacency list
struct AdjacencyList
{   

    // pointer used to point towards the head of the node list
    struct ListNode *head;  

};

struct Graph
{
    int V;
    struct AdjacencyList* array;
};

// A structure to represent a graph with an array of adjacency lists.
// Size of the array will be V 
struct Graph* graph1 ;
int existsArray[10000][10000] ;
int array_dist[1000][1000] ;
int path[1000][1000] ; // defined an adjacency list


int from,to;
int src, edgeCtr, row, col, dest  ;

// A utility function that creates a graph of V vertices
struct Graph* createTheGraph(int V)
{
	int i ;

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjacencyList*) malloc(V * sizeof(struct AdjacencyList));

   // Initialize each adjacency list as empty by making head as NULL
    for ( i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}

// A utility function to create a new adjacency list node
struct ListNode* newAdjListNode(int dest, int weight)
{
    struct ListNode* newNode = (struct ListNode*) malloc(sizeof(struct ListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Adds an edge to an undirected graph
void add_Edge_To_Graph(struct Graph* graph, int src, int dest, int weight)
{

    // Add an edge from source to destination.  
    //A new node is added to the adjacency list of source.  The node is added at the beginning.

    struct ListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

   // Since graph is undirected, add an edge from destination to source 

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// finding distance of intermediate points i,k and k, j
int FindDist_ik_kj(struct Graph *graph, int src, int dest)
{
	struct ListNode* h ;
	h  = graph1->array[src].head ;	
	while (h->next != NULL) {
		if (h->dest == dest)
			return h->weight ;
			h = h->next ;
	}
	if (h->dest == dest) 
	return h->weight ;
 
	return 0 ;	
}

void floydAlgo(struct Graph* graph, int src, int dest) {
	int i, j, k, V ;

	struct ListNode* h ;

	int distik, distkj ;

  //Initializing the solution matrix same as input graph matrix
	
    V = graph->V;// Get the number of vertices in graph
    for (i = 0; i < V; i++)  {
		for (j = 0; j < V ; j++)
  {
			array_dist[i][j] = INT_MAX ;
			path[i][j] = -1;		}
	}

	
    for (i = 0; i < V; i++) {
			h  = graph1->array[i].head ;	
			while (h->next != NULL) {
				k = h->dest ;
				array_dist[i][k] = h->weight;
				h = h->next ;
			}
                        //print the last node
			array_dist[i][h->dest] = h->weight;
			
	}
	
    for (k = 0; k < V; k++)
    {
	// Picking all vertices as source one after another	
        for (i = 0; i < V; i++)
        {
           // Picking all vertices as destination for the above selected source
            for (j = 0; j < V; j++)
            {
				distik = 0 ;
				distkj = 0 ;
				distik =  FindDist_ik_kj(graph, i, k) ;
				distkj =  FindDist_ik_kj(graph, k, j) ;
              
              // If vertex k is on the shortest path from i to j, then update the value of array_dist[i][j]
                if ((distik + distkj) < array_dist[i][j]) 
{
                    array_dist[i][j] = distik + distkj; 
					if (i != j)  {
						path[i][j] = k;
					}
						
				}
			
            }
        }
    }

	
	for (i = 0; i < V ; i++) {
		if (i == src ) {
			printf("\n\tNode      Distance \n");
			for (j = 0; j < V ; j++) {
				if (i == src && j == dest)
					printf("\t %d \t\t %d\n",j, array_dist[i][j]) ;
			}
		}
	}

	printf("\n") ;

	printf("\tPATH %d \t", src) ;
	for (i = 0; i < V ; i++) {
		for (j = 0; j < V ; j++) {
			if (i == src && j == dest) 
				if (path[i][j] != -1 )
					printf("%d\t", path[i][j]) ;
		}
	}
	printf("%d", dest) ;
	
	printf("\n") ;
	
}
			
			
int main()
{	
        int stop, seed  ;
        int graph[maxVertices][maxVertices],size[maxVertices]={0},distance[maxVertices]={0},cost[maxVertices][maxVertices];
        int vertices,edges,weight;
        int iter;
		int i, dontInsertNode, r, c;
		struct ListNode* h ;
		
              /* ask user to enter number of vertices and max value of weight  */
		printf("Enter vertices: \t");
                scanf("%d",&vertices);
              
             //create the graph with input number of vertices
		  graph1 = createTheGraph(vertices);
	
              // random inputs
		for (row = 0; row < vertices ; row++) {
			for (col = 0; col < vertices  ; col++)
 {
					if (row != col) {
						dontInsertNode = 1 ;
						stop = 0 ;
						dontInsertNode = 0 ;

									if ((existsArray[col][row] != 1) && existsArray[row][col] != 1) {
										existsArray[col][row] = 1 ;
										existsArray[row][col] = 1 ;
										dontInsertNode = 0 ;
									}
									else	{
										dontInsertNode = 1 ;
									}
						
						if(!dontInsertNode)  {

							from = row ;
							to = col ;
							weight = 1 + rand() % 30;
							add_Edge_To_Graph(graph1, from, to, weight) ;
						}	
						
					}
					else {
						from = row ;
						to = col ;
					}
			}
		}
		printf("\n");

              //print linked list
		for (i = 0; i < vertices; i++) {
			printf("HeadNode[%d] >>  ", i) ;
			h  = graph1->array[i].head ;	
			while (h->next != NULL) {
				printf("%d (%d) " , h->dest, h->weight) ;
				h = h->next ;
			}
			printf("%d (%d) " , h->dest, h->weight) ;
			
			printf("\n") ;
		}
		printf("\n") ; 
             // loop for all nodes 
		printf("\n\t Enter source node to find shortest path\n\t");
                scanf("%d",&src);
		if ((src >= vertices) || src < 0) {
			printf(" Source node must be greater than 0 and less than %i " , vertices) ;
			return 0;
			
		}
		
		printf("\n\t Enter source node to find shortest path\n\t");
                scanf("%d",&dest);
		if ((dest >= vertices) || dest < 0) {
			printf("Source node must be greater than 0 and less than %i " , vertices) ;
			return 0;
			
		}
	
	    floydAlgo(graph1, src, dest);


        return 0;
}
