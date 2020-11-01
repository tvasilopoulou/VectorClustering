#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm> 
#include <list> 
#include <bits/stdc++.h> 
#include "classes.hpp"
#include "clustering_functions.hpp"

/*./cluster -i train-images.idx3-ubyte -c cluster.conf -o output.txt -complete -m Classic */

using namespace std;

int main(int argc, char * argv[]){
	int i;
	// argument check
	if (argc > 10 || argc < 9)
	{
		cout << ("Please try running ./cluster again. Number of arguments was different than expected.\n");
		return -1;
	}

	char * inputFile, * configFile, * outputFile, * method;
	int complete = 0, flag = 0;

	for (i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			inputFile=(char *)malloc(sizeof(argv[i+1] + 1)); 
			strcpy(inputFile, argv[i+1]);
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			configFile = (char *)malloc(sizeof(argv[i+1] + 1)); 
			strcpy(configFile, argv[i+1]);
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			outputFile = (char *)malloc(sizeof(argv[i+1] + 1)); 
			strcpy(outputFile, argv[i+1]);
		}
		else if (strcmp(argv[i], "-complete") == 0)
		{
			complete = 1;
		}
		else if (strcmp(argv[i], "-m") == 0)
		{
			if ((strcmp(argv[i+1], "Classic") == 0) || (strcmp(argv[i+1], "LSH") == 0) || (strcmp(argv[i+1], "Hypercube") == 0))
			{
				method = (char *)malloc(sizeof(argv[i+1] + 1)); 
				strcpy(method, argv[i+1]);
				}
			else
			{
				cout << ("Please try running ./cluster again. Invalid method has been chosen.\n");
				return -1;
			}
		}
		
	}

	cout << inputFile << " " << configFile << " " << outputFile << " " << complete << " " << method << endl;

    /////////////////////////////////////////////////////////////////////////////
	
	// read cluster configuration file and get the values included
	int K, L, k, M, kHypercube, probes, lineConuter = 0;
	
	ifstream configF(configFile, ios::in);

	char lineCopy[50];
	string line;
	char * token;
	
	if (!configF.is_open()) 
	{
		perror("Error while opening config file");
		exit(EXIT_FAILURE);
	}

	while (getline(configF, line))
	{
    	strcpy(lineCopy, line.c_str());
    	token = strtok(lineCopy, ":");
    	token = strtok(NULL, ": ");
    	lineConuter++;
    	switch (lineConuter)
    	{
			case 1:
				K = atoi(token);
				break;
			case 2:
				L = atoi(token);
				break;
			case 3: 
				k = atoi(token);
				break;
			case 4:
				M = atoi(token);
				break;
			case 5:
				kHypercube = atoi(token);
				break;
			case 6:
				probes = atoi(token);
				break;
			default:
				break;
		}

    }
    configF.close();
    cout << K << " " << L << " " << k << " " << M << " " << kHypercube << " " << probes << endl;
    /////////////////////////////////////////////////////////////////////////////
	
	// read the first 4 line of input file to retireve metadata
	int w = 4000;
	int magicNum, numOfImages, dx, dy;
	ifstream inputF(inputFile, ios::in | ios::binary);
	// if (inputF.is_open()){
	for (i = 0; i < 4; i++)
	{
		uint8_t buffer[4] = {0};
		inputF.read((char*)buffer, sizeof(buffer));
		unsigned int result = buffer[0];
		result = (result << 8) | buffer[1];
		result = (result << 8) | buffer[2];
		result = (result << 8) | buffer[3];
		switch (i)
		{
			case 0:
				magicNum = result;
				break;
			case 1:
				numOfImages = result;
				break;
			case 2: 
				dx = result;
				break;
			case 3:
				dy = result;
				break;
			default:
				break;
		} 
	}
    cout << magicNum << " " << numOfImages << " " << dx << " " << dy << endl;
    /////////////////////////////////////////////////////////////////////////////

    int dimensions = dx*dy;	
	vector <Image*> imagesVector;
	uint8_t * imagesArray[numOfImages];
	uint8_t * buffer;
	i = 0;
	
	ofstream outputF(outputFile, ios::out);
  	outputF << "Algorithm: " << method << endl;


	// read input file to retrieve images
	while (i!=numOfImages)
	{
		buffer = new uint8_t[dimensions];					
		inputF.read((char*)buffer, dimensions);	
		imagesVector.push_back(new Image(i, buffer, dimensions));
		i++;

	}
	delete buffer;
	inputF.close();
    /////////////////////////////////////////////////////////////////////////////

	// run kmeans++ initialization
	vector <Image*> initalCentroids = kMeansInitialization(imagesVector, L, K, numOfImages, dimensions);

	// use the initial centroids produced by kmeans++ for Lloyd's algorithm
	// vector <Image*> updatedCentroids = LloydsAlgorithm(imagesVector, initalCentroids, numOfImages);
	// vector<Cluster *> clusterSet = LloydsAlgorithm(imagesVector, initalCentroids, numOfImages);

	// vector<double> si = Silhouette(clusterSet, imagesVector);
	vector<double> si = {0.0};

	// PrintResults(outputF, clusterSet, si, imagesVector, complete);

	vector <Image *> centroidsReverse = initalCentroids;
	reverseAssignmentLSH(initalCentroids, imagesVector, L, k);
	initalCentroids = centroidsReverse;
	// reverseAssignmentCube(initalCentroids, imagesVector, M, kHypercube, probes);
	outputF.close();

	// clear vectors, free variables and return
	initalCentroids.clear();
	// updatedCentroids.clear();
	free(inputFile);
	free(outputFile);
	free(configFile);
	free(method);
	
	return 0;
}


