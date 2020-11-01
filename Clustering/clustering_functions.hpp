#include <iostream>

// functions to implement clustering using kmeans++ initialization, lloyd's algorithm, reverse assignment using range search and range search for hypercube
vector<Image*> kMeansInitialization(vector<Image*>, int, int, int, int);

double CalculateMedianDistance(vector<Image *>);

double CalculateSecondBestMedianDistance(vector<Image *> );

void InitializeClusters(vector<Image *>, vector<Cluster *> *);

void reverseAssignmentLSH(vector <Image*> , vector<Image *>, int, int);

void reverseAssignmentCube(vector <Image*> , vector <Image*> , int, int, int );

vector<double> Silhouette(vector<Cluster *>, vector<Image *>);

vector<Cluster *> LloydsAlgorithm(vector<Image*>, vector<Image*>, int);

void PrintResults(ofstream&, vector<Cluster *>, vector<double>, vector<Image *>, int);
