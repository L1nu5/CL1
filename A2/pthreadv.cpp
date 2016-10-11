#include<stdio.h>
#include<pthread.h>

int k=0;
pthread_t threads[100];

struct args
{
	int *arr;
	int low;
	int high;
	int tid;
};

int partition(int *arr, int low_index, int high_index)
{
	int i, j, temp, key;
	key = arr[low_index];
	i= low_index + 1;
	j= high_index;
	while(1)
	{
		while(i < high_index && key >= arr[i])
			i++;
		while(key < arr[j])
			j--;
		if(i < j)
		{
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			temp= arr[low_index];
			arr[low_index] = arr[j];
			arr[j]= temp;
			return(j);
		}
	}
}


void* quicksort(void *arguments)
{
	struct args* arg=(struct args *)arguments;
	int j;
	int low_index=arg->low;
	int high_index=arg->high;
	int *arr=arg->arr;
	int tid=arg->tid;
	if(low_index < high_index)
	{
		j = partition(arr, low_index, high_index);
		printf("Pivot element with index %d has been found out by thread %d\n",j,tid);

		struct args* arg1=new args();
		arg1->low=low_index;
		arg1->high=j-1;
		arg1->arr=arr;
		arg1->tid=2*arg->tid+1;
		//quicksort(arg1);
		pthread_create(&threads[arg1->tid],NULL,quicksort,(void *)arg1);


		struct args* arg2=new args();
		arg2->low=j+1;
		arg2->high=high_index;
		arg2->arr=arr;
		arg2->tid=2*arg->tid+1;
		//quicksort(arg2);
		pthread_create(&threads[arg2->tid],NULL,quicksort,(void *)arg2);

		pthread_join(threads[arg1->tid],NULL);
		pthread_join(threads[arg2->tid],NULL);

	}
}


int main()
{
	int arr[100];
	int n,i;

	printf("Enter the value of n\n");
	scanf("%d",&n);
	printf("Enter the %d number of elements \n",n);

	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}
	struct args* arg=new args();
	arg->low=0;
	arg->high=n-1;
	arg->arr=arr;
	arg->tid=0;
	//quicksort(arg);
	pthread_create(&threads[arg->tid],NULL,quicksort,(void *)arg);
	pthread_join(threads[arg->tid],NULL);
	printf("Elements of array after sorting \n");

	for(i=0;i<n;i++)
	{
		printf("%d\t",arr[i]);
	}

	printf("\n");
}

***************** OUTPUT *************************

pict@pict:~/CL1/A2$ g++ a2.cpp -pthread
pict@pict:~/CL1/A2$ ./a.out 
Enter the value of n
5
Enter the 5 number of elements 
5 1 67 32 45
Pivot element with index 1 has been found out by thread 0
Pivot element with index 4 has been found out by thread 1
Pivot element with index 3 has been found out by thread 3
Elements of array after sorting 
1	5	32	45	67
