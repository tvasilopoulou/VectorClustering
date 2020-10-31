#include <iostream>

vector<Image*> kMeansInitialization(vector<Image*>, int, int, int, int);

double CalculateMedianDistance(vector<Image *>);

void InitializeClusters(vector<Image *>, vector<Cluster *> *);

vector<Image*>	LloydsAlgorithm(vector<Image*>, vector<Image*>, int);
