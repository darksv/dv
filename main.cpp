#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <unordered_map>


enum class Operator {
    Plus,
    Minus,
    Asterisk,
    Slash,
    LessThan
};

class Expression;

class ConstantExpression;

class IdentifierExpression;

class UnaryExpression;

class BinaryExpression;

class CallExpression;

class AssignStatement;

class BlockStatement;

class ExpressionStatement;

class IfStatement;

class WhileLoop;

class FunctionStatement;

class ReturnStatement;

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
    void apply(ConstantExpression* expr) override {
        stream_ << expr->val();
    }

    void apply(IdentifierExpression* expr) override {
        stream_ << expr->id();
    }

    void apply(UnaryExpression* expr) override {
        stream_ << "(";
        op(expr->op());
        expr->operand()->accept(*this);
        stream_ << ")";
    }

    void apply(BinaryExpression* expr) override {
        stream_ << "(";
        expr->lhs()->accept(*this);
        stream_ << " ";
        op(expr->op());
        stream_ << " ";
        expr->rhs()->accept(*this);
        stream_ << ")";
    }

    void apply(CallExpression* call) override {
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

    void apply(AssignStatement* assign) override {
        indent();
        stream_ << assign->lhs()->id() << " = ";
        assign->rhs()->accept(*this);
        stream_ << ";\n";
    }

    void apply(BlockStatement* assign) override {
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

    void apply(IfStatement* cond) override {
        indent();
        stream_ << "if (";
        cond->cond()->accept(*this);
        stream_ << ") ";
        cond->trueBody()->accept(*this);
        stream_ << " else\n";
        level_++;
        cond->falseBody()->accept(*this);
        level_--;
    }

    void apply(ExpressionStatement* expr) override {
        expr->expr()->accept(*this);
        stream_ << ";";
    }

    void apply(WhileLoop* loop) override {
        indent();
        stream_ << "while (";
        loop->cond()->accept(*this);
        stream_ << ") ";
        loop->body()->accept(*this);
    }

    void apply(FunctionStatement* func) override {
        indent();
        stream_ << "func " << func->id() << "() ";
        func->body()->accept(*this);
    }

    void apply(ReturnStatement* ret) override {
        indent();
        stream_ << "\n";
        indent();
        stream_ << "return ";
        ret->expr()->accept(*this);
        stream_ << ";";
    }

    PrintVisitor(std::ostream& stream) : stream_{stream} {}
};

class EvaluationVisitor : public Visitor {
private:
    std::stack<float> stack_;
    std::unordered_map<std::string, float> variables_;

public:
    void apply(ConstantExpression* expr) override {
        stack_.push(expr->val());
    }

    void apply(IdentifierExpression* expr) override {
        const auto& it = variables_.find(expr->id());
        if (it == variables_.end()) {
            throw std::runtime_error("undefined variable " + expr->id());
        }

        stack_.push(it->second);
    }

    void apply(UnaryExpression* expr) override {
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

    void apply(BinaryExpression* expr) override {
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

    void apply(CallExpression* call) override {
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

    void apply(AssignStatement* assign) override {
        assign->rhs()->accept(*this);
        auto a = stack_.top();
        stack_.pop();

        variables_[assign->lhs()->id()] = a;
    }

    void apply(BlockStatement* block) override {
        for (const auto& stmt : block->stmts()) {
            stmt->accept(*this);
        }
    }

    void apply(IfStatement* cond) override {
        cond->cond()->accept(*this);
        auto a = stack_.top();
        stack_.pop();

        if (a) {
            cond->trueBody()->accept(*this);
        } else {
            cond->falseBody()->accept(*this);
        }
    }

    void apply(ExpressionStatement* expr) override {
        expr->expr()->accept(*this);
        stack_.pop();
    }

    void apply(WhileLoop* loop) override {
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

    void apply(FunctionStatement* func) override {
        func->body()->accept(*this);
    }

    void apply(ReturnStatement* ret) override {
        ret->expr()->accept(*this);
    }
};


int main() {
    auto x = new BlockStatement(
            {
                    new AssignStatement(
                            new IdentifierExpression("x"),
                            new ConstantExpression(0)
                    ),
                    new WhileLoop(
                            new BinaryExpression(
                                    Operator::LessThan,
                                    new IdentifierExpression("x"),
                                    new ConstantExpression(10)
                            ),
                            new BlockStatement(
                                    {
                                            new AssignStatement(
                                                    new IdentifierExpression("x"),
                                                    new BinaryExpression(
                                                            Operator::Plus,
                                                            new IdentifierExpression("x"),
                                                            new ConstantExpression(1)
                                                    )
                                            ),
                                            new ExpressionStatement(
                                                    new CallExpression(
                                                            "print",
                                                            {
                                                                    new BinaryExpression(
                                                                            Operator::Asterisk,
                                                                            new IdentifierExpression("x"),
                                                                            new ConstantExpression(10)
                                                                    ),
                                                                    new IdentifierExpression("x"),
                                                                    new BinaryExpression(
                                                                            Operator::Slash,
                                                                            new IdentifierExpression("x"),
                                                                            new ConstantExpression(10)
                                                                    )
                                                            }
                                                    )
                                            )
                                    }
                            )
                    ),
                    new ReturnStatement(
                            new IdentifierExpression("x")
                    )
            }
    );

    auto y = new FunctionStatement("main", x);

    std::cout << "Source: \n";
    PrintVisitor pv{std::cout};
    y->accept(pv);

    std::cout << "\nExecution: \n";
    EvaluationVisitor ev;
    x->accept(ev);



//    printf("printme: %p %p\n", printme, &printme);
//
//    void* p = VirtualAlloc(nullptr, 0x1000, MEM_COMMIT, PAGE_READWRITE);
//    printf("Allocated at %p\n", p);
//
//    std::uint8_t* pp = reinterpret_cast<std::uint8_t*>(&printme);
//
//    std::uint8_t xd[] = {0xb8, pp[0], pp[1], pp[2], pp[3], 0xFF, 0xE0};
//    std::fill_n((std::uint8_t*)p, 0x1000, 0xCC);
//    std::copy_n(xd, 7, (std::uint8_t*)p);
//
//    DWORD s;
//    VirtualProtect(p, 0x1000, PAGE_EXECUTE, &s);
//    reinterpret_cast<void(*)()>(p)();
//    printme();

    return 0;
}