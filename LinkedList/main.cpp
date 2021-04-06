#include <iostream>
#include <string>
#include <cassert>

template<typename T>
struct Node {
    T value{};
    Node<T>* next{nullptr};
};

template<typename T>
class LinkedList {
    Node<T>* _head_ptr{};
    Node<T>* _current_ptr{};
    size_t _size{};

    void reset_current_ptr() {
        _current_ptr = _head_ptr;
        for (size_t i = 0; i < _size - 1; i++) {
            _current_ptr = _current_ptr->next;
        }
    }

public:
    size_t size() const {
        return _size;
    }

    bool empty() const {
        return !_size;
    }

    void push_back(T value) {
        if (_size == 0) {
            _head_ptr = new Node<T>;

            _head_ptr->value = value;
            _head_ptr->next = nullptr;

            _current_ptr = _head_ptr;

            _size++;

            return;
        }

        _current_ptr->next = new Node<T>;
        _current_ptr = _current_ptr->next;

        _current_ptr->value = value;
        _current_ptr->next = nullptr;

        _size++;
    }

    void pop_back() {
        if (_size == 0) {
            return;
        }
        _current_ptr = _head_ptr;

        if (_size == 1) {
            delete _current_ptr;
            _head_ptr = nullptr;
            _current_ptr = nullptr;
            _size--;
            return;
        }

        for (size_t i = 0; i < _size - 2; i++) {
            _current_ptr = _current_ptr->next;
        }
        delete _current_ptr->next;
        _current_ptr->next = nullptr;
        _size--;
    }

    void remove_by_index(size_t index) {
        assert(index >= 0 && index < _size);
        if (index == 0) {
            Node<T>* after_head_ptr = _head_ptr->next;
            delete _head_ptr;
            _head_ptr = after_head_ptr;
            _size--;
            return;
        }
        _current_ptr = _head_ptr;
        for (size_t i = 0; i < index - 1; i++) {
            _current_ptr = _current_ptr->next;
        }
        Node<T>* after_ptr = _current_ptr->next->next;
        delete _current_ptr->next;
        _current_ptr->next = after_ptr;
        _size--;

        reset_current_ptr();
    }

    void remove_since_index(size_t index) {
        assert(index >= 0 && index < _size);
        size_t count = _size - index;
        for (size_t i = 0; i < count; i++) {
            remove_by_index(index);
        }
    }

    T& head() {
        assert(_head_ptr != nullptr);
        return _head_ptr->value;
    }

    T& tail() {
        assert(_current_ptr != nullptr);
        return _current_ptr->value;
    }

    ~LinkedList() {
        while (_size) {
            pop_back();
        }
    }

    friend std::ostream& operator<< (std::ostream& out, const LinkedList& list) {
        Node<T>* current_ptr = list._head_ptr;

        while (current_ptr) {
            out << current_ptr->value << " ";
            current_ptr = current_ptr->next;
        }
        return out;
    }
};

int main() {
    LinkedList<std::string> list;
    list.push_back("Car");
    list.push_back("House");
    list.push_back("Cat");
    list.push_back("Dog");
    list.push_back("Sky");
    list.push_back("Table");
    list.push_back("Chair");

    list.remove_by_index(2); // remove Cat
    std::cout << list << '\n'; // Car House Dog Sky Table Chair
    list.remove_since_index(1); // remove House Dog Sky Table Chair
    std::cout << list << '\n'; // Car
    
    return 0;
}
