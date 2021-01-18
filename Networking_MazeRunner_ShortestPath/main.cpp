#include <iostream>
#include <bits/stdc++.h>
#define INFINITY 9999
#define MAX 10
#include <conio.h>



using namespace std;

void dijkstra(int source,int vertcies,int destination);
int check_empty(int vertices);
int extractMinimum(int vertices);
void output(int vertices, int source, int destination);
void minPath(int x);


class vertix{
    public:
    int row;
    int coloumn;


    vertix(int r ,int c)
        :row(r) , coloumn(c)
    {

    }
    vertix(){       //to make array of vertix
    }

};
int N ;
vertix solution[50];
int vertices,edges;
int arr[50][50];
int Graph[MAX][MAX] = {0}, di[MAX], visited[MAX], parent[MAX],timeArray[MAX][MAX] = {0}, totalTime = 0 , m, checked = 0;
int check[MAX];

void BFS(int v,int k)
{
    int f,s,i;

    vector <int> values;
    vector <bool> visited(false);
    queue <pair <int,int> >Q;

    Q.push({v,0});
    visited[v] = true;

    while(!Q.empty())
    {
        f = Q.front().first;
        s = Q.front().second;

        Q.pop();

        visited[f] = true;

        if(s == k)
            values.push_back(f);

        for(i=0 ; i < edges ; i++)
        {
            if(arr[f][i] == 1 && !visited[i])
            {
                Q.push({i,s+1});
                visited[i] = true;
            }
        }
    }
    printf("\nThere are %d people with %d connections away starting from %d.\n\n",values.size(),k,v);


}

void initializeArray()
{
    int i,j;
    for(i = 0 ; i < edges ; i++)
    {
        for(j = 0 ; j < edges ; j++)
            arr[i][j] = 0;
    }
}

void initializeEdges()
{
    int u,v,i;

    printf("Please enter edges in form of(u v):\n");

    for(i = 0 ; i < edges ; i++)
    {
        scanf("%d %d",&u,&v);
        arr[u][v] = 1;
        arr[v][u] = 1;
    }
}

void part1()
{
    int v,k;

    printf("Please enter number of vertices:\n");
    scanf("%d",&vertices);

    printf("Please enter number of edges:\n");
    scanf("%d",&edges);

    initializeArray();
    initializeEdges();

    printf("Please enter starting vertex:\n");
    scanf("%d",&v);

    printf("Please enter value k:\n");
    scanf("%d",&k);

    BFS(v,k);

}

void print(vertix solution[],int i){
    int j=0;
     printf("\n");
 while(j<=i){
printf("(%d-%d)",solution[j].row,solution[j].coloumn);
           j++;
        }
}

int paths(std::vector<std::vector<int> >const&maze){
    vertix source(0,0);
    bool visited[N][N];
     int in2=0;
     for(int r=0; r<=N-1; r++)
    {

            solution[r].coloumn=0;
            solution[r].row=0;

    }
     if( (maze[N-1][N-1]==1))
    {
        printf("\n\t there's no paths\n");
        return 0;
    }
    if( (maze[0][0]==1))
    {
        printf("\n\t there's no paths\n");
        return 0;

    }

    queue<vertix>q;
    //push the starting node in the queue (starting position)
    q.push(source);
    visited[source.row][source.coloumn]=true;     //mark it as visited
    int i=0;
    int finished=0;
    while(!q.empty()){
            int in=0;
            //pull  node from the queue
          vertix p=q.front();
            q.pop();
            // if arrived to the destination
            if (p.row==N-1 && p.coloumn == N-1){
            solution[i].row=p.row;
            solution[i].coloumn=p.coloumn;
                   finished=1;
                   print(solution,i);
                   cout<<"\n\n    arrived to my destination   \n\n";
             break;
            }
            //moving right
                    if (p.coloumn + 1 < N && visited[p.row][p.coloumn + 1] == false && maze[p.row][p.coloumn+1]==0) {
            q.push(vertix(p.row, p.coloumn + 1));
            visited[p.row][p.coloumn + 1] = true;
            solution[i].row=p.row;
            solution[i].coloumn=p.coloumn;
            in=1;
            }
                    // moving down
      else  if (p.row + 1 < N && visited[p.row + 1][p.coloumn] == false && maze[p.row+1][p.coloumn]==0) {
            q.push(vertix(p.row + 1, p.coloumn));
            visited[p.row + 1][p.coloumn] = true;
            solution[i].row=p.row;
            solution[i].coloumn=p.coloumn;
            in=1;
        }
             // moving up
        else if (p.row - 1 >= 0 && visited[p.row - 1][p.coloumn] == false && maze[p.row-1][p.coloumn]==0) {
              //   printf("%d up %d",p.row,p.coloumn);
            q.push(vertix(p.row - 1, p.coloumn));
            visited[p.row - 1][p.coloumn] = true;
            solution[i].row=p.row;
            solution[i].coloumn=p.coloumn;
            in=1;
        }
             // moving left
       else  if (p.coloumn - 1 >= 0 && visited[p.row][p.coloumn - 1] == false && maze[p.row][p.coloumn-1]==0) {
            q.push(vertix(p.row, p.coloumn - 1));
            visited[p.row][p.coloumn - 1] = true;
            solution[i].row=p.row;
            solution[i].coloumn=p.coloumn;
            in=1;
        }else {
            visited[p.row][p.coloumn]=true;   //if the way is blocked
             --i;
             while(solution[i].coloumn==0 && solution[i].row==0){
                printf("there's no paths");
                return 0;
             }
             q.push(solution[i]);
        }
        if(in!=0){
            i++;
        }

    }

}

void part2(){
    int r=0,c=0,num=0, i=0;
    printf("please enter size of maze:");
    scanf("%d",&N);
   while( N==0){
       printf("please enter number bigger than zero:");
       scanf("%d",&N);

   }
    vector<vector<int> > maze(N , vector<int>(N));
    //input maze
    for(r=0; r<=N-1; r++)
    {
        for(c=0; c<=N-1; c++)
        {
            printf("please enter cell #%d: ",num);
            scanf("%d",&maze[r][c]);

            num++;
        }
    }
     printf("\n   the maze     ");
     printf("\n");
    for (int row=0; row<=N-1; row++)
{
    for(int columns=0; columns<=N-1; columns++)
    {
         printf("   %d", maze[row][columns]);
    }
    printf("\n");
}
    paths(maze);
}


int check_empty(int vertices)
{
    int sum = 0, i ;
    for(i=1;i<=vertices;i++)
        sum += check[i];
    return sum ;
}
int extractMinimum(int vertices)
{
    int i, x, minimum = INFINITY ;
    for(i=1;i<=vertices;i++)
    {
        if(di[i]<=minimum && visited[i] == 0)
        {
            minimum = di[i];
            x = i;
        }
    }
    check[x] = 0;
    return x ;
}
void output(int vertcies, int source, int destination)
{
    int i;
    cout<<"The route with minimum cost is ";
    for(i=1;i<=vertcies;i++)
    {
        if (i == destination)
        {
            cout<<source;
            minPath(i);
            cout<<"\nTotal time "<<totalTime<<"hour(s)"<<endl;
            if(checked > 1)
                cout<<"Total cost = "<<di[i] + m * totalTime<<"$"<<endl;
            else
                cout<<"Total cost = "<<di[i]<<"$"<<endl;

        }
    }
}
void minPath(int x)
{
    if(parent[x] == - 1)
        return;

    if(checked > 0)
        totalTime++;

    totalTime+= timeArray[parent[x]][x];

    checked++;
    minPath(parent[x]);

    cout<<"->"<<x;
}

void dijkstra(int source,int vertcies,int destination)
{
    int minimum, i;
    int Empty = check_empty(vertcies);

    while(Empty > 0)
    {
        minimum = extractMinimum(vertcies);
        visited[minimum] = 1;
        for(i=1;i<=vertcies;i++)
        {
            if(Graph[minimum][i] > 0)
            {
                if(di[minimum] + Graph[minimum][i] < di[i])
                {
                    di[i] = di[minimum] + Graph[minimum][i];
                    parent[i] = minimum;
                }
            }
        }
        totalTime = timeArray[minimum][i];
        Empty = check_empty(vertcies);
    }

    output(vertcies,source,destination);

}
void part3()
{
    int source, Source, vertcies, edges, destination, Destination, time, cost;
    int i;
    cout<<"please enter amount M:"<<endl;
    cin>>m;
    cout<<"please enter number of cities:"<<endl;
    cin>>vertcies;
    cout<<"please enter number of routes:"<<endl;
    cin>>edges;
    cout<<"please enter source, destination, time and cost for each route:"<<endl;
    for(i=1;i<=edges;i++)
    {
        scanf("%d %d %d %d",&source,&destination,&time,&cost);
        Graph[source][destination] = cost;
        timeArray[source][destination] = time;
    }
    cout<<"Enter the source city:"<<endl;
    cin>>Source;
    cout<<"Enter the destination city:"<<endl;
    cin>>Destination;

    for(i=1;i<=vertcies;i++)
    {
        di[i] = INFINITY;
        visited[i] = 0;
        check[i] = 1;
        parent[i] = -1;
    }

   di[Source] = 0;
   dijkstra(Source,vertcies,Destination);

}

int main()
{



    char c;
    printf("  \t\t\tChoose number from 1 to 4");
    printf("\n---------------------------------------------------------------------------------------");
    printf("\n\tMAIN MENU:");
    printf("\n\t\t1.Part 1 - Networking");
    printf("\n\t\t2.Part 2 - Maze Runner");
    printf("\n\t\t3.Part 3 - Shortest Path");
    printf("\n\t\t4.Exit");
    printf("\t\n      ----------------------------------------");
    printf("\n\tEnter your choice:");
    scanf("%c",&c);
    fflush(stdin);

    system("cls");
    switch(c)
    {
    case '1':
        part1();
        printf("\n\t\t\tPress any key to return back:");
        getche();
        main();
        break;
    case '2':
        part2();
        printf("\n\t\t\tPress any key to return back:");
        getche();
        main();
        break;
    case '3':
        part3();
        printf("\n\t\t\tPress any key to return back:");
        getche();
        main();
        break;

    case '4':
        exit(0);
        break;
    default:
        system("cls");
        main();
    }

    return 0;
}


