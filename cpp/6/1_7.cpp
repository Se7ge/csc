#include <iostream>
using namespace std;

/*
 * В предыдущей версии предполагается,
 * что для типа T определен оператор присваивания или он ему не нужен
 * (например, для примитивных типов он не нужен).
 * При создании шаблонных классов контейнеров (вроде Array и не только)
 * разумно стараться минимизировать требования к типам шаблонных параметров.
 * Поэтому усложним задачу, реализуйте класс Array не полагаясь на то,
 * что для типа T определен оператор присваивания.
 * Hints: используйте placement new и явный вызов деструктора,
 * чтобы создавать и уничтожать объекты,
 * аллоцировать правильно выровненную память можно с помощью new char[N * sizeof(T)],
 * где N - количество элементов массива.
 * */


#include <cstddef>
template <typename T>
class Array
{
    // Список операций:
    //
    // Array(size_t size, const T& value = T())
    //   конструктор класса, который создает
    //   Array размера size, заполненный значениями
    //   value типа T. Считайте что у типа T есть
    //   конструктор, который можно вызвать без
    //   без параметров, либо он ему не нужен.
    //
    // Array()
    //   конструктор класса, который можно вызвать
    //   без параметров. Должен создавать пустой
    //   Array.
    //
    // Array(const Array &)
    //   конструктор копирования, который создает
    //   копию параметра. Для типа T оператор
    //   присвивания не определен.
    //
    // ~Array()
    //   деструктор, если он вам необходим.
    //
    // Array& operator=(...)
    //   оператор присваивания.
    //
    // size_t size() const
    //   возвращает размер массива (количество
    //                              элемнтов).
    //
    // T& operator[](size_t)
    // const T& operator[](size_t) const
    //   две версии оператора доступа по индексу.

    public:
    explicit Array(size_t size, const T& value = T()) {
        size_ = size;
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i != size_; ++i){
            new (data_ + i) T(value);
        }
    }
    Array() {
        size_ = 0;
        data_ = (T*) new char[size_ * sizeof(T)];
    }
    Array(const Array & obj) {
        size_ = obj.size_;
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i != size_; ++i) {
            new (data_ + i) T(obj.data_[i]);
        }
    }
    Array& operator=(const Array & obj){
        if (this != &obj) {
            mem_free();
            size_ = obj.size_;
            data_ = (T*) new char[size_ * sizeof(T)];
            for (size_t i = 0; i != size_; ++i) {
                new (data_ + i) T(obj.data_[i]);
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
        mem_free();
    }

    private :
        size_t size_ ;
        T * data_ ;

    void mem_free(){
        for (size_t i = 0; i != size_; ++i) {
            data_[i].~T();
        }
        delete [] data_;
    }
};

int main() {
    Array<int> *arr0 = new Array<int>();
    Array<int> *arr1 = new Array<int>(10,7);
    Array<float> *arr2 = new Array<float>(5,8.88f);
    Array<float> arr3 = Array<float>(*arr2);
    Array<float> arr4;
    Array<string> *arr5 = new Array<string>(10,"42");
    arr4 = arr3;
    //my_arr1->~Array();
    //my_arr2->~Array();

    for (size_t i = 0; i < arr0->size(); i++)
        cout << "Value of " << i << " element is " << (*arr1)[i] << endl;
    cout<<endl;
    for (size_t i = 0; i < arr1->size(); i++)
        cout << "Value of " << i << " element is " << (*arr1)[i] << endl;
    cout<<endl;
    for (size_t i = 0; i < arr5->size(); i++)
        cout << "Value of " << i << " element is " << (*arr5)[i] << endl;

    cout<<endl;

    for (size_t i = 0; i < arr4.size(); i++)
        cout << "Value of " << i << " element is " << arr4[i] << endl;

    //system("pause");
    return 0;
}
