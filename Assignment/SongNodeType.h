#pragma once
#include <string>
using namespace std;
class SongNodeType
{
public:
	string title;
	string singer;
	double duration;
	SongNodeType* next;
	SongNodeType* prev;
};

