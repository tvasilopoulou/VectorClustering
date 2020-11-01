#include <iostream>

vector<Image*> kMeansInitialization(vector<Image*>, int, int, int, int);

double CalculateMedianDistance(vector<Image *>);

double CalculateSecondBestMedianDistance(vector<Image *> );

void InitializeClusters(vector<Image *>, vector<Cluster *> *);

vector<Image*>	LloydsAlgorithm(vector<Image*>, vector<Image*>, int);

void reverseAssignmentLSH(vector <Image*> , vector<Image *>, int, int);

void reverseAssignmentCube(vector <Image*> , vector <Image*> , int, int, int );

