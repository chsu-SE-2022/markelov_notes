#pragma once
using namespace std;

class Container {
protected:
    void** data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        void** new_data = new void* [new_capacity];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Container() {
        data = nullptr;
        size = 0;
        capacity = 0;
    }

    virtual ~Container() {
        delete[] data;
    }
};