/*
 * Реализуйте ScopedPtr, 
 * как было описано ранее (реализуйте методы get и release, операторы * и ->, а также конструктор от указателя на Expression). 
 * Hint: в качестве признака того, что ScopedPtr не хранит никакого указателя (после вызова release), 
 * используйте нулевой указатель, при этом вы можете явно проверить указатель в деструкторе, 
 * но это не обязательно, так как delete от нулевого указателя ничего не делает.
 * */
struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    // explicit ScopedPtr(Expression *ptr = 0)
    // ~ScopedPtr()
    // Expression* get() const
    // Expression* release()
    // void reset(Expression *ptr = 0)
    // Expression& operator*() const
    // Expression* operator->() const
    
    explicit ScopedPtr(Expression *ptr = 0): ptr_(ptr) {}
    Expression* get() const {
	    return ptr_;	
	}
	Expression* release() {
		Expression * temp = ptr_;
		ptr_ = 0;
		return temp;
	}
	void reset(Expression *ptr = 0){
		delete ptr_;
		ptr_ = ptr;
	}
	Expression& operator*() const {
		return *ptr_;
	}
	Expression* operator->() const {
	    return ptr_;	
	}
    
    ~ScopedPtr(){
        delete ptr_;
    }

private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};
