#include <iostream>
#include <iterator> 
#include <string>
#include <map>
#include <utility>      
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
	this->flag = -1;
}
Values::Values(int index, int hashResult){
	this->index = index;
	this->hashResult = hashResult;
}
void Values::setIndex(int index){
	this->index = index;
}

void Values::setFlag(int flag){
	this->flag = flag;
}

void Values::setHashResult(int hashResult){
	this->hashResult = hashResult;
}
int Values::getIndex(void){
	return this->index;
}

int Values::getFlag(void){
	return this->flag;
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
	this->M = pow(2, 32/k) -1;							
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


string HashTable::hashFunctionCubeG(int w, int d, uint8_t * image, int imageNumber){
	int it;
	string g;
	vector <int> hashFunctions;
	map <int, int> cubeMap;
	for(int p=0; p<this->k; p++){			//generate k number of hi(x)'s to concat, for single image
		int aValues[d];				//for every hash function h
		it = rand()%d;
		hashFunctions.push_back(it);
		if(hashCache.find(it) == hashCache.end()) {
			for(int j=0; j<d; j++){
				aValues[j] = floor(((long int)image[j] - this->sValues[j])/w);

			}
			hashCache[it] = hashFunctionH(this->sValues, aValues);
		}
		cubeMap[hashCache.at(it)] = rand()%2;
		g += to_string(cubeMap[hashCache.at(it)]);
	}

	if(imageNumber==pow(2, 32 - this->k)) return g;
	HashBucket hBucket = HashBucket(imageNumber, image);
	this->hashBuckets[stoi(g, 0, 2)%this->size].push_back(hBucket);
	return g;
}




int HashTable::hashFunctionG(int w, int d, uint8_t * image, int imageNumber){
	unsigned int g = 0;
	int it;
	for(int p=0; p<this->k; p++){			//generate k number of hi(x)'s to concat, for single image
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
	// cout << (long int) image << endl;
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

vector <string> HashMap::getCandidates(){
	return this->candidates;
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
	for(int i=0; i<this->size; i++){		//for every hashTable
		index = this->getHashTableByIndex(i)->hashFunctionG(this->w, this->d, qImage, pow(2, 32-this->k));		//only return list
		hBucket = this->getHashTableByIndex(i)->getHashBucket(index);
		int length = hBucket.size();
		int count = 0;
		for(int j=0;j<length; j++){				//for every bucket in list-array
			int dist = manhattanDistance(hBucket[j].getImage(), qImage, this->d);
			if(dist < maxDist){			//closer than what is currently available
				int oldIndex = exists(neighbors, hBucket[j].getId(), this->N);
				if(oldIndex>=0){
					if(neighbors[oldIndex].getIndex() > dist){
						neighbors[oldIndex].setIndex(dist);
					}
				}
				else{
					neighbors[this->N - 1].setIndex(dist);
					neighbors[this->N - 1].setHashResult(hBucket[j].getId());
				}
				sort(neighbors + 0, neighbors + this->N);
				maxDist = neighbors[this->N - 1].getIndex();
				count++;
				if(count == 10*this->size) break;

			}
			if(count == 10*this->size) break;
		}


	}
	return neighbors;
}


Values * HashMap::ANNCube(uint8_t * qImage, int probes){		//pass probes - 1!!!
	vector <HashBucket> hBucket;
	Values * neighbors = new Values[this->N];
	int maxDist = pow(2, 32-this->k);
	this->candidates.clear();
	string gValue = this->getHashTableByIndex(0)->hashFunctionCubeG(this->w, this->d, qImage, pow(2, 32-this->k));
	this->candidates.push_back(gValue);

	for(int c=1; this->candidates.size()<=probes; c++){
		this->hammingCalc(gValue, gValue.size() -1 , c);		//change 1 to i in loop

	}

	this->candidates.resize(probes);

	for(int i=0; i<this->candidates.size(); i++){		//for every hashTable
		int index = stoi(this->candidates[i], 0, 2) % (this->size);
		hBucket = this->getHashTableByIndex(0)->getHashBucket(index);
		int length = hBucket.size();
		int count = 0;
		// bucketArray = &hBucket[0];			// convert to array
		for(int j=0;j<length; j++){				//for every bucket in list-array

			int dist = manhattanDistance(hBucket[j].getImage(), qImage, this->d);
			if(dist == 0) continue;
			if(dist < maxDist){			//closer than what is currently available
				int oldIndex = exists(neighbors, hBucket[j].getId(), this->N);
				if(oldIndex>=0){
					if(neighbors[oldIndex].getIndex() > dist){
						neighbors[oldIndex].setIndex(dist);
					}
				}
				else{
					neighbors[this->N - 1].setIndex(dist);
					neighbors[this->N - 1].setHashResult(hBucket[j].getId());
				}
				sort(neighbors + 0, neighbors + this->N);
				maxDist = neighbors[this->N - 1].getIndex();
				count++;
				if(count == 10*this->size) break;

			}
			
		}
		if(count == 10*this->size) break;	
	}


	return neighbors;
}


Values * HashMap::ARangeSearch(uint8_t * qImage, double R){
	vector <HashBucket> hBucket;
	HashBucket * bucketArray;
	int index;
	int limit = 20 * (this->size);
	Values * neighbors = new Values[limit];
	int l=0;
	for(int i=0; i<this->size; i++){		//for every hashTable
		index = this->getHashTableByIndex(i)->hashFunctionG(w, d, qImage, -1);
		hBucket = this->getHashTableByIndex(i)->getHashBucket(index);
		int length = hBucket.size();
		for(int j=0; j<length; j++){				//instead of length -> 10*L
			int dist = manhattanDistance(hBucket[j].getImage(), qImage, this->d);
			if(dist < R){
				if(exists(neighbors, hBucket[j].getId(), limit)>=0) continue;
				neighbors[l].setIndex(dist);
				neighbors[l].setHashResult(hBucket[j].getId());			//hashResult instead--> image id!!!
				l++;
				if(l == limit) break;
			}
		}
		if(l == limit) break;

	}

	return neighbors;
}


Values * HashMap::ARangeSearchCube(uint8_t * qImage, int probes, double R, int size, int M){
	Values * neighbors = new Values[M];
	vector <HashBucket> hBucket;
	int maxDist = pow(2, 32-this->k);
	this->candidates.clear();
	string gValue = this->getHashTableByIndex(0)->hashFunctionCubeG(this->w, this->d, qImage, pow(2, 32-this->k));
	this->candidates.push_back(gValue);

	for(int c=1; this->candidates.size()<=probes; c++){
		this->hammingCalc(gValue, gValue.size() -1 , c);		//change 1 to i in loop

	}

	this->candidates.resize(probes);

	for(int i=0; i<this->candidates.size(); i++){		//for every hashTable
		int index = stoi(this->candidates[i], 0, 2) % size;
		hBucket = this->getHashTableByIndex(0)->getHashBucket(index);
		int length = hBucket.size();
		int count = 0;
		int l=0;
		for(int j=0;j<length; j++){				//for every bucket in list-array
			int dist = manhattanDistance(hBucket[j].getImage(), qImage, this->d);
			if(dist < R){			//closer than what is currently available
				if(exists(neighbors, hBucket[j].getId(), M)>=0) continue;
				neighbors[l].setIndex(dist);
				neighbors[l].setHashResult(hBucket[j].getId());			//hashResult instead--> image id!!!
				l++;
				if(l == M) break;
			}

			
		}
		if(l == M) break;

			
	}


	return neighbors;
}



/*string to compare, length of string -1, max hamming distance*/
void HashMap::hammingCalc(string str, const int i, const int changesLeft) {
	if (changesLeft == 0) {
		this->candidates.push_back(str);
		return;
	}
	if (i < 0) return;
	str[i] ^= 1;
	hammingCalc(str, i-1, changesLeft-1);
	str[i] ^= 1;
	hammingCalc(str, i-1, changesLeft);
}