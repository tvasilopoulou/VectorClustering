#include <iostream>
#include <vector> 

using namespace std;


typedef class Image{
	int imageId;
	int clusterId;
	int minDist;
	int secondNearestCentroid;
	int secondMinDist;
	int dimensions;
	uint8_t * image;
public:
	Image(int id, uint8_t * image, int);
	uint8_t * getVal();
	int getDimensions();
    int getCluster();
    int getID();
	int getMinDist();
    void setCluster(int);
	void setMinDist(int);
	void setSecondNearestCentroid(int);
    void setSecondMinDist(int);

}Image;

typedef class Cluster
{
	vector<uint8_t *> imagesInCluster;
	Image * cluster;
public:
	Cluster(Image *);
	vector<uint8_t *> getImagesVector();
	void setCluster(Image *);
	// ~Cluster();
	
}Cluster;