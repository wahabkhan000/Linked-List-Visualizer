#include <iostream>
#include <limits>
using std::cout,std::cin,std::string,std::endl;
struct Node{
    char character;
    Node *next;
    Node *prev;
    Node(char character) {
        this->character = character;
        next = nullptr;
        prev = nullptr;
    }
};
char read_character() {
    char character;
    cout<<"Enter the character you want to insert:"<<endl;
    cin>>character;
    return character;
}
void insert_character(Node *&Head,Node *&cursor,Node *&Tail) {
    if (Head == nullptr) {
        Head = new Node(read_character());
        cursor = Head;
        Tail = Head;
    }
    else {
        if (!(cursor->next)) {
            Tail->next = new Node(read_character());
            Tail->next->prev = Tail;
            Tail = Tail->next;
            cursor = Tail;
        }
        else if (!(cursor->prev)) {
            Head->prev = new Node(read_character());
            Head->prev->next = Head;
            Head = Head->prev;
            cursor = Head;
        }
        else {
            Node *temp = new Node(read_character());
            cursor->next->prev = temp;
            temp->next = cursor->next;
            temp->prev = cursor;
            cursor->next = temp;
            cursor = temp;
        }
    }
}
void menu() {
    cout<<"========== TEXT EDITOR ==========\n"
          "1. Insert Character \n"
          "2. Delete Character \n"
          "3. Move Cursor Left \n"
          "4. Move Cursor Right \n"
          "5. Show Current Text \n"
          "6. Show Text with Cursor \n"
          "7. Clear Entire Text \n"
          "0. Exit\n"
          "Choice:"<<endl;
}
void character_deletion(Node *&Head,Node *&cursor,Node *&Tail) {
    if (Head == nullptr || cursor == nullptr) {
        cout<<"\aThere is no Text to delete!"<<endl;
        return;
    }
    if (cursor == Head) {
        Node *temp = Head;
        if (Head->next) {
            Head = Head->next;
            Head->prev = nullptr;
            cursor = Head;
            delete temp;
        }
        else {
            delete temp;
            Head = nullptr;
            cursor = nullptr;
            Tail = nullptr;
        }
        cout<<"Text deleted successfully."<<endl;
        return;
    }
    if (cursor == Tail) {
        Node *temp = Tail;
        Tail->prev->next = nullptr;
        Tail = Tail->prev;
        cursor = Tail;
        delete temp;
        cout<<"Text deleted successfully."<<endl;
        return;
    }
    Node *temp = cursor;
    cursor->prev->next = cursor->next;
    cursor->next->prev = cursor->prev;
    cursor = cursor->prev;
    delete temp;
    cout<<"Text deleted successfully."<<endl;
}
void entire_text_deletion(Node *& Head,Node *&cursor,Node *&Tail) {
    if (Head == nullptr) {
        cout<<"\aThere is no Text to delete!"<<endl;
        return;
    }
    Node *curr = Head;
    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    cursor = nullptr;
    Tail = nullptr;
    Head = nullptr;
    cout<<"\aText is deleted successfully."<<endl;
}
void move_validation(int &move) {
    move = 0;
    do {
        if (move == 0) {
            cout<<"Choose the operation from menu. and press[0-7]:"<<endl;
        }
        else {
            cout<<"\aInvalid Input! Press again."<<endl;
        }
        menu();
        cin>>move;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (move<0 || move>7);
}
void move_cursor(Node *&Head,Node *&cursor,int argument,string &text) {
    text.clear();
    if (Head) {
        Node *curr = Head;
        cout<<"Current cursor position is: ";
        while (curr) {
            if (curr == cursor && argument == 0) {
                text+='|';
            }
            text+=curr->character;
            if (curr == cursor && argument == 1) {
                text+='|';
            }
            curr = curr->next;
        }
        if (argument == 0 && cursor->prev) {
            cursor = cursor->prev;
        }
        if (argument == 1 && cursor->next) {
            cursor = cursor->next;
        }
        cout<<text<<endl;
    }
    else {
        cout<<"\aThere is no Text to show!"<<endl;
    }
}
void string_match(Node *&Head,Node *&cursor,string &text) {
    if (text.empty()) {
        text = "";
    }
    string match;
    Node *curr = Head;
    while (curr) {
        if (cursor == Head && curr == Head) {
            if (text[0] == '|') {
                match+='|';
                match+=curr->character;
            }
            else if (text[1] == '|') {
                match+=curr->character;
                match+='|';
            }
        }
        else if (curr == cursor){
            match+=curr->character;
            match+='|';
        }
        else {
            match+=curr->character;
        }
        curr = curr->next;
    }
    text = match;
}
int main() {
    string text;
    Node *Head = nullptr;
    Node *Tail = Head;
    Node *cursor = Head;
    while (true) {
        int move = 0;
        move_validation(move);
        if (move == 1) {
            insert_character(Head,cursor,Tail);
        }
        if (move == 2) {
            character_deletion(Head,cursor,Tail);
        }
        if (move == 3) {
            move_cursor(Head,cursor,0,text);
        }
        if (move == 4) {
            move_cursor(Head,cursor,1,text);
        }
        if (move == 5) {
            if (Head) {
                Node *curr = Head;
                cout<<"Current Text is: ";
                while (curr) {
                    cout<<curr->character;
                    curr = curr->next;
                }
                cout<<endl;
            }
            else {
                cout<<"\aThere is no Text to show!"<<endl;
            }
        }
        if (move == 6) {
            if (Head) {
                string_match(Head,cursor,text);
                cout<<"Current Text with cursor is: ";
                cout<<text<<endl;
            }
            else {
                cout<<"\aThere is no Text to show!"<<endl;
            }
        }
        if (move == 7) {
            entire_text_deletion(Head,cursor,Tail);
        }
        if (move == 0) {
            cout<<"You selected to exit the Text Editor."<<endl;
            break;
        }
    }
    if (Head) {
        entire_text_deletion(Head,cursor,Tail);
    }
    cout<<"You Successfully Exit the Text Editor!"<<endl;
    cout<<"Thank you for your time and co-operation."<<endl;
    return EXIT_SUCCESS;
}
