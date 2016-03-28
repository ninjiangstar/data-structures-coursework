#include <string>
#include <utility>
#include "msort.h"

using namespace std;


class SortPairName_Ascending {
	public:
		bool operator()(pair<string, int> elem1, pair<string, int> elem2){
			return elem1.first < elem2.first;
		}
};

class SortPairName_Descending {
	public:
		bool operator()(pair<string, int> elem1, pair<string, int> elem2){
			return elem1.first > elem2.first;
		}
};

class SortPairValue_Increasing {
	public:
		bool operator()(pair<string, int> elem1, pair<string, int> elem2){
			return elem1.second < elem2.second;
		}
};

class SortPairValue_Decreasing {
	public:
		bool operator()(pair<string, int> elem1, pair<string, int> elem2){
			return elem1.second > elem2.second;
		}
};