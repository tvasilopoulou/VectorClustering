#include <iostream>
#include <iterator> 
#include <string>
#include <map>
#include <utility>
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
    this->minDist = 0;
    this->secondNearestCentroid = 0;
    this->secondMinDist = 0;
    this->image = image;
    //initially not assigned to any cluster
    this->clusterId = 0;
}
uint8_t * Image::getVal(){
	return this->image;
}
int Image::getDimensions(){
    return this->dimensions;
}

int Image::getCluster(){
    return this->clusterId;
}

int Image::getID(){
    return this->imageId;
}

int Image::getMinDist(){
    return this->minDist;
}

void Image::setCluster(int val){
    this->clusterId = val;
}

void Image::setMinDist(int val){
    this->minDist = val;
}
void Image::setSecondNearestCentroid(int val){
    this->secondNearestCentroid = val;
}
void Image::setSecondMinDist(int val){
    this->secondMinDist = val;
}


Cluster::Cluster(Image * centroidImage){
    this->cluster = centroidImage;
}

vector<uint8_t *> * Cluster::getImagesVector(){
    return &(this->imagesInCluster);
}

Image * Cluster::getCluster(){
    return this->cluster;
}


