#ifndef _JSPATH_COMPILER_H
#define _JSPATH_COMPILER_H
#include <stack>
#include <memory>
#include <map>
#include <vector>
namespace jspath
{
class Expression;
struct SubExpressionParser
{
public:
    enum type
    {
        Any,
        Init,
        Space,
        Dot,
        GenericLocation,
        RegexLocation,
        QuoteLocation,
        TwoDotLocation,
        MultiLocation,
        ArrayIndex,
        PredicateExp,
        Exception
    };
    virtual ~SubExpressionParser();

    virtual void onEntry();
    virtual size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) = 0;
    virtual std::shared_ptr<Expression> onExit() = 0;
    virtual type getCode() const = 0;
};

struct InitParser: public SubExpressionParser
{
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override { return fromPos; }
    std::shared_ptr<Expression> onExit() override { return nullptr; }
    type getCode() const override { return Init; }
};

struct SpaceParser: public SubExpressionParser
{
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override { return nullptr; }
    type getCode() const override { return Space; }
};

struct DotParser: public SubExpressionParser
{
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) { return fromPos + 1; }
    std::shared_ptr<Expression> onExit() override { return nullptr; }
    type getCode() const override { return Dot; }
};


struct RegexLocationParser: public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;
    type getCode() const override { return RegexLocation; }

private:
    std::string mRegexText;
};

struct QuoteLocationParser : public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;
    type getCode() const override { return QuoteLocation; }

private:
    bool mIsWildcard;
    std::string mLocation;
};

class GenericLocationParser: public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;

    type getCode() const override { return GenericLocation; }
private:
    bool mIsWildcard;
    std::string mLocation;
};

struct TwoDotLocationParser: public SubExpressionParser
{
public:
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override { return fromPos + 1; }
    std::shared_ptr<Expression> onExit() override;
    type getCode() const override { return TwoDotLocation; }
};

struct MultiLocationParser: public SubExpressionParser
{
public:
    MultiLocationParser();

    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;
    type getCode() const override { return MultiLocation; }

private:
    const std::string* mFullExpression;
    std::vector<std::size_t> mSubExpressionIndices;
};

struct PositionalParser: public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;
    type getCode() const override { return ArrayIndex; }
private:
    std::string mIndex;
};

struct PredicateParser: public SubExpressionParser
{
public:
    void onEntry() override;
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override;

    type getCode() const override { return PredicateExp; }
private:
    std::string mPredicate;
};

struct ExceptionParser: public SubExpressionParser
{
    void onEntry() override {}
    size_t parse(const std::string& fullExpression, size_t fromPos, size_t endPos) override;
    std::shared_ptr<Expression> onExit() override { return nullptr; }

    type getCode() const override { return Exception; }
};
struct Compiler
{
public:
    Compiler();
    std::shared_ptr<Expression> compile(const std::string& strExpression
                                        , size_t& begPos
                                        , size_t endPos = std::string::npos);

private:
    typedef std::shared_ptr<SubExpressionParser> State;
    typedef char Event;
    typedef std::shared_ptr<std::map<Event, State>> SubTransaction;

    std::map<SubExpressionParser::type, SubTransaction> mTransactions;
    State mCurrentState;
    SubTransaction mCurrentSubState;
    SubTransaction mAnySubState;

    void addTransaction(State fromState, Event, State toState);
    std::shared_ptr<Expression> processEvent(Event event);

    static const Event DotEvent = '.';
    static const Event SlashEvent = '/';
    static const Event QuoteEvent = '"';
     const Event OtherEvent = 2;
    static const Event OpenBrace = '{';
    static const Event CloseBrace = '}';
    static const Event OpenBracket = '[';
    static const Event CloseBracket = ']';
    static const Event OpenParenthesis = '(';
    static const Event CloseParenthesis = ')';
    static const Event EOFEvent = 1;
};

}
#endif

