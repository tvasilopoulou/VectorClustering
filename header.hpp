#include <iostream>

using namespace std;

typedef class Values{
	int index;
	int hashResult;
public:
	Values();
	Values(int , int );
	void setIndex(int );
	void setHashResult(int);
	int getIndex(void);
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

} HashBucket;

typedef class HashTable{						// 1-1 hashTable - hashFunction
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
	int hashFunctionG(int w, int d, uint8_t * image);

} HashTable;

typedef class HashMap{
private:
	int k;
	int d;
	int w;
	int size;
	int * sValues;
	map <int,int> hashCache;
	HashTable ** hashTable;
public:
	HashMap(int size, int fixedInd, int k, int d, int w);
	~HashMap();
	void generateSValues(int d, int w);
	int getSize();
	HashTable * getHashTableByIndex(int index);
	Values * ANN(uint8_t * qImage);
	Values * ARangeSearch(uint8_t * qImage, double R);

} HashMap;

