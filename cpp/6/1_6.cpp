#include <iostream>
using namespace std;

/*
 * Реализуйте шаблонную версию класса Array.
 * Список всех операций, которые должен поддерживать класс Array, приведен в шаблоне кода.
 * */


#include <cstddef>
template <typename T>
class Array
{
    // Список операций:
    //
    // explicit Array(size_t size = 0, const T& value = T())
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    // Array(const Array &)
    //   конструктор копирования, который создает
    //   копию параметра. Считайте, что для типа
    //   T определен оператор присваивания.
    //
    // ~Array()
    //   деструктор, если он вам необходим.
    //
    // Array& operator=(...)
    //   оператор присваивания.
    //
    // size_t size() const
    //   возвращает размер массива (количество
    //                              элементов).
    //
    // T& operator[](size_t)
    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.

    public:
    explicit Array(size_t size = 0, const T& value = T()) : size_(size), data_(new T[size]) {
        for (size_t i = 0; i != size_; ++i){
            data_[i] = value;
        }
    }
    Array(const Array & obj) : size_(obj.size_), data_(new T[obj.size_]) {
        for (size_t i = 0; i != size_; ++i){
            data_[i] = obj.data_[i];
        }
    }
    Array& operator=(const Array & obj){
        if (this != &obj) {
            delete [] data_;
            size_ = obj.size_;
            data_ = new T[size_];
            for (size_t i = 0; i != size_; ++i) {
                data_[i] = obj.data_[i];
            }
        }
        return *this;
    }

    size_t size() const {
        return size_;
    }
    T& operator[](size_t i) {
        return data_[i];
    }
    const T& operator[](size_t i) const {
        return data_[i];
    }
    ~Array() {
        delete[] data_;
    }

    private :
        size_t size_ ;
        T * data_ ;
};

int main() {
    Array<int> *arr0 = new Array<int>();
    Array<int> *arr1 = new Array<int>(10,7);
    Array<float> *arr2 = new Array<float>(5,8.88f);
    Array<float> arr3 = Array<float>(*arr2);
    Array<float> arr4;
    arr4 = arr3;
    //my_arr1->~Array();
    //my_arr2->~Array();

    for (size_t i = 0; i < arr1->size(); i++)
        cout << "Value of " << i << " element is " << (*arr1)[i] << endl;

    cout<<endl;

    for (size_t i = 0; i < arr4.size(); i++)
        cout << "Value of " << i << " element is " << arr4[i] << endl;

    //system("pause");
    return 0;
}