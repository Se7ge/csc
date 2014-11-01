#include <iostream>
using namespace std;
/*
* В первом уроке вы реализовали простой шаблон ValueHolder,
* в этом задании мы используем его чтобы написать класс Any (интересно, что не шаблонный),
* который позволяет хранить значения любого типа!
* Например, вы сможете  создать массив объектов типа Any,
* и сохранять в них int-ы, double-ы или даже объекты Array.
* Подробности в шаблоне кода.
* Hint: в нешаблонном классе Any могут быть шаблонные методы, например, шаблонный конструктор.
* */

struct ICloneable
{
    virtual ICloneable* clone() const = 0;
    virtual ~ICloneable() { }
};

// Поле data_ типа T в классе ValueHolder
// открыто, к нему можно обращаться
template <typename T>
struct ValueHolder : ICloneable {

    ValueHolder(T value) : data_(value) {};

    ValueHolder * clone() const {
        return new ValueHolder(*this);
    }

    ~ValueHolder() {}

    T data_;
};


// Это класс, который вам нужно реализовать

class Any
{
    // В классе Any должен быть конструктор,
    // который можно вызвать без параметров,
    // чтобы работал следующий код:
    //    Any empty; // empty ничего не хранит
public:
    Any() : data_(0){}

    // В классе Any должен быть шаблонный
    // конструктор от одного параметра, чтобы
    // можно было создавать объекты типа Any,
    // например, следующим образом:
    //    Any i(10); // i хранит значение 10

    template < class T >
    Any(T data) : data_(new ValueHolder<T>(data)){}

    // Не забудьте про деструктор. Все выделенные
    // ресурсы нужно освободить.

    ~Any(){
        delete data_;
    }

    // В классе Any также должен быть конструктор
    // копирования (вам поможет метод clone
    // интерфейса ICloneable)

    Any (Any const & obj) : data_(obj.data_->clone()) {}

    // В классе должен быть оператор присваивания и/или
    // шаблонный оператор присваивания, чтобы работал
    // следующий код:
    //    Any copy(i); // copy хранит 10, как и i
    //    empty = copy; // empty хранит 10, как и copy
    //    empty = 0; // а теперь empty хранит 0

    template <typename T>
    Any& operator=(const T & obj){
//        if (this != &obj) {
            delete data_;
            data_ = new ValueHolder<T>(obj);
//        }
        return *this;
    }

    Any& operator=(const Any & obj){
        if (this != &obj){
            delete data_;
            data_ = obj.data_->clone();
        }
        return *this;
    }

    // Ну и наконец, мы хотим уметь получать хранимое
    // значение, для этого определите в классе Any
    // шаблонный метод cast, который возвращает
    // указатель на хранимое значение, или нулевой
    // указатель в случае несоответствия типов или
    // если объект Any ничего не хранит:
    //    int *iptr = i.cast<int>(); // *iptr == 10
    //    char *cptr = i.cast<char>(); // cptr == 0,
    //        // потому что i хранит int, а не char
    //    Any empty2;
    //    int *p = empty2.cast<int>(); // p == 0
    // При реализации используйте dynamic_cast,
    // который мы уже обсуждали ранее.
    template <typename T>
    T* cast() {
        if (data_) {
            ValueHolder<T> *res = dynamic_cast<ValueHolder<T> *>(data_);
            if (res) {
                return &(res->data_);
            }
        }
        return 0;
    }

    ICloneable * data_;
};

int main() {
    Any empty;
    Any i(10);
    cout << "[1] i      = " << i.cast<int>() << endl;
    Any copy(i);
    cout << "[2] copy   = " << copy.cast<int>() << endl;
    empty = copy;
    cout << "[3] empty  = " << empty.cast<int>() << endl;
    cout << "[3] *empty = " << *empty.cast<int>() << endl;
    empty = 0;
    cout << "[4] empty  = " << empty.cast<int>() << endl;
    cout << "[4] *empty = " << *empty.cast<int>() << endl;
    int *iptr = i.cast<int>();
    cout << "[5] iptr   = " << iptr << endl;
    char *cptr = i.cast<char>(); // cptr = 0
    // cout << "[6] cptr=" << cptr << endl; // undefined behavior for char * == 0
    cout << "[6] cptr   = " << (void*)cptr << endl;
    Any empty2;
    int *p = empty2.cast<int>();
    cout << "[7] p      = " << p << endl;
    Any a = 20;
    cout << "[8] a      = " << a.cast<int>() << endl;
    a=0;
    cout << "[9] a      = " << a.cast<int>() << endl;
    a = 'w';
    cout << "[10] a     = " << a.cast<char>() << endl; // overloaded operator << for char *
    cout << "[10] a     = " << (void *)a.cast<char>() << endl;
    return 0;

    return 0;
}