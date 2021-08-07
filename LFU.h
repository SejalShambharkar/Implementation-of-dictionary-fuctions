#include<iostream>
#include<string>
#include<stdlib.h>
#include<vector>
#include<fstream>
#include<unistd.h>
#include<conio.h>
#define ALPHABETS 26
using namespace std;
class LFUCache {
public:

	int siz = 0;
	int min_freq;
	int capacity;
	unordered_map <int, pair<int, int>> cache; //key to {value,freq};
	unordered_map <int, list<int>::iterator> freqIter; //key to list iterator;
	unordered_map <int, list<int>>  freq;  //freq to key list;

	LFUCache(int n) {
		capacity = n;
	}

	int get(int key) {
		if (cache.count(key) == 0) {
			return -1;
		}
		else {
			freq[cache[key].second].erase(freqIter[key]);
			cache[key].second++;
			freq[cache[key].second].push_back(key);
			freqIter[key] = --freq[cache[key].second].end();
			if (freq[min_freq].size() == 0)
				min_freq++;
			return cache[key].first;
		}
	}

	void put(int key, int value) {
		if (cache.find(key) != cache.end()) {
			freq[cache[key].second].erase(freqIter[key]);
			cache[key].second++;
			freq[cache[key].second].push_back(key);
			freqIter[key] = --freq[cache[key].second].end();
			if (freq[min_freq].size() == 0)
				min_freq++;
			cache[key].first = value;

		}
		else {
			if (siz == capacity) {
				cache.erase(freq[min_freq].front());
				freqIter.erase(freq[min_freq].front());
				freq[min_freq].pop_front();
				siz--;
			}
			cache[key] = {value, 1};
			freq[1].push_back(key);
			freqIter[key] = --freq[1].end();
			min_freq = 1;
			siz++;
		}
	}

};
