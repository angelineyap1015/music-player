#pragma once
#include <string>
#include"SongNodeType.h"
using namespace std;
class PlaylistNodeType
{
public:
	string name;
	int size;
	PlaylistNodeType* nextPlaylist;
	SongNodeType* tailSong;
};

