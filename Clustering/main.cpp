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

	/* ARGUMENT CHECK */
	if (argc > 10 || argc < 9)
	{
		cout << ("Please try running ./cluster again. Number of arguments was different than expected.\n");
		return -1;
	}

	char * inputFile, * configFile, * outputFile, * method;
	int complete = 0, flag = 0;
	// int k, L, N, complete;
	// double R;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			inputFile=(char *)malloc(sizeof(argv[i+1] + 1)); 
			strncpy(inputFile, argv[i+1], strlen(argv[i+1]) + 1);
		}
		else if (strcmp(argv[i], "-c") == 0)
		{
			configFile = (char *)malloc(sizeof(argv[i+1] + 1)); 
			strncpy(configFile, argv[i+1], strlen(argv[i+1]) + 1);
		}
		else if (strcmp(argv[i], "-o") == 0)
		{
			outputFile = (char *)malloc(sizeof(argv[i+1] + 1)); 
			strncpy(outputFile, argv[i+1], strlen(argv[i+1]) + 1);
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
				strncpy(method, argv[i+1], strlen(argv[i+1]) + 1);
				}
			else
			{
				cout << ("Please try running ./cluster again. Invalid method has been chosen.\n");
				return -1;
			}
		}
		
	}

	cout << inputFile << " " << configFile << " " << outputFile << " " << complete << " " << method << endl;

	/*END OF ARGUMENT CHECK*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/
	
	/*READ CLUSTER CONFIGURATION FILE AND GET THE VALUES OF THE INCLUDED VARIABLES*/ 
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

	while(getline(configF, line))
	{
    	strcpy(lineCopy, line.c_str());
    	token = strtok(lineCopy, ":");
    	token = strtok(NULL, ": ");
    	lineConuter++;
    	switch(lineConuter){
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
	/*END OF CONFIG FILE READ*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/
	
	/*READ FIRST 4 LINES OF INPUT FILE TO RETRIEVE METADATA*/
	int w = 4000;
	int magicNum, numOfImages, dx, dy;
	ifstream inputF(inputFile, ios::in | ios::binary);
	// if (inputF.is_open()){
	for(int i=0; i<4; i++){
		uint8_t buffer[4] = {0};
		inputF.read((char*)buffer, sizeof(buffer));
		unsigned int result = buffer[0];
		result = (result << 8) | buffer[1];
		result = (result << 8) | buffer[2];
		result = (result << 8) | buffer[3];
		switch(i){
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
	/*END OF METADATA RETRIEVAL*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/
    
    int dimensions = dx*dy;
    
 //    // obtain a random number from hardware
 //    random_device rd;
 //    // seed the generator
	// mt19937 gen(rd());
	// uniform_int_distribution<> distr(0, numOfImages);
 //    int initialCentroid = distr(gen);
    
 //    cout << initialCentroid << endl;

    int i = 0;
	
	// uint8_t centralImage[dimensions] = {0};
	// inputF.seekg(dimensions*initialCentroid);
	// inputF.read((char*)centralImage, sizeof(centralImage));
	
	// cout << (long int )(centralImage) << endl;
	
	inputF.seekg(4*sizeof(int));
	
	vector <Image*> imagesVector;
	uint8_t * imagesArray[numOfImages];

	uint8_t * buffer;

	while(i!=numOfImages)
	{
		buffer = new uint8_t[dimensions];					
		inputF.read((char*)buffer, dimensions);	
		imagesVector.push_back(new Image(i, buffer, dimensions));
		i++;
	}


	vector <Image*> initalCentroids = kMeansInitialization(imagesVector, L, K, numOfImages, dimensions);
	// for (int i = 0; i < numOfImages; i++)
	// {
	// 	cout << (long int)imagesVector[i]->getVal() << endl;
	// }
	
	inputF.close();


	return 0;
}


