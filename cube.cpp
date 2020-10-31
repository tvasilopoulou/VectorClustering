#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm> 
#include <list> 
#include <vector>
#include <bits/stdc++.h> 
#include "header.hpp"
#include "funcHeader.hpp"

/*./main -d train-images.idx3-ubyte -o output.txt -q t10k-images.idx3-ubyte -k 4 -L 5 -R 0.1 -N 3 */

using namespace std;

int main(int argc, char * argv[]){
	// while(1){
	if (argc > 17 || argc < 7 || argc % 2 != 1)
	{
		cout << ("Please try running Cube again. Number of arguments was different than expected.\n");
		return -1;
	}
    //check arguements in pairs
	if ((strcmp(argv[1],"-d") && strcmp(argv[3],"-d") && strcmp(argv[5],"-d") && strcmp(argv[7],"-d") && strcmp(argv[9],"-d") && strcmp(argv[11],"-d") && strcmp(argv[13],"-d"))
	|| (strcmp(argv[1],"-q") && strcmp(argv[3],"-q") && strcmp(argv[5],"-q") && strcmp(argv[7],"-q") && strcmp(argv[9],"-q") && strcmp(argv[11],"-q") && strcmp(argv[13],"-q"))
	|| (strcmp(argv[1],"-o") && strcmp(argv[3],"-o") && strcmp(argv[5],"-o") && strcmp(argv[7],"-o") && strcmp(argv[9],"-o") && strcmp(argv[11],"-o") && strcmp(argv[13],"-o")))
	{
		cout << ("Please try running Cube again. Arguments given were either in the wrong order, or incorrect.\n");
		return -2;
	}

	char * inputFile, * queryFile, * outputFile;
	int k, M, N, probes;
	double R;



/*-d*/
	//set variables assigned from input
	if (!(strcmp(argv[1],"-d"))){inputFile=(char *)malloc(sizeof(argv[2]+1)) ; strncpy(inputFile, argv[2], strlen(argv[2])+1);} 
	else if (!(strcmp(argv[3],"-d"))) { inputFile=(char *)malloc(sizeof(argv[4]+1)) ; strncpy(inputFile, argv[4], strlen(argv[4])+1); } 
	else if (!(strcmp(argv[5],"-d"))) { inputFile=(char *)malloc(sizeof(argv[6]+1)) ; strncpy(inputFile, argv[6], strlen(argv[6])+1); } 
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-d"))) { inputFile=(char *)malloc(sizeof(argv[8]+1)) ; strncpy(inputFile, argv[8], strlen(argv[8])+1); } 		
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-d"))) { inputFile=(char *)malloc(sizeof(argv[10]+1)) ; strncpy(inputFile, argv[10], strlen(argv[10])+1); } 
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-d"))) { inputFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(inputFile, argv[12], strlen(argv[12])+1); } 
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-d"))) { inputFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(inputFile, argv[12], strlen(argv[12])+1); } 


/*-q*/
	//set variables assigned from input
	if (!(strcmp(argv[1],"-q"))){queryFile=(char *)malloc(sizeof(argv[2]+1)) ; strncpy(queryFile, argv[2], strlen(argv[2])+1);} 
	else if (!(strcmp(argv[3],"-q"))) { queryFile=(char *)malloc(sizeof(argv[4]+1)) ; strncpy(queryFile, argv[4], strlen(argv[4])+1); } 
	else if (!(strcmp(argv[5],"-q"))) { queryFile=(char *)malloc(sizeof(argv[6]+1)) ; strncpy(queryFile, argv[6], strlen(argv[6])+1); } 
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-q"))) { queryFile=(char *)malloc(sizeof(argv[8]+1)) ; strncpy(queryFile, argv[8], strlen(argv[8])+1); } 		
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-q"))) { queryFile=(char *)malloc(sizeof(argv[10]+1)) ; strncpy(queryFile, argv[10], strlen(argv[10])+1); } 
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-q"))) { queryFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(queryFile, argv[12], strlen(argv[12])+1); } 
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-q"))) { queryFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(queryFile, argv[12], strlen(argv[12])+1); } 

/*-o*/
	//set variables assigned from input
	if (!(strcmp(argv[1],"-o"))){outputFile=(char *)malloc(sizeof(argv[2]+1)) ; strncpy(outputFile, argv[2], strlen(argv[2])+1);} 
	else if (!(strcmp(argv[3],"-o"))) { outputFile=(char *)malloc(sizeof(argv[4]+1)) ; strncpy(outputFile, argv[4], strlen(argv[4])+1); } 
	else if (!(strcmp(argv[5],"-o"))) { outputFile=(char *)malloc(sizeof(argv[6]+1)) ; strncpy(outputFile, argv[6], strlen(argv[6])+1); } 
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-o"))) { outputFile=(char *)malloc(sizeof(argv[8]+1)) ; strncpy(outputFile, argv[8], strlen(argv[8])+1); } 		
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-o"))) { outputFile=(char *)malloc(sizeof(argv[10]+1)) ; strncpy(outputFile, argv[10], strlen(argv[10])+1); } 
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-o"))) { outputFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(outputFile, argv[12], strlen(argv[12])+1); } 
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-o"))) { outputFile=(char *)malloc(sizeof(argv[14]+1)) ; strncpy(outputFile, argv[14], strlen(argv[14])+1); } 

/*-k*/
	if (!(strcmp(argv[1],"-k"))) k=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-k"))) k=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-k"))) k=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-k"))) k=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-k"))) k=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-k"))) k=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-k"))) k=atoi(argv[14]);	
	else if (argv[15]!=NULL && !(strcmp(argv[15],"-k"))) k=atoi(argv[16]);	
	else k=3;

/*-M*/
	if (!(strcmp(argv[1],"-M"))) M=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-M"))) M=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-M"))) M=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-M"))) M=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-M"))) M=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-M"))) M=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-M"))) M=atoi(argv[14]);	
	else if (argv[15]!=NULL && !(strcmp(argv[15],"-M"))) M=atoi(argv[16]);	
	else M=10;

/*-probes*/
	if (!(strcmp(argv[1],"-probes"))) probes=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-probes"))) probes=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-probes"))) probes=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-probes"))) probes=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-probes"))) probes=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-probes"))) probes=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-probes"))) probes=atoi(argv[14]);	
	else if (argv[15]!=NULL && !(strcmp(argv[15],"-probes"))) probes=atoi(argv[16]);	
	else probes=2;

/*-N*/
	if (!(strcmp(argv[1],"-N"))) N=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-N"))) N=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-N"))) N=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-N"))) N=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-N"))) N=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-N"))) N=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-N"))) N=atoi(argv[14]);	
	else if (argv[15]!=NULL && !(strcmp(argv[15],"-N"))) N=atoi(argv[16]);	
	else N=1;

/*-R*/
	if (!(strcmp(argv[1],"-R"))) R=atof(argv[2]);
	else if (!(strcmp(argv[3],"-R"))) R=atof(argv[4]);
	else if (!(strcmp(argv[5],"-R"))) R=atof(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-R"))) R=atof(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-R"))) R=atof(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-R"))) R=atof(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-R"))) R=atof(argv[14]);	
	else if (argv[15]!=NULL && !(strcmp(argv[15],"-R"))) R=atof(argv[16]);	
	else R=1.0;

	/*END OF ARGUMENT CHECK*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/
	int w = 400;
	int magicNum, numOfImages, dx, dy;
	string line;
	ifstream inputF(inputFile, ios::in | ios::binary);
	// if (inputF.is_open()){
	for(int i=0; i<4; i++){
		uint8_t buffer[4] = {0};
		inputF.read((char*)buffer, sizeof(buffer));
		unsigned int result = buffer[0];
		result = (result << 8) | buffer[1];
		result = (result << 8) | buffer[2];
		result = (result << 8) | buffer[3];
		// cout << result << endl;
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
// }

	int fixedInd = numOfImages/16;
	int dimensions = dx*dy;

	int i=0;
	uint8_t * imagesArray[numOfImages];
	vector <uint8_t *> imagesVector;
	HashMap * hashMap = new HashMap(1, fixedInd, k, dimensions, w, N);
	uint8_t * buffer;

	while(i<numOfImages){
		buffer = new uint8_t[dimensions];
		inputF.read((char*)buffer, sizeof(buffer));
		imagesVector.push_back(buffer);
		//add to hashTables accordingly
		hashMap->getHashTableByIndex(0)->hashFunctionCubeG(w, dimensions,buffer, i); 
		i++;
	}
	inputF.close();

	/*----------------------------------------------------------------------------------------------------------------------------------*/

	int count=0;
	ifstream queryF(queryFile, ios::in | ios::binary);
	for(int i=0; i<4; i++){
		uint8_t buffer[4] = {0};
		queryF.read((char*)buffer, sizeof(buffer));
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

	uint8_t * queryImages[numOfImages];

	for(i=0; i<numOfImages; i++){
		buffer = new uint8_t[dimensions];
		queryF.read((char*)buffer, dimensions);
 		// Values * neighbors = hashMap->ANNCube(buffer, probes);
		Values * neighbors = hashMap->ARangeSearchCube(buffer, probes, R, fixedInd);
		for(int o=0; o<20; o++) if(neighbors[o].getIndex() < R) cout<< neighbors[o].getIndex() << endl;
	}



	delete hashMap;
	return 0;
}