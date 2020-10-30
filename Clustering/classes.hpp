#include <iostream>
#include <vector> 

using namespace std;


typedef class Image{
	int imageId;
	int clusterId;
	double minDist;
	int dimensions;
	uint8_t * image;
public:
	Image(int id, uint8_t * image, int);
	uint8_t * getVal();
	int getDimensions();
    int getCluster();
    int getID();
    void setCluster(int);
}Image;
