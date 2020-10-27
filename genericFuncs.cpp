#include <iostream>
#include <bits/stdc++.h> 
#include <cmath>
#include "header.hpp"
using namespace std; 

/*functions regarding QuickSort => GeeksForGeeks*/

void swap(int* a, int* b) { 
	int t = *a; 
	*a = *b; 
	*b = t; 
} 


int partition (int arr[], int low, int high) { 
	int pivot = arr[high]; // pivot 
	int i = (low - 1); // Index of smaller element 

	for (int j = low; j <= high - 1; j++) { 
		// If current element is smaller than the pivot 
		if (arr[j] < pivot) { 
			i++; // increment index of smaller element 
			swap(&arr[i], &arr[j]); 
		} 
	} 
	swap(&arr[i + 1], &arr[high]); 
	return (i + 1); 
} 


void quickSort(int arr[], int low, int high) 
{ 
	if (low < high){ 
		int pi = partition(arr, low, high); 
		quickSort(arr, low, pi - 1); 
		quickSort(arr, pi + 1, high); 
	} 
} 

/* Function to print an array */
void printArray(int arr[], int size){ 
	for (int i = 0; i < size; i++) 
		cout << arr[i] << " "; 
	cout << endl; 
} 


int manhattanDistance(uint8_t * qImage, uint8_t * tempImage, int size){		//size = dims
	int distance = 0;
	for (int i=0; i<size; i++){
		distance += abs(qImage[i] - tempImage[i]);
	}
	return distance;
}

bool operator<(Values & x, Values & y){
    return x.getIndex() < y.getIndex();
}

bool hasSpace(Values * neighbors, int k){
	if(neighbors[k-1].getIndex() == -1) return true;
	else return false;
}