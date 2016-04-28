#include <cmath>
#include "Map.h"

class Hash : public Map
{
public:
	Hash() : base(40961), currBucket(0), count(0)
	{ // setup environment
		int bucketsTemp[13] = {11, 23, 41, 83, 163, 331, 641, 1283, 2579, 5147, 10243, 20483, 40961};
		for(int i = 0; i < 13; i++) buckets[i] = bucketsTemp[i];
		table = new std::pair<const std::string, int>*[buckets[currBucket]]();
	}
	~Hash()
	{ // deallocation
		for(unsigned int i = 0; i < buckets[currBucket]; i++) if(table[i]) delete table[i];
		delete [] table;
	}

	void add(const std::string& word)
	{
		if(count > buckets[currBucket]/2 && currBucket != 12) resize();
		const std::string newWord = convertToLower(word);
		unsigned int loc = probe(newWord); // get prob location
		if(table[loc]) table[loc]->second++; // if exist, increment
		else
		{
			table[loc] = new std::pair<const std::string, int>(newWord, 1); // else, create it
			count++;
		}
	}

	void reportAll(std::ostream& output)
	{ // print everything in order, if exists
		for(unsigned int i = 0; i < buckets[currBucket]; i++)
			if(table[i]) output << table[i]->first << " " << table[i]->second << std::endl;
		std::cout << "Count: " << count << std::endl;
	}

private:
	std::pair<const std::string, int> ** table;
	const unsigned int base;
	unsigned int currBucket, buckets[13], count;

	const std::string convertToLower(const std::string & string) const
	{
		std::string word = string;
		for(unsigned int i=0; i < word.length(); i++)
			if(word[i] >= 'A' && word[i] <= 'Z') word[i] += 32;
		return word;
	}

	unsigned int probe(const std::string & string) const
	{
		unsigned int currHash = hash(string);
		std::pair<const std::string, int> * currPair = table[currHash];
		// utilize quadratic probing
		unsigned int probe = 1;
		while(currPair != NULL) // not NULL
		{
			if(currPair->first == string) break;
			currHash = (currHash + (probe * probe)) % buckets[currBucket];
			currPair = table[currHash];
			probe++;
		}

		return currHash;
	}

	void resize()
	{
		std::pair<const std::string, int> ** oldTable = table;
		table = new std::pair<const std::string, int>*[buckets[++currBucket]]();
		for(unsigned int i = 0; i < buckets[currBucket-1]; i++)
		{
			if(oldTable[i])
			{ // transfer pointers!
				unsigned int loc = probe(oldTable[i]->first);
				table[loc] = oldTable[i];
			}
		}
		delete [] oldTable; // pairs are recycled, no need to de-allocate
	}

	unsigned int hash(const std::string & string) const
	{
		unsigned int wordLength = string.length(), * w = new unsigned int[15]();

		for(unsigned int i = 4; i > 0; i--)
		{
			unsigned long long preHash = 0LL;
			for(unsigned int j = 8; j > 0; j--)
			{ // split int 8's
				if(wordLength == 0) break; // string is exhausted
				double multiplier = pow(128.0,(double)(8 - j));
				preHash += (unsigned long long) multiplier * (unsigned long long) string[wordLength-1];
				wordLength--;
			}
			for(unsigned int j = 4; j > 0; j--)
			{ // fill digits
				if(preHash == 0) break;
				w[(i * 4) + j - 6] = (unsigned int)(preHash % (unsigned long long) base);
				preHash = preHash / (unsigned long long) base;
			}
		}

		// create hash
		unsigned int hash = (34394 * w[1] + 36706 * w[2] + 38074 * w[3] + 16351 * w[4] + 2623 * w[5] + 10174 * w[6] + 22339 * w[7] + 27779 * w[8] + 36642 * w[9] + 19250 * w[10] + 36216 * w[11] + 33514 * w[12] + 24019 * w[13] + 5552 * w[14]) % buckets[currBucket];

		delete [] w; // deallocate first
		return hash;
	}

};