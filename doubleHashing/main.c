#include <stdio.h>
#include <stdlib.h>
#define SIZE 13

int array[SIZE]={0};
void insert()
{
    int k, i, j, hash1, hash2;

    printf("\nEnter value to be inserted:");
    scanf("%d",&k);
    printf("\nInserting Value %d.... \n",k);

    hash1 = k%SIZE;
    hash2 = 7 - (k%SIZE) ;

    for(j = 0 ; j < SIZE ; j++)
    {
        i = (hash1 + j*hash2) % SIZE;
        if(array[i] == NULL)
        {
           array[i] = k;
           printf("The value is inserted.\n\n");
           break;
        }
    }

    if(i == SIZE)
        printf("The value can't be inserted.\n\n");

}

void search()
{
    int k, i, j, hash1, hash2;
    printf("\nEnter value to search:");
    scanf("%d",&k);
    printf("\nSearching Value %d.... \n",k);

    hash1 = k%SIZE;
    hash2 = 7 - (k%SIZE) ;

    for(j = 0 ; j < SIZE ; j++)
    {
        i = (hash1 + j*hash2) % SIZE;
        if(array[i] == k)
        {
           printf("The value is found at index %d.\n\n",i);
           break;
        }
    }

    if(i == SIZE)
        printf("The value is not found.\n\n");
}

void display()
{
    printf("\nDisplaying values...\n");
    int i;
    for(i = 0 ; i < SIZE ; i++)
        printf("%d. %d\n",i,array[i]);
}
int main()
{
    int n;

    printf("\n1. Insert");
    printf("\n2. Display");
    printf("\n3.Search");
    printf("\nEnter your choice:");
    scanf("%d",&n);

    switch(n)
    {
    case 1:
        insert();
        main();
    case 2:
        display();
        main();
    case 3:
        search();
        main();
    default:
       printf("\nTry again.\n\n");
       main();

    }

    return 0;
}
