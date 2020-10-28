#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm> 
#include <list> 
#include <bits/stdc++.h> 
#include "header.hpp"
#include "funcHeader.hpp"

/*./main -d train-images.idx3-ubyte -o output.txt -q t10k-images.idx3-ubyte -k 4 -L 5 -R 0.1 -N 3 */

using namespace std;

int main(int argc, char * argv[]){
	// while(1){
	if (argc > 15 || argc < 7 || argc % 2 != 1)
	{
		cout << ("Please try running LSH again. Number of arguments was different than expected.\n");
		return -1;
	}
    //check arguements in pairs
	if ((strcmp(argv[1],"-d") && strcmp(argv[3],"-d") && strcmp(argv[5],"-d") && strcmp(argv[7],"-d") && strcmp(argv[9],"-d") && strcmp(argv[11],"-d") && strcmp(argv[13],"-d"))
	|| (strcmp(argv[1],"-q") && strcmp(argv[3],"-q") && strcmp(argv[5],"-q") && strcmp(argv[7],"-q") && strcmp(argv[9],"-q") && strcmp(argv[11],"-q") && strcmp(argv[13],"-q"))
	|| (strcmp(argv[1],"-o") && strcmp(argv[3],"-o") && strcmp(argv[5],"-o") && strcmp(argv[7],"-o") && strcmp(argv[9],"-o") && strcmp(argv[11],"-o") && strcmp(argv[13],"-o")))
	{
		cout << ("Please try running LSH again. Arguments given were either in the wrong order, or incorrect.\n");
		return -2;
	}

	char * inputFile, * queryFile, * outputFile;
	int k, L, N;
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
	else k=4;

/*-L*/
	if (!(strcmp(argv[1],"-L"))) L=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-L"))) L=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-L"))) L=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-L"))) L=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-L"))) L=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-L"))) L=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-L"))) L=atoi(argv[14]);	
	else L=5;

/*-N*/
	if (!(strcmp(argv[1],"-N"))) N=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-N"))) N=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-N"))) N=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-N"))) N=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-N"))) N=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-N"))) N=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-N"))) N=atoi(argv[14]);	
	else N=4;

/*-R*/
	if (!(strcmp(argv[1],"-R"))) R=atof(argv[2]);
	else if (!(strcmp(argv[3],"-R"))) R=atof(argv[4]);
	else if (!(strcmp(argv[5],"-R"))) R=atof(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-R"))) R=atof(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-R"))) R=atof(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-R"))) R=atof(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-R"))) R=atof(argv[14]);	
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
	HashMap * hashMap = new HashMap(L, fixedInd, k, dimensions, w, N);

	random_device rd; // obtain a random number from hardware
	mt19937 gen(rd()); // seed the generator
	uniform_int_distribution<> distr(0, dimensions);

	while(!inputF.eof()){
		uint8_t buffer[dimensions] = {0};					//q
		inputF.read((char*)buffer, sizeof(buffer));
		imagesArray[i] = buffer;
		for(int j=0; j<L; j++)
			hashMap->getHashTableByIndex(j)->hashFunctionG(w, dimensions,buffer, i); 
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

	uint8_t * queryImages[numOfImages];
	i=0;

	ofstream outputF;
	outputF.open (outputFile);

	// dimensions = dx*dy;
	while(!queryF.eof()){
		uint8_t buffer[dimensions] = {0};					//q
		queryF.read((char*)buffer, sizeof(buffer));
		queryImages[i] = buffer;
		Values * neighbors = hashMap->ANN(queryImages[i]);
		// Values * neighborsInRange = hashMap->ARangeSearch(queryImages[i], R);
		outputF << "Query: " << i << endl;
		for(int j=0; j<N; j++){
			// if(neighbors[j].getIndex()>0)
				outputF << "Nearest neighbor-" << j+1 << ": " << neighbors[j].getHashResult() << endl << endl;
		}

		i++;
	}



	delete hashMap;

	/*cout << "Run finished, would you like to continue?(Y/n): " ;
	char * prompt;
	cin >> prompt; 
	while(1){
		if(prompt == "n") return 0;
		else if(prompt == "Y") break;
		else continue;
	}
	}*/
	return 0;
}

