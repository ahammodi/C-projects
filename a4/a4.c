#include <stdio.h>
#include <stdlib.h>
/*
Ahmed Hammodi
1191299
Assignment 4
*/

typedef struct Node //struct
{
    int sum_key;
    int key[3];
    int content[7];
} node;

void swap(int *a, int *b) //swap two elements
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

void heapify(node rowKey[], int n, int i) //function to heapify the array
{
    int smallest = i; //smallest index as root
    int left = 2 * i+1; //left child node
    int right = 2 * i+2; //right child node

    //compare the two child nodes to determine which one is smallest
    if (left < n && rowKey[left].sum_key < rowKey[smallest].sum_key)
    {
        smallest = left;

    }
    if (right < n && rowKey[right].sum_key < rowKey[smallest].sum_key)
    {
        smallest = right;

    }

    // if statement compares the larger child node with the parent
    if (smallest != i)
    {
        swap(&rowKey[i].sum_key, &rowKey[smallest].sum_key); //swap parent node with child node
        for (int j = 0; j < 3; j++)
        {
            swap(&rowKey[i].key[j], &rowKey[smallest].key[j]); //swap parent node with child node
        }
        for (int k = 0; k < 7; k++)
        {
            swap(&rowKey[i].content[k], &rowKey[smallest].content[k]); //swap parent node with child node
        }
        heapify(rowKey, n, smallest); //recursively calls heapify function to heapify sub-tree
    }
}
void buildHeap(node rowKey[], int n) //builds min-heap from parameters
{
    int lastNonLeaf = (n / 2) - 1; //gets index number of last non-leaf node
    for (int i = lastNonLeaf; i >= 0; i--) //transverses from non-last leaf node to root node to heapify
    {
        heapify(rowKey, n, i);
    }
}
int* getArr(int array[20][10])
{
    FILE *file;
    file = fopen("f.dat", "r");
    if (file == NULL) //error message
    {
        printf("Error with opening file");
        return 1;
    }

    int f = 0;

    while(!feof(file) && !ferror(file)) //runs until file ends or error occurs
    {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (fscanf(file, "%d", &f) != NULL)
                {
                    array[i][j] = f;
                }
            }
        }
        break;
    }
    fclose(file);
    return array;

}
void createValues(int array[20][10], node rowKey[20]) //function that translates values from array to array struct
{
    int counter = 0;
    for (int i = 0; i < 20; i++)
    {
        node temp;
        int k = 0;
        int keys[3];
        int arrValue[10];
        for (int j = 0; j < 10; j++)
        {
            if (j < 3) //if index value less than 3, it is key
            {
                k += array[i][j]; //add key value to sum of key
                keys[j] = array[i][j]; //add key value to keys
            }
            else
            {
                arrValue[j-3] = array[i][j]; //add content value to contents
            }
        }
        //copy everything to struct
        temp.sum_key = k;
        for (int i = 0; i < 3; i++)
        {
            temp.key[i] = keys[i]; 
        }
        for (int j = 0; j < 7; j++)
        {
            temp.content[j] = arrValue[j];
        }

        rowKey[counter] = temp;
        counter++;
    }
}
void printArray(node rowKey[]) //prints out contents of array
{
    for (int k = 0; k < 20; k++)
    {
        for (int i = 0; i < 3; i++)
        {
            printf("%d ", rowKey[k].key[i]);
        }
        for (int j = 0; j < 7; j++)
        {
            printf("%d ", rowKey[k].content[j]);
        }
        printf("\n");
    }
}
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		int array[20][10]; //2D array
		node rowKey[20]; //Array that stores each row in file
		getArr(array); //gets values from f.dat file
		createValues(array, rowKey);
		buildHeap(rowKey, 20); //start heapifying
		printArray(rowKey); //prints out arrays after heapification
	}
	else
	{
		printf("Error");
	}

	return 0;
}


