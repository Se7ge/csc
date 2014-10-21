/*
 * Задание повышенной сложности. 
 * Реализуйте класс SharedPtr как описано ранее. 
 * Задание немного сложнее, чем кажется на первый взгляд. У
 * делите особое внимание "граничным случаям" - нулевой указатель, 
 * присваивание самому себе, вызов reset на нулевом SharedPtr и прочее. 
 * Hint: возможно, вам понадобится завести вспомогательную структуру.
 * */

struct Expression;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

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
};


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
}
