#include <iostream>
#include <limits>
using std::cout,std::cin,std::string,std::endl,std::string;
struct Node{
    string Key;
    int Value;
    Node *next;
    Node *prev;
    Node(const string &key,int value) {
        Key = key;
        Value = value;
        next = nullptr;
        prev = nullptr;
    }
};
void hash_function(const string &key,int &buffer) {
    for (int i = key.length()-1;i>=0;i--) {
        buffer =buffer*11+key[i];
    }
    buffer%=10;
}
void key_validation(string &key,Node *bucket[],int &index,int &value) {
    Node *curr = nullptr;
    do {
        key.clear();
        cout<<"Enter key:"<<endl;
        cin>>key;
        hash_function(key,index);
        Node *Head = bucket[index];
        curr = Head;
        while (curr) {
            if (curr->Key == key) {
                cout<<"Key already exist! Retry."<<endl;
                break;
            }
            curr = curr->next;
        }
    }while (curr);
    cout<<"Enter value:"<<endl;
    cin>>value;
}
void insert_key(int *buffer,Node* bucket[],int &collisions,int &stored_elements) {
    int index = 0;
    string key;int value = 0;
    key_validation(key,bucket,index,value);
    buffer[index]++;
    stored_elements++;
    Node *Head = bucket[index];
    Node *Tail = Head;
    if (Head == nullptr) {
        Head = new Node(key,value);
    }
    else{
        collisions++;
        while (Tail->next) {
            Tail = Tail->next;
        }
        Tail->next = new Node(key,value);
        Tail->next->prev = Tail;
    }
    bucket[index] = Head;
    cout<<"Value and Key added to Hash Table."<<endl;
}
void menu() {
    cout<<"=========================================\n"
          "WAHAB HASH TABLE\n"
          "=========================================\n"
          "1. Insert Key-Value Pair \n"
          "2. Search Key \n"
          "3. Update Value \n"
          "4. Delete Key \n"
          "5. Check if Key Exists \n"
          "6. Display Hash Table \n"
          "7. Display Statistics \n"
          "8. Get Total Elements \n"
          "9. Check if Table is Empty \n"
          "10. Clear Hash Table \n"
          "0. Exit\n"
          "=========================================\n"
          "Enter your choice:"<<endl;
}
void delete_key(Node *bucket[],const string &key,int *buffer,int &collisions,int &stored_elements) {
    int index = 0;
    hash_function(key,index);
    Node* Head = bucket[index];
    if (Head == nullptr) {
        cout<<"Invalid Key"<<endl;
        return;
    }
    Node *Tail = Head;
    Node *curr = Head;
    while (curr) {
        if (curr->Key == key) {
            break;
        }
        curr = curr->next;
    }
    if (!curr) {
        cout<<"Invalid Key"<<endl;
        return;
    }
    if (curr == Head) {
        if (Head->next) {
            Node *temp = Head;
            delete temp;
            Head = Head->next;
            Head->prev = nullptr;
            collisions--;
        }
        else {
            delete Head;
            Head = nullptr;
        }
        buffer[index]--;
        stored_elements--;
        cout<<"Key and Value deleted successfully."<<endl;
        bucket[index] = Head;
        return;
    }
    if (!curr->next) {
        while (Tail->next) {
            Tail = Tail->next;
        }
        Node *temp = Tail;
        Tail->prev->next = nullptr;
        delete temp;
        buffer[index]--;
        collisions--;
        stored_elements--;
        cout<<"Key and Value deleted successfully."<<endl;
        bucket[index] = Head;
        return;
    }
    Node *temp = curr;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    buffer[index]--;
    collisions--;
    stored_elements--;
    cout<<"Key and Value deleted successfully."<<endl;
    bucket[index] = Head;
    delete temp;
}
void clear_hash_table(Node* bucket[],int &stored_elements,int &collisions,int *buffer) {
    stored_elements = 0;
    collisions = 0;
    for (int i=0;i<10;i++) {
        buffer[i] = 0;
        Node *Head = bucket[i];
        Node *curr = Head;
        while (curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
        Head = nullptr;
        bucket[i] = Head;
    }
}
void move_validation(int &move) {
    move = 0;
    do {
        if (move == 0) {
            cout<<"Choose the operation from menu. and press[0-10]:"<<endl;
        }
        else {
            cout<<"\aInvalid Input! Press again."<<endl;
        }
        menu();
        cin>>move;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }while (move<0 || move>10);
}
void search_key(Node* bucket[],const string &key) {
    int index = 0;
    hash_function(key,index);
    if (bucket[index] == nullptr) {
        cout<<"Key not exist."<<endl;
        return;
    }
    Node *Head = bucket[index];
    Node *curr = Head;
    while (curr) {
        if (curr->Key == key) {
            break;
        }
        curr = curr->next;
    }
    if (curr) {
        cout<<"Key found:"<<endl;
        cout<<"Key : "<<curr->Key<<endl;
        cout<<"Value : "<<curr->Value<<endl;
    }
    else {
        cout<<"Key not exist"<<endl;
    }
}
void display_hash_table(Node *bucket[]) {
    cout<<"==================== HASH TABLE ===================="<<endl;
    for (int i=0;i<10;i++) {
        cout<<"Bucket "<<i<<" : ";
        Node *Head = bucket[i];
        if (Head == nullptr) {
            cout<<"Empty"<<endl;
        }
        else {
            Node *curr = Head;
            while (curr) {
                cout<<"("<<curr->Key<<","<<curr->Value<<")";
                if (curr->next) {
                    cout<<"->";
                }
                curr = curr->next;
            }
            cout<<endl;
        }
        cout<<endl;
    }
    cout<<"===================================================="<<endl;
}
void update_value(Node *bucket[]) {
    int index = 0;
    string key;
    int new_value = 0;
    cout<<"Enter Key:"<<endl;
    cin>>key;
    hash_function(key,index);
    if (bucket[index] == nullptr) {
        cout<<"Key not exist."<<endl;
        return;
    }
    cout<<"Enter new Value:"<<endl;
    cin>>new_value;
    Node *Head = bucket[index];
    Node *curr = Head;
    while (curr) {
        if (curr->Key == key) {
            break;
        }
        curr = curr->next;
    }
    if (curr) {
        curr->Value = new_value;
        cout<<"Key value updated:"<<endl;
        cout<<"Key : "<<curr->Key<<endl;
        cout<<"Value : "<<curr->Value<<endl;
    }
    else {
        cout<<"Key not exist"<<endl;
    }
}
void chain_length(int &longest_chain,int &shortest_chain,const int *buffer) {
    longest_chain = buffer[0];
    shortest_chain = buffer[0];
    for (int i=0;i<10;i++) {
        if (buffer[i]>longest_chain) {
            longest_chain = buffer[i];
        }
        if (buffer[i]<shortest_chain) {
            shortest_chain = buffer[i];
        }
    }
}
int main() {
    int stored_elements = 0;
    int collisions = 0;
    int buffer[10] = {0};
    Node* bucket[10] = {nullptr};
    while (true) {
        int move = 0;
        move_validation(move);
        if (move == 1) {
            insert_key(buffer,bucket,collisions,stored_elements);
        }
        if (move == 2) {
            string key;
            cout<<"Enter key you want to search:"<<endl;
            cin>>key;
            search_key(bucket,key);
        }
        if (move == 3) {
            update_value(bucket);
        }
        if (move == 4) {
            string key;
            cout<<"Enter key you want to delete:"<<endl;
            cin>>key;
            delete_key(bucket,key,buffer,collisions,stored_elements);
        }
        if (move == 5) {
            string key;
            cout<<"Enter key you want to check:"<<endl;
            cin>>key;
            search_key(bucket,key);
        }
        if (move == 6) {
            display_hash_table(bucket);
        }
        if (move == 7) {
            int longest_chain = 0;
            int shortest_chain = 0;
            chain_length(longest_chain,shortest_chain,buffer);
            cout<<"========== HASH TABLE STATISTICS ==========\n"
                  "Total Buckets     :"<<10<<"\n"
                  "Stored Elements   :"<<stored_elements<<"\n"
                  "Collisions        :"<<collisions<<"\n"
                  "Load Factor       :"<<stored_elements/10.0<<"\n"
                  "Longest Chain     :"<<longest_chain<<"\n"
                  "Shortest Chain    :"<<shortest_chain<<"\n"
                  "=========================================="<<endl;
        }
        if (move == 8) {
            cout<<"Total elements are"<<stored_elements<<endl;
        }
        if (move == 9) {
            if (stored_elements == 0) {
                cout<<"Table is empty."<<endl;
            }
            else {
                cout<<"Table is not empty."<<endl;
            }
        }
        if (move == 10) {
            clear_hash_table(bucket,stored_elements,collisions,buffer);
            cout<<"Hash Table is cleard."<<endl;
        }
        if (move == 0) {
            break;
        }
    }
    clear_hash_table(bucket,stored_elements,collisions,buffer);
    cout<<"Thank you for using this Hash Table"<<endl;
}
