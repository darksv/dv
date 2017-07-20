//
// Created by darksv on 20.07.2017.
//

#ifndef DV_VISITOR_H
#define DV_VISITOR_H

class ExpressionStatement;

class AssignStatement;

class BlockStatement;

class IfStatement;

class WhileLoop;

class FunctionStatement;

class ReturnStatement;

class Expression;

class ConstantExpression;

class IdentifierExpression;

class CallExpression;

class UnaryExpression;

class BinaryExpression;

class Visitor {
public:
    virtual void apply(ConstantExpression* expr) = 0;

    virtual void apply(IdentifierExpression* expr) = 0;

    virtual void apply(UnaryExpression* expr) = 0;

    virtual void apply(BinaryExpression* expr) = 0;

    virtual void apply(CallExpression* call) = 0;

    virtual void apply(AssignStatement* assign) = 0;

    virtual void apply(BlockStatement* block) = 0;

    virtual void apply(IfStatement* cond) = 0;

    virtual void apply(ExpressionStatement* expr) = 0;

    virtual void apply(WhileLoop* loop) = 0;

    virtual void apply(FunctionStatement* func) = 0;

    virtual void apply(ReturnStatement* ret) = 0;
};

#endif //DV_VISITOR_H
