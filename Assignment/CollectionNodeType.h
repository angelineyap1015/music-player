#pragma once
#include <string>
using namespace std;

class CollectionNodeType
{
public:
	string title;
	string singer;
	string playlists[5] = {"","","","",""};
	double duration;
	CollectionNodeType* next;
};

