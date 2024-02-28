#ifndef LAB_7_CircleBuffer_H
#define LAB_7_CircleBuffer_H

template<typename T>
class CircularBuffer {
private:

    T* _buffer = nullptr;
    int _size = 0;
    int _capacity = 0;

public:

    class MyIterator:public std::iterator<std::random_access_iterator_tag, T> {
    private:

        T* _data = nullptr;

    public:

        explicit MyIterator(T* val) {
            _data = val;
        }
        ~MyIterator() = default;

        MyIterator(const MyIterator& other) {
            _data = other._data;
        }

        T& operator*() {
            return *_data;
        }

        T operator->() {
            return _data;
        }

        MyIterator operator++() {
            ++_data;
            return *this;
        }

        MyIterator operator--() {
            --_data;
            return *this;
        }

        MyIterator operator+(T value) {
            _data = _data + value;
            return *this;
        }

        MyIterator operator-(T val) {
            _data = _data - val;
            return *this;
        }

        using difference_type = typename std::iterator<std::random_access_iterator_tag, T>::difference_type;
        difference_type operator-(const MyIterator& other) const {
            return _data - other._data;
        }

        bool operator==(MyIterator& other) const{
            return _data == other._data;
        }

        bool operator!=(MyIterator& other) const{
            return _data != other._data;
        }

        bool operator<=(MyIterator& other) const{
            return _data <= other._data;
        }

        bool operator>=(MyIterator& other) const{
            return _data >= other._data;
        }

        bool operator<(MyIterator& other) const{
            return _data < other._data;
        }

        bool operator>(MyIterator& other) const{
            return _data > other._data;
        }
    };

    MyIterator begin() const {
        return MyIterator(_buffer);
    }

    MyIterator end() const {
        return MyIterator(_buffer + _size);
    }

    CircularBuffer() = default;
    explicit CircularBuffer(int s) {
        _capacity = s;
        _buffer = new T[_capacity];
    };
    ~CircularBuffer() {
        delete [] _buffer;
    }
    
    int size() {
        return _size;
    }
    int capacity() {
        return _capacity;
    }

    void push_back(T val) {
        // добавить элемент в конец
        if (_size < _capacity) {
            _buffer[_size++] = val;
        } else {
            // так как буфер полон, то перезаписываем новое значение в первую ячейку
            for (int i = 1; i < _capacity; i++) {
                _buffer[i - 1] = _buffer[i];
            }
            _buffer[_capacity - 1] = val;
        }
    }

    T pop_back() {
        // удалить элемент с конца
        if (_size == 0) {
            // буфер пуст
            return -1;
        } else {
            return _buffer[--_size];
        }
    }

    void push_front(T val) {
        // добавить элемент в начало
        if (_size < _capacity) {
            for (size_t i = _size; i >= 1; i--) {
                _buffer[i] = _buffer[i - 1];
            }
            _size++;
            _buffer[0] = val;
        } else {
            // так как буфер полон, то смещаем все вправо и перезаписываем 0 значение
            for (int i = _capacity - 1; i > 0; i--) {
                _buffer[i] = _buffer[i - 1];
            }
            _buffer[0] = val;
        }
    }

    T pop_front() {
        // удалить элемент с начала
        if (_size == 0) {
            // буфер пуст
            return -1;
        } else {
            T val = _buffer[0];
            for (int i = 1; i < _capacity; i++) {
                _buffer[i - 1] = _buffer[i];
            }
            --_size;
            return val;
        }
    }

    void push_by_iterator(MyIterator i, T val) {
        int ind = i - begin();
        _buffer[ind % _capacity] = val;
    }

    T pop_by_iterator(MyIterator i) {
        // удаление по итератору из произвольного места
        if (_size != 0) {
            T val = *i;
            int ind = (i - begin());


            for (int iter = ind; iter < _size; iter++) {
                _buffer[(i - begin() + iter - 1) % _capacity] = _buffer[(i - begin() + iter) % _capacity];
            }
            --_size;

            return val;
        }
    }

    T get_front() {
        // взятие элемента с начала
        if (_size == 0) {
            return -1;
        } else {
            return _buffer[0];
        }
    }

    T get_back() {
        // взятие элемента с конца
        if (_size == 0) {
            return -1;
        } else {
            return _buffer[_size - 1];
        }
    }

    void change_capacity(int new_capacity) {
        // изменение капасити
        T* NewBuffer = new T[new_capacity];
        _size = std::min(_size, new_capacity);
        for (size_t i = 0; i < _size; i++)
            NewBuffer[i] = _buffer[i];

        delete _buffer;

        _buffer = NewBuffer;
        _capacity = new_capacity;
    }

    T operator[](int i) {
        // доступ по индексу
        return _buffer[i % _capacity];
    }

};

#endif
