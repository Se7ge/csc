#include <iostream>
#include <string> // std::string
#include <cassert>
#include <cmath>  // sqrt и fabs

/*
Копирование AST можно было реализовать, например, просто добавив виртуальный метод clone, похожий на метод evaluate. Но используя Visitor, через единственный метод transform мы можем реализовать не только копирование. В этой задаче вам необходимо реализовать сворачивание констант в дереве (constant folding). Например, у нас есть выражение (точнее, дерево, описывающее это выражение) abs(var * sqrt(32.0 - 16.0)), на выходе мы должны получить дерево для следующего выражения abs(var * 4.0), т. е. подвыражение sqrt(32.0 - 16.0) было вычислено.
Для того, чтобы определить, что выражение (Expression) на самом деле является числом (Number), используйте оператор dynamic_cast.
Все промежуточные узлы дерева, которые вы создали, нужно освободить.
*/

using namespace std;

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
    virtual Expression *transform(Transformer *tr) const = 0;
};

struct Transformer
{
    virtual ~Transformer() { }
    virtual Expression *transformNumber(Number const *) = 0;
    virtual Expression *transformBinaryOperation(BinaryOperation const *) = 0;
    virtual Expression *transformFunctionCall(FunctionCall const *) = 0;
    virtual Expression *transformVariable(Variable const *) = 0;
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
    
    Expression *transform(Transformer *tr) const {
		return tr->transformNumber(this);
	}

private:
    double value_;
};

struct BinaryOperation : Expression
{
    enum {
        PLUS = '+',
        MINUS = '-',
        DIV = '/',
        MUL = '*'
    };

    BinaryOperation(Expression const *left, int op, Expression const *right)
        : left_(left), op_(op), right_(right)
    { assert(left_ && right_); }

    ~BinaryOperation()
    {
        delete left_;
        delete right_;
    }

    Expression const *left() const
    { return left_; }

    Expression const *right() const
    { return right_; }

    int operation() const
    { return op_; }

    double evaluate() const
    {
        double left = left_->evaluate();
        double right = right_->evaluate();
        switch (op_)
        {
        case PLUS: return left + right;
        case MINUS: return left - right;
        case DIV: return left / right;
        case MUL: return left * right;
        }
        assert(0);
        return 0.0;
    }
    Expression *transform(Transformer *tr) const {
		return tr->transformBinaryOperation(this);
	}

private:
    Expression const *left_;
    Expression const *right_;
    int op_;
};

struct FunctionCall : Expression
{
	FunctionCall(std::string const &name, Expression const *arg)
        : name_(name), arg_(arg)
    {
        assert(arg_);
        assert(name_ == "sqrt" || name_ == "abs");
    }

    // реализуйте оставшие методы из
    // интерфейса Expression и не забудьте
    // удалить arg_, как это сделано в классе
    // BinaryOperation

    std::string const & name() const
    {
        return name_;
    }

    Expression const *arg() const
    {
         return arg_;   
    }
    
    double evaluate() const {
        
        if (name_ == "sqrt"){
            return sqrt(arg_->evaluate());
        }else if(name_ == "abs"){
            return abs(arg_->evaluate());
        }
        
        assert(0);
        return 0.0;
    }

    ~FunctionCall()
    {
        delete arg_;
    }
    Expression *transform(Transformer *tr) const {
		return tr->transformFunctionCall(this);	
	}

private:
    std::string const name_;
    Expression const *arg_;
};

struct Variable : Expression
{
    Variable(std::string const name) : name_(name){}
    std::string const & name() const {
		return name_;
	}
    double evaluate() const
    {
		return 0.0;
	}
    Expression *transform(Transformer *tr) const 
    {
		return tr->transformVariable(this);
	}

private:
    std::string const name_;
};

/**
 * реализуйте все необходимые методы класса
 * вы можете определять любые вспомогательные
 * методы, если хотите
 */
struct CopySyntaxTree : Transformer
{
    Expression *transformNumber(Number const *number)
    { 	
		return new Number(number->value());
	}

    Expression *transformBinaryOperation(BinaryOperation const *binop)
    {
		return new BinaryOperation(binop->left()->transform(this), binop->operation(), binop->right()->transform(this));
	}

    Expression *transformFunctionCall(FunctionCall const *fcall)
    { 
		return new FunctionCall(fcall->name(), fcall->arg()->transform(this));
	}

    Expression *transformVariable(Variable const *var)
    { 		
		return new Variable(var->name());
	}
};

/**
 * реализуйте все необходимые методы
 * если считаете нужным, то можете
 * заводить любые вспомогательные
 * методы
 */
struct FoldConstants : Transformer
{
    Expression *transformNumber(Number const *number)
    { 
		return new Number(number->value());
	}

    Expression *transformBinaryOperation(BinaryOperation const *binop)
    {
		Expression *left_new = binop->left()->transform(this);
		Expression *right_new = binop->right()->transform(this);
		BinaryOperation *binop_new = new BinaryOperation(left_new, binop->operation(), right_new);
		
        if (dynamic_cast<Number*>(left_new) && dynamic_cast<Number*>(right_new)){
			double res = binop_new->evaluate();
			delete binop_new;
			//delete left_new;
			//delete right_new;
			return new Number(res);
		} else {
			return binop_new;
		}
	}

    Expression *transformFunctionCall(FunctionCall const *fcall)
    { 
		Expression *arg = fcall->arg()->transform(this);
		FunctionCall * fcall_new = new FunctionCall(fcall->name(), arg);
		if(dynamic_cast<Number*>(arg)){
			double res = fcall_new->evaluate();
			//delete arg;
			delete fcall_new;
			return new Number(res);
		} else {
			return fcall_new;
		}
	}

    Expression *transformVariable(Variable const *var)
    { 
		return new Variable(var->name());	
	}
};


int main() {
  struct Number *x = new Number(10);
  struct Number *y = new Number(6);

  Expression *expression1 = new BinaryOperation(x,BinaryOperation::PLUS,y);
  Transformer *transformer1 = new FoldConstants();
  Expression *new_expression1 = expression1->transform(transformer1);

  cout<<"binary operation 1: "<<new_expression1->evaluate()<<endl;

  Expression *expression2 = new FunctionCall("sqrt", new_expression1);
  Expression *new_expression2 = expression2->transform(transformer1);

  cout<<"function call 1: "<<new_expression2->evaluate()<<endl;

  Expression *expression3 = new FunctionCall("sqrt", new_expression2);
  Expression *new_expression3 = expression3->transform(transformer1);

  cout<<"function call 2: "<<new_expression3->evaluate()<<endl;

  Expression *expression4 = new BinaryOperation(new_expression3,BinaryOperation::DIV,y);
  Expression *new_expression4 = expression4->transform(transformer1);

  cout<<"binary operation 2: "<<new_expression4->evaluate()<<endl;
  //system("pause");
  return 0;
}
