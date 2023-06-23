// Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "CollectionLinkedList.h"
#include "PlaylistLinkedList.h"
#include <thread>
#include <algorithm>
#include <iterator>
#include <Windows.h>
#include <fstream>
#include <sstream>
using namespace std;
using std::cout;
using std::cin;

int input;
bool check4 = true;

void listen_input(); 


int main()
{
    bool check = true, check1 = true, check2 = true, check3 = true;
    bool play = true, shuffle = false, loop = false, previous = false;
    int option, option1, option2, option3;
    CollectionLinkedList collectionList;
    PlaylistLinkedList playlistList;
    PlaylistNodeType* selectedPlaylist;
    CollectionNodeType* curCollection;
    string playlist, details;
    bool flag;
    string* detailsToDelete;
    string timeString, timefirst, timethird, timefourth, sumsecond, strsecond2, strminutes, display,username,password,readtext,fileusername,filepassword,token;
    int second, minute, sum, minute2, second2, count=0, indicator=0;

 
    PlaylistNodeType* newCopiedPlaylistNode = new PlaylistNodeType;
    PlaylistNodeType* newShuffledPlaylistNode = new PlaylistNodeType;
    
    SongNodeType* toCopy;
    SongNodeType* toShuffle;

    while (true) {

        // ask user for the username and password to validate
        ifstream myReadFile("user.txt");
        username = "";
        password = "";
        indicator = 0;
        cout << "Enter your name and password: \n";

        // if input equal to 3, exit the application
        cin >> username;
        if (username == "3") {
            return 0;
        }

        cin >> password;
        if (password == "3") {
            return 0;
        }

       //read the file and compare the username and password  
       /**
       * Following source code obtained from (w3schools, n.d.)
       */
        while (getline(myReadFile, readtext)) {
            stringstream ss(readtext);
            while (getline(ss, token, ',')) {
                if (count == 0) {
                    fileusername = token;
                    count++;
                }
                else if (count == 1) {
                    filepassword = token;
                    count = 0;
                }

            }
            if (username == fileusername && password == filepassword) {
                indicator = 1;
                break;
            }
            else if (username == fileusername && password != filepassword) {
                indicator = 2;
                break;
            }
            else if (username != fileusername) {
                indicator = 3;
            }

        }
               
        //display the related message  
        switch (indicator) {
        case 1:
            cout << "Validate user\n";
            break;

        case 2:
            cout << "Wrong password. Please reenter your password. Enter 3 to exit\n";
            break;

        case 3:
            cout << "User not found! Enter 3 to exit\n";
            break;
        }
        if (indicator == 1) {
            break;
        }   
        myReadFile.close();
    }

    do {
        check = true;
        cout << "Please select the operation \n1.Song collection\n2.Playlists\n3.Exit\n";
        cin >> option;
        switch (option) {
         case 1:
                do {
                    check1 = true;
                    string detailsToDeleteArray[7] = { "","","","","","","" };
                    detailsToDelete = detailsToDeleteArray;
                    cout << "Please select the operation \n1.Insert song\n2.Display songs\n3.Delete song\n4.Playlists search\n5.Back\n";
                    std::cin >> option1;

                    switch (option1) {
                    case 1:
                        collectionList.addSong();
                        break;
                    case 2:
                        collectionList.displaySong();
                        break;
                    case 3:
                        collectionList.deleteSong(detailsToDelete);
                        playlistList.updatePlaylist(detailsToDelete);
                        break;
                    case 4:
                        collectionList.playlistSearch();
                        break;
                    case 5:
                        check1 = false;
                        break;
                    default:
                        cout << "Invalid input\n";
                        cin.clear();
                        cin.ignore();  
                        break;
                    }
                } while (check1 == true);
                detailsToDelete = NULL;
                break;
        case 2:
            do{
                check2 = true;
                cout << "Please select the operation \n1.Create playlist\n2.View playlists\n3.Delete playlist\n4.Select playlist\n5.Back\n";
                cin >> option2;

                switch (option2) {
                case 1:
                    playlistList.createPlaylist();
                    break;
                case 2:
                    playlistList.viewPlaylist();
                    break;
                case 3:
                    playlist = playlistList.deletePlaylist();
                    collectionList.updatePlaylist(playlist);
                    break;
                case 4:
                    selectedPlaylist = playlistList.selectPlaylist();
                    // to check if the playlist node available
                    if (selectedPlaylist != NULL) {
                        do {
                            check3 = true;
                            cout << "Please select the operation \n1.Add song\n2.View songs\n3.Delete song\n4.Play song\n5.Back\n";
                            cin >> option3;

                            switch (option3) {
                            case 1:
                                curCollection = collectionList.searchSongToAdd();
                                // check if the song that wanted to added by the user if available
                                if (curCollection != NULL) {
                                    flag = playlistList.addSongIntoPlaylist(selectedPlaylist, curCollection);
                                    // check if the song node have added into the playlist linked list
                                    if (flag == true) {
                                        collectionList.addPlaylist(curCollection, selectedPlaylist);
                                    }
                                }
                                break;
                            case 2:
                                playlistList.viewSongInPlaylist(selectedPlaylist);
                                break;
                            case 3:
                                details = playlistList.removeSongFromPlaylist(selectedPlaylist);
                                collectionList.updateCollection(details, selectedPlaylist);
                                break;
                            case 4:
                                //check the availability of song node of the selected playlist node in the playlist linked list
                                if (selectedPlaylist->tailSong != NULL) {
                                    
                                    play = true;
                                    shuffle = false;
                                    loop = false;  
                                    previous = false;
                                    int time;
                                    double time1;
                                    int size, random;
                                    

                               
                                    // populate copied playlist node 
                                    newCopiedPlaylistNode->tailSong = NULL;
                                    newCopiedPlaylistNode->size = selectedPlaylist->size;

                                    size = selectedPlaylist->size;
                                    toCopy = selectedPlaylist->tailSong->next;

                                
                                    // duplicating the song node in selected playlist node
                                    for (int i = 0; i < size; i++) {

                                        //create and populate song node for copied playlist node
                                        SongNodeType* newCopiedSongNode = new SongNodeType;
                                        newCopiedSongNode->title = toCopy->title;
                                        newCopiedSongNode->singer = toCopy->singer;
                                        newCopiedSongNode->duration = toCopy->duration;
                                        if (newCopiedPlaylistNode->tailSong == NULL) {
                                            newCopiedPlaylistNode->tailSong = newCopiedSongNode;
                                            newCopiedSongNode->next = newCopiedSongNode;
                                            newCopiedSongNode->prev = newCopiedSongNode;
                                        }
                                        else {
                                            newCopiedSongNode->prev = newCopiedPlaylistNode->tailSong;
                                            newCopiedSongNode->next = newCopiedSongNode->prev->next;
                                            newCopiedPlaylistNode->tailSong->next = newCopiedSongNode;
                                            newCopiedPlaylistNode->tailSong = newCopiedSongNode;
                                            newCopiedSongNode->next->prev = newCopiedSongNode;
                                        }
                                        toCopy = toCopy->next;
                                    }


                                    //populate shuffled playlist node 
                                    newShuffledPlaylistNode->size = selectedPlaylist->size;
                                    newShuffledPlaylistNode->tailSong = NULL;
                                                                
                                    
                                    if (newCopiedPlaylistNode->tailSong != NULL) {
                                        cout << "Entry 1" << endl;
                                        toShuffle = newCopiedPlaylistNode->tailSong->next;
                                        
                                        // populate the shuffled playlist node by ramdonly duplicating the song node in copied playlist node
                                        for (int i = 0; i < size; i++) {
                                            random = rand() % (size - i);
                                            for (int j = 0; j <= random; j++) {
                                                toShuffle = toShuffle->next;
                                            }

                                            //create and populate song node for shuffled playlist node
                                            SongNodeType* newShuffledSongNode = new SongNodeType;
                                            newShuffledSongNode->title = toShuffle->title;
                                            newShuffledSongNode->singer = toShuffle->singer;
                                            newShuffledSongNode->duration = toShuffle->duration;

                                            if (newShuffledPlaylistNode->tailSong == NULL) {
                                                newShuffledPlaylistNode->tailSong = newShuffledSongNode;
                                                newShuffledSongNode->next = newShuffledSongNode;
                                                newShuffledSongNode->prev = newShuffledSongNode;
                                            }
                                            else {
                                                newShuffledSongNode->prev = newShuffledPlaylistNode->tailSong;
                                                newShuffledSongNode->next = newShuffledSongNode->prev->next;
                                                newShuffledPlaylistNode->tailSong->next = newShuffledSongNode;
                                                newShuffledPlaylistNode->tailSong = newShuffledSongNode;
                                                newShuffledSongNode->next->prev = newShuffledSongNode;
                                            }

                                            SongNodeType* toDelete = toShuffle;

                                            // delete the current song node for copied playlist node
                                            if (toDelete != NULL) {
                                                                                              
                                                if (toDelete == newCopiedPlaylistNode->tailSong && toDelete->next == newCopiedPlaylistNode->tailSong) {
                                                    newCopiedPlaylistNode->tailSong = NULL;
                                                    delete toDelete;
                                                }
                                                else {
                                                    toShuffle = toShuffle->next;
                                                    toDelete->prev->next = toDelete->next;
                                                    toDelete->next->prev = toDelete->prev;
                                                    if (toDelete == newCopiedPlaylistNode->tailSong) {
                                                        newCopiedPlaylistNode->tailSong = toDelete->prev;
                                                    }
                                                    delete toDelete;
                                                }
                                                newShuffledPlaylistNode->size--;
                                            }
                                        }
                                    }
                                 
                                    cout << "Please select the operation \n1.Pause/Play\n2.Previous\n3.Next\n4.Loop current song\n5.Loop playlist\n6.Shuffle\n7.Exit\n";

                                    // check the availability of song node in the selected playlist node
                                    if (selectedPlaylist->tailSong->next != NULL) {
                                        SongNodeType* current = selectedPlaylist->tailSong->next;
                                        cout << endl << "current song: " << current->title << " by " << current->singer << endl;
                                        time1 = current->duration;
                                        
                                        //open the thread and listen to input
                                        /**
                                        * Following source code obtained from (Software Testing Help, 2021)
                                        */
                                        thread th1(listen_input);
                                        do {
                                            //convert time in double to string and extract the minute and second to add up to find the sum of the second
                                            timefirst = "";
                                            timethird = "";
                                            timefourth = "";
                                            timeString = to_string(time1);
                                            timefirst = timefirst + timeString[0];
                                            timethird = timethird + timeString[2];
                                            timefourth = timefourth + timeString[3];
                                            sumsecond = timethird + timefourth;
                                            second = stoi(sumsecond);
                                            minute = stoi(timefirst);
                                            minute = minute * 60;
                                            sum = 0;
                                            sum = minute + second;

                                            time = sum;
                                            
                                            check4 = true;
                                            while (time >= 0) {

                                                
                                                input = 0;
                                                if (play) {

                                                    // calculate the minute and second and display 
                                                    minute2 = time / 60;
                                                    second2 = time % 60;

                                                    if (second2 >= 0 && second2 <= 9) {
                                                        strsecond2 = to_string(second2);
                                                        strsecond2 = "0" + strsecond2;
                                                    }
                                                    else {
                                                        strsecond2 = to_string(second2);
                                                    }
                                                    strminutes = to_string(minute2);
                                                    display = strminutes + "." + strsecond2;
                                                    cout << current->title << "\rTime remaining: " << display<<flush;

                                                    //stop the program for one second
                                                    Sleep(1000);

                                                    // reduce the time
                                                    time--;
                                                }
                                                else { 
                                                    // stop for program for one second
                                                    Sleep(1000);
                                                }

                                                if (input == 1) {
                                                    if (play) {
                                                        play = false;
                                                    }
                                                    else {
                                                        play = true;
                                                    }
                                                }
                                                else if (input == 2) {
                                                    if (!shuffle) {
                                                        if (current != selectedPlaylist->tailSong->next) {
                                                            // travel to two previous song node and reintialize the time to zero
                                                            playlistList.previousSong(current, current);
                                                            time = 0;
                                                            previous = true;
                                                        }
                                                        else {
                                                            // reinitialilze the time to sum
                                                            time = sum;
                                                        }
                                                    }
                                                    else {
                                                        if (current != newShuffledPlaylistNode->tailSong->next) {
                                                            // travel to two previous song node and reintialize the time to zero
                                                            playlistList.previousSong(current, current);
                                                            time = 0;
                                                            previous = true;
                                                        }
                                                        else {
                                                            // reinitialilze the time to sum
                                                            time = sum;                                                           
                                                        }
                                                    }

                                                    break;
                                                }
                                                else if (input == 3) {
                                                    time = 0;
                                                    break;
                                                }
                                                else if (input == 4) {
                                                    playlistList.loopSong(current, current);
                                                    previous = true;
                                                }
                                                else if (input == 5) {
                                                    if (loop) {
                                                        loop = false;
                                                    }
                                                    else {
                                                        loop = true;
                                                    }

                                                }
                                                else if (input == 6) {
                                                    if (shuffle) {
                                                        SongNodeType* toShift = selectedPlaylist->tailSong->next;
                                                        do {
                                                            //travel the song node for selected playlist node to find the song node which match with the details of current song node
                                                            if (toShift->title == current->title && toShift->singer == current->singer) {
                                                                current = toShift;
                                                                break;
                                                            }
                                                            toShift = toShift->next;
                                                        } while (toShift != selectedPlaylist->tailSong->next);
                                                        shuffle = false;
                                                    }
                                                    else {
                                                        SongNodeType* toShift = newShuffledPlaylistNode->tailSong->next;
                                                        SongNodeType* toShiftPrev = newShuffledPlaylistNode->tailSong;
                                                        do {
                                                            //travel the song node for shuffled playlist node to find the song node which match with the details of current song node
                                                            if (toShift->title == current->title && toShift->singer == current->singer) {
                                                                current = toShift;
                                                                break;
                                                            }
                                                            toShiftPrev = toShift;
                                                            toShift = toShift->next;
                                                        } while (toShift != newShuffledPlaylistNode->tailSong->next);

                                                        // update the tail for shuffled playlist node
                                                        newShuffledPlaylistNode->tailSong = toShiftPrev;
                                                        shuffle = true;
                                                    }
                                                }
                                                else if (input == 7) {
                                                    check4 = false;
                                                    break;
                                                }
                                               
                                            }
                                            if (time <= 0) {
                                                current = current->next;
                                                time1 = current->duration;
                                                if (!previous) {
                                                    if (!loop) {
                                                        if (shuffle) {
                                                            if (current == newShuffledPlaylistNode->tailSong->next) {
                                                                check4 = false;
                                                                cout << endl << "Playlist has reached the end. Please enter 7 to exit and proceed to other operation." << endl;
                                                                break;
                                                            }
                                                        }
                                                        else {
                                                            if (current == selectedPlaylist->tailSong->next) {
                                                                check4 = false;
                                                                cout << endl << "Playlist has reached the end. Please enter 7 to exit and proceed to other operation." << endl;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                }
                                                previous = false;
                                                cout << endl << "\n" << "current song: " << current->title << " by " << current->singer << endl;
                                            }
                                        } while (check4 == true);
                                        th1.join();
                                       
                                    }
                                    
                                }
                                else {
                                    cout << "No song can be played in this playlist\n";
                                }

                                //clearing the song node for shuffled playlist node
                                if (newShuffledPlaylistNode->tailSong != NULL) {
                                    toCopy = newShuffledPlaylistNode->tailSong->next->next;
                                    toShuffle = newShuffledPlaylistNode->tailSong->next;
                                    do {
                                        if (toShuffle != newShuffledPlaylistNode->tailSong) {
                                            delete toShuffle;
                                            toShuffle = toCopy;
                                            if (toCopy != newShuffledPlaylistNode->tailSong) {
                                                toCopy = toCopy->next;
                                            }
                                        }
                                        else {
                                            delete toShuffle;
                                            newShuffledPlaylistNode->tailSong = NULL;
                                            newShuffledPlaylistNode->size = 0;
                                        }
                                    } while (newShuffledPlaylistNode->tailSong != NULL);
                                    toShuffle = NULL;
                                    toCopy = NULL;
                                }
                                break;

                            case 5:
                                check3 = false;
                                break;
                            default:
                                cout << "Invalid input\n";
                                cin.clear();
                                cin.ignore();
                                break;
                            }
                        } while (check3 == true);
                    }
                    break;
                case 5:
                    check2 = false;
                    break;
                default:
                    cout << "Invalid input\n";
                    cin.clear();
                    cin.ignore();
                    break;
                 }                
                }while (check2 == true);
                break;
        case 3:
            check = false;
            break;
        default:
            cout << "Invalid input\n";
            cin.clear();
            cin.ignore();
            break;
        } 
    }while (check == true);
    return 0;
}

//listen for user input 
void listen_input() {
    while (true) {
        cin >> input; 
        // check and compare the input
        if (input == 7) {
            break;
        }
        if (input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 6 && input != 7 && input != NULL) {
            cin.clear();
            cin.ignore();
        }
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
