//
// Created by darksv on 20.07.2017.
//

#ifndef DV_EVALUATION_VISITOR_H
#define DV_EVALUATION_VISITOR_H


#include "ast.h"

class EvaluationVisitor : public Visitor {
private:
    std::stack<float> stack_;
    std::unordered_map<std::string, float> variables_;

public:

    void apply(ConstantExpression* expr) override;

    void apply(IdentifierExpression* expr) override;

    void apply(UnaryExpression* expr) override;

    void apply(BinaryExpression* expr) override;

    void apply(CallExpression* call) override;

    void apply(AssignStatement* assign) override;

    void apply(BlockStatement* block) override;

    void apply(IfStatement* cond) override;

    void apply(ExpressionStatement* expr) override;

    void apply(WhileLoop* loop) override;

    void apply(FunctionStatement* func) override;

    void apply(ReturnStatement* ret) override;
};

#endif //DV_EVALUATION_VISITOR_H
