//
// Created by darksv on 20.07.2017.
//

#ifndef DV_PRINT_VISITOR_H
#define DV_PRINT_VISITOR_H


#include <iostream>
#include "visitor.h"
#include "ast.h"

class PrintVisitor : public Visitor {
private:
    int level_ = 0;
    std::ostream& stream_;

    void indent() {
        for (int i = 0; i < level_; ++i) {
            std::cout << " ";
        }
    }

    void op(Operator op) {
        switch (op) {
            case Operator::Plus:
                stream_ << "+";
                break;
            case Operator::Minus:
                stream_ << "-";
                break;
            case Operator::Asterisk:
                stream_ << "*";
                break;
            case Operator::Slash:
                stream_ << "/";
                break;
            case Operator::LessThan:
                stream_ << "<";
                break;
        }
    }

public:
    void apply(ConstantExpression* expr) override;

    void apply(IdentifierExpression* expr) override;

    void apply(UnaryExpression* expr) override;

    void apply(BinaryExpression* expr) override;

    void apply(CallExpression* call) override;

    void apply(AssignStatement* assign) override;

    void apply(BlockStatement* assign) override;

    void apply(IfStatement* cond) override;

    void apply(ExpressionStatement* expr) override;

    void apply(WhileLoop* loop) override;

    void apply(FunctionStatement* func) override;

    void apply(ReturnStatement* ret) override;

    PrintVisitor(std::ostream& stream) : stream_{stream} {}
};

#endif //DV_PRINT_VISITOR_H
