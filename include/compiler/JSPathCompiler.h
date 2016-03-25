#ifndef _JSPATH_COMPILER_H
#define _JSPATH_COMPILER_H
#include <stack>
#include <memory>
namespace jspath
{
class Expression;
struct SubExpressionParser
{
public:
    virtual ~SubExpressionParser();

    virtual void onEntry();
    virtual bool parse(char c) = 0;
    virtual std::shared_ptr<Expression> createExpression() = 0;
};

struct RegexLocationParser: public SubExpressionParser
{
public:
    bool parse(char c) override;
    std::shared_ptr<Expression> createExpression() override;

private:

};

struct Compiler
{

private:
    std::stack<std::shared_ptr<SubExpressionParser>> m;
};

}
#endif

