/* Mohammad Fareed                      -_-                                          1212387
 * section 4                                                                    6-7-2023
 * In this project we construct a graph to represent the path between cities then we represent two
 * algorithms (BFS AND DIJKSTRA) to find the shortest path between these cities */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//linked list to represent the cities
struct node {
    char Name[50];
    int dest;
    struct node *next;
};
//struct to represent the vertices(nodes)
struct head{
    struct node* City;
    struct head* prev;
    int visted;
    int id;
    int distance;
};
//the struct to represent the graph
struct  Graph{
    int size;
    struct head* array;
};
//struct for queue
struct queue{
    char city[500];
    struct queue *next;
};
//struct for heap
struct heap {
    struct head* array;
    int size;
    int capacity;
};
//this array is used to save the answer of the shortest path before print it on the file
char info[500]="";
//queue to save all paths that user try before he exits.
struct queue *q1=NULL;
//heap functions
struct heap* createHeap(int capacity, struct head* c);
void heapify(struct heap* h, int index);
struct head* extractMin(struct Graph *graph,struct heap* h);
void insertHelper(struct heap* h, int index);
//queue functions
struct queue* enqueue(struct queue*,char city[]);
struct head* dequeue(struct Graph *graph,struct queue **q);
struct queue* make_empty(struct queue*);
int is_empty(struct queue*);
//Graph and system function
struct Graph* creat_Graph();
struct node* creatnode(char c[]);
int isnot_found(struct node *c,char city[]);
struct node* make_empty1(struct node *c);
struct Graph* insert_edge(struct Graph *graph,char city1[],char city2[],int);
struct Graph* read_fromfile(struct Graph*);
void print_Graph(struct Graph *graph);
struct head* find_city(struct Graph*,char city[]);
void BFS(struct Graph *graph,char city[],char city2[]);
void print(struct head *c1,struct head *c,int *num);
void print_onFile();
void Dijkstra (struct Graph *graph,char city[],char city2[]);
//declare a proper menu for the user
int main( )
{
    printf(".............Welcome to shortest path program................\n");
    struct Graph *graph= NULL;
    int sel=0;
    char city1[50],city2[50];
    int is_loaded=-1;
    while (sel!=4){
        printf("Enter your choice\n1-Load cities\n2-Enter source City\n3-Enter destination City"
               "\n4-Exit and Print on File\n");
        scanf("%d",&sel);
        switch (sel) {
            case 1:
                graph= creat_Graph();
                graph= read_fromfile(graph);
                print_Graph(graph);
                is_loaded=1;
                break;
            case 2:
                if(is_loaded==1){
                printf("Enter the name of the source City\n");
                scanf("%s",city1);}
                else
                    printf("YOU NEED TO LOAD THE GRAPH\n");
                break;

            case 3:
                 if(is_loaded==1){
                printf("Enter the name of the destination City\n");
                scanf("%s",city2);
                printf("BFS shortest path:\n");
                BFS(graph,city1,city2);
                printf("*********************************\n");
                printf("Dijkstra shortest path:\n");
                Dijkstra(graph,city1,city2);}
                else
                    printf("YOU NEED TO LOAD THE GRAPH\n");
                break;
            case 4:
                print_onFile();
                break;
            default:
                printf("Invalid Choice\n");
        }
        printf("*******************************************************************\n");
    }

    return 0;
}
//function to creat city heap by taking its capacity and the cities
struct heap* createHeap(int capacity, struct head* cities)
{   //the main principle in creating heaps the heapify function
    struct heap* h = (struct heap*)malloc(sizeof(struct heap));

    if (h == NULL) {
        printf("Memory error");
        return NULL;
    }

    h->size = 0;
    h->capacity = capacity;

    h->array = (struct head*)malloc(capacity * sizeof(struct head));

    if (h->array == NULL) {
        printf("Memory error");
        return NULL;
    }
    int i;
    for (i = 0; i < capacity; i++) {
        h->array[i] = cities[i];
        h->array[i].id=i;
    }
    h->size = i;
    i = (h->size - 2) / 2;
    while (i >= 0) {
        heapify(h, i);
        i--;
    }
    return h;
}
//this function is the main function in the heap that rearrange the heap by compare the root
//by it children and make the swap operation depending on min
void heapify(struct heap* h, int index)
{   //find the left and the right children
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    int min = index;
    //checking if the left or right is NULL
    if (left >= h->size || left < 0)
        left = -1;
    if (right >= h->size || right < 0)
        right = -1;
    //decide which children is min depending on distance
    if (left != -1 && h->array[left].distance < h->array[index].distance)
        min = left;
    if (right != -1 && h->array[right].distance < h->array[min].distance)
        min = right;

    // the swap operation
    if (min != index) {
        h->array[min].id=index;
        h->array[index].id=min;
        struct head temp = h->array[min];
        h->array[min] = h->array[index];
        h->array[index] = temp;
        heapify( h,min);
    }
}
//this function is used to delete the min element from the heap
struct head* extractMin(struct Graph* graph,struct heap* h)
{
    struct head* deleteItem;
    if (h->size == 0) {
        printf("\nHeap id empty\n");
        return NULL;
    }

    // save the element before deletion
    deleteItem = find_city(graph,h->array[0].City->Name);
    // replace the min node with the last added node and change it ID and change the size of heap
    h->array[0] = h->array[h->size - 1];
    h->array[0].id=0;
    h->size--;
   // heapify the heap after this change for index 0
    heapify(h, 0);
    return deleteItem;
}
//this function is used to reheap the heap when we change the distance of one element
void insertHelper(struct heap* h, int index)
{
   //find the parent of the element
    int parent = (index - 1) / 2;

    if (h->array[parent].distance > h->array[index].distance) {
       //do the swap operation after check the min
        h->array[parent].id=index;
        h->array[index].id=parent;
        struct head temp = h->array[parent];
        h->array[parent] = h->array[index];
        h->array[index] = temp;

        //recheck for the parents
        insertHelper(h, parent);
    }
}
//function to creat a node
struct node* creatnode(char c[]){
    struct node *city=(struct node*)malloc (sizeof (struct node));
    strcpy(city->Name,c);
    city->next=NULL;
    return city;

}
//function to check is not in the list
int isnot_found(struct node *c,char city[]){
    struct node *temp =c;
    while (temp!=NULL){
        if(strcmp(temp->Name,city)==0)return 0;
        temp=temp->next;
    }
    return 1;
}
//make empty the list
struct node* make_empty1(struct node *c){
    struct node *temp=c;
    struct node *temp2;
    while (temp!=NULL){
        temp2=temp->next;
        free(temp);
        temp=temp2;
    }
    return NULL;


}
//function to creat a graph by finding its size first and give initial information
struct Graph* creat_Graph(){
    struct Graph *graph=(struct Graph*)malloc(sizeof (struct Graph));
    FILE *fin= fopen("cities.txt","r");
    int s,count=0;
    char city1[30];
    char city2[30];
    char dest[10];
    struct node *c1= creatnode(city1);
    struct node *c2;
    s= fscanf(fin,"%s%s%s",city1,city2,dest);
    //read all the city from the file then add the city to a linked list if it is new and increase
    //the count which represent the number of the cities
    while(s!=EOF){
        //check for destination
        if(isnot_found(c1,city2)){
        count++;
         c2= creatnode(city2);
        c2->next=c1->next;
        c1->next=c2;}
        s= fscanf(fin,"%s%s%s",city1,city2,dest);
        //check for the source
        if(isnot_found(c1,city1)){
            count++;
            c2= creatnode(city1);
            c2->next=c1->next;
            c1->next=c2;}
    }
    if(isnot_found(c1,city2)){
        count++;
        c2= creatnode(city1);
        c2->next=c1->next;
        c1->next=c2;}
    fclose(fin);
    //empty the linked list after we finished
    c1= make_empty1(c1);
    graph->size=count;
    //declare the graph after we know its size
    graph->array=(struct head*) malloc(count*sizeof (struct head));

    for(int i=0;i<graph->size;i++){
        graph->array[i].City=NULL;
        graph->array[i].visted=0;
        graph->array[i].distance=999999999;
    }
    return graph;

}
//function used to insert edge between two cities
struct Graph* insert_edge(struct Graph *graph,char city1[],char city2[],int dest){
    struct node *c2= creatnode(city2);
    c2->dest=dest;
    //first we check if the source city in the graph
    //if we found it we insert the second city to its linked list
    //if not we creat a new linked list for the first city and insert the second city to
    for(int i=0;i<graph->size;i++){
       if(graph->array[i].City==NULL){
           struct node *c1= creatnode(city1);
           c1->dest=0;
           graph->array[i].City=c1;
           c1->next=c2;
           break;
       }
       else if(strcmp(graph->array[i].City->Name,city1)==0){
           struct node *temp=graph->array[i].City;
           while (temp->next!=NULL){
               temp=temp->next;
           }
           temp->next=c2;
           break;
       }

    }
    return graph;
}
//function to read and construct the graph from the file
struct Graph* read_fromfile(struct Graph* graph){
    FILE *fin= fopen("cities.txt","r");
    int s;
    char city1[30];
    char city2[30];
    int dest;
    char unit[5];
    //read the source,destination,distance,unit
    s= fscanf(fin,"%s%s%d%s",city1,city2,&dest,unit);
    while(s!=EOF){
       graph= insert_edge(graph,city1,city2,dest);
        s= fscanf(fin,"%s%s%d%s",city1,city2,&dest,unit);
    }
    fclose(fin);
    return graph;
}
//function to print the graph for the user
void print_Graph(struct Graph *graph){
    struct node *temp;
    for(int i=0;i<graph->size;i++){
        if(graph->array[i].City!=NULL){
            printf("%s----->",graph->array[i].City->Name);
            temp=graph->array[i].City->next;
            while (temp!=NULL){
                printf("%s %d   ",temp->Name,temp->dest);
                temp=temp->next;
            }
            printf("\n");
        }
    }
}
//insert a new element to the queue
struct queue* enqueue(struct queue* q1,char city[]){
    if(q1==NULL){
       q1= (struct queue*)malloc(sizeof (struct queue));
        strcpy(q1->city,city);
        q1->next=q1;
        return q1;
    }
    struct queue *new=(struct queue*)malloc(sizeof (struct queue));
    strcpy(new->city,city);
    new->next=q1->next;
    q1->next=new;
    q1=new;
    return q1;
}
//delete the first elemnt from the queue
struct head* dequeue(struct Graph *graph,struct queue **q1){
    struct head *c= find_city(graph,(*q1)->next->city);
    if((*q1)->next==(*q1)){
        free((*q1));
        (*q1)=NULL;
    }
    else{
    struct queue *temp=(*q1)->next;
    (*q1)->next=temp->next;
    free(temp);}
    return c;
}
//function to empty the queue
struct queue* make_empty(struct queue* q1){
    struct queue *temp=q1->next;
    while (q1!=NULL){
        if(q1->next==q1){
            free(q1);
           q1= NULL;
        }
        else{
        q1->next=temp->next;
        free(temp);
        temp=q1->next;
        }
    }
    return q1;
}
//function to check if the queue is empty
int is_empty(struct queue* q1){
    if(q1==NULL)return 1;
    else return 0;
}
//function that find a specific city from the graph
struct head* find_city(struct Graph* graph,char city[]){
    for(int i=0;i<graph->size;i++){
        if(strcmp(graph->array[i].City->Name,city)==0){
            return &graph->array[i];
        }
    }
    return NULL;
}
//the BFS algorithm depends on select a source city than we find its adjacency cities and marked them
//as visited and see their adjacency unvisited cities and so on
void BFS(struct Graph *graph,char city[],char city2[]){
    //clear the info array to put the new path in
    info[0]=' ';
    info[1]='\0';
    //for this algorithm we use queue
    //first we push the source node and marked it as visited
    //second dequeue the city and enqueue their adjacency unvisited cities
    //repeat this operation until the queue become empty
    struct queue *q1=NULL;
    struct head *initial= find_city(graph,city);
    struct head *t;
    struct node *temp;
    q1= enqueue(q1,initial->City->Name);
    initial->prev=NULL;
    initial->distance=0;
    initial->visted=1;
    while (!is_empty(q1)){
       initial= dequeue(graph,&q1);
        temp=initial->City->next;
        while (temp!=NULL){
            t=find_city(graph,temp->Name);
            if(t->visted==0){
                q1=enqueue(q1, temp->Name);
                t->visted=1;
                t->distance=initial->distance+temp->dest;
                t->prev=initial;
            }
            temp=temp->next;
        }
    }
    //this part of the code used to add the path to the info array and print the path to the user
    //showing the path,number of edges which is most important and the total distance
    int n=0;
    struct head *c1=find_city(graph,city);
    struct head *c2=find_city(graph,city2);
    if(c1&&c2){
    strcat(info,"BFS Shortest Path \n");
    print(c1,c2,&n);
    printf("\nNumber of edges %d",n-1);
    printf("\nTotal Distance %dKM\n",c2->distance);
    char n1[10],distance[10];
    sprintf(n1,"%d",n-1);
    sprintf(distance,"%dKM",c2->distance);
    strcat(info,"\nNumber of edges ");
    strcat(info,n1);
    strcat(info,"\nTotal Distance ");
    strcat(info,distance);
    strcat(info,"\n");}
    //if one of the two cities is not in the graph we told the user that
    else{
        printf("Sorry  there is error with the inputs cities\n ");
    }
    // remake the cities an unvisited
    for(int i=0;i<graph->size;i++){

        graph->array[i].visted=0;
        graph->array[i].distance=999999999;
    }
}
//function used to print the path to the user and it to array
void print(struct head *c1,struct head *c,int *numofdege){
    if(c!=NULL){
        (*numofdege)++;
        print(c1,c->prev,numofdege);
        int d=0;
        if(c->prev!=NULL)
            d=c->distance-c->prev->distance;

        if(d!=0){
            printf("--%dKM-> %s  ",d,c->City->Name);
            char NUM[10];
            sprintf(NUM,"%dKM",d);
            strcat(info,NUM);
            strcat(info,"    ");
            strcat(info,c->City->Name);
            strcat(info,"    ");

    }
        else {
            printf("%s  ", c->City->Name);
            strcat(info,c->City->Name);
            strcat(info,"    ");
        }
    }}
//in the dijkstra algorithm we always select the short path and its-not necessary to be adjacency
//to the source node to do this we use priority queue (heap)
void Dijkstra (struct Graph *graph,char city[],char city2[]){
    struct heap* h=NULL;
    struct head *c1= find_city(graph,city);
    struct head *t;
    struct node *temp;
    c1->distance=0;
    c1->prev=NULL;
    h= createHeap(graph->size,graph->array);
    int count=0;
    //after we creat the heap we delete the min which is the source with distance 0
    //after that we check if the path from the deleted node to adjacency node is less than
    //the nodes distance, so we change it we keep do that until the heap become empty
    while (h->size!=0){
        c1= extractMin(graph,h);
        c1->visted=1;
        //check the adjacency nodes
        temp=c1->City->next;
        while (temp!=NULL) {
            t = find_city(graph, temp->Name);
            for(count=0;count<h->size;count++)
                    if(h->array[count].City==t->City)
                        break;
            if (temp->dest + c1->distance < t->distance) {
                t->distance = temp->dest + c1->distance;
                h->array[count].distance=t->distance;
                //reheap the changed node
                insertHelper(h,count);
                t->prev = c1;

            }
            temp = temp->next;
        }}
    //this part of code to print the path and total distance and number of edges and add these
    //information to info array
    int n=0;
    struct head *c=find_city(graph,city);
    struct head *c2=find_city(graph,city2);
    if(c&&c2){
    strcat(info,"Dijkstra Shortest path\n ");
    print(c,c2,&n);
    printf("\nNumber of edges %d",n-1);
    printf("\nTotal Distance %dKM\n",c2->distance);
    char n1[10],distance[10];
    sprintf(n1,"%d",n-1);
    sprintf(distance,"%dKM",c2->distance);
    strcat(info,"\nNumber of edges ");
    strcat(info,n1);
    strcat(info,"\nTotal Distance ");
    strcat(info,distance);
    strcat(info,"\n");
    q1=enqueue(q1,info);}
    else{
        printf("Sorry  there is error with the inputs cities\n ");
    }
    for(int i=0;i<graph->size;i++){
        graph->array[i].visted=0;
        graph->array[i].distance=999999999;
    }
    //free the heap
    free(h->array);
    free(h);
}
//function to print the all paths that user try to the file before the exit
void print_onFile(){
    if(q1!=NULL){
    FILE *fout= fopen("shortest_distance.txt","a");
    struct queue *temp=q1->next;
    do{
        fprintf(fout,"%s",temp->city);
        fprintf(fout,"***************************************************************\n");
        temp=temp->next;
    } while (temp!=q1->next);
        q1=make_empty(q1);
        fclose(fout);
}}
