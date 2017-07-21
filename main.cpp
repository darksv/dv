#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>
#include <unordered_map>
#include "ast.h"
#include "print-visitor.h"
#include "evaluation-visitor.h"

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
                                                                            Operator::Minus,
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
                                            ),
                                            new IfStatement(
                                                    new BinaryExpression(
                                                            Operator::LessThan,
                                                            new IdentifierExpression("x"),
                                                            new ConstantExpression(5)
                                                    ),
                                                    new ExpressionStatement(
                                                            new CallExpression(
                                                                    "print",
                                                                    {
                                                                            new BinaryExpression(
                                                                                    Operator::Minus,
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
                                                    ),
                                                    nullptr
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