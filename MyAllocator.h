#pragma once
#include <cstddef>

template<typename T, int ChunkSize>
struct MyAllocator {
    typedef T value_type;

    template<class U>
    struct rebind
    {
        using other = MyAllocator<U, ChunkSize>;
    };

    MyAllocator() noexcept {
        std::cout << "MyAllocator ctr\n";
        //std::cout << __FUNCSIG__ << std::endl;
        size = 0;
        capacity = 0;
    }
    MyAllocator(const MyAllocator& ot) {
        std::cout << "MyAllocator copy ctr\n";
        size = ot.size;
        capacity = ot.capacity;
    }

    ~MyAllocator() {
        std::cout << "MyAllocator dctr\n";
        //std::cout << __FUNCSIG__ << std::endl;
        std::cout << "\tMyAllocator Size: " << size << std::endl;
    }

    template<typename U> MyAllocator(const MyAllocator<U, ChunkSize>&) noexcept {
        std::cout << "MyAllocator rebind ctr\n";
        //std::cout << __FUNCSIG__ << std::endl;
        size = 0;
        capacity = 0;
    }

    T* allocate(std::size_t n);
    void deallocate(T* p, std::size_t n);

private:
    std::vector<T*> buffers;
    std::size_t size;
    int capacity;
};

template <typename T, int ChunkSize>
T* MyAllocator<T, ChunkSize>::allocate (size_t n) {
    std::cout << "MyAllocator allocate: " << n << std::endl;
    //std::cout << __FUNCSIG__ << std::endl;

    if (capacity-size < n) {
        if (capacity == 0) {
            std::cout << "First alloc: " << capacity << std::endl;
            auto p = std::malloc(ChunkSize * sizeof(T));
            if (!p)
                throw std::bad_alloc();
            buffers.push_back(reinterpret_cast<T *>(p));    
            capacity += ChunkSize;
        }
        else {
            throw std::bad_alloc();
        }
    }

    size_t first_free = size;
    size += n;
    std::cout << "MyAllocator allocate: " << &buffers[0][first_free] << std::endl;
	return &buffers[0][first_free];
}

template <typename T, int ChunkSize>
void MyAllocator<T, ChunkSize>::deallocate(T* p, std::size_t ) {
    std::cout << "MyAllocator deallocate: " << p << std::endl;
    //std::cout << __FUNCSIG__ << std::endl;
    size -= 1;
    //if (p)
    if (size <= 0) {
        std::cout << "MyAllocator deallocate free: " << &buffers[0][0] << std::endl;
        if (buffers.size() > 0)
            std::free(&buffers[0][0]);
    }
}

template <class T, class U, int ChunkSize>
constexpr bool operator== (const MyAllocator<T, ChunkSize>&, const MyAllocator<U, ChunkSize>&) noexcept {
    return true;
}

template <class T, class U, int ChunkSize>
constexpr bool operator!= (const MyAllocator<T, ChunkSize>&, const MyAllocator<U, ChunkSize>&) noexcept {
    return false;
}