#include <iostream>
#include <string> // std::string
#include <cassert>
#include <cmath>  // sqrt и fabs

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


int main() {
  
  Expression * expression = new Number(10.0);
  Transformer * transformer = new CopySyntaxTree();
  Expression * new_expression = expression->transform(transformer);

  delete expression;
  delete transformer;
  cout<<"number: "<<new_expression->evaluate()<<endl;
  delete new_expression;

  expression = new Variable("x");
  transformer = new CopySyntaxTree();
  new_expression = expression->transform(transformer);

  delete expression;
  delete transformer;
  cout<<"new variable: "<<new_expression->evaluate()<<endl;
  delete new_expression;

  enum { PLUS = '+', MINUS = '-', DIV = '/', MUL = '*' };
  struct Number *x = new Number(2);
  struct Number *y = new Number(3);

  expression = new BinaryOperation(x,MUL,y);
  transformer = new CopySyntaxTree();
  new_expression = expression->transform(transformer);

  delete expression;
  delete transformer;
  cout<<"binary operation: "<<new_expression->evaluate()<<endl;
  delete new_expression;
  
  
  x = new Number(2);
  expression = new FunctionCall("sqrt",x);
  transformer = new CopySyntaxTree();
  new_expression = expression->transform(transformer);

  delete expression;
  delete transformer;
  cout<<"function call: "<<new_expression->evaluate()<<endl;
  delete new_expression;

  //system("pause");
  return 0;
}
