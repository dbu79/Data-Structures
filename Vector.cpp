#include <iostream>
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
                data = static_cast<T*>(operator new(capacity * sizeof(T)));
                for (size_t i{}; i < size;  i++){
                    new (data + i) T(other.data[i]);
                }
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
        std::cout << vector[i] << std::endl;
    }
}

int main() {
    Vector<int> vector;
    // std::cout << vector.Size() << std::endl;
    // std::cout << vector.Capacity();
}
