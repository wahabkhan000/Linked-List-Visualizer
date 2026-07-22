#include <limits>
#include <iostream>
#include <windows.h>
using std::cout,std::cin,std::string,std::endl;
struct Node{
    string Song_name;
    string Artist;
    string Duration;
    Node *next;
    Node *prev;
    Node(const string &song_name,const string &artist_name,const string &duration){
        Song_name = song_name;
        Artist = artist_name;
        Duration = duration;
        next = nullptr;
        prev = nullptr;
    }
};
void pause() {
    cout<<"******* Please Wait! we are processing your request *******"<<endl;
    Sleep(1000);
}
void get_length(int &length) {
    pause();
    int key = 0;
    do {
        if (key == 0) {
            cout<<"Enter the total number of songs you want to enter in playlist: "<<endl;
        }
        else {
            cout<<"Please enter the correct number above 0."<<endl;
        }
        cin>>length;
        key = 1;
    }while (length<1);
}
void node_addition(Node *&Tail) {
    string Song_name;
    cout<<"Enter Song Name:"<<endl;
    std::getline(cin,Song_name);
    string Artist_name;
    cout<<"Enter Artist Name:"<<endl;
    std::getline(cin,Artist_name);
    string Duration;
    cout<<"Enter Song Duration:"<<endl;
    std::getline(cin,Duration);
    Node *temp = new Node(Song_name,Artist_name,Duration);
    Tail->next = temp;
    temp->prev = Tail;
    Tail = temp;

}
void node_creation(Node *&Head, Node *&Tail, int length) {
    for (int i=0;i<length;i++) {
        if (Head == nullptr) {
            pause();
            cout<<"Enter details of Song No. "<<i+1<<":"<<endl;
            string Song_name;
            cout<<"Enter Song Name:"<<endl;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(cin,Song_name);
            string Artist_name;
            cout<<"Enter Artist Name:"<<endl;
            std::getline(cin,Artist_name);
            string Duration;
            cout<<"Enter Song Duration:"<<endl;
            std::getline(cin,Duration);
            Head = new Node(Song_name,Artist_name,Duration);
            Tail = Head;
        }
        else {
            pause();
            cout<<"Enter details of Song No. "<<i+1<<":"<<endl;
            node_addition(Tail);
        }
    }
    Tail->next = Head;
    Head->prev = Tail;
}
void menu() {
    cout<<"======= MUSIC PLAYLIST =======\n"
          "1. Add Song\n"
          "2. Delete Current Song\n"
          "3. Play Current Song\n"
          "4. Next Song\n"
          "5. Previous Song\n"
          "6. Show Playlist\n"
          "7. Search Song\n"
          "8. Jump To Song\n"
          "9. Rename Song\n"
          "0. Exit\n"
          "Choice:"<<endl;
}
void node_deletion(Node *&curr,Node *&Head) {
    if (Head == nullptr || curr == nullptr) {
        return;
    }
    if (curr->next == curr) {
        delete curr;
        Head = nullptr;
        return;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    if (curr == Head) {
        Head = curr->next;
    }
    delete curr;
}
bool song_search(const string &playlist_song,const string &comparison_song) {
    string playlist_copy;
    string comparison_copy;
    for (int i=0;i<playlist_song.length();i++) {
        if (playlist_song[i] != ' ') {
            playlist_copy+=playlist_song[i];
            if (playlist_copy[i]>='A'&&playlist_copy[i]<='Z') {
                playlist_copy[i]+=32;
            }
        }
    }
    for (int i=0;i<comparison_song.length();i++) {
        if (comparison_song[i] != ' ') {
            comparison_copy+=comparison_song[i];
            if (comparison_copy[i]>='A'&&comparison_copy[i]<='Z') {
                comparison_copy[i]+=32;
            }
        }
    }
    if (comparison_copy!=playlist_copy) {
        return false;
    }
    else {
        return true;
    }
}
void all_node_deletion(Node *& Head) {
    Node *curr = Head->next;
    while (curr != Head) {
        Node *temp = curr->next;
        delete curr;
        curr = temp;
    }
    delete Head;
    Head = nullptr;
}
int main() {
    Node *Head = nullptr;
    Node *Tail = Head;
    int length = 0;
    get_length(length);
    node_creation(Head,Tail,length);
    Node *traverse = Head;
    int move = -1;
    pause();
    while (true) {
        int key = 0;
        do {
            if (key == 0) {
                cout<<"Select the operation from menu and Press[0-9]:"<<endl;
                menu();
            }
            else {
                cout<<"You press wrong button. Please press again:"<<endl;
                menu();
            }
            cin>>move;
            key = 1;
        }while (move>9 || move<0);
        if (move == 1) {
            pause();
            key = 0;
            int reply = 0;
            cout<<"Do you want to add new song?\nPress[0] for \"NO\" and Press[1] for \"YES\":"<<endl;
            do {
                if (key == 1) {
                    cout<<"You press wrong button:"<<endl;
                }
                cin>>reply;
                key = 1;
            }while (reply>1 || reply<0);
            if (reply == 1) {
                pause();
                length++;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                node_addition(Tail);
                Tail->next = Head;
                Head->prev = Tail;
                cout<<"Song added successfully!"<<endl;
            }
        }
        if (move == 2) {
            pause();
            key = 0;
            int reply = 0;
            cout<<"Do you want to delete current song?\nPress[0] for \"NO\" and Press[1] for \"YES\":"<<endl;
            do {
                if (key == 1) {
                    cout<<"You press wrong button:"<<endl;
                }
                cin>>reply;
                key = 1;
            }while (reply>1 || reply<0);
            if (reply == 1) {
                pause();
                if (length == 0) {
                    cout<<"You deleted the whole playlist. So there is no song to process. Thank you."<<endl;
                    break;
                }
                node_deletion(traverse,Head);
                length--;
                cout<<"Song deleted successfully!"<<endl;
            }
        }
        if (move == 3) {
            pause();
            cout<<"Now Playing\n"
                "\tSong    : "<<traverse->Song_name<<"\n"
                "\tArtist  : "<<traverse->Artist<<"\n"
                "\tDuration: "<<traverse->Duration<<endl;
        }
        if (move == 4) {
            pause();
            traverse = traverse->next;
            cout<<"Current Song is:"<<traverse->Song_name<<endl;
        }
        if (move == 5) {
            pause();
            traverse = traverse->prev;
            cout<<"Current Song is:"<<traverse->Song_name<<endl;
        }
        if (move == 6) {
            pause();
            Node *curr = Head;
            int song_count = 1;
            cout<<"Playlist"<<endl;
            for (int i=0;i<length;i++) {
                cout<<"\tSong No. : "<<song_count<<"\n"
                "\tSong name : "<<curr->Song_name<<"\n"
                "\tArtist : "<<curr->Artist<<"\n"
                "\tDuration : "<<curr->Duration<<endl;
                curr = curr->next;
                song_count++;
            }
        }
        if (move == 7 || move == 8 || move == 9) {
            pause();
            bool flag = false;
            string search_song;
            if (move == 7) {
                cout<<"Please enter the song name you want to search:"<<endl;
            }
            if (move == 8) {
                cout<<"Please enter the song name you want to jump to:"<<endl;
            }
            if (move == 9) {
                cout<<"Please enter the song name you want to rename:"<<endl;
            }
            std::getline(cin,search_song);
            pause();
            Node *search = Head;
            for (int i=0;i<length;i++) {
                if (song_search(search->Song_name,search_song)) {
                    flag = true;
                    break;
                }
                search = search->next;
            }
            if (flag) {
                if (move == 7) {
                    cout<<"Song Found\n\n"
                        "Song : "<<search->Song_name<<"\n"
                        "Artist : "<<search->Artist<<"\n"
                        "Duration : "<<search->Duration<<endl;
                }
                if (move == 8) {
                    traverse = search;
                    cout<<"Song Found\n\n"
                        "The current song is:\n"
                        "Song : "<<traverse->Song_name<<"\n"
                        "Artist : "<<traverse->Artist<<"\n"
                        "Duration : "<<traverse->Duration<<endl;
                }
                if (move == 9) {
                    traverse = search;
                    cout<<"Enter the new name for "<<traverse->Song_name<<":"<<endl;
                    std::getline(cin,search_song);
                    traverse->Song_name = search_song;
                    pause();
                    cout<<"Song is successfully renamed\n\n"
                        "The new name is:\n"
                        "Song : "<<traverse->Song_name<<"\n"
                        "Artist : "<<traverse->Artist<<"\n"
                        "Duration : "<<traverse->Duration<<endl;
                }
            }
            else {
                cout<<"Song Not Found"<<endl;
            }
        }
        if (move == 0) {
            pause();
            key = 0;
            int reply = 0;
            cout<<"Do you want to Exit?\nPress[0] for \"NO\" and Press[1] for \"YES\":"<<endl;
            do {
                if (key == 1) {
                    cout<<"You press wrong button:"<<endl;
                }
                cin>>reply;
                key = 1;
            }while (reply>1 || reply<0);
            if (reply == 1) {
                break;
            }
        }
    }
    if (length!=0) {
        all_node_deletion(Head);
    }
    pause();
    cout<<"All the songs are deleted and You Successfully Exit the playlist!"<<endl;
    cout<<"Thank you for your time and co-operation."<<endl;
    return EXIT_SUCCESS;
}
