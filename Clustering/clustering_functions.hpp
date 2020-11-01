#include <iostream>

vector<Image*> kMeansInitialization(vector<Image*>, int, int, int, int);

double CalculateMedianDistance(vector<Image *>);

void InitializeClusters(vector<Image *>, vector<Cluster *> *);

vector<double> Silhouette(vector<Cluster *>, vector<Image *>);

vector<Cluster *> LloydsAlgorithm(vector<Image*>, vector<Image*>, int);

void PrintResults(ofstream&, vector<Cluster *>, vector<double>, vector<Image *>, int);