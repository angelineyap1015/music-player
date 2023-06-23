#include <iostream>
#include <string>
#include "CollectionLinkedList.h"
#include <algorithm>
#include <sstream>
using namespace std;

CollectionLinkedList::CollectionLinkedList(){
	head = NULL;
	size = 0;
};

// create new collection node in collection linked list
void CollectionLinkedList::addSong() {
	bool flag = true;
	string title, singer;
	double duration, sec;
	long min;

	//ask for user input for the details of the collection node to be created
	cout << "Enter the title of the song \n";
	cin >> title;
	cout << "Enter the name of the singer\n";
	cin >> singer;
	cout << "Enter the duration of the song (min.sec)\n";
	cin >> duration;

	// validate the format of the inputted duration info
	/**
	* Following source code obtained from (NullUserException, 2011)
	*/
	min = (long)duration;
	sec = duration - min;
	while (sec > 0.59||min>9) {
		cout << "Invalid duration. Enter the duration of the song (min.sec)\n";
		cin >> duration;
		min = (long)duration;
		sec = duration - min;
	}
	
	// check for the availability of the collection node with same details in the collection linked list
	if (head != NULL) {
		CollectionNodeType* current = head;
		while (current != NULL) {
			if (current->title == title && current->singer == singer) {
				flag = false;
				break;
			}
			current = current->next;
		}
	}
	
	// insert the new collection node at begining if the collection node with same info is not exist in the collection linked list
	if (flag == true) {

		// create and populate new collection node
		CollectionNodeType* newNode = new CollectionNodeType;
		newNode->title = title;
		newNode->singer = singer;
		newNode->duration = duration;

		//update the pointer
		newNode->next = head;
		head = newNode;
		size++;
		cout << "Song have added \n";
	}
	else {
		cout << "Song was existed \n";
	}
}

// displsy all collection node in collection linked list
void CollectionLinkedList::displaySong() {
	if (head != NULL) {
		CollectionNodeType* current = head;

		// travel every collection node in collection linked list and display their info 
		while (current != NULL) {
			cout << "Title: " << current->title<<"\n";
			cout << "Singer: " << current->singer << "\n";
			current = current->next;
		}
	}
	else {
		cout << "The collection is empty\n";
	}
}

// delete a collection node in collection linked list
void CollectionLinkedList::deleteSong(string* d) {
	bool exist = false;
	string title, singer;

	// check if there any collection node in the collection linked list
	if (head == NULL) {
		cout << "The collection is empty. No song can be deleted\n";
	}
	else {

		//ask for user input for the details of the collection node to be deleted
		cout << "Enter the title of the song to be delete\n";
		cin >> title;
		cout << "Enter the name of the singer\n";
		cin >> singer;

		CollectionNodeType* toDelete = head;
		CollectionNodeType* prev = NULL;

		// check the availability of the collection node to be deleted in collection linked list
		while (toDelete != NULL) {
			if (toDelete->title == title && toDelete->singer == singer) {
				exist = true;
				break;
			}
			prev = toDelete;
			toDelete = toDelete->next;
		}

		if (exist) {

			// assign the details of collection node to be deleted to the array that pointed by pointer d for updating the song node in playlist linked list
			if (toDelete->playlists[0] != ""){
				*(d + 0) = title;
				*(d + 1) = singer;
				for (int i = 2; i < 7; i++) {
					*(d + i) = toDelete->playlists[i - 2];
				}
			}

			// delete the collection node if it is the first song node in the collection linked list
			if (toDelete == head) {
				head = head->next;
				delete toDelete;
			}
			// delete the collection node if it is at random position in the collection linked list 
			else {
				prev->next = toDelete->next;
				delete toDelete;
			}
			size--;
			cout << "Song have deleted\n";
		}
		else {
			cout << "Song not found\n";
		}
	}
}

//search for a collection node to display its playlist info
void CollectionLinkedList::playlistSearch() {
	bool found = false;
	string title, singer;

	// check if there any collection node in the collection linked list
	if (head == NULL) {
		cout << "The collection is empty. No song can be searched\n";
	}
	else {
		// ask for user input for the collection node to be searched for playlist info
		cout << "Enter the title of the song to search for the playlist\n";
		cin >> title;
		cout << "Enter the singer's name of the song\n";
		cin >> singer;

		CollectionNodeType* current = head;
		while (current != NULL) {
			// check the availability of the collection node to be searched in collection linked list
			if (current->title == title && current->singer == singer) {
				found = true;
				break;
			}
			current = current->next;
		}
		if (found) {
			// check the availability of playlist info of the collection node that searched by the user
			if (current->playlists[0] != "") {
				// output the playlists info of the collection node
				for (int i = 0; i <5; i++) {
					if (current->playlists[i] != "") {
						cout << current->playlists[i] << "\n";
					}
				}
			}
			else {
				cout << "The song have not be added into any playlist yet\n";
			}
		}
		else {
			cout << "Song not found\n";
		}
	}
}

// travel the collection linked list to check for the avaibility of certain playlist in the playlist info of the collection node and delete that playlist from playlist info
void CollectionLinkedList::updatePlaylist(string p) {
	int exist=NULL, empty=NULL;

	// check if there any collection node needed to be updated for the playlist info
	if (p != "") {
		CollectionNodeType* current = head;

		// travel the collection linked list
		while (current != NULL) {
			bool flag = false;

			// check the availability of playlist info for the current pointed collection node
			if (current->playlists[0] != "") {
				for (int i = 0; i < 5; i++){

					// check the position of the playlist that needed to be removed from playlist info
					if (current->playlists[i] == p) {
						exist = i;
						flag = true;
					}

					// check the position of empty value in the array of playlist info
					if (current->playlists[i] == "") {
						empty = i;
						break;
					}
				}
			}

			// update the playlist info of the pointed collection node 
			if (flag) {
				if (empty > 0) {
					current->playlists[exist] = current->playlists[empty - 1];
					current->playlists[empty - 1] = "";
				}
			}
			current = current->next;
		}
	}
}

//search for certain collection node in collection linked list to return the pointer of that collection node if available
CollectionNodeType* CollectionLinkedList::searchSongToAdd() {
	bool exist = false;
	bool full = false;
	string title, singer;
	CollectionNodeType* current = head;
	cout << "Enter the title of the song to be added\n";
	cin >> title;
	cout << "Enter the name of the singer to be added\n";
	cin >> singer;

	// check if there any collection node in the collection linked list
	if (head != NULL) {

		while (current != NULL) {
			// check the availability of the collection node to be searched in the collection linked list
			if (current->title == title && current->singer == singer) {
				exist = true;

				// check whether the collection node's playlist array has fulled
				if (current->playlists[4] != "") {
					full = true;
				}
				break;
			}
			current = current->next;
		}
		if (!exist) {
			cout << "Song not found\n";
		}
		if (full) {
			cout << "You cannot add this song into current playlist. The song has added into 5 playlists\n";
			current = NULL;
		}
	}
	else {
		cout << "Collection is empty. No song can be added\n";
	}
	return current;
}


// add certain playlist into the playlist info of the collection node in collection linked list
void CollectionLinkedList::addPlaylist(CollectionNodeType* c, PlaylistNodeType* p) {
	int i = 0;
	
	// travel to the empty position of playlist array of the collection node that pointed by pointer c in collection linked list
	while (c->playlists[i] != "") {
		i++;
	}
	
	//add the playlist name into the playlist info of the collection node
	c->playlists[i] = p->name;
}

//search for a collection node in collection linked list and delete certain playlist info from that collection node
void CollectionLinkedList::updateCollection(string details, PlaylistNodeType* p) {
	int exist = NULL, empty = NULL;

	// seperate the string to extract details of song node by delimiter
	/**
	* Following source code obtained from (Yola, 2017)
	*/
	stringstream ss(details);
	string token, title, singer;
	int count = 0;
	bool flag = false;
	while (getline(ss, token, ',')) {
		if (count == 0) {
			title = token;
			count = count + 1;
		}
		else if (count == 1) {
			singer = token;
		}
	}
	CollectionNodeType* current = head;
	if (title != "" && singer != "") {

		// travel the collection linked list
		while (current != NULL) {

			// check the info of the collection node
			if (current->singer == singer && current->title == title) {

				// travel the playlist array of collection node
				for (int i = 0; i < 5; i++) {

					// check the availability of the playlist deleted 
					if (current->playlists[i] == p->name) {
						exist = i;
						flag = true;
					}

					// check the position of empty value in the array
					if (current->playlists[i] == "") {
						empty = i;
						break;
					}

					
				}
				if (current->playlists[4] != "") {
					empty = 5;
				}
				break;				
			}
			current = current->next;
		}
	}
	if (flag) {
		if (empty > 0) {
			current->playlists[exist] = current->playlists[empty - 1];
			current->playlists[empty - 1] = "";
		}
	}
}