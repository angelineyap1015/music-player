#pragma once
#include"CollectionNodeType.h"
#include"PlaylistNodeType.h"
class CollectionLinkedList
{
public:
	CollectionNodeType* head;
	int size;

	CollectionLinkedList();
	void addSong();
	void displaySong();
	void deleteSong(string*);
	void playlistSearch();
	void updatePlaylist(string);
	CollectionNodeType* searchSongToAdd();
	void addPlaylist(CollectionNodeType*, PlaylistNodeType*);
	void updateCollection(string, PlaylistNodeType*);
};

