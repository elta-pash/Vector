#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
#include<initializer_list>
#include<stdexcept>
#include<cstddef>
template<typename T>
class Vector {

    public:
    class ConstIterator;
    class Iterator;
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using iterator = typename Vector<T>::Iterator;
    using const_iterator =  typename Vector<T>::ConstIterator;
    private:
    std::size_t sz;
    std::size_t max_sz;
    pointer values;
    void resize(std::size_t n) {
        if (max_sz < n) {
            std::size_t new_max{max_sz*2+1};
            while (new_max < n) {
                new_max *= 2;
            }
            pointer new_values = new value_type[new_max];
            if (values != nullptr) {
                for (std::size_t i{0}; i < sz; ++i) {
                    new_values[i] = values[i];
            }
            }
            delete[] values;
            values = new_values;
            max_sz = new_max; 
        }
    }
    public:
    Vector() : sz{0}, max_sz{0}, values{nullptr} {} //default
    Vector(std::size_t n) : sz{0}, max_sz{n}, values{n? new value_type[n] : nullptr} {} //parameterlist1
    Vector(const Vector& v) : Vector(v.size()) {
        for (; sz < v.sz; ++sz) {
            values[sz] = v.values[sz];
        }
    } //copy construct
    Vector(std::initializer_list<value_type> l) : Vector(l.size()) {
        for (const auto& value : l) {
            values[sz++] = value;
        }
    } //parameterliste2
    ~Vector() {
        delete[] values;
    } //destructor
    Vector& operator=(const Vector& rightop) {
        if (this == &rightop) {
            return *this;
        }
        else {
        delete[] values; 
        max_sz = rightop.max_sz;
        sz = rightop.sz;  
        values = new value_type[rightop.max_sz];
        for (std::size_t i=0; i < sz; ++i){
            values[i] = rightop.values[i];
        } 
        }
        return *this;
    }
    std::size_t size() const {
        return sz;
    }
    bool empty() const {
        if (sz == 0) {
            return true;
        }
        return false;
    }
    void clear() {
        delete[] values;
        sz = 0;
        //i'll try to delete values
        values = nullptr; 
    }
    void reserve(std::size_t n) {
        if (max_sz < n) {
            pointer new_values = new value_type[n];
            for (std::size_t i{0}; i < sz; ++i) {
                new_values[i] = values[i];
            }
            delete[] values;
            values = new_values;
            max_sz = n;
        }
    }
    void shrink_to_fit() {
        if (sz < max_sz) {
            pointer new_values = new value_type[sz];
            for (std::size_t i{0}; i < sz; ++i) {
                new_values[i] = values[i];
            }
            delete[] values;
            values = new_values;
            max_sz = sz;
        }    
    }
    void push_back(const_reference value) {
        resize(sz+1);
        values[sz++] = value;
    }
    void pop_back() {
        if (empty()) {
            throw std::runtime_error ("vector is empty");
        }
        if (sz > 0) {
            --sz;
           //resize(sz);
            pointer new_values = new value_type[sz];
            for (std::size_t i{0}; i < sz; ++i) {
                new_values[i] = values[i];
            }
            delete[] values;
            values = new_values;
            
        }
    }
    reference operator[] (std::size_t index) {
        if (index >= sz) {
            throw std::runtime_error ("index is not allowed");
        }
        return values[index];
    }
    const_reference operator[] (std::size_t index) const {
        if (index >= sz) {
            throw std::runtime_error ("index is not allowed");
        }
        return values[index];      
    }
    std::size_t capacity() const {
        return max_sz;
    }
    std::ostream& print(std::ostream& o) const {
        o << "[";
        bool first{true};
        for (std::size_t i{0}; i < sz; ++i) {
            if (first) {
                first = false;
            }
            else {
                o << ", ";
            }
            o << values[i];
        }
        return o << "]";
    }

//begin and end
iterator begin() {
    return iterator (values, values+sz);
}
iterator end() {
    return iterator (values+sz, values+sz);
}
const_iterator begin() const {
    return const_iterator (values, values+sz);
}
const_iterator end() const {
    return const_iterator (values+sz, values+sz);
}


//CLASS ITERATOR
class Iterator {
    public:
    using value_type = Vector::value_type;
    using reference = Vector::reference;
    using pointer = Vector::pointer;
    using difference_type = Vector::difference_type;
    using iterator_category = std::forward_iterator_tag;
    private:
    pointer ptr;
    pointer border;
    public:
    Iterator() : ptr{nullptr}, border{nullptr} {}
    Iterator(pointer ptr, pointer border=nullptr) : ptr{ptr}, border{border} {}
    reference operator*() const {
        if (ptr == border) {
            throw std::runtime_error ("Iterator is unavailable (*)");
        }
        return *ptr;
    }
    pointer operator->() const {
        if (ptr == border) {
            throw std::runtime_error ("Iterator is unavailable (->)");
        }
        return ptr;
    }
    bool operator==(const const_iterator& rightop) const {
        if ((static_cast<const_iterator>(*this)) == rightop) {
            return true;
        }
        return false;
    }
    bool operator!=(const const_iterator& rightop) const {
        if ((static_cast<const_iterator>(*this)) == rightop) {
            return false;
        }
        return true;
    }
    iterator& operator++() { 
        if (ptr != border) {
        ++ptr;
        }
        return *this;
    }
    iterator operator++(int) {
        iterator before = *this;
        if (ptr != border) {
        ++ptr;
        }
        return before;
    }
    operator const_iterator() const {
        return const_iterator (ptr, border);
    }
    Vector::difference_type operator-(const const_iterator& rightop) const {
    return (static_cast<const_iterator>(*this) - rightop);
    }
};


//CLASS CONST_ITERATOR
class ConstIterator {
    public:
    using value_type = Vector::value_type;
    using reference = Vector::const_reference;
    using pointer = Vector::const_pointer;
    using difference_type = Vector::difference_type;
    using iterator_category = std::forward_iterator_tag;
    private:
    pointer ptr;
    pointer border_const;
    public:
    ConstIterator() : ptr{nullptr}, border_const{nullptr} {}
    ConstIterator(pointer ptr, pointer border_const=nullptr) : ptr{ptr}, border_const{border_const} {}
    reference operator*() const {
        if (ptr == border_const) {
            throw std::runtime_error ("Iterator is unavailable (*)");
        }
        return *ptr;
    }
    pointer operator->() const {
        if (ptr == border_const) {
            throw std::runtime_error ("Iterator is unavailable (->)");
        }
        return ptr;
    }
    bool operator==(const const_iterator& rightop) const {
        if (ptr == rightop.ptr) {
            return true;
        }
        return false;
    }
    bool operator!=(const const_iterator& rightop) const {
        if (ptr == rightop.ptr) {
            return false;
        }
        return true;
    }
    const_iterator& operator++() {
        if (ptr != border_const) {
        ++ptr; 
        }
        return *this;
    }
    const_iterator operator++(int) {
        const_iterator before = *this;
        if (ptr != border_const) {
        ++ptr;
        }
        return before;
    }
    /*Vector::difference_type operator-(const const_iterator& rightop) const {
        return (ptr - rightop.ptr);
    }*/
    friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
        return lop.ptr-rop.ptr;
}
};


//INSERT ERASE
iterator insert(const_iterator pos, const_reference val) { 
    auto diff = pos - begin(); 
    if (diff < 0 || static_cast<size_type>(diff) > sz) 
        throw std::runtime_error ("Iterator out of bounds"); 
    size_type current {static_cast<size_type>(diff)}; 
    if(sz >= max_sz) { 
        reserve (max_sz * 2 + 10); 
    } //Attention special case, if no minimum size is defined 
    for (auto i{sz}; i-->current;) {
    values[i + 1] = values[i]; 
    }
    values[current]=val; 
    ++sz; 
    return iterator{values+current, values+sz};
} 
iterator erase(const_iterator pos) { 
    auto diff = pos - begin(); 
    if (diff < 0 || static_cast<size_type>(diff) >= sz) 
    throw std::runtime_error("Iterator out of bounds");
    size_type current{static_cast<size_type>(diff)}; 
    for (auto i{current}; i < sz - 1; ++i) {
        values[i]=values[i+1]; 
        }
    --sz;
    return iterator{values+current, values+sz};
}
/*friend Vector::difference_type operator-(const Vector::ConstIterator& lop, const Vector::ConstIterator& rop) {
  return lop.ptr-rop.ptr;
}*/
};
template<typename T>
inline std::ostream& operator<<(std::ostream& o, Vector<T>& v) {
    return v.print(o);
}

#endif