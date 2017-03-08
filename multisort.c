#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* the number of threads required are 3:- 2 to sort, and 1 to merge */
#define THREADS 3

/* function prototypes */
void* sort(void *params);
void* merge(void *params);

/* array to store the values input by the user */
int *array;

/* array to store the sorted values */
int *sortedArray;

/* struct to store the START of the thread */
typedef struct	{
	int start;
	int end;
} parameters;


int main(int argc, char **argv)	{

	/* thread ID declaration */
	pthread_t sortThread[THREADS];

	/* variable to store the SIZE of array, and a looping variable */
	int SIZE=argc-1,i;

	if(argc==1)	{
		printf("Usage: ./a.out <array elements separated by spaces>\n\n");
		exit(0);
	}
	
	/* allocating necessary space to the int pointers to store array elements */
	array = (int *) malloc(SIZE*sizeof(int));
	sortedArray = (int *) malloc(SIZE*sizeof(int));
	
	//storing the 
	for(i=0 ; i<SIZE ; i++)
		array[i] = atoi(argv[i+1]);

	
	/* The first half of the array goes into the first thread to get sorted */
	parameters *firstHalf = (parameters *) malloc(sizeof(parameters));
	firstHalf->start = 0;
	firstHalf->end = SIZE/2;

	/* 1st thread is created with tid=sortThread[0]*/
	pthread_create(&sortThread[0],NULL,sort,firstHalf);
	
	
	/* The second half of array goes into the second thread to get sorted */
	parameters *secondHalf = (parameters *) malloc(sizeof(parameters));
	secondHalf->start = (SIZE/2);
	secondHalf->end = SIZE;	

	/* 2nd thread is created with tid=sortThread[1]*/
	pthread_create(&sortThread[1],NULL,sort,secondHalf);
	
	
	/* wait till both halves are sorted */
	pthread_join(sortThread[0],NULL);
	pthread_join(sortThread[1],NULL);
	
	
	/* whole size of the array is given to the sortedArray thread */
	parameters *fullArray = (parameters *) malloc(sizeof(parameters));
	fullArray->start = 0;
	fullArray->end   = SIZE;

	/* 3rd thread is created with tid=sortThread[2] */
	pthread_create(&sortThread[2],NULL,merge,fullArray);	
	
	/* wait whole array is merged */
	pthread_join(sortThread[2],NULL);
	
	/* Prints the sorted array */
	printf("\nThe sorted array is: \n");
	for(i=0 ; i<SIZE ; i++)
		printf("sortedArray[%d] = %d\n",i,sortedArray[i]);
	printf("\n\n");
}//end of main()

/* The sorting logic to be used by the threads to sort the halves: BUBBLE SORT */
void* sort(void *params)	{

	/* local variable to store the lower and upper bounds of the array to be sorted */
	parameters *p = (parameters *)params;	
	int begin = p->start;
	int   end = p->end;
	
	int i,j,temp;
	
	for (i = begin; i < end; ++i)	{
		for (j = i + 1; j < end; ++j)	{
         if (array[i] > array[j])	{
		     		 temp = array[i];
            array[i] = array[j];
            array[j] = temp;
         }//if ends
      }//inner-for ends
   }//outer-for ends
}//end of sort()


/* The merging logic to be used by the thread to merge the sorted halves */
void* merge(void *params)	{

	/* local variable to store the lower and upper bounds provided */
	parameters *p = (parameters *)params;
	
	int 	  first = p->start;
	int fhalf_end = p->end/2;
	int 		last = p->end;
	int shalf_end = last;
	
	int i = first;
	int j = fhalf_end;
	int k;
			
	/* Merges both the sorted halves */
	for(k=0 ; k<last ; k++)	{
		
		if(i>=fhalf_end || j>=shalf_end)
			break;

		//left-half element lesser than right-half element			
		if(array[i]<array[j])
			sortedArray[k]=array[i++];
			
		//left-half element greater than right-half element	
		else if(array[i]>array[j])
			sortedArray[k]=array[j++];
		
		else	{
			sortedArray[k++]=array[j++];
			sortedArray[k]=array[i++];
		}
	}//for-loop ends

	/* Adds the remaining elements */
	while(i<fhalf_end)
		sortedArray[k++]=array[i++];
		
	while(j<shalf_end)
		sortedArray[k++]=array[j++];
}//end of merge()
