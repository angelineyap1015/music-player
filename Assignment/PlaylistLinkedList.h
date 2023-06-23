#pragma once
#include"PlaylistNodeType.h"
#include"CollectionNodeType.h"
class PlaylistLinkedList
{
public:
	PlaylistNodeType* head;
	int size;

	PlaylistLinkedList();
	void createPlaylist();
	void viewPlaylist();
	string deletePlaylist();
	PlaylistNodeType* selectPlaylist();///return the pointer of that playlist. If not null, then only pass the name to other function
	bool addSongIntoPlaylist(PlaylistNodeType*,CollectionNodeType*);// call collectionLinkedList.searchSongToAdd first and pass the returned arguement
	void viewSongInPlaylist(PlaylistNodeType*);
	string removeSongFromPlaylist(PlaylistNodeType*);
	void updatePlaylist(string*);
	void previousSong(SongNodeType*, SongNodeType*&);
	void loopSong(SongNodeType*, SongNodeType*&);
	
};


