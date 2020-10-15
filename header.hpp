#include <iostream>
#include <list> 
#include <iterator> 
#include <string>

using namespace std;

typedef class HashBucket{
private:
	int id;
	char image[784];
public:
	HashBucket(int id, char * image){			//look up referrences, save some space!
		this->id = id;	
		strncpy(this->image, image, 784);
		cout << "HashBucket created" << endl;
	}
} HashBucket;

typedef class HashTable{						// 1-1 hashTable - hashFunction
private:
	int size;
	int m;
	int M;
	int k;
	list <HashBucket> * hashBuckets;
public:
	HashTable(int size, int k){
		this->size = size;
		this->m = pow(2, 32-k);
		this->M = pow(2, 32/k);							//experiment!!
		this->k = k;
		this->hashBuckets = new list <HashBucket> [size];
		cout << "HashTable constructed" << endl;
		// char arr[784] = {1};
		// HashBucket bucket(1, arr);
		// this->hashBuckets->push_back(bucket);
	}

	~HashTable(){
		delete [] hashBuckets;
	}

	int getSize(){
		return this->size;
	}

	int calcM(int mPrev){
		return (((mPrev % this->M) * ((this->m) % (this->M))) % M);
	}

	int hashFunctionH(int * sValues, int * aValues){
		int mArray[k];
		int hashValue = aValues[k-1];
		mArray[0] = this->m;
		hashValue += mArray[0]*aValues[k-2];
		for(int i=1; i<k; i++){
			mArray[i] = this->calcM(mArray[i-1]);
			hashValue += mArray[i] * aValues[(this->k) - i -1];
		}
		hashValue %= M;
		return hashValue;					//not true -> need to concat with other h(x)!!!
	}

	int hashFunctionG(int numOfImages, int w, uint8_t ** imagesArray){
		// for(int p=0; p<k; p++){
			int sValues[k], aValues[k];
			for(int i=0; i<numOfImages; i++){
				/* https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range */
				random_device rand_dev;
			    mt19937 generator(rand_dev());
			    uniform_int_distribution <int> distr(0, w);
				for (int j = 0; j < k; ++j){							// PERHAPS NOT K BUT D!! CHECK !!
					sValues[j] = distr(generator);
					// cout << "a = floor((" << (long int)imagesArray[i][j] << " - " << sValues[j] << ")/" << w << ")" << endl;
					aValues[j] = floor(((long int)imagesArray[i][j] - sValues[j])/w);
				} 
			}
		// }
	}


} HashTable;

typedef class HashMap{
private:
	int size;
	HashTable ** hashTable;
public:
	HashMap(int size, int fixedInd, int k){
		this->size = size;
		this->hashTable = new HashTable * [size];
		for(int i=0; i<size; i++){
			hashTable[i] = new HashTable(fixedInd, k);
		}
		cout << "HashMap constructed" << endl;
	};

	~HashMap(){
		for(int i=0; i<size; i++){
			delete hashTable[i];
		}
		delete [] hashTable;
	}

	int getSize(){
		return this->size;
	}
	HashTable * getHashTableByIndex(int index){
		return this->hashTable[index];
	}
} HashMap;

