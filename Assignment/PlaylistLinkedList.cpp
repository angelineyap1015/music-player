#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include "PlaylistLinkedList.h"
using namespace std;

PlaylistLinkedList::PlaylistLinkedList(){
	head = NULL;
	size = 0;
}

// create new playlist node in playlist linked list
void PlaylistLinkedList::createPlaylist() {
	bool flag=true;
	string name;
	
	// ask for user input for the details of the playlist node to be created
	cout << "Enter the name of the playlist to be created\n";
	cin >> name;

	//check the availability of the playlist node with the same details in playlist linked list
	if (head != NULL) {
		PlaylistNodeType* current = head;
		while (current != NULL) {
			if (current->name == name) {
				flag = false;
				break;
			}
			current = current->nextPlaylist;
		}
	}

	// insert the playlist node at the begining if the playlist node with same info is not exist in playlist linked list
	if (flag == true) {
		PlaylistNodeType* newNode = new PlaylistNodeType;
		newNode->name = name;
		newNode->nextPlaylist = head;
		newNode->tailSong = NULL;

		head = newNode;
		size++;
		cout << "Playlist has added\n";
	}
	else {
		cout << "Playlist was existed\n";
	}
}

//display all playlist node in the playlist linked list
void PlaylistLinkedList::viewPlaylist() {
	int counter=1;

	if (head != NULL) {
		PlaylistNodeType* current = head;

		// travel every playlist node in playlist linked list and display their info 
		while (current != NULL) {
			cout << counter << "." << current->name<<"\n";
			counter++;
			current = current->nextPlaylist;
		}
	}
	else {
		cout << "No playlist to display\n";
	}
}

//delete a playlist node in playlist linked list
string PlaylistLinkedList::deletePlaylist() {
	bool exist = false;
	string name;

	// check if there any playlist node in the playlists linked list
	if (head == NULL) {
		cout << "No playlist existed. Delete action cannot be performed\n";
		name = "";
	}
	else {

		// ask for user input for the details of the playlist node to be deleted
		cout << "Enter the name of palylist to be deleted\n";
		cin >> name;

		PlaylistNodeType* toDelete = head;
		PlaylistNodeType* prev = NULL;

		// check the availability of the playlist node to be deleted in playlist linked list
		while (toDelete != NULL) {
			if (toDelete->name == name) {
				exist = true;
				break;
			}
			prev = toDelete;
			toDelete = toDelete->nextPlaylist;
		}

		if (exist) {
			// check if there any collection node in the collection linked list need to be updated
			if (toDelete->size == 0) {
				name = "";
			}

			// delete the playlist node if it is the first node in the playlist linked list 
			if (toDelete == head) {
				head = head->nextPlaylist;
				delete toDelete;
			}
			// delete the playlist node if it is at the random position at the playlist linked list
			else {
				prev->nextPlaylist = toDelete->nextPlaylist;
				delete toDelete;
			}
			size--;
			cout << "Playlist has deleted\n";
		}
		else {
			name = "";
			cout << "Playlist not found\n";
		}
	}
	return name;
}

// find the intended playlist node and return the pointer if exist
PlaylistNodeType* PlaylistLinkedList::selectPlaylist() {
	bool exist = false;
	string name;
	PlaylistNodeType* current = head;

	// check if there any palylist node in the playlist linked list
	if (head == NULL) {
		cout << "No playlist existed. Select action cannot be performed\n";
	}
	else {
		cout << "Enter the name of playlist to select\n";
		cin >> name;

		//travel the playlist node
		while (current != NULL) {

			// check the availability of the playlist node to be searched by checking the name info of the playlist node
			if (current->name == name ) {
				exist = true;
				break;
			}
			current = current->nextPlaylist;
		}
		if (!exist) {
		cout << "Playlist not found\n";
		}
	}
	// return pointer that point to the playlist node to be searched
	return current;
}

// create new song node in playlist linked list for selected playlist node
bool PlaylistLinkedList::addSongIntoPlaylist(PlaylistNodeType* p, CollectionNodeType* c) {
	PlaylistNodeType* curPlaylist = p;
	CollectionNodeType* curCollection = c;
	bool flag = true;

	// check the availability of the song node with same details in the playlist linked list for selected playlist node
	if (curPlaylist->tailSong != NULL) {
		SongNodeType* current = curPlaylist->tailSong->next;
		do {
			if (current->title == curCollection->title && current->singer == curCollection->singer) {
				flag = false;
			}
			current = current->next;
		} while (current != curPlaylist->tailSong->next);
	}

	//insert new song node at the end of playlist linked list for the selected playlist node
	if (flag == true) {

		// create the song node and populate
		SongNodeType* newNode = new SongNodeType;
		newNode->title = curCollection->title;
		newNode->singer = curCollection->singer;
		newNode->duration = curCollection->duration;

		
		if (curPlaylist->tailSong == NULL) {
			// insert at the end if there is no any song node for the selected playlist node
			curPlaylist->tailSong = newNode;
			newNode->next = newNode;
			newNode->prev = newNode;
		}
		else {
			// insert at the end if there is song node for the selected playlist node
			newNode->prev = curPlaylist->tailSong;
			newNode->next = newNode->prev->next;
			curPlaylist->tailSong->next = newNode;
			curPlaylist->tailSong = newNode;
			newNode->next->prev = newNode;
		}
		curPlaylist->size++;
		cout << "Song has added\n";
	}
	else {
		cout << "Song was existed\n";
	}
	return flag;
}

//display all song node in the playlist linked list for the selected playlist node
void PlaylistLinkedList::viewSongInPlaylist(PlaylistNodeType* p) {
	PlaylistNodeType* curPlaylist = p;

	//check if there any song node in the playlist linked list for the selected playlist node
	if (curPlaylist->tailSong != NULL) {

		// travel the playlist linked list for the selected playlist node and display their info
		SongNodeType* current = curPlaylist->tailSong->next;
		do {
			cout << "Title:" << current->title<< "\n";
			cout << "Singer: " << current->singer<< "\n";
			current = current->next;
		} while (current != curPlaylist->tailSong->next);
	}
	else {
		cout << "No song found in this playlist\n";
	}
}

//remove song node from the playlist linked list for the selected playlist node
string  PlaylistLinkedList::removeSongFromPlaylist(PlaylistNodeType* p) {
	bool exist = false;
	string title, singer;
	PlaylistNodeType* curPlaylist = p;

	// check if there any song node in the playlist linked list for the selected playlist node
	if (curPlaylist->tailSong == NULL) {
		cout << "No song found in this playlist. Delete action cannot be performed\n";
		title = "";
		singer = "";
	}
	else {

		//ask for user about the details of the song node to be removed
		cout << "Enter the name of the song to be deleted\n";
		cin >> title;
		cout << "Enter the singer name of the song\n";
		cin >> singer;

		SongNodeType* toDelete = curPlaylist->tailSong->next;

		//ask the availability of the song node to be deleted in the playlist linked list for the selected playlist node
		do {
			if (toDelete->title ==title && toDelete->singer==singer) {
				exist=true;
				break;
			}
			toDelete = toDelete->next;
		} while (toDelete != curPlaylist->tailSong->next);
		
		
		if (exist) {
			
			//delete the song node if it is the only node in the playlist linked list for the selected playlist node
			if (toDelete == curPlaylist->tailSong && toDelete->next == curPlaylist->tailSong) {
				curPlaylist->tailSong = NULL;
				delete toDelete;
			}
			else {
				//delete the song node if it is at any random position in the playlist linked list for the selected playlist node
				toDelete->prev->next = toDelete->next;
				toDelete->next->prev = toDelete->prev;

				//update the pointer if the song node is the last node in the playlist linked list for the selected playlist node
				if (toDelete == curPlaylist->tailSong) {
					curPlaylist->tailSong = toDelete->prev;
				}
				delete toDelete;
			}
			curPlaylist->size--;
			cout << "Song have removed from the playlist\n";
		
		}
		else {
			cout << "Song not found in the playlist\n";
			title = "";
			singer = "";
		}

	}
	title = title + "," + singer; 
	return title;
}


void PlaylistLinkedList::updatePlaylist(string* d) {

	int counter = 0;
	// check if there any playlist node need to be updated
	if (*(d + 0) != "") {
		PlaylistNodeType* current = head;

		// travel the playlist linked list
		while (current != NULL) {

			// check if the current playlist node have the info that matched with the value that point by the pointer d
			if (current->name == *(d + 2) || current->name == *(d + 3) || current->name == *(d + 4) || current->name == *(d + 5) || current->name == *(d + 6)) {

				// check if there any song node in the playlist linked list for current playlist node
				if (current->tailSong != NULL) {
					SongNodeType* toDelete = current->tailSong->next;
					if (toDelete != NULL) {

						// travel the playlist linked list for the selected playlist node
						do {

							// check if the song node matched with the value that pointed by pointer b
							if (toDelete->title == *(d + 0) && toDelete->singer == *(d + 1)) {
								
								if (toDelete == current->tailSong && toDelete->next == current->tailSong) {
									//delete the song node if it is the only node in the playlist linked list for current playlist node
									current->tailSong = NULL;
									delete toDelete;
								}
								else {
									//delete the song node in the playlist linked list for current playlist node
									toDelete->prev->next = toDelete->next;
									toDelete->next->prev = toDelete->prev;

									// update the pointer if it is the last song node in the playlist linked list for current playlist no
									if (toDelete == current->tailSong) {
										current->tailSong = toDelete->prev;
									}
									delete toDelete;
								}
								current->size--;
								break;
							}
							toDelete = toDelete->next;

						} while (toDelete != current->tailSong->next);
					}
					counter++;
				}
								
			}

			// if song node have deleted in 5 selected playlist node in the playlist linked list
			if (counter == 5) {
				break;
			}
			current = current->nextPlaylist;
		}
	}

}

//travel to the two previous song node and set the pointer 
void PlaylistLinkedList::previousSong(SongNodeType* curSong, SongNodeType*& curPtr) {
	curSong = curSong->prev->prev;
	curPtr = curSong;
}

// travel to the previous song node and set pointer
void PlaylistLinkedList::loopSong(SongNodeType* curSong, SongNodeType*& curPtr) {
	curSong = curSong->prev;
	curPtr = curSong;
}

