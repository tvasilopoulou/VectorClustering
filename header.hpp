#include <iostream>
#include <list> 
#include <iterator> 
#include <string>

using namespace std;

typedef class HashBucket{
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
	list <HashBucket> * hashBuckets;
public:
	HashTable(int size){
		this->size = size;
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

	int hashFunction(){
		return 1;
	}


} HashTable;

typedef class HashMap{
	private:
		int size;
		HashTable ** hashTable;
	public:
		HashMap(int size, int fixedInd){
			this->size = size;
			this->hashTable = new HashTable * [size];
			for(int i=0; i<size; i++){
				hashTable[i] = new HashTable(fixedInd);
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

