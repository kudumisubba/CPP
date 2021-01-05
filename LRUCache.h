#pragma once

#include "Cache.h"

class LRUCache : public Cache {

public:
	//Constructor
	LRUCache(int c);

	void set(int,int);
	int get(int);
};
