#include <iostream>
#include <cassert>
#include "mylist.h"

template<class T, size_t TotalElems>
class Mollocator {
private:
    using Node = typename Stack::Node;
    Stack m_freeStack;

    void *m_start_ptr = nullptr;
    std::size_t m_chunkSize = sizeof(T);
protected:
    std::size_t m_totalSize = TotalElems * m_chunkSize;
    std::size_t m_used = 0;
    std::size_t m_peak = 0;
public:
    //TYPE DEFINITIONS
    typedef std::size_t size_type;
    typedef T *pointer;
    typedef T value_type;

    template<class U>
    struct rebind {
        typedef Mollocator<U, TotalElems> other;
    };

    Mollocator() {
        assert(m_chunkSize >= 4 && "Chunk size must be greater or equal to 4");
        assert(m_totalSize % m_chunkSize == 0 && "Total Size must be a multiple of Chunk Size");
        m_start_ptr = malloc(m_totalSize);
        Reset();
    }

    Mollocator(const Mollocator &copy) {
        m_freeStack = copy.m_freeStack;
        m_start_ptr = copy.m_start_ptr;
        m_chunkSize = copy.m_chunkSize;
        m_totalSize = copy.m_totalSize;
        m_used = copy.m_used;
        m_peak = copy.m_peak;
    }


    ~Mollocator() {
        free(m_start_ptr);
    }

    pointer allocate(const std::size_t n) {
        assert(n!=0 && "n cannot be zero!");
        Node * freePosition;
        for (int i = 0; i < n; i++) {
            assert(m_freeStack.head != nullptr && "The pool allocator is full");
            freePosition=m_freeStack.pop();
            m_used += m_chunkSize;
            m_peak = std::max(m_peak, m_used);
        }
        return reinterpret_cast<pointer> (freePosition);
    }

    void deallocate(pointer ptr, size_type n) {
        for (int i = 0; i < n; i++) {
            m_used -= m_chunkSize;
            m_freeStack.push((Node *) ptr);
            ptr++;
        }

    }

    void Reset() {
        m_used = 0;
        m_peak = 0;
        // Create a linked-list with all free positions
        const int nChunks = m_totalSize / m_chunkSize;
        for (int i = 0; i < nChunks; ++i) {
            std::size_t address = (std::size_t) m_start_ptr + i * m_chunkSize;
            m_freeStack.push((Node *) address);
        }

    }
};


