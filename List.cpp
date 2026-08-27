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
            Clear();
        };
        
        LinkedList(const LinkedList& other){
            Node* current = other.head;
            while (current != nullptr){
                PushBack(current->data);
                current = current->next;
            }
        }
        
        LinkedList& operator = (const LinkedList& other){
            if (this != &other){
                Clear();

                Node* current = other.head;
                while (current != nullptr){
                    PushBack(current->data);
                    current = current->next;
                }
            }
            return *this;
        }


        void Clear(){
            Node* current = head; 
            while (current != nullptr){
                Node* temp = current->next;
                delete current;
                current = temp; 
            }
            size = 0; 
            head = tail = nullptr;
        }
            
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
        
        void PopBack(){
            if (tail == nullptr){
                std::cout << "List is empty" << std::endl;
            } else {
                Node* newTail = tail->prev;
                delete tail;
                tail = newTail;

                if (tail == nullptr){
                    head = nullptr;
                } else {
                    tail->next = nullptr;
                }
                size--;
            }
        }

        void PopFront(){
            if (tail == nullptr){
                std::cout << "List is empty" << std::endl;
            } else {
                Node* newHead = head->next;
                delete head;
                head = newHead;
                
                if (head == nullptr){
                    tail = nullptr;
                } else {
                    head->prev = nullptr;
                }
                size--;
            }
        }

        size_t Size() const {
            return size;
        }


    void PrintList(){
        Node* current = head; 
        while (current != nullptr){
            std::cout << current->data << " "; 
            current = current->next; 
        }
    }
};


int main(){
    LinkedList<int> list; 

    list.PushBack(1);
    list.PushBack(2);
    list.PrintList();
    return 0;
}
