//
// Created by darksv on 20.07.2017.
//

#ifndef DV_AST_H
#define DV_AST_H

#include <vector>
#include "visitor.h"

enum class Operator {
    Plus,
    Minus,
    Asterisk,
    Slash,
    LessThan
};


class Statement {
public:
    virtual void accept(Visitor& visitor) = 0;
};


class ExpressionStatement : public Statement {
private:
    Expression* expr_;

public:
    Expression* expr() const { return expr_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    ExpressionStatement(Expression* expr) : expr_{expr} {}
};


class AssignStatement : public Statement {
private:
    IdentifierExpression* lhs_;
    Expression* rhs_;

public:
    IdentifierExpression* lhs() const { return lhs_; }

    Expression* rhs() const { return rhs_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    AssignStatement(IdentifierExpression* lhs, Expression* rhs) : lhs_{lhs}, rhs_{rhs} {}
};


class BlockStatement : public Statement {
private:
    std::vector<Statement*> stmts_;

public:
    const std::vector<Statement*>& stmts() const { return stmts_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    BlockStatement(std::vector<Statement*> stmts) : stmts_{stmts} {}
};


class IfStatement : public Statement {
private:
    Expression* cond_;
    Statement* trueBody_;
    Statement* falseBody_;

public:
    Expression* cond() const { return cond_; }

    Statement* trueBody() const { return trueBody_; }

    Statement* falseBody() const { return falseBody_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    IfStatement(Expression* cond, Statement* trueBody, Statement* falseBody) : cond_{cond}, trueBody_{trueBody},
                                                                               falseBody_{falseBody} {}
};


class WhileLoop : public Statement {
private:
    Expression* cond_;
    Statement* body_;

public:
    Expression* cond() const { return cond_; }

    Statement* body() const { return body_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    WhileLoop(Expression* cond, Statement* body) : cond_{cond}, body_{body} {}
};


class FunctionStatement : public Statement {
private:
    std::string id_;
    BlockStatement* body_;

public:
    std::string id() const { return id_; }

    BlockStatement* body() const { return body_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    FunctionStatement(std::string id, BlockStatement* body) : id_{id}, body_{body} {}
};


class ReturnStatement : public Statement {
private:
    Expression* expr_;

public:
    Expression* expr() const { return expr_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    ReturnStatement(Expression* expr) : expr_{expr} {}
};


class Expression {
public:
    virtual void accept(Visitor& visitor) = 0;
};

class ConstantExpression : public Expression {
private:
    float value_;

public:
    float val() const { return value_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    ConstantExpression(float value) : value_{value} {}
};


class IdentifierExpression : public Expression {
private:
    std::string identifier_;

public:
    std::string id() const { return identifier_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    IdentifierExpression(std::string id) : identifier_{id} {}
};


class UnaryExpression : public Expression {
private:
    Operator operator_;
    Expression* operand_;

public:
    Operator op() const { return operator_; }

    Expression* operand() const { return operand_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    UnaryExpression(Operator op, Expression* expr) : operator_{op}, operand_{expr} {};
};


class BinaryExpression : public Expression {
private:
    Operator operator_;
    Expression* lhsOperand_;
    Expression* rhsOperand_;

public:
    Operator op() const { return operator_; }

    Expression* lhs() const { return lhsOperand_; }

    Expression* rhs() const { return rhsOperand_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    BinaryExpression(Operator op, Expression* lhs, Expression* rhs) : operator_{op}, lhsOperand_{lhs},
                                                                      rhsOperand_{rhs} {}
};


class CallExpression : public Expression {
private:
    std::string id_;
    std::vector<Expression*> args_;

public:
    std::string id() const { return id_; }

    const std::vector<Expression*>& args() const { return args_; }

    void accept(Visitor& visitor) override {
        visitor.apply(this);
    }

    CallExpression(std::string id, std::vector<Expression*> args) : id_{id}, args_{args} {}
};


#endif //DV_AST_H
