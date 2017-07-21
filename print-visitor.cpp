//
// Created by darksv on 20.07.2017.
//

#include <unordered_map>
#include <vector>
#include <fstream>
#include "print-visitor.h"


void PrintVisitor::apply(ConstantExpression* expr) {
    stream_ << expr->val();
}

void PrintVisitor::apply(IdentifierExpression* expr) {
    stream_ << expr->id();
}

void PrintVisitor::apply(UnaryExpression* expr) {
    stream_ << "(";
    op(expr->op());
    expr->operand()->accept(*this);
    stream_ << ")";
}

void PrintVisitor::apply(BinaryExpression* expr) {
    stream_ << "(";
    expr->lhs()->accept(*this);
    stream_ << " ";
    op(expr->op());
    stream_ << " ";
    expr->rhs()->accept(*this);
    stream_ << ")";
}

void PrintVisitor::apply(CallExpression* call) {
    indent();
    stream_ << call->id() << "(";
    for (auto i = 0; i < call->args().size() - 1; ++i) {
        call->args()[i]->accept(*this);
        stream_ << ", ";
    }

    if (call->args().size() > 0) {
        call->args().back()->accept(*this);
    }

    stream_ << ")";
}

void PrintVisitor::apply(AssignStatement* assign) {
    indent();
    stream_ << assign->lhs()->id() << " = ";
    assign->rhs()->accept(*this);
    stream_ << ";\n";
}

void PrintVisitor::apply(BlockStatement* assign) {
    stream_ << "{\n";
    level_++;
    for (const auto& stmt : assign->stmts()) {
        stmt->accept(*this);
    }
    level_--;
    indent();

    stream_ << "\n";
    indent();
    stream_ << "}";
};

void PrintVisitor::apply(IfStatement* cond) {
    indent();
    stream_ << "if (";
    cond->cond()->accept(*this);
    stream_ << ") ";
    cond->ifBody()->accept(*this);
    if (cond->elseBody()) {
        stream_ << " else\n";
        level_++;
        cond->elseBody()->accept(*this);
        level_--;
    }
}

void PrintVisitor::apply(ExpressionStatement* expr) {
    expr->expr()->accept(*this);
    stream_ << ";";
}

void PrintVisitor::apply(WhileLoop* loop) {
    indent();
    stream_ << "while (";
    loop->cond()->accept(*this);
    stream_ << ") ";
    loop->body()->accept(*this);
}

void PrintVisitor::apply(FunctionStatement* func) {
    indent();
    stream_ << "func " << func->id() << "() ";
    func->body()->accept(*this);
}

void PrintVisitor::apply(ReturnStatement* ret) {
    indent();
    stream_ << "\n";
    indent();
    stream_ << "return ";
    ret->expr()->accept(*this);
    stream_ << ";";
}