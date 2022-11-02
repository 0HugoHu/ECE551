#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

class Expression {
 public:
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 private:
  int num;

 public:
  NumExpression(int n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << num;
    return sstream.str();
  }
  virtual ~NumExpression() {}
};

class OpExpression : public Expression {
 private:
  const char * operand;
  Expression * lhs;
  Expression * rhs;

 public:
  OpExpression(const char * op, Expression * lhs, Expression * rhs) :
      operand(op), lhs(lhs), rhs(rhs) {}
  virtual std::string toString() const {
    std::stringstream sstream;
    sstream << "(" << lhs->toString() << " " << *operand << " " << rhs->toString() << ")";
    return sstream.str();
  }
  virtual ~OpExpression() {
    delete lhs;
    delete rhs;
  }
};

class PlusExpression : public OpExpression {
 public:
  PlusExpression(Expression * lhs, Expression * rhs) : OpExpression("+", lhs, rhs) {}
};

class MinusExpression : public OpExpression {
 public:
  MinusExpression(Expression * lhs, Expression * rhs) : OpExpression("-", lhs, rhs) {}
};

class TimesExpression : public OpExpression {
 public:
  TimesExpression(Expression * lhs, Expression * rhs) : OpExpression("*", lhs, rhs) {}
};

class DivExpression : public OpExpression {
 public:
  DivExpression(Expression * lhs, Expression * rhs) : OpExpression("/", lhs, rhs) {}
};
