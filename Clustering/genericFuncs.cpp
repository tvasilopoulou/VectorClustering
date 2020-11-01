#include <iostream>
#include <bits/stdc++.h> 
#include <cmath>
#include <vector>
#include "header.hpp"
using namespace std; 


bool operator<(Values & x, Values & y){
    return x.getIndex() < y.getIndex();
}


/*brute force calculations*/
// vector <int> calculateDistances(uint8_t * qImage, int dimensions, vector <uint8_t *> imageVector, int N){
// 	vector <int> distances;
// 	for (auto &image : imageVector){
// 		if(qImage!=image) distances.push_back(manhattanDistance(qImage, image, dimensions));
// 	}
// 	sort(distances.begin(),distances.end());
// 	return distances;
// }

// int hammingDistance(int n1, int n2) { 
// 	int x = n1 ^ n2; 
// 	int setBits = 0; 
// 	while (x > 0) { 
// 		setBits += x & 1; 
// 		x >>= 1; 
// 	} 
// 	return setBits; 
// } 

int exists(Values * neighbors, int id , int size){
	for(int i = 0; i < size; i++){
		if(neighbors[i].getHashResult() == id) return i;
	}
	return -1;
}

int existsInVector(vector <Values> neighbors, int id){
	for(int i = 0; i < neighbors.size(); i++){
		if(neighbors[i].getHashResult() == id) return i;
	}
	return -1;
}

int manhattanDistance(uint8_t * qImage, uint8_t * tempImage, int size){   //size = dims
    int distance = 0, i;
    for (i = 0; i < size; i++)
    {
        distance += abs(qImage[i] - tempImage[i]);
    }
    return distance;
}

