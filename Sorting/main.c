#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<time.h>

void PrintArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d    ", arr[i]);
}

void Merge(int arr[], int p, int q, int r)
{
    int i, j, k;
    int n1 = q - p + 1;
    int n2 =  r - q;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[q + 1+ j];

    i = 0;
    j = 0;
    k = p;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void MergeSort(int arr[], int p, int r)
{
    if (p < r)
    {
        int q = p+(r-p)/2;

        MergeSort(arr, p, q);
        MergeSort(arr, q+1, r);

        Merge(arr, p, q, r);
    }
}

int Left(int i)
{
    return 2*i+1;
}
int Right(int i)
{
    return 2*i+2;
}

void Max_Heapify(int arr[], int n, int i)
{
    int L,R;
    int largest;
    L=Left(i);
    R=Right(i);

    if(L<n&&arr[L]>arr[i])
        largest=L;
    else
        largest=i;

    if(R<n&&arr[R]>arr[largest])
        largest=R;

    if (largest!=i)
    {
        int temp;
        temp=arr[largest];
        arr[largest]=arr[i];
        arr[i]=temp;
        Max_Heapify(arr,n,largest);
    }
}

void BuildMaxHeap(int arr[],int n)
{
     for (int i = n / 2-1; i >= 0; i--)
        Max_Heapify(arr, n, i);
}
void HeapSort(int arr[],int n)
{
   BuildMaxHeap(arr,n);
    for (int i=n-1; i>=0; i--)
    {
        int maxarray;
        maxarray=arr[0];
        arr[0]=arr[i];
        arr[i]=maxarray;

        Max_Heapify(arr, i,0 );
    }
}

void InsertionSort(int arr[], int n)
{
    int key,i,j;
    for(j=1; j<n; j++)
    {
        key=arr[j];

        i=j-1;
        while(i>=0&&arr[i]>key)
        {
            arr[i+1]=arr[i];
            i=i-1;
            arr[i+1]=key;
        }

    }
}

int SizeOfArray(char*filename)
{
    char line[100];
    int i=0,count=0;

    FILE *fptr;
    fptr = fopen(filename,"r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while(fgets(line, sizeof line, fptr)!=NULL)
    {
        count++;
    }
    return count;
}


void FillArrayFromFile(char*filename,int arr[])
{
    char line[100];
    int i=0,count=0;

    FILE *fptr;
    fptr = fopen(filename,"r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    }

    while(fgets(line, sizeof line, fptr)!=NULL)
    {
        arr[i]=atoi(line);
        i++;
    }

    fclose(fptr);
}

void FunctionWriteToFile(char*filename)
{

    int i, n;
    time_t t;
    n=1000000;

    srand((unsigned) time(&t));
    FILE *filePointer ;
    filePointer = fopen(filename, "w");

    for( i = 0 ; i < n ; i++ )
        fprintf(filePointer, "%d\n", rand() % 500);

    fclose(filePointer);
}

void FunctionCompare(int arr1[],int arr2[],int n1,int n2)
{
    int i=0;
    int flag=1;

    if (n1!=n2)
    {
        flag=0;
        printf("\nThe two arrays aren't identical\n");
    }

    for (int i = 0; i < n1; i++)
    {
        if (arr1[i] != arr2[i]&&n1==n2)
        {
            flag=0;
            printf("\nThe two arrays aren't identical\n");
            break;

        }
    }

    if(flag==1)
        printf("\nThe two arrays identical\n");


}

void ExecutionTimeHeapSort(int arr[],int n)
{
    double time_spent=0.0;
    clock_t begin =clock();
    HeapSort(arr,n);
    clock_t end =clock();
    time_spent = (((double)(end-begin))*1000.0)/CLOCKS_PER_SEC;
    //PrintArray(arr,n);
    printf("\nTime Execution of heap sort= %f\n",time_spent);
}


void ExecutionTimeMergeSort(int arr[],int n)
{
    double time_spent=0.0;
    clock_t begin =clock();
    MergeSort(arr,0,n-1);
    clock_t end =clock();
    time_spent = (((double)(end-begin))*1000.0)/CLOCKS_PER_SEC;
    //PrintArray(arr,n);
    printf("\nTime Execution of merge sort= %f\n",time_spent);


}

void ExecutionTimeInsertionSort(int arr[],int n)
{
    double time_spent=0.0;
    clock_t begin =clock();
    InsertionSort(arr,n);
    clock_t end =clock();
    time_spent = (((double)(end-begin))*1000.0)/CLOCKS_PER_SEC;
    //PrintArray(arr,n);
    printf("\nTime Execution of insertion sort= %f\n",time_spent);


}




int main()
{


    char filename1[100],filename2[100],filename3[100];
    char exit;

    printf("Enter the filename to open \n");
    scanf("%s", filename1);
    FunctionWriteToFile(filename1);
    int n1=SizeOfArray(filename1);
    printf("Size of array = %d\n",n1);
    int* arr1=malloc(n1*sizeof(int));
    FillArrayFromFile(filename1,arr1);
    ExecutionTimeHeapSort(arr1,n1);
    //ExecutionTimeInsertionSort(arr1,n1);
    //ExecutionTimeMergeSort(arr1,n1);

    printf("\nEnter the filename to open \n");
    scanf("%s", filename2);
    FunctionWriteToFile(filename2);
    int n2=SizeOfArray(filename2);
    printf("Size of array2= %d\n",n2);
    int* arr2=malloc(n2*sizeof(int));
    FillArrayFromFile(filename2,arr2);
    ExecutionTimeInsertionSort(arr2,n2);
    //ExecutionTimeHeapSort(arr2,n2);
    //ExecutionTimeMergeSort(arr2,n2);

    printf("\nEnter the filename to open \n");
    scanf("%s", filename3);
    FunctionWriteToFile(filename3);
    int n3=SizeOfArray(filename3);
    printf("Size of array = %d\n",n1);
    int* arr3=malloc(n3*sizeof(int));
    FillArrayFromFile(filename3,arr3);
    ExecutionTimeMergeSort(arr3,n3);
    //ExecutionTimeHeapSort(arr3,n3);
    //ExecutionTimeInsertionSort(arr3,n3);

    FunctionCompare(arr1,arr2,n1,n2);

   /* printf("Do you want to exit? y/n?");
    scanf("%s",&exit);
    if(exit== 'n')
        main();*/


    return 0;

}
