#include <limits>
#include <iostream>
using std::cout,std::cin,std::string,std::endl;
struct Page {
    string Title;
    string URL;
    string Visit_Time;
};
struct Node{
    Page page_detail;
    Node *next;
    Node *prev;
    Node() {
        next = nullptr;
        prev = nullptr;
    }
};
void read_page_details(Node *&traverse) {
    cout<<"Enter Page Title:"<<endl;
    std::getline(cin,traverse->page_detail.Title);
    cout<<"Enter Page URL:"<<endl;
    std::getline(cin,traverse->page_detail.URL);
    cout<<"Enter Visit_Time of Page:"<<endl;
    std::getline(cin,traverse->page_detail.Visit_Time);
}
void new_page_visit(Node *&Tail) {
    Node *temp = new Node();
    read_page_details(temp);
    Tail->next = temp;
    temp->prev = Tail;
    Tail = temp;
}
void page_visit(Node *&Head, Node *&Tail) {
    if (Head == nullptr) {
        cout<<"Enter details of Page you want to visit: "<<endl;
        Head = new Node();
        read_page_details(Head);
        Tail = Head;
    }
    else {
        cout<<"Enter details of Page you want to visit: "<<endl;
        new_page_visit(Tail);
    }
}
void menu() {
    cout<<"========= BROWSER HISTORY =========\n"
          "1. Visit Page\n"
          "2. Back\n"
          "3. Forward\n"
          "4. Show Current Page\n"
          "5. Show History\n"
          "0. Exit\n"
          "Choice:"<<endl;
}
void page_deletion(Node *&traverse,Node *&Tail) {
    Node *curr = traverse->next;
    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    Tail = traverse;
    Tail->next = nullptr;
}
void History_deletion(Node *& Head) {
    if (Head == nullptr) {
        return;
    }
    Node *curr = Head;
    while (curr) {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    Head = nullptr;
}
void reply_validation(int &reply) {
    int key = 0;
    do {
        if (key == 0) {
            cout<<"Are you sure? Press [1] for \"YES\" and Press[0] for \"NO\"\n";
        }
        else {
            cout<<"\aInvalid Input! Press [1] for \"YES\" and Press[0] for \"NO\"\n"<<endl;
        }
        cin>>reply;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        key = 1;
    }while (reply>1 || reply<0);
}
void current_page(Node *&traverse) {
    cout<<"\tPage Title : "<<traverse->page_detail.Title<<"\n"
           "\tPage URL : "<<traverse->page_detail.URL<<"\n"
           "\tVisit_Time : "<<traverse->page_detail.Visit_Time<<endl;
}
int main() {
    Node *Head = nullptr;
    Node *Tail = Head;
    page_visit(Head,Tail);
    Node *traverse = Head;
    while (true) {
        int move = -1;
        int key = 0;
        do {
            if (key == 0) {
                cout<<"Select the operation from menu and Press[0-5]:"<<endl;
                menu();
            }
            else {
                cout<<"\aInvalid Input! Please press again:"<<endl;
                menu();
            }
            cin>>move;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            key = 1;
        }while (move>5 || move<0);
        if (move == 1) {
            int reply = -1;
            reply_validation(reply);
            if (reply == 1) {
                if (traverse != Tail) {
                    page_deletion(traverse,Tail);
                }
                new_page_visit(Tail);
                traverse = Tail;
                cout<<"Visited Page Added to History Successfully!"<<endl;
            }
        }
        if (move == 2) {
            if (traverse->prev) {
                traverse = traverse->prev;
                cout<<"After moving backward Current Page is: "<<traverse->page_detail.Title<<endl;
            }
            else {
                cout<<"\aYou cannot go backward further."<<endl;
            }
        }
        if (move == 3) {
            if (traverse->next) {
                traverse = traverse->next;
                cout<<"After moving forward Current Page is: "<<traverse->page_detail.Title<<endl;
            }
            else {
                cout<<"\aYou cannot go forward further."<<endl;
            }
        }
        if (move == 4) {
            cout<<"****** Current Page ******\n";
            current_page(traverse);
        }
        if (move == 5) {
            Node *curr = Head;
            int page_count = 1;
            cout<<"***** Browser History *****"<<endl;
            while (curr) {
                cout<<"\tPage No. : "<<page_count<<"\n";
                current_page(curr);
                curr = curr->next;
                page_count++;
            }
        }
        if (move == 0) {
            int reply = -1;
            reply_validation(reply);
            if (reply == 1) {
                break;
            }
        }
    }
    if (Head) {
        History_deletion(Head);
    }
    cout<<"All the pages are deleted and You Successfully Exit the Browser History!"<<endl;
    cout<<"Thank you for your time and co-operation."<<endl;
    return EXIT_SUCCESS;
}
