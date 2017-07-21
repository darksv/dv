//
// Created by darksv on 20.07.2017.
//

#include <unordered_map>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "evaluation-visitor.h"


void EvaluationVisitor::apply(ConstantExpression* expr) {
    stack_.push(expr->val());
}

void EvaluationVisitor::apply(IdentifierExpression* expr) {
    const auto& it = variables_.find(expr->id());
    if (it == variables_.end()) {
        throw std::runtime_error("undefined variable " + expr->id());
    }

    stack_.push(it->second);
}

void EvaluationVisitor::apply(UnaryExpression* expr) {
    expr->operand()->accept(*this);
    auto a = stack_.top();
    stack_.pop();
    switch (expr->op()) {
        case Operator::Plus:
            stack_.push(a);
            break;
        case Operator::Minus:
            stack_.push(-a);
            break;
        default:
            break;
    }
}

void EvaluationVisitor::apply(BinaryExpression* expr) {
    expr->lhs()->accept(*this);
    expr->rhs()->accept(*this);

    auto a = stack_.top();
    stack_.pop();
    auto b = stack_.top();
    stack_.pop();

    switch (expr->op()) {
        case Operator::Plus:
            stack_.push(a + b);
            break;
        case Operator::Minus:
            stack_.push(b - a);
            break;
        case Operator::Asterisk:
            stack_.push(a * b);
            break;
        case Operator::Slash:
            stack_.push(b / a);
            break;
        case Operator::LessThan:
            stack_.push(b < a);
            break;
    }
}

void EvaluationVisitor::apply(CallExpression* call) {
    for (const auto& arg : call->args()) {
        arg->accept(*this);

        if (call->id() == "print") {
            std::cout << stack_.top() << " ";
            stack_.pop();
        }
    }
    std::cout << "\n";
    stack_.push(0);
}

void EvaluationVisitor::apply(AssignStatement* assign) {
    assign->rhs()->accept(*this);
    auto a = stack_.top();
    stack_.pop();

    variables_[assign->lhs()->id()] = a;
}

void EvaluationVisitor::apply(BlockStatement* block) {
    for (const auto& stmt : block->stmts()) {
        stmt->accept(*this);
    }
}

void EvaluationVisitor::apply(IfStatement* cond) {
    cond->cond()->accept(*this);
    auto a = stack_.top();
    stack_.pop();

    if (a) {
        cond->ifBody()->accept(*this);
    } else if (cond->elseBody() != nullptr) {
        cond->elseBody()->accept(*this);
    }
}

void EvaluationVisitor::apply(ExpressionStatement* expr) {
    expr->expr()->accept(*this);
    stack_.pop();
}

void EvaluationVisitor::apply(WhileLoop* loop) {
    while (1) {
        loop->cond()->accept(*this);

        auto a = stack_.top();
        stack_.pop();

        if (!a) {
            break;
        }

        loop->body()->accept(*this);
    }
}

void EvaluationVisitor::apply(FunctionStatement* func) {
    func->body()->accept(*this);
}

void EvaluationVisitor::apply(ReturnStatement* ret) {
    ret->expr()->accept(*this);
}