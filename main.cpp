#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main(int argc, char * argv[]){
	if (argc > 15 || argc < 7 || argc % 2 != 1)
	{
		cout << ("Please try running LSH again. Number of arguments was different than expected.\n");
		return -1;
	}
    //check arguements in pairs
	if ((strcmp(argv[1],"-d") && strcmp(argv[3],"-d") && strcmp(argv[5],"-d") && strcmp(argv[7],"-d") && strcmp(argv[9],"-d") && strcmp(argv[11],"-d"))
	|| (strcmp(argv[1],"-q") && strcmp(argv[3],"-q") && strcmp(argv[5],"-q") && strcmp(argv[7],"-q") && strcmp(argv[9],"-q") && strcmp(argv[11],"-q"))
	|| (strcmp(argv[1],"-o") && strcmp(argv[3],"-o") && strcmp(argv[5],"-o") && strcmp(argv[7],"-o") && strcmp(argv[9],"-o") && strcmp(argv[11],"-o")))
	{
		cout << ("Please try entering the Bitcoin Network again. Arguments given were either in the wrong order, or incorrect.\n");
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
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-o"))) { outputFile=(char *)malloc(sizeof(argv[12]+1)) ; strncpy(outputFile, argv[12], strlen(argv[12])+1); } 

/*-k*/
	if (!(strcmp(argv[1],"-k"))) k=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-k"))) k=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-k"))) k=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-k"))) k=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-k"))) k=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-k"))) k=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-k"))) k=atoi(argv[12]);	
	else k=4;

/*-L*/
	if (!(strcmp(argv[1],"-L"))) L=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-L"))) L=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-L"))) L=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-L"))) L=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-L"))) L=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-L"))) L=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-L"))) L=atoi(argv[12]);	
	else L=5;

/*-N*/
	if (!(strcmp(argv[1],"-N"))) N=atoi(argv[2]);
	else if (!(strcmp(argv[3],"-N"))) N=atoi(argv[4]);
	else if (!(strcmp(argv[5],"-N"))) N=atoi(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-N"))) N=atoi(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-N"))) N=atoi(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-N"))) N=atoi(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-N"))) N=atoi(argv[12]);	
	else N=1;

/*-R*/
	if (!(strcmp(argv[1],"-R"))) R=atof(argv[2]);
	else if (!(strcmp(argv[3],"-R"))) R=atof(argv[4]);
	else if (!(strcmp(argv[5],"-R"))) R=atof(argv[6]);
	else if (argv[7]!=NULL && !(strcmp(argv[7],"-R"))) R=atof(argv[8]);
	else if (argv[9]!=NULL && !(strcmp(argv[9],"-R"))) R=atof(argv[10]);	
	else if (argv[11]!=NULL && !(strcmp(argv[11],"-R"))) R=atof(argv[12]);	
	else if (argv[13]!=NULL && !(strcmp(argv[13],"-R"))) R=atof(argv[12]);	
	else R=1.0;

	/*END OF ARGUMENT CHECK*/
	/*----------------------------------------------------------------------------------------------------------------------------------*/

	string line;
	ifstream inputF(inputFile);
	if (inputF.is_open()){
		while ( getline (inputF,line) ){
			// cout << line << endl;
			break;
		}
		inputF.close();
	}

	else cout << "Unable to open file"; 

	return 0;
}