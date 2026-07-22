#include <iostream>
using std::cout,std::cin,std::string,std::endl;
struct Node{
    int data;
    Node *next;
    Node *prev;
    Node(int value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }
};
void get_length(int &length) {
    int key = 0;
    do {
        if (key == 0) {
            cout<<"Enter the length of linked list: "<<endl;
        }
        else {
            cout<<"Please enter the correct length above 0."<<endl;
        }
        cin>>length;
        key = 1;
    }while (length<1);
}
void node_creation(Node *&Head, Node *&Tail, int length) {
    cout<<"Enter the values in linked list upto "<<length<<" place:"<<endl;
    for (int i=0;i<length;i++) {
        if (Head == nullptr) {
            int input = 0;
            cin>>input;
            Head = new Node(input);
            Tail = Head;
        }
        else {
            int input = 0;
            cin>>input;
            Node *temp = new Node(input);
            Tail->next = temp;
            temp->prev = Tail;
            Tail = temp;
        }
    }
    Tail->next = Head;
    Head->prev = Tail;
}
void menu() {
    cout<<"1) Move Forward [Press 1]\n"
          "2) Move Backward [Press 2]\n"
          "3) Stop Moving [Press 0]"<<endl;
}
void validate_move(int &move) {
    int key = 0;
    do {
        if (key == 0) {
            cout<<"If you want to move select from menu:"<<endl;
            menu();
        }
        else {
            cout<<"You pressed wrong button! Press Again."<<endl;
            menu();
        }
        key = 1;
        cin>>move;
    }while (move!= 0 && move!= 1 && move!= 2);
}
void validate_forward_jump(int &jump) {
    int key = 0;
    do {
        if (key == 0) {
            cout<<"As you decided to move forward. So, how much steps you want to jump?"<<endl;
        }
        else {
            cout<<"You entered wrong jump. Please TRY AGAIN."<<endl;
        }
        cin>>jump;
        key = 1;
    }while (jump<0);
}
void move_forward(Node *&print,int jump) {
    for (int i=0;i<jump;i++) {
        print = print->next;
    }
}
void validate_backward_jump(int &jump) {
    int key = 0;
    do {
        if (key == 0) {
            cout<<"As you decided to move backward. So, how much steps you want to jump?"<<endl;
        }
        else {
            cout<<"You entered wrong jump. Please TRY AGAIN."<<endl;
        }
        cin>>jump;
        key = 1;
    }while (jump<0);
}
void move_backward(Node *&print,int jump) {
    for (int i=0;i<jump;i++) {
        print = print->prev;
    }
}
void node_deletion(Node *& Head) {
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
    Node *print = Head;
    int move = -1;
    while (move != 0) {
        validate_move(move);
        int jump = 0;
        if (move == 1) {
            validate_forward_jump(jump);
            cout<<"Current Node : "<<print->data<<endl;
            cout<<"Move Forward : "<<jump<<endl;
            move_forward(print,jump%=length);
            cout<<"Reached Node : "<<print->data<<endl;
        }
        if (move == 2) {
            validate_backward_jump(jump);
            cout<<"Current Node : "<<print->data<<endl;
            cout<<"Move Backwards : "<<jump<<endl;
            move_backward(print,jump%=length);
            cout<<"Reached Node : "<<print->data<<endl;
        }
        cout<<endl;
    }
    cout<<"You Press [0]. So you exit the program."<<endl;
    return EXIT_SUCCESS;
}
