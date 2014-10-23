#include <iostream>
/*
 * Задание повышенной сложности. 
 * Реализуйте класс SharedPtr как описано ранее. 
 * Задание немного сложнее, чем кажется на первый взгляд. 
 * Уделите особое внимание "граничным случаям" - нулевой указатель, 
 * присваивание самому себе, вызов reset на нулевом SharedPtr и прочее. 
 * Hint: возможно, вам понадобится завести вспомогательную структуру.
 * */

struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
};
struct Number : Expression
{
	Number(double value)
        : value_(value)
    {}

    double value() const
    { return value_; }

    double evaluate() const
    { return value_; }

private:
    double value_;
};

struct SharedPtr
{
    // реализуйте следующие методы
    //
    // explicit SharedPtr(Expression *ptr = 0)
    // ~SharedPtr()
    // SharedPtr(const SharedPtr &)
    // SharedPtr& operator=(const SharedPtr &)
    // Expression* get() const
    // void reset(Expression *ptr = 0)
    // Expression& operator*() const
    // Expression* operator->() const

    explicit SharedPtr(Expression *ptr = 0){
		ptr_ = ptr;
		counter_ = new int;
        *counter_ = 0;
        if (ptr_) {
            *counter_ = 1;
        }
	}
	SharedPtr(const SharedPtr & obj) {
        if (this != &obj) {
            ptr_ = obj.ptr_;
            counter_ = obj.counter_;
            if (ptr_){
                ++(*counter_);
            }
		}
	}
	void reset(Expression *ptr = 0){
        if (ptr_ != ptr){
            if (*counter_ && !--(*counter_)){
                delete counter_;
                if (ptr_) {
                    ptr_ = NULL;
                    delete ptr_;
                }
            }
            ptr_ = ptr;
			counter_ = new int;
            if (ptr) {
                *counter_ = 1;
            } else {
				*counter_ = 0;
			}
        }
	}
    Expression* get() const {
        return ptr_;
    }
//	SharedPtr& operator=(const SharedPtr & obj) {
//		if (this != &obj) {
//            if (*counter_ && !--(*counter_)){
//                delete counter_;
//                ptr_ = NULL;
//                delete ptr_;
//            }
//			ptr_ = obj.ptr_;
//			counter_ = new int;
//            counter_ = obj.counter_;
//            if (ptr_) {
//                ++(*counter_);
//            }
//		}
//		return *this;
//	}
	SharedPtr& operator=(const SharedPtr & obj) {
		if (this != &obj) {
            if (*counter_ && ptr_){
                --(*counter_);
            }
            if (!(*counter_)){
                ptr_ = obj.ptr_;
                counter_ = new int;
                counter_ = obj.counter_;
                if (ptr_) {
                    ++(*counter_);
                }
            }
            if (*obj.counter_ && obj.ptr_){
                ++(*obj.counter_);
            }
		}
		return *this;
	}
	Expression& operator*() const {
		return *ptr_;
	}
	Expression* operator->() const {
	    return ptr_;
	}
	int count() const{
		return *counter_;
	}
	~SharedPtr(){
        if (*counter_ && !--(*counter_)) {
            delete counter_;
        }
        if (!(*counter_)){
            ptr_ = NULL;
            delete ptr_;
        }
	}

private:
    Expression *ptr_;
    int *counter_;
};
/*
int main(){
    Number *n32 = new Number(32.0);
    Number *n16 = new Number(16.0);
    Number *n42 = new Number(42.0);
    std::cout<<"------------------"<<std::endl;
    std::cout<<"SharedPtr p1(n32)"<<std::endl;
    SharedPtr p1(n32);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"SharedPtr p2 = p1"<<std::endl;
    SharedPtr p2 = p1;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"SharedPtr p3(p1)"<<std::endl;
    SharedPtr p3(p1);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p3.reset(n16)"<<std::endl;
    p3.reset(n16);
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p3.reset(0)"<<std::endl;
    p3.reset(0);
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;


    std::cout<<"p1 = p1"<<std::endl;
    p1 = p1;
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;


    std::cout<<"p3.~SharedPtr()"<<std::endl;
    p3.~SharedPtr();
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p1.reset(n42)"<<std::endl;
    p1.reset(n42);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p1.~SharedPtr()"<<std::endl;
    p1.~SharedPtr();
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p2.~SharedPtr()"<<std::endl;
    p2.~SharedPtr();

    return 0;
}
*/
int main(){

    Number *n16 = new Number(16.0);
    Number *n32 = new Number(32.0);
    Number *n42 = new Number(42.0);

    std::cout<<"------------------"<<std::endl;
    std::cout<<"Test 1. SharedPtr p1(n32)"<<std::endl;
    SharedPtr p1(n32);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 2. SharedPtr p2 = p1"<<std::endl;
    SharedPtr p2 = p1;
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 3. SharedPtr p3(p1)"<<std::endl;
    SharedPtr p3(p1);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 4. p3.reset(n16)"<<std::endl;
    p3.reset(n16);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 5. p3.reset(0)"<<std::endl;
    p3.reset(NULL);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 6. p1 = p1"<<std::endl;
    p1 = p1;
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"p3.count() = "<<p3.count()<<";  (size_t) p3.get(): "<<(size_t)p3.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 7. p3.~SharedPtr()"<<std::endl;
    p3.~SharedPtr();
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 8. p1.reset(n42)"<<std::endl;
    p1.reset(n42);
    std::cout<<"p1.count() = "<<p1.count()<<";  (size_t) p1.get(): "<<(size_t)p1.get()<<std::endl;
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 9. p1.~SharedPtr()"<<std::endl;
    p1.~SharedPtr();
    std::cout<<"p2.count() = "<<p2.count()<<";  (size_t) p2.get(): "<<(size_t)p2.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 10. p2.~SharedPtr()"<<std::endl;
    p2.~SharedPtr();
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 11. SharedPtr p4(NULL)"<<std::endl;
    SharedPtr p4(NULL);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 12. SharedPtr p5(NULL)"<<std::endl;
    SharedPtr p5(NULL);
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 13. p5 = p4"<<std::endl;
    p5 = p4;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 14. SharedPtr p6(p4)"<<std::endl;
    SharedPtr p6(p4);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 15. p6.reset(n16)"<<std::endl;
    p6.reset(n16);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 16. p5 = p6"<<std::endl;
    p5 = p6;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 17. p6 = p4"<<std::endl;
    p6 = p4;
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"Test 18. p5.reset(NULL)"<<std::endl;
    p5.reset(NULL);
    std::cout<<"p4.count() = "<<p4.count()<<";  (size_t) p4.get(): "<<(size_t)p4.get()<<std::endl;
    std::cout<<"p5.count() = "<<p5.count()<<";  (size_t) p5.get(): "<<(size_t)p5.get()<<std::endl;
    std::cout<<"p6.count() = "<<p6.count()<<";  (size_t) p6.get(): "<<(size_t)p6.get()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    return 0;
}
/*
int main(){
    Number *n32 = new Number(32.0);
    Number *n16 = new Number(16.0);
    Number *n42 = new Number(42.0);
    std::cout<<"------------------"<<std::endl;
    std::cout<<"SharedPtr p1(n32)"<<std::endl;
    SharedPtr p1(n32);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"SharedPtr p2 = p1"<<std::endl;
    SharedPtr p2 = p1;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"SharedPtr p3(p1)"<<std::endl;
    SharedPtr p3(p1);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p3.reset(n16)"<<std::endl;
    p3.reset(n16);
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p3.reset(0)"<<std::endl;
    p3.reset(0);
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;


    std::cout<<"p1 = p1"<<std::endl;
    p1 = p1;
    std::cout<<"p3 = "<<p3.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;


    std::cout<<"p3.~SharedPtr()"<<std::endl;
    p3.~SharedPtr();
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p1.reset(n42)"<<std::endl;
    p1.reset(n42);
    std::cout<<"p1 = "<<p1.count()<<std::endl;
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p1.~SharedPtr()"<<std::endl;
    p1.~SharedPtr();
    std::cout<<"p2 = "<<p2.count()<<std::endl;
    std::cout<<"------------------"<<std::endl;

    std::cout<<"p2.~SharedPtr()"<<std::endl;
    p2.~SharedPtr();


////    std::cout<<"------------------"<<std::endl;
////    std::cout<<"SharedPtr p1(n32)"<<std::endl;
////    SharedPtr p1(n32);
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"SharedPtr p2 = p1"<<std::endl;
////    SharedPtr p2 = p1;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"SharedPtr p3(p1)"<<std::endl;
////    SharedPtr p3(p1);
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p3 = "<<p3.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p3.reset(n16)"<<std::endl;
////    p3.reset(n16);
////    std::cout<<"p3 = "<<p3.count()<<std::endl;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p3.reset(n32)"<<std::endl;
////    p3.reset(n32);
////    std::cout<<"p3 = "<<p3.count()<<std::endl;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p3.~SharedPtr()"<<std::endl;
////    p3.~SharedPtr();
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p1.reset(n42)"<<std::endl;
////    p1.reset(n42);
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"SharedPtr p4(n32)"<<std::endl;
////    SharedPtr p4(n32);
////    std::cout<<"p4 = "<<p4.count()<<std::endl;
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p1 = "<<p1.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p1.~SharedPtr()"<<std::endl;
////    p1.~SharedPtr();
////    std::cout<<"p2 = "<<p2.count()<<std::endl;
////    std::cout<<"p4 = "<<p4.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
////
////    std::cout<<"p2.~SharedPtr()"<<std::endl;
////    p2.~SharedPtr();
////    std::cout<<"p4 = "<<p4.count()<<std::endl;
////    std::cout<<"------------------"<<std::endl;
}
*/
