#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef class Values{
	int index;
	int hashResult;
	int flag;
public:
	Values();
	Values(int , int );
	void setIndex(int );
	void setFlag(int );
	void setHashResult(int);
	int getIndex(void);
	int getFlag(void);
	int getHashResult(void);
	~Values();

}Values;

typedef class HashBucket{
private:
	int id;
	int hashValue;
	uint8_t * image;
public:
	HashBucket(int id, uint8_t * image);
	uint8_t * getImage();
	int getId();

} HashBucket;

typedef class HashTable{
private:
	int size;
	int m;
	int M;
	int k;
	int d;
	int * sValues;
	map <int,int> hashCache;
	vector <HashBucket> * hashBuckets;
public:
	HashTable(int size, int k, int d, int w, int * sValues, map <int,int> * hashCache);
	~HashTable();
	vector <HashBucket> getHashBucket(int index);
	int getSize();
	int * calcA(int * aValues);
	int hashFunctionH(int * sValues, int * aValues);	
	string hashFunctionCubeG(int w, int d, uint8_t * image, int imageNumber);
	int hashFunctionG(int w, int d, uint8_t * image, int imageNumber);

} HashTable;

typedef class HashMap{
private:
	int k;
	int d;
	int w;
	int N;
	int size;
	int * sValues;
	vector <string> candidates;
	map <int,int> hashCache;
	HashTable ** hashTable;
public:
	HashMap(int size, int fixedInd, int k, int d, int w, int N);
	~HashMap();
	void generateSValues(int d, int w);
	int getSize();
	vector <string> getCandidates();
	HashTable * getHashTableByIndex(int index);
	Values * ANN(uint8_t * );
	Values * ANNCube(uint8_t * , int);
	Values * ARangeSearch(uint8_t * , double);
	Values * ARangeSearchCube(uint8_t * , int, double, int, int);
	void hammingCalc(string , const int , const int);

} HashMap;

