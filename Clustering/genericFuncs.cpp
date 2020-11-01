#include <iostream>
#include <bits/stdc++.h> 
#include <cmath>
#include <vector>
#include "header.hpp"
using namespace std; 


bool operator<(Values & x, Values & y){
    return x.getIndex() < y.getIndex();
}

// check if value exists in a set of values
int exists(Values * neighbors, int id , int size){
	for(int i = 0; i < size; i++){
		if(neighbors[i].getHashResult() == id) return i;
	}
	return -1;
}

// check if a value exists in vector
int existsInVector(vector <Values> neighbors, int id){
	for(int i = 0; i < neighbors.size(); i++){
		if(neighbors[i].getHashResult() == id) return i;
	}
	return -1;
}

// calculate manhattan distance
int manhattanDistance(uint8_t * qImage, uint8_t * tempImage, int size){
    int distance = 0, i;
    for (i = 0; i < size; i++)
    {
        distance += abs(qImage[i] - tempImage[i]);
    }
    return distance;
}

