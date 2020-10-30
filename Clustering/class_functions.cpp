#include <iostream>
#include <iterator> 
#include <string>
#include <map>
#include <utility>      // std::pair
#include <ctime> 
#include <vector> 
#include <cmath> 
#include <algorithm> 
#include <bits/stdc++.h> 

#include "classes.hpp"

using namespace std;


Image::Image(int id, uint8_t * image, int dimensions){
    this->dimensions = dimensions;
    this->imageId = id;
    this->minDist = 10000000000;
    this->image = image;
    this->clusterId = 0; //Initially not assigned to any cluster
}
uint8_t * Image::getVal(){
	return this->image;
}
int Image::getDimensions(){
    return dimensions;
}

int Image::getCluster(){
    return clusterId;
}

int Image::getID(){
    return imageId;
}

void Image::setCluster(int val){
    clusterId = val;
}
