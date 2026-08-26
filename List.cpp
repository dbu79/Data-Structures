#include <iostream>
#include <cstddef>


template <typename T>
class LinkedList{
    private:
    struct Node{
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const T& value) : data(value) {};
        };
        
        Node* head = nullptr;
        Node* tail = nullptr;
        size_t size = 0;
    

    public:
        LinkedList(){};
        ~LinkedList(){
        };

        void PushBack(const T& value){
            Node* newNode = new Node(value);

            if (tail == nullptr){
                 head = tail = newNode;
            } else {
                newNode->prev = tail; 
                tail->next = newNode;
                tail = newNode;
            }
            size++;
        }

        void PushFront(const T& value){
            Node* newNode = new Node(value);

            Node* current = tail;
            if (head == nullptr){
                head = tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            size++;
        }

        size_t Size() const {
            return size;
        }


    void PrintList(){
        Node* current = head; 
        while (current->next != nullptr){
            std::cout << current->data << " "; 
            current = current->next; 
        }
    }
};


int main(){
    LinkedList<int> list; 

    list.PushBack(1);
    list.PushBack(2);
    list.PushBack(3);
    
    list.PrintList();
    return 0;
}
