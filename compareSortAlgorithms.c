#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void merge(int pData[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    //temporary arrays
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = pData[l + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = pData[m + 1 + j];
    }

    // Merge the temporary arrays back into pData
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            pData[k] = L[i];
            i++;
        }
        else {
            pData[k] = R[j];
            j++;
        }
        extraMemoryAllocated += sizeof(int);
    }

    // Copying the remaining elements of L[] if any
    while (i < n1) {
        pData[k] = L[i];
        i++;
        k++;
        extraMemoryAllocated += sizeof(int);
    }

    // Copying the remaining elements of R[] if any
    while (j < n2) {
        pData[k] = R[j];
        j++;
        k++;
        extraMemoryAllocated += sizeof(int);
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);

        merge(pData, l, m, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = pData[i];
        j = i - 1;

        while (j >= 0 && pData[j] > key) {
            pData[j + 1] = pData[j];
            j = j - 1;
            extraMemoryAllocated += sizeof(int);
        }
        pData[j + 1] = key;
        extraMemoryAllocated += sizeof(int);
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        // Last i elements are already sorted
        for (j = 0; j < n - i - 1; j++) {
            if (pData[j] > pData[j + 1]) {
                temp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = temp;
                extraMemoryAllocated += sizeof(int);
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int i, j, minski;
    extraMemoryAllocated += sizeof(int);
 
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        minski = i;
        extraMemoryAllocated += sizeof(int);

        for (j = i+1; j < n; j++)
        {
            if (pData[j] < pData[minski])
            {
                minski = j;
                extraMemoryAllocated += sizeof(int);
            }
        }

        // Swap the found minimum element with the first element
        int temp = pData[minski];
        pData[minski] = pData[i];
        pData[i] = temp;
        extraMemoryAllocated += (2 * sizeof(int));
    }
}

// parses input file to an integer array
int parseData(char* inputFileName, int** ppData) {
    FILE* inputFile;
    int dataSize = 0;
    int* pData = NULL;
    
    // Open it
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error: unable to open input file '%s'\n", inputFileName);
        return -1;
    }
    
    // Read data size
    if (fscanf(inputFile, "%d", &dataSize) != 1) {
        printf("Error: unable to read data size from input file '%s'\n", inputFileName);
        fclose(inputFile);
        return -1;
    }
    
    // Allocate it
    pData = (int*)malloc(dataSize * sizeof(int));
    if (pData == NULL) {
        printf("Error: unable to allocate memory for data\n");
        fclose(inputFile);
        return -1;
    }
    
    // Read it
    for (int i = 0; i < dataSize; i++) {
        if (fscanf(inputFile, "%d", &pData[i]) != 1) {
            printf("Error: unable to read data element %d from input file '%s'\n", i, inputFileName);
            free(pData);
            fclose(inputFile);
            return -1;
        }
    }
    
    fclose(inputFile);
    
    *ppData = pData;
    
    return dataSize;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}
