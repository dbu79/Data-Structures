#include <iostream>

template <typename T> 

class Vector{
    private: 
        T* data = nullptr; 
        size_t size = 0; 
        size_t capacity = 0;
        
        void ReAlloc(size_t newCapacity){

            T* newBlock = new T[newCapacity];

            if (newCapacity <= size)
                size = newCapacity;
            
            for (size_t i{}; i < size; i++){
                newBlock[i] = data[i];
            }
            delete[] data;
            data = newBlock;
            capacity = newCapacity;
        }
    public: 
        Vector(){
        }

        void PushBack(const T& value){
            if(size >= capacity){
                ReAlloc(capacity == 0 ? 2 : capacity + capacity / 2);
            }

            data[size++] = value;
        }
        
        const T& operator[](size_t index) const{
            return data[index];
        }

        T& operator[](size_t index){
            return data[index];
        }

        size_t Size() const {
            return size; 
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
    vector.PushBack(2);
    vector.PushBack(1);
    vector.PushBack(1);
    vector.PushBack(1);
    vector.PushBack(1);

    PrintVec(vector);
}
