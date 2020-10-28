#include <iostream>
#include <iterator> 
#include <string>
#include <map>
#include <utility>      // std::pair
#include <ctime> 
#include <vector> 
#include <cmath> 
#include <algorithm> 
#include <bits/stdc++.h> 
#include "header.hpp"
#include "funcHeader.hpp"


Values::Values(){
	this->index = pow(2, 28);
	this->hashResult = -1;
}
Values::Values(int index, int hashResult){
	this->index = index;
	this->hashResult = hashResult;
}
void Values::setIndex(int index){
	this->index = index;
}
void Values::setHashResult(int hashResult){
	this->hashResult = hashResult;
}
int Values::getIndex(void){
	return this->index;
}
int Values::getHashResult(void){
	return this->hashResult;
}
Values::~Values(){ }


HashBucket::HashBucket(int id, uint8_t * image){
	this->id = id;	
	this->hashValue = -1;
	this->image = image;
}
uint8_t * HashBucket::getImage(){
	return this->image;
}

int HashBucket::getId(){
	return this->id;
}


HashTable::HashTable(int size, int k, int d, int w, int * sValues, map <int,int> * hashCache){
	this->size = size;
	this->m = pow(2, 32-k);
	this->M = pow(2, 32/k) -1;							//experiment!!
	this->k = k;
	this->d = d;
	this->sValues = sValues;
	this->hashCache = *hashCache;
	this->hashBuckets = new vector <HashBucket> [size];
}

HashTable::~HashTable(){
	delete [] hashBuckets;
}

vector <HashBucket> HashTable::getHashBucket(int index){
	return this->hashBuckets[index];
}

int HashTable::getSize(){
	return this->size;
}

int * HashTable::calcA(int * aValues){
	for(int i=0; i<this->d; i++){
		if(aValues[i]<0) aValues[i] = (aValues[i]%this->M +this->M) % this->M;
		else aValues[i] = aValues[i] % this->M; 
	}
	return aValues;
}

int HashTable::hashFunctionH(int * sValues, int * aValues){
	int mArray[this->d];
	aValues = calcA(aValues);
	int hashValue = aValues[this->d -1] % this->M;
	mArray[0] = this->m % this->M;
	hashValue += (mArray[0]*aValues[this->d -2]) % this->M;
	for(int i=1; i<this->d; i++){
		mArray[i] = (((mArray[i-1] % this->M) * ((this->m) % (this->M))) % this->M);
		hashValue += mArray[i] * aValues[(this->d) - i -1];
	}
	return hashValue;
}


int HashTable::hashFunctionG(int w, int d, uint8_t * image, int imageNumber){
	unsigned int g = 0;
	int it;
	for(int p=0; p<k; p++){			//generate k number of hi(x)'s to concat, for single image
		int aValues[d];				//for every hash function h
		it = rand()%d;
		int j=0;
		if(hashCache.find(it) != hashCache.end()) {
			if(p){
				g <<= 8;
				g |= hashCache.at(it);
			} 
			else if (p==0){
				g = hashCache.at(it);
			}
			j=d+1;
		}
		while(j<d){
			aValues[j] = floor(((long int)image[j] - this->sValues[j])/w);
			j++;
		} 
		if(j>d) continue;
		if(p){
			g <<= 8;
			hashCache[it] = hashFunctionH(this->sValues, aValues);
			g |= hashCache[it];
		} 
		else if (p==0){
			hashCache[it] = hashFunctionH(this->sValues, aValues);
			g = hashCache[it];
		}
	}
	if(imageNumber==pow(2, 32 - this->k)) return g%this->size;
	HashBucket hBucket = HashBucket(imageNumber, image);
	// if((g%this->size)!=0)cout << g%this->size << endl;
	this->hashBuckets[g%this->size].push_back(hBucket);
	return g%this->size;
}


HashMap::HashMap(int size, int fixedInd, int k, int d, int w, int N){
	srand(time(0));
	this->k = k;
	this->d = d;
	this->w = w;
	this->N = N;
	this->size = size;
	this->sValues = new int[d];
	this->hashTable = new HashTable * [size];
	generateSValues(d, w);
	for(int i=0; i<size; i++){
		hashTable[i] = new HashTable(fixedInd, k, d, w, this->sValues, &(this->hashCache));
	}
	// cout << "HashMap constructed" << endl;
};

HashMap::~HashMap(){
	for(int i=0; i<size; i++){
		delete hashTable[i];
	}
	delete [] hashTable;
}

void HashMap::generateSValues(int d, int w){
	/* https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range */
	random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution <int> distr(0, w);

    for(int i = 0; i<d; i++){
		this->sValues[i] = distr(generator);
	}

}

int HashMap::getSize(){
	return this->size;
}
HashTable * HashMap::getHashTableByIndex(int index){
	return this->hashTable[index];
}

Values * HashMap::ANN(uint8_t * qImage){
	vector <HashBucket> hBucket;
	HashBucket * bucketArray;
	int index;
	Values * neighbors = new Values[this->N];
	int maxDist = pow(2, 32-this->k);
	for(int i=0; i<size; i++){		//for every hashTable
		index = this->getHashTableByIndex(i)->hashFunctionG(w, d, qImage, pow(2, 32-this->k));		//only return list
		hBucket = this->getHashTableByIndex(i)->getHashBucket(index);
		int length = hBucket.size();
		// if(length==0) continue;				// if no neighbors in current list of hashtable, skip
		int count = 0;
		bucketArray = &hBucket[0];			// convert to array
		for(int j=0;j<length; j++){				//for every bucket in list-array
			// maxDist = neighbors[this->N - 1].getIndex();

			int dist = manhattanDistance(hBucket[j].getImage(), qImage, this->d);
			// cout << dist << " is < than " << maxDist << "?" << endl;
			if(dist < maxDist){			//closer than what is currently available
				neighbors[this->N - 1].setIndex(dist);
				neighbors[this->N - 1].setHashResult(hBucket[j].getId());
				sort(neighbors + 0, neighbors + this->N);
				maxDist = neighbors[this->N - 1].getIndex();
				count++;
				// cout << "MaxDist now is " << maxDist << endl;
				if(count == 10*this->size) break;

			}
			
		}


	}
	return neighbors;
}

Values * HashMap::ARangeSearch(uint8_t * qImage, double R){
	vector <HashBucket> hBucket;
	HashBucket * bucketArray;
	int index;
	int limit = 20 * (this->size);
	Values * neighbors = new Values[limit];
	for(int i=0; i<size; i++){		//for every hashTable
		index = this->getHashTableByIndex(i)->hashFunctionG(w, d, qImage, -1);
		hBucket = this->getHashTableByIndex(i)->getHashBucket(index);
		int length = hBucket.size();
		bucketArray = &hBucket[0];
		for(int j=0; j<limit; j++){				//instead of length -> 10*L
			int dist = manhattanDistance(bucketArray[j].getImage(), qImage, this->d);
			if(dist < R){
				neighbors[j].setIndex(dist);
				neighbors[j].setHashResult(dist);			//hashResult instead--> image id!!!
				sort(neighbors + 0, neighbors + limit);
			}
			
		}


	}
	return neighbors;
}