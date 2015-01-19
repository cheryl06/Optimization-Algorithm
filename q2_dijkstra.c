
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<assert.h>
#define MAX 100
#define  infinity 100000


struct Point
{
	int status, prev, distance;
};

// Defined a structure for minimum heap
struct MinHeapVertex
{
    int  v;
    int dist;
};


typedef struct VertexNode
{
      int vertex;
	  int distance;
	  
}VertexNode;

struct MinHeap
{
    int minHipSize;  // defined variable to check the number of heap nodes present currently    
    int cap;         // cap is a variable defined to store the value for min heap
    int *pos;        // used for decreasekey()
    struct MinHeapVertex **array;
};

//representing nodes in adjacency list
struct AdjListVertex
{
    int dest, weight;
    struct AdjListVertex* next;
};
 
//representing nodes in adjacency list
struct AdjcentList
{
    struct AdjListVertex *head;  
};
 
// representing graph is an array of the adjacency list
struct Graph
{
    int V;
    struct AdjcentList* array;
};

// represent a min heap 

struct Graph* graph1 ;
struct MinHeapVertex* root ; 
struct MinHeapVertex *lastNode ;

int usedArray[1000][1000] ;
VertexNode heap[1000000];
VertexNode temp;

int seen[MAX];
int from,to;
int heapSize, now;
int source, edgeCtr, rows, cols, correct , dest , rq[1000], tmpRq[1000] ; ; ;
int array[MAX], ctrEle ;

//Initializing heap 
void Init()
{
        heapSize = 0; // initially assigning value of heapSize to 0 
        heap[0].distance = INT_MAX;
        heap[0].vertex  = -1;
}

//Inserting an element into the heap
void Insert(VertexNode element)
{
        heapSize++;
        heap[heapSize] = element; //Insert in the last place
        // Adjust the position of the heap	
        now = heapSize;
		
        while(heap[now/2].distance > element.distance) 
        {
                heap[now] = heap[now/2];
                now /= 2;
        }
        heap[now] = element;
		
	}
VertexNode DeleteMin()
{
    
		VertexNode minElement,lastElement;
        int child,now;
        minElement = heap[1];
     
        lastElement = heap[heapSize--];//Refers to the index at which we are currently present
        
        for(now = 1; now*2 <= heapSize ;now = child)
        {
                child = now*2;
                if(child != heapSize && heap[child+1].distance < heap[child].distance ) 
                {
                        child++;
                }
                if(lastElement.distance > heap[child].distance)
                {
                        heap[now] = heap[child];
                }
                else /* It fits there */
                {
                        break;
                }
        }
        heap[now] = lastElement;
        return minElement;
}


struct Graph* createTheGraph(int V) // creating a graph of V vertices
{
	int i ;

    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    
    graph->array = (struct AdjcentList*) malloc(V * sizeof(struct AdjcentList));

     
    for ( i = 0; i < V; ++i)  //Initializing each head of adjacency list as NULL 
        graph->array[i].head = NULL;
 
    return graph;
}

//utility function to create a new adjacency list node
struct AdjListVertex* newAdjListNode(int dest, int weight)
{
    struct AdjListVertex* newNode =
            (struct AdjListVertex*) malloc(sizeof(struct AdjListVertex));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, int weight)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining

    struct AdjListVertex* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// A utility function to create a new Min Heap Node
struct MinHeapVertex* newMinHeapNode(int v, int dist)
{
    struct MinHeapVertex* minHeapNode =
           (struct MinHeapVertex*) malloc(sizeof(struct MinHeapVertex));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int cap)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(cap * sizeof(int));
    minHeap->minHipSize = 0;
    minHeap->cap = cap;
    minHeap->array =
         (struct MinHeapVertex**) malloc(cap * sizeof(struct MinHeapVertex*));
    return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapVertex** a, struct MinHeapVertex** b)
{
    struct MinHeapVertex* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->minHipSize &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->minHipSize &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct MinHeapVertex *smallestNode = minHeap->array[smallest];
        struct MinHeapVertex *idxNode = minHeap->array[idx];
 
        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->minHipSize == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapVertex* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
	
    // Store the root node
    root = minHeap->array[0];
 
    // Replace root node with last node
    lastNode = minHeap->array[minHeap->minHipSize - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->v] = minHeap->minHipSize-1;
    minHeap->pos[lastNode->v] = 0;
 
    // Reduce heap minHipSize and heapify root
    --minHeap->minHipSize;
    minHeapify(minHeap, 0);
 
    return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;
 
    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}


// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->minHipSize)
     return 1;
   return 0;
}

// A utility function used to print the solution
void printArr(int dist[], int n, int src, int dest, int sp[])
{	
	int i,s ;
    printf("\n\t NODE   DISTANCE\n");
    for (i = 0; i < n; ++i)
		if (i == dest )
			printf("\t [%d] --->>  %d\n", i, dist[i]);
	
    printf("\n   ");
    
	printf("\n\t PATH : ");

       for(i=ctrEle - 1;i >=0;i--) {
		if(array[i]!=-1)
			printf("%d  ",array[i]);
	}	
	
	printf(" \n");
	
	
		
		
}


// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(struct Graph* graph, int src, int dest)
{
	struct Point ste[MAX];
	int v, s, i ;
    int V = graph->V;// Get the number of vertices in graph
    int dist[1000];      // dist values used to pick minimum weight edge in cut
	int sp[1000] ;
	
    struct MinHeap* minHeap = createMinHeap(V);

	for(i=0;i<V;i++)
	{
		ste[i].prev=-1;
		ste[i].distance = infinity;
		ste[i].status = 0;
	}

	 
	ste[s].prev=-1;
	ste[s].distance = 0;
	ste[s].status = 1;

	
    for (v = 0; v < V; ++v)
    {
		sp[v] = -1 ;
	}

    for (v = 0; v < V; ++v)
    {
		rq[v] = 0 ;
	}

    for (v = 0; v < V; ++v)
    {
		tmpRq[v] = 0 ;
	}
	
    // Initialize min heap with all vertices. dist value of all vertices 
    for (v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);
 
    // Initially minHipSize of min heap is equal to V
    minHeap->minHipSize = V;
 
    // In the followin loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapVertex* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // Store the extracted vertex number
		
		int fnd ;
        // Traverse through all adjacent vertices of u (the extracted
        // vertex) and update their distance values
        struct AdjListVertex* pCrawl = graph->array[u].head;
		tmpRq[u] = 1 ;
		
		//printf(" spt RQ = 1 %d \n", u) ;
		//printf("FIRST %d \n", u) ;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
		
            // If shortest distance to v is not finalized yet, and distance to v
            // through u is less than its previously calculated distance
			
			if (isInMinHeap(minHeap, v) && (dist[u] != INT_MAX) && 
                                          (pCrawl->weight + dist[u] < dist[v]) && (rq[u] != 1 ))
            {

                dist[v] = dist[u] + pCrawl->weight;
				ste[v].prev = u;
				
				
				tmpRq[u] = 1;
				
				fnd = 0 ;
				for (s= 0; s < V;s++) {
					if (sp[s] == u) {
						fnd = 1;
						
						break ;
					}
				}
				if (!fnd && u != dest &&  u != src) {
					sp[v] = u ;
				
				}
                // update distance value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
			else {
				if ((isInMinHeap(minHeap, v)) && (dist[u] != INT_MAX) && 
                                          (pCrawl->weight + dist[u] > dist[v]) ) {
  				
					sp[v] = -1;
					if (rq[u] != 1)
						tmpRq[u] = 0;
					
					}
				
			}
		
            pCrawl = pCrawl->next;
        }
		if ((tmpRq[u] == 1) && (rq[u] !=1)) {
			
			rq[u] =1 ;
		}
		
    }
	ctrEle = 0 ;
	v = dest ;
	i = -1 ;
	while (1) {
		i++ ;
		
		if (v == -1)
			break ;
		ctrEle = ctrEle + 1 ;
		array[i]=v;
		v=ste[v].prev;
		}
	
    printArr(dist, V, src, dest, sp);
}


int main()
{	
		int stop ;
        int graph[MAX][MAX],minHipSize[MAX]={0},distance[MAX]={0},cost[MAX][MAX];
        int vertices,edges,weight;
        int iter;
		int i, exists, r, c		;
		struct AdjListVertex* h ;
		
        printf("\n\t Enter node in Graph  \n\t");

        scanf("%d",&vertices);
		correct = 0 ;
		
		
		  graph1 = createTheGraph(vertices);
		 
        // random inputs
		for (rows = 0; rows < vertices ; rows++) {
			for (cols = 0; cols < vertices  ; cols++) {
				
					if (rows != cols) {
						exists = 1 ;
						stop = 0 ;
						
							exists = 0 ;
							
						        if ((usedArray[cols][rows] != 1) && usedArray[rows][cols] != 1) {
							usedArray[cols][rows] = 1 ;
						        usedArray[rows][cols] = 1 ;
						        exists = 0 ;
							}
							else	{
								exists = 1 ;
									}
							
						
						if(!exists)  {
							
							from = rows ;
							to = cols ;
							weight = 1 + rand()%20 ;
							assert(from>=0 && from<vertices);
							assert(to>=0 && to<vertices);
							 // adding edges to the graph
							addEdge(graph1, from, to, weight) ;
						}	
						
					}
					else {
						from = rows ;
						to = cols ;
						
					}
					
			}
		}
		
		printf("\n");
		
        
		//print linked list
		for (i = 0; i < vertices; i++) {
			printf("\tHeadNode[%d] ->> ", i) ;
			h  = graph1->array[i].head ;	
			while (h->next != NULL) {
				printf("%d|%d|   " , h->dest, h->weight) ;
				
				h = h->next ;
			}
			//print the last node 
			printf("%d|%d| \t" , h->dest, h->weight) ;
			
			printf("\n") ;
		}
		

		// loop for all nodes 
		printf("\n\t Enter source node for shortest path \n\t");
                scanf("%d",&source);
		if ((source >= vertices) || source < 0) {
			printf("Source node must be greater than 0 and less than %i " , vertices) ;
			return 0;
			
		}
		
		printf("\n\t Enter destination node for shortest path \n\t");
                scanf("%d",&dest);
		if ((dest >= vertices) || dest < 0) {
			printf("Destination node must be greater than 0 and less than %i " , vertices) ;
			return 0;			
		}

		
	    dijkstra(graph1, source, dest);
			

			return 0;

}
