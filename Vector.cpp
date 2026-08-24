#include <iostream>
#include <iterator>
#include <new>

template <typename T> 

class Vector{
    private: 
        T* data = nullptr; 
        size_t size = 0; 
        size_t capacity = 0;
        
        void Alloc(size_t newCapacity){
            
            T* newBlock = static_cast<T*>(operator new(newCapacity * sizeof(T))); 

            for (size_t i{}; i < size; i++){
                new (&newBlock[i]) T(std::move(data[i]));
                data[i].~T();
            }
            
            operator delete(data);
            data = newBlock;
            capacity = newCapacity;
        }
    public: 
        // Constructor 
        Vector(){
        }

        // Destructor
        ~Vector(){
            for (size_t i{}; i < size; i++){
                data[i].~T();
            }
            operator delete(data);
        }
        
        // Copy Constructor
        Vector(const Vector& other)
            : size(other.size), capacity(other.capacity){
                std::cout << "Copy constructor called" << std::endl;
                data = static_cast<T*>(operator new(capacity * sizeof(T)));
                for (size_t i{}; i < size;  i++){
                    new (data + i) T(other.data[i]);
                }
            }

        // Copy Assignment
        Vector& operator = (const Vector& other) {
            std::cout << "Copy assignment called" << std::endl;
            if (this != &other){
                T* new_data = static_cast<T*>(operator new(other.capacity * sizeof(T)));
                for (size_t i = 0; i < other.size; i++){
                    new (new_data + i) T(other.data[i]);
                }
                for (size_t i = 0; i < size; i++){
                    data[i].~T();
                }
                operator delete(data);
                data = new_data;
                size = other.size;
                capacity = other.capacity;
            }
            return *this;
        }

        // Move Constructor
        Vector(Vector&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) {
            std::cout << "Move constructor called" << std::endl;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        
        // Move Assignment 
        Vector& operator=(Vector&& other) noexcept {
            std::cout << "Move assignment called" << std::endl;
            if (this != &other){
                for (size_t i{}; i < size; i++){
                    data[i].~T();
                }
                operator delete(data);

                data = other.data;
                size = other.size;
                capacity = other.capacity;
            }
            return *this;
        }
        void PushBack(const T& value){
            if(size >= capacity){
                Alloc(capacity == 0 ? 2 : capacity + capacity / 2);
            }
            
            new(&data[size++]) T(value);
        }
        
        void PopBack(){
            if (size != 0){
                size--; 
                data[size].~T();
            }
        }

        const T& operator[](size_t index) const{
            return data[index];
        }

        void Clear(){
            for (size_t i{}; i < size; i++){
                data[i].~T();
            }
            size = 0;
        }

        T& operator[](size_t index){
            return data[index];
        }

        size_t Size() const {
            return size; 
        }

        size_t Capacity() const {
            return capacity;
        }
};

template <typename T>
void PrintVec(const Vector<T>& vector){
    for(size_t i = 0; i < vector.Size(); i++){
        std::cout << vector[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    Vector<int> vector;
    vector.PushBack(2);
    vector.PushBack(1);
    PrintVec(vector);
    
    Vector<int> vector3;
    vector3.PushBack(1);
    vector3.PushBack(2);
    auto a = vector;
    a = vector;
    Vector<int> vector2 = std::move(vector);
    vector3 = std::move(vector);
}
