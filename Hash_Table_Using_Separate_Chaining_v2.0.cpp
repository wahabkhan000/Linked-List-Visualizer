#include <iostream>
#include <limits>
using std::cout,std::cin,std::string,std::endl,std::string;
struct Node{
    string Key;
    int Value;
    Node *next;
    Node(const string &key,int value) {
        Key = key;
        Value = value;
        next = nullptr;
    }
};
void hash_function(const string &key,int &buffer,int bucket_size) {
    for (int i = key.length()-1;i>=0;i--) {
        buffer =buffer*11+key[i];
    }
    buffer%=bucket_size;
}
void key_validation(string &key,Node *bucket[],int &index,int &value,int bucket_size) {
    Node *curr = nullptr;
    do {
        key.clear();
        cout<<"Enter key:"<<endl;
        cin>>key;
        hash_function(key,index,bucket_size);
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
void insert_key(int *buffer,Node* bucket[],int &collisions,int &stored_elements,int bucket_size) {
    int index = 0;
    string key;int value = 0;
    key_validation(key,bucket,index,value,bucket_size);
    Node *Head = bucket[index];
    if (Head == nullptr) {
        Head = new Node(key,value);
    }
    else{
        Node *temp = new Node(key,value);
        temp->next = Head;
        Head = temp;
        collisions++;
    }
    buffer[index]++;
    stored_elements++;
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
bool key_operation(Node *&curr,const string &key) {
    while (curr) {
        if (curr->Key == key) {
            break;
        }
        curr = curr->next;
    }
    if (curr) {
        return true;
    }
    else {
        return false;
    }
}
void delete_key(Node *bucket[],const string &key,int *buffer,int &collisions,int &stored_elements,int bucket_size) {
    int index = 0;
    hash_function(key,index,bucket_size);
    Node* Head = bucket[index];
    if (Head == nullptr) {
        cout<<"Key not exist."<<endl;
        return;
    }
    Node *curr = Head;
    if (key_operation(curr,key) == 0) {
        cout<<"Key not exist."<<endl;
        return;
    }
    if (curr == Head) {
        delete curr;
        if (Head->next) {
            Head = Head->next;
            collisions--;
        }
        else {
            Head = nullptr;
        }
    }
    else if (curr != Head) {
        Node *prev = Head;
        while (prev->next != curr) {
            prev = prev->next;
        }
        if (!curr->next) {
            delete curr;
            prev->next = nullptr;
        }
        else {
            prev->next = curr->next;
            delete curr;
        }
        collisions--;
    }
    buffer[index]--;
    stored_elements--;
    bucket[index] = Head;
    cout<<"Key and Value deleted Successfully."<<endl;
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
void search_key(Node* bucket[],const string &key,int bucket_size) {
    int index = 0;
    hash_function(key,index,bucket_size);
    if (bucket[index] == nullptr) {
        cout<<"Key not exist."<<endl;
        return;
    }
    Node *curr = bucket[index];
    if (key_operation(curr,key) == 1) {
        cout<<"Key found:"<<endl;
        cout<<"Key : "<<curr->Key<<endl;
        cout<<"Value : "<<curr->Value<<endl;
    }
    else {
        cout<<"Key not exist"<<endl;
    }
}
void update_value(Node *bucket[],int bucket_size) {
    int index = 0;
    string key;
    int new_value = 0;
    cout<<"Enter Key:"<<endl;
    cin>>key;
    hash_function(key,index,bucket_size);
    if (bucket[index] == nullptr) {
        cout<<"Key not exist."<<endl;
        return;
    }
    cout<<"Enter new Value:"<<endl;
    cin>>new_value;
    Node *curr = bucket[index];
    if (key_operation(curr,key) == 1) {
        curr->Value = new_value;
        cout<<"Key value updated."<<endl;
        cout<<"Key : "<<curr->Key<<endl;
        cout<<"Value : "<<curr->Value<<endl;
    }
    else {
        cout<<"Key not exist"<<endl;
    }
}
void chain_length(int &longest_chain,int &shortest_chain,const int *buffer,int bucket_size) {
    longest_chain = buffer[0];
    shortest_chain = buffer[0];
    for (int i=0;i<bucket_size;i++) {
        if (buffer[i]>longest_chain) {
            longest_chain = buffer[i];
        }
        if (buffer[i]<shortest_chain) {
            shortest_chain = buffer[i];
        }
    }
}
int main() {
    const int bucket_size = 10;
    int stored_elements = 0;
    int collisions = 0;
    int buffer[bucket_size] = {0};
    Node* bucket[bucket_size] = {nullptr};
    while (true) {
        int move = 0;
        move_validation(move);
        if (move == 1) {
            insert_key(buffer,bucket,collisions,stored_elements,bucket_size);
        }
        if (move == 2) {
            string key;
            cout<<"Enter key you want to search:"<<endl;
            cin>>key;
            search_key(bucket,key,bucket_size);
        }
        if (move == 3) {
            update_value(bucket,bucket_size);
        }
        if (move == 4) {
            string key;
            cout<<"Enter key you want to delete:"<<endl;
            cin>>key;
            delete_key(bucket,key,buffer,collisions,stored_elements,bucket_size);
        }
        if (move == 5) {
            string key;
            cout<<"Enter key you want to check:"<<endl;
            cin>>key;
            search_key(bucket,key,bucket_size);
        }
        if (move == 6) {
            display_hash_table(bucket);
        }
        if (move == 7) {
            int longest_chain = 0;
            int shortest_chain = 0;
            chain_length(longest_chain,shortest_chain,buffer,bucket_size);
            cout<<"========== HASH TABLE STATISTICS ==========\n"
                  "Total Buckets     :"<<bucket_size<<"\n"
                  "Stored Elements   :"<<stored_elements<<"\n"
                  "Collisions        :"<<collisions<<"\n"
                  "Load Factor       :"<<stored_elements/(float)bucket_size<<"\n"
                  "Longest Chain     :"<<longest_chain<<"\n"
                  "Shortest Chain    :"<<shortest_chain<<"\n"
                  "=========================================="<<endl;
        }
        if (move == 8) {
            cout<<"Total elements are "<<stored_elements<<endl;
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
