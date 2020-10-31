#include <iostream>
#include <bits/stdc++.h> 
#include <cmath>
#include "classes.hpp"
#include "clustering_functions.hpp"

using namespace std; 

int manhattanDistance(uint8_t * qImage, uint8_t * tempImage, int size){   //size = dims
    int distance = 0, i;
    for (i = 0; i < size; i++)
    {
        distance += abs(qImage[i] - tempImage[i]);
    }
    return distance;
}


vector<Image*> kMeansInitialization(vector<Image*> images, int iterations, int k, int numOfImages, int dimensions){
	
    vector<int> centroidsIds;
	vector<Image*> centroids;
	
    // randomly choose the first centroid
    
    // obtain a random number from hardware
    random_device rd;
    // seed the generator
	mt19937 gen(rd());
	uniform_int_distribution<> distr(0, numOfImages-1);
    int centroidId = distr(gen);
    
    // add the initial centroid to a vector	
	centroids.push_back(images[centroidId]);
    // keep the centroid ID to a vector
    centroidsIds.push_back(centroidId);
    /////////////////////////////////////////////////////////////////////////////
    
    vector<int> distances;
    vector<double> partialSum;
    
    int t = 1;
   	// for each cluster
    while (t != k)
   	{
   		distances.clear();
   		partialSum.clear();

   		for(int i = 0; i < numOfImages; i++)
 	   	{     
            // for non centroids calculate the manhattan distance from centroid 
      	   	if (i == centroidId || (find(centroidsIds.begin(), centroidsIds.end(), i) != centroidsIds.end()))
      	   	{
      	   		distances.push_back(-1);
      	   	}
            else
            {
       		   distances.push_back(manhattanDistance(images[centroidId]->getVal(), images[i]->getVal(), dimensions));
            }
            /////////////////////////////////////////////////////////////////////////////
        }
   		
        // keep the max distance in order to calculate partial sums
        int maxDist = *max_element(distances.begin(), distances.end());
   		double sum = 0.0;
   	    
        // for each distance calculated compute the partial sum
        for (int j = 0; j < distances.size(); j++)
   		{
            if (distances[j] == -1)
            {
                partialSum.push_back(sum);   
            }
            else
            {
                sum += ((double)distances[j]/(double)maxDist)*((double)distances[j]);
                partialSum.push_back(sum);
            }
   		}
        /////////////////////////////////////////////////////////////////////////////
        
        // pick a random float in range 0 - maximum partial sum   	
   	   	double maxPartialSum = *max_element(partialSum.begin(), partialSum.end());
   	   	uniform_real_distribution<double> distrD(0.0, maxPartialSum - 1);
   	    double x = distrD(gen); 
        /////////////////////////////////////////////////////////////////////////////
   	    
        // find the next centroid routine
        int nextCentroid;
             
        if (x < partialSum[0])
        {
            nextCentroid = 0;
        }
        else{
            for (int r = 0; r < partialSum.size() - 1; r++)
            {               
                if (x > partialSum[r] && x <= partialSum[r + 1])
                {
                    nextCentroid = r + 1;
                }
            }
        }
		centroids.push_back(images[nextCentroid]);
        centroidsIds.push_back(nextCentroid);
    	centroidId = nextCentroid;
        /////////////////////////////////////////////////////////////////////////////

   	    t++;
   	}
    
	return centroids;
}


double CalculateMedianDistance(vector<Image *> data){
    
    // find the mean of min distances
    double medianDist = 0.0;
    int i;
    for (i = 0; i < data.size(); ++i)
    {
        medianDist += (double)data[i]->getMinDist()/(double)data.size();
    }
    /////////////////////////////////////////////////////////////////////////////

    return medianDist;
}

void InitializeClusters(vector<Image *> centroids, vector<Cluster *> *clusters){
    // initialize all clusters of cluster vector
    int c;
    for (c = 0; c < centroids.size(); c++)
    {
        Cluster * newCluster = new Cluster(centroids[c]);
        clusters->push_back(newCluster);
    }
    /////////////////////////////////////////////////////////////////////////////
    return;
}


vector<Image *>  LloydsAlgorithm(vector<Image *> images, vector<Image *> centroids, int numOfImages)
{
    vector<Image *> updatedCentroids;
    vector<Cluster *> clusters;
    
    int i, c, p;
    
    // base step
    double percentage = 1.0;
    double medianDistance = CalculateMedianDistance(images);
    
    while (percentage > 0.5)
    {
        double currentMedian;

        InitializeClusters(centroids, &clusters);

        // assign images to clusters
        for (i = 0; i < numOfImages; i++)
        {
            int min1 = 10000000;
            int min2 = min1;
            int id1, id2;

            for (c = 0; c < centroids.size(); c++)
            {
                // if the image is not a centroid itself
                if (images[i]->getID() == centroids[c]->getID())
                {
                    continue;
                }
                // calculate the image's distances from centroid
                int dist = manhattanDistance(centroids[c]->getVal(), images[i]->getVal(), images[i]->getDimensions());
                
                // find minimum
                if (dist >= min1 && dist < min2)
                {
                    min2 = dist;
                    id2 = c;
                }
                if (dist < min1)
                {
                    min1 = dist;
                    id1 = c;
                }
                /////////////////////////////////////////////////////////////////////////////

            }

            // update the corresponing fields of object
            images[i]->setCluster(id1);
            images[i]->setMinDist(min1);
            images[i]->setSecondNearestCentroid(id2);
            images[i]->setSecondMinDist(min2);
            /////////////////////////////////////////////////////////////////////////////

        } 
        /////////////////////////////////////////////////////////////////////////////

        // keep the images that are assigned to each cluster     
        for (int c = 0; c < clusters.size(); c++)
        {
            for (i = 0; i < numOfImages; i++)
            {
                if (images[i]->getCluster() == c)
                {      
                    (clusters[c]->getImagesVector())->push_back(images[i]->getVal());
                }
            }
        }
        /////////////////////////////////////////////////////////////////////////////
        
        int dimensions = centroids[0]->getDimensions();
        for (c = 0; c < clusters.size(); c++)
        {  
            int median;
            uint8_t * newCentroid = new uint8_t[dimensions];
            // cout << "clusters size "<< (*clusters[c]->getImagesVector()).size() << endl;
            for (i = 0; i < dimensions; i++)
            {
                vector<uint8_t> newPixel;
                // keep the i-th pixels of all images that are assigned to the cluster
                for (p = 0; p < (*clusters[c]->getImagesVector()).size(); p++)
                {
                    uint8_t * tempImage = (*clusters[c]->getImagesVector())[p];
                    newPixel.push_back(tempImage[i]);
                }
                /////////////////////////////////////////////////////////////////////////////

                // sort the pixel vector and keep the median index
                sort(newPixel.begin(), newPixel.end());
                median = ceil((double)newPixel.size()/2.0);

                // assign the new pixel arrangement to the new image
                newCentroid[i] = newPixel[median];     
            }

            // add the new image to centroids
            Image * newClusterCenter = new Image(-1, newCentroid, dimensions);
            updatedCentroids.push_back(newClusterCenter);
        }
        /////////////////////////////////////////////////////////////////////////////
        
        // cout << "antio tommy " << endl; 
        
        // calculate new percetange
        currentMedian = CalculateMedianDistance(images);
        percentage = (double)(abs(currentMedian - medianDistance)/(double)medianDistance);
        medianDistance = currentMedian;
        /////////////////////////////////////////////////////////////////////////////

        // assign new current centroids set and proceed to next loop
        centroids.clear();
        centroids = updatedCentroids;
        
        updatedCentroids.clear();
        clusters.clear();        
    }

    cout << "assignment done " << endl;
    return updatedCentroids;
}
