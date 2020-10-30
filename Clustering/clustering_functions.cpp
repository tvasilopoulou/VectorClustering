#include <iostream>
#include <bits/stdc++.h> 
#include <cmath>
#include "classes.hpp"
#include "clustering_functions.hpp"

using namespace std; 

int manhattanDistance(uint8_t * qImage, uint8_t * tempImage, int size){   //size = dims
  int distance = 0;
  for (int i=0; i<size; i++){
    distance += abs(qImage[i] - tempImage[i]);
  }
  return distance;
}


vector<Image*> kMeansInitialization(vector<Image*> images, int iterations, int k, int numOfImages, int dimensions){
	
	vector<Image*> centroids;
	// obtain a random number from hardware
    random_device rd;
    // seed the generator
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, numOfImages);
    int initialCentroid = distr(gen);
		
	centroids.push_back(images[initialCentroid]);

    vector<int> distances;
    vector<int> partialSum;
    int t = 1;
    // int maxDist = -1;
   	while (t != k)
   	{
   		distances.clear();
   		partialSum.clear();

		int flag;
   		for(int i = 0; i < numOfImages; i++)
   	   	{
   			flag = 0;
		   	for(int c = 0; c < centroids.size() ; c++)
		   	{
		   		if( images[i]->getID() == centroids[c]->getID())
		   		{
		   			flag = 1;
		   			break;
		   		}
		   	}
		   	
		   	if (i == initialCentroid || flag == 1)
		   	{
		   		continue;
		   	}
   			distances.push_back(manhattanDistance(images[initialCentroid]->getVal(), images[i]->getVal(), dimensions));   	   		
   	   	}
   		int maxDist = *max_element(distances.begin(), distances.end());
   		int sum = 0;
   	   	for (int j = 0; j < numOfImages; j++)
   		{
   			flag = 0;
		   	for(int c = 0; c < centroids.size() ; c++)
		   	{
		   		if( images[j]->getID() == centroids[c]->getID()){
		   			flag = 1;
		   			break;
		   		}
		   	}
		   	
		   	if (j == initialCentroid || flag == 1)
		   	{
		   		continue;
		   	}

   			sum += (distances[j]/maxDist)*distances[j];
   			partialSum.push_back(sum);
   		}
   	
   	   	double end = *max_element(partialSum.begin(), partialSum.end());
   	   	uniform_real_distribution<double> distrD(0.0, end);
   	    
   	    int x = distrD(gen);
   	    int nextCentroid;
   	    for (int r = 0; r < partialSum.size(); r++)
   	    {
   	    	if (x > partialSum[r] && x <= partialSum[r + 1])
   	    	{
   	    		nextCentroid = r + 1;
   	    	}
   	    }
    	initialCentroid = nextCentroid;
		centroids.push_back(images[nextCentroid]);
   	    t++;
   	}
    
   	for (int i = 0; i < centroids.size(); ++i)
   	{
    	cout << "centroid " << centroids[i]->getID() << endl;
   		
   	}

	// cout << "size centroid " << centroids.size() << endl;

	return centroids;
}