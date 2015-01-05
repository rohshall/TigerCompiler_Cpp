#include "gtest/gtest.h"

#include "Parser.h"
#include <typeinfo>
#include <iostream>

using namespace std;
using namespace AST;

void AssertThatAstsMatch(const Expression& lhs, const Expression& rhs);

void AssertThatTypesMatch(const Type& lhs, const Type& rhs)
{
    const char* lTy = typeid(lhs).name();
    const char* rTy = typeid(rhs).name();

    if (strcmp(lTy, rTy) != 0)
    {
        cout << "lTy: " << lTy << "\nrTy: " << rTy << "\n";
        ASSERT_EQ(true, false);
    }

    const char* namTy = typeid(NameType).name();
    const char* recTy = typeid(RecordType).name();
    const char* arrTy = typeid(ArrayType).name();

    if (strcmp(lTy, namTy) == 0)
    {
        auto lv = dynamic_cast<const NameType*>(&lhs);
        auto rv = dynamic_cast<const NameType*>(&rhs);
        ASSERT_STREQ(lv->name.c_str(), rv->name.c_str());
    }
    if (strcmp(lTy, recTy) == 0)
    {
        auto lv = dynamic_cast<const RecordType*>(&lhs);
        auto rv = dynamic_cast<const RecordType*>(&rhs);
        for (unsigned int i = 0; i < lv->fields.size(); ++i)
        {
            ASSERT_STREQ(lv->fields[i].name.c_str(), rv->fields[i].name.c_str());
            ASSERT_STREQ(lv->fields[i].type.c_str(), rv->fields[i].type.c_str());
        }
    }
    if (strcmp(lTy, arrTy) == 0)
    {
        auto lv = dynamic_cast<const ArrayType*>(&lhs);
        auto rv = dynamic_cast<const ArrayType*>(&rhs);
        ASSERT_STREQ(lv->name.c_str(), rv->name.c_str());
    }
}

void AssertThatVarsMatch(const Var& lhs, const Var& rhs)
{
    const char* lTy = typeid(lhs).name();
    const char* rTy = typeid(rhs).name();

    if (strcmp(lTy, rTy) != 0)
    {
        cout << "lTy: " << lTy << "\nrTy: " << rTy << "\n";
        ASSERT_EQ(true, false);
    }

    const char* smpTy = typeid(SimpleVar).name();
    const char* fldTy = typeid(FieldVar).name();
    const char* subTy = typeid(SubscriptVar).name();

    if (strcmp(lTy, smpTy) == 0)
    {
        auto lv = dynamic_cast<const SimpleVar*>(&lhs);
        auto rv = dynamic_cast<const SimpleVar*>(&rhs);
        ASSERT_STREQ(lv->symbol.c_str(), rv->symbol.c_str());
    }
    if (strcmp(lTy, fldTy) == 0)
    {
        auto lv = dynamic_cast<const FieldVar*>(&lhs);
        auto rv = dynamic_cast<const FieldVar*>(&rhs);
        ASSERT_STREQ(lv->symbol.c_str(), rv->symbol.c_str());
        AssertThatVarsMatch(*lv->var, *rv->var);
    }
    if (strcmp(lTy, subTy) == 0)
    {
        auto lv = dynamic_cast<const SubscriptVar*>(&lhs);
        auto rv = dynamic_cast<const SubscriptVar*>(&rhs);
        AssertThatVarsMatch(*lv->var, *rv->var);
        AssertThatAstsMatch(*lv->expression, *rv->expression);
    }
}

void AssertThatDeclarationsMatch(const Declaration& lhs, const Declaration& rhs)
{
    const char* lTy = typeid(lhs).name();
    const char* rTy = typeid(rhs).name();

    if (strcmp(lTy, rTy) != 0)
    {
        cout << "lTy: " << lTy << "\nrTy: " << rTy << "\n";
        ASSERT_EQ(true, false);
    }

    const char* funTy = typeid(FunctionDeclaration).name();
    const char* varTy = typeid(VarDeclaration).name();
    const char* tyTy = typeid(TypeDeclaration).name();

    if (strcmp(lTy, funTy) == 0)
    {
        auto lv = dynamic_cast<const FunctionDeclaration*>(&lhs);
        auto rv = dynamic_cast<const FunctionDeclaration*>(&rhs);
        ASSERT_EQ(lv->decls.size(), rv->decls.size());
        for (unsigned int i = 0; i < lv->decls.size(); ++i)
        {
            const FunDec* ld = &lv->decls[i];
            const FunDec* rd = &rv->decls[i];
            ASSERT_STREQ(ld->name.c_str(), rd->name.c_str());
            ASSERT_STREQ(ld->resultTy.c_str(), rd->resultTy.c_str());
            AssertThatAstsMatch(*ld->body, *rd->body);
            ASSERT_EQ(ld->fields.size(), rd->fields.size());
            for (unsigned int j = 0; j < ld->fields.size(); ++j)
            {
                ASSERT_STREQ(ld->fields[j].name.c_str(), rd->fields[j].name.c_str());
                ASSERT_STREQ(ld->fields[j].type.c_str(), rd->fields[j].type.c_str());
            }
        }
    }
    if (strcmp(lTy, varTy) == 0)
    {
        auto lv = dynamic_cast<const VarDeclaration*>(&lhs);
        auto rv = dynamic_cast<const VarDeclaration*>(&rhs);
        ASSERT_STREQ(lv->name.c_str(), rv->name.c_str());
        ASSERT_STREQ(lv->type.c_str(), rv->type.c_str());
        AssertThatAstsMatch(*lv->init, *rv->init);
    }
    if (strcmp(lTy, tyTy) == 0)
    {
        auto lv = dynamic_cast<const TypeDeclaration*>(&lhs);
        auto rv = dynamic_cast<const TypeDeclaration*>(&rhs);
        ASSERT_EQ(lv->types.size(), rv->types.size());
        for (unsigned int i = 0 ; i < lv->types.size(); ++i)
        {
            ASSERT_STREQ(lv->types[i].name.c_str(), rv->types[i].name.c_str());
            AssertThatTypesMatch(*lv->types[i].type, *rv->types[i].type);
        }
    }
}

void AssertThatAstsMatch(const Expression& lhs, const Expression& rhs)
{
    const char* lTy = typeid(lhs).name();
    const char* rTy = typeid(rhs).name();

    if (strcmp(lTy, rTy) != 0)
    {
        cout << "lTy: " << lTy << "\nrTy: " << rTy << "\n";
        ASSERT_EQ(true, false);
    }

    const char* varTy = typeid(VarExpression).name();
    const char* nilTy = typeid(NilExpression).name();
    const char* intTy = typeid(IntExpression).name();
    const char* strTy = typeid(StringExpression).name();
    const char* calTy = typeid(CallExpression).name();
    const char*  opTy = typeid(OpExpression).name();
    const char* recTy = typeid(RecordExpression).name();
    const char* seqTy = typeid(SeqExpression).name();
    const char* assTy = typeid(AssignmentExpression).name();
    const char*  ifTy = typeid(IfExpression).name();
    const char* whlTy = typeid(WhileExpression).name();
    const char* forTy = typeid(ForExpression).name();
    const char* brkTy = typeid(BreakExpression).name();
    const char* letTy = typeid(LetExpression).name();
    const char* arrTy = typeid(ArrayExpression).name();

    if (strcmp(lTy, varTy) == 0)
    {
        return;
    }
    if (strcmp(lTy, nilTy) == 0)
    {
        // always matches
        return;
    }
    if (strcmp(lTy, intTy) == 0)
    {
        auto lxp = dynamic_cast<const IntExpression*>(&lhs);
        auto rxp = dynamic_cast<const IntExpression*>(&rhs);
        ASSERT_EQ(lxp->value, rxp->value);
    }
    if (strcmp(lTy, strTy) == 0)
    {
        auto lxp = dynamic_cast<const StringExpression*>(&lhs);
        auto rxp = dynamic_cast<const StringExpression*>(&rhs);
        ASSERT_STREQ(lxp->value.c_str(), rxp->value.c_str());
    }
    if (strcmp(lTy, calTy) == 0)
    {
        auto lxp = dynamic_cast<const CallExpression*>(&lhs);
        auto rxp = dynamic_cast<const CallExpression*>(&rhs);
        ASSERT_STREQ(lxp->function.c_str(), rxp->function.c_str());
        ASSERT_EQ(lxp->args.size(), rxp->args.size());
        for (unsigned int i = 0; i < lxp->args.size(); i++)
        {
            AssertThatAstsMatch(*lxp->args[i], *rxp->args[i]);
        }
    }
    if (strcmp(lTy, opTy) == 0)
    {
        auto lxp = dynamic_cast<const OpExpression*>(&lhs);
        auto rxp = dynamic_cast<const OpExpression*>(&rhs);
        ASSERT_EQ(static_cast<int>(lxp->op), static_cast<int>(rxp->op));
        AssertThatAstsMatch(*lxp->lhs, *rxp->lhs);
        AssertThatAstsMatch(*lxp->rhs, *rxp->rhs);
    } 
    if (strcmp(lTy, recTy) == 0)
    {
        auto lxp = dynamic_cast<const RecordExpression*>(&lhs);
        auto rxp = dynamic_cast<const RecordExpression*>(&rhs);
        ASSERT_STREQ(lxp->type.c_str(), rxp->type.c_str());
        ASSERT_EQ(lxp->fields.size(), rxp->fields.size());
        for (unsigned int i = 0; i < lxp->fields.size(); ++i)
        {
            ASSERT_STREQ(lxp->fields[i].field.c_str(), rxp->fields[i].field.c_str());
            AssertThatAstsMatch(
                    *lxp->fields[i].expr,
                    *rxp->fields[i].expr);
        }
    }
    if (strcmp(lTy, seqTy) == 0)
    {
        auto lxp = dynamic_cast<const SeqExpression*>(&lhs);
        auto rxp = dynamic_cast<const SeqExpression*>(&rhs);
        ASSERT_EQ(lxp->expressions.size(), rxp->expressions.size());
        for (unsigned int i = 0; i < lxp->expressions.size(); ++i)
        {
            AssertThatAstsMatch(
                    *lxp->expressions[i],
                    *rxp->expressions[i]);
        }
    }
    if (strcmp(lTy, assTy) == 0)
    {
        auto lxp = dynamic_cast<const AssignmentExpression*>(&lhs);
        auto rxp = dynamic_cast<const AssignmentExpression*>(&rhs);
        AssertThatVarsMatch(*lxp->var, *rxp->var);
        AssertThatAstsMatch(*lxp->expression, *rxp->expression);
    }
    if (strcmp(lTy, ifTy) == 0)
    {
        auto lxp = dynamic_cast<const IfExpression*>(&lhs);
        auto rxp = dynamic_cast<const IfExpression*>(&rhs);
        AssertThatAstsMatch(*lxp->test, *rxp->test);
        AssertThatAstsMatch(*lxp->thenBranch, *rxp->thenBranch);
        if (!lxp->elseBranch)
        {
            ASSERT_EQ(nullptr, rxp->elseBranch.get());
        }
        else
        {
            AssertThatAstsMatch(*lxp->elseBranch, *rxp->elseBranch);
        }
    }
    if (strcmp(lTy, whlTy) == 0)
    {
        auto lxp = dynamic_cast<const WhileExpression*>(&lhs);
        auto rxp = dynamic_cast<const WhileExpression*>(&rhs);
        AssertThatAstsMatch(*lxp->test, *rxp->test);
        AssertThatAstsMatch(*lxp->body, *rxp->body);
    }
    if (strcmp(lTy, forTy) == 0)
    {
        auto lxp = dynamic_cast<const ForExpression*>(&lhs);
        auto rxp = dynamic_cast<const ForExpression*>(&rhs);
        ASSERT_STREQ(lxp->var.c_str(), rxp->var.c_str());
        AssertThatAstsMatch(*lxp->high, *rxp->high);
        AssertThatAstsMatch(*lxp->low, *rxp->low);
        AssertThatAstsMatch(*lxp->body, *rxp->body);
    }
    if (strcmp(lTy, brkTy) == 0)
    {
       return; 
    }
    if (strcmp(lTy, letTy) == 0)
    {
        auto lxp = dynamic_cast<const LetExpression*>(&lhs);
        auto rxp = dynamic_cast<const LetExpression*>(&rhs);
        AssertThatAstsMatch(*lxp->body, *rxp->body);
        ASSERT_EQ(lxp->decls.size(), rxp->decls.size());
        for (unsigned int i = 0 ; i < lxp->decls.size(); ++i)
        {
            AssertThatDeclarationsMatch(*lxp->decls[i], *rxp->decls[i]);
        }
    }
    if (strcmp(lTy, arrTy) == 0)
    {
        auto lxp = dynamic_cast<const ArrayExpression*>(&lhs);
        auto rxp = dynamic_cast<const ArrayExpression*>(&rhs);
        ASSERT_STREQ(lxp->type.c_str(), rxp->type.c_str());
        AssertThatAstsMatch(*lxp->size, *rxp->size);
        AssertThatAstsMatch(*lxp->init, *rxp->init);
    }
}


class ParserTest : public ::testing::Test
{
public:
    void SetUp() override { parser = nullptr; }
    void CreateFromString(const string& program);
    std::unique_ptr<Parser> parser;
};

void ParserTest::CreateFromString(const string& program)
{
    unique_ptr<istream> stream = make_unique<stringstream>(program);
    TokenStream tokenStream(move(stream));
    parser = make_unique<Parser>(move(tokenStream));
}

TEST_F(ParserTest, NilExp_noParens) 
{
    CreateFromString("nil");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> nil = make_unique<Program>(make_unique<NilExpression>());
    AssertThatAstsMatch(*nil->expression, *prog->expression);
}

TEST_F(ParserTest, IntExp_noParens)
{
    CreateFromString("4");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> four = make_unique<Program>(make_unique<IntExpression>(4));
    AssertThatAstsMatch(*prog->expression, *four->expression);
}

TEST_F(ParserTest, SimpleArithExp_noParens)
{
    CreateFromString("4 + 5");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<OpExpression>(
        make_unique<IntExpression>(4),
        make_unique<IntExpression>(5),
        BinOp::Plus
    ));
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, StringExp)
{
    CreateFromString("\"Hello\"");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<StringExpression>("Hello"));
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, BreakExp)
{
    CreateFromString("break");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<BreakExpression>());
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, UnMatchedParens_throws)
{
    CreateFromString("( int ");
    ASSERT_THROW(parser->Parse(), ParseException);
}

TEST_F(ParserTest, MatchedParens_Int)
{
    CreateFromString("(4)");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> four = make_unique<Program>(make_unique<IntExpression>(4));
    AssertThatAstsMatch(*prog->expression, *four->expression);
}

TEST_F(ParserTest, NegExpression)
{
    CreateFromString("-6");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<OpExpression>(
        make_unique<IntExpression>(0),
        make_unique<IntExpression>(6),
        BinOp::Minus
    ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, Unit)
{
    CreateFromString("()");
    unique_ptr<Program> prog = parser->Parse();

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<SeqExpression>(vector<unique_ptr<Expression>>())
    );
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, SeqUnit)
{
    CreateFromString("(4 ; ())");
    unique_ptr<Program> prog = parser->Parse();

    vector<unique_ptr<Expression>> vec;
    vec.push_back(make_unique<IntExpression>(4));
    vec.push_back(make_unique<SeqExpression>(vector<unique_ptr<Expression>>()));

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<SeqExpression>(move(vec))
    );
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, SeqInts)
{
    CreateFromString("(4 ; 5)");
    unique_ptr<Program> prog = parser->Parse();

    vector<unique_ptr<Expression>> vec;
    vec.push_back(make_unique<IntExpression>(4));
    vec.push_back(make_unique<IntExpression>(5));

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<SeqExpression>(move(vec))
    );
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, AndWeirdness)
{
    CreateFromString("4 & 7");
    unique_ptr<Program> prog = parser->Parse();

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<IfExpression>(
            make_unique<IntExpression>(4),
            make_unique<IntExpression>(7),
            make_unique<IntExpression>(0))
        );
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, OrWeirdness)
{
    CreateFromString("4 | 7");
    unique_ptr<Program> prog = parser->Parse();

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<IfExpression>(
            make_unique<IntExpression>(4),
            make_unique<IntExpression>(1),
            make_unique<IntExpression>(7))
        );
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, IfWithElse)
{
    CreateFromString("if 4 then 7 else 5");
    unique_ptr<Program> prog = parser->Parse();

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<IfExpression>(
            make_unique<IntExpression>(4),
            make_unique<IntExpression>(7),
            make_unique<IntExpression>(5))
        );
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, IfWithNoElse)
{
    CreateFromString("if 4 then 7");
    unique_ptr<Program> prog = parser->Parse();

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<IfExpression>(
            make_unique<IntExpression>(4),
            make_unique<IntExpression>(7),
            nullptr)
        );
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, ArithExp_Precedence)
{
    CreateFromString("4 + 5 * 3");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<OpExpression>(
        make_unique<IntExpression>(4),
        make_unique<OpExpression>(
            make_unique<IntExpression>(5),
            make_unique<IntExpression>(3),
            BinOp::Times
        ),
        BinOp::Plus
    ));
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, ArithExp_PrecedenceBustingParens)
{
    CreateFromString("(4 + 5) * 3");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<OpExpression>(
        make_unique<OpExpression>(
            make_unique<IntExpression>(4),
            make_unique<IntExpression>(5),
            BinOp::Plus
        ),
        make_unique<IntExpression>(3),
        BinOp::Times
    ));
    AssertThatAstsMatch(*prog->expression, *target->expression);
}

TEST_F(ParserTest, WhileExpr)
{
    CreateFromString("while 1 do 2");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<WhileExpression>(
        make_unique<IntExpression>(1),
        make_unique<IntExpression>(2)
        ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, ForExpr)
{
    CreateFromString("for a := 1 to 2 do 3");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<ForExpression>(
        "a",
        make_unique<IntExpression>(1),
        make_unique<IntExpression>(2),
        make_unique<IntExpression>(3)
        ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, CallExprNoArgs)
{
    CreateFromString("a()");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(make_unique<CallExpression>(
        "a",
        vector<unique_ptr<Expression>>()
        ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, CallExprOneArg)
{
    CreateFromString("a(1)");
    unique_ptr<Program> prog = parser->Parse();
    vector<unique_ptr<Expression>> args;
    args.push_back(make_unique<IntExpression>(1));
    unique_ptr<Program> target = make_unique<Program>(make_unique<CallExpression>(
        "a",
        move(args)
        ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}


TEST_F(ParserTest, CallExprManyArgs)
{
    CreateFromString("a(1, 2, 3)");
    unique_ptr<Program> prog = parser->Parse();
    vector<unique_ptr<Expression>> args;
    args.push_back(make_unique<IntExpression>(1));
    args.push_back(make_unique<IntExpression>(2));
    args.push_back(make_unique<IntExpression>(3));
    unique_ptr<Program> target = make_unique<Program>(make_unique<CallExpression>(
        "a",
        move(args)
        ));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, BigSeq)
{
    CreateFromString("(a := 5; a + 1)");
    unique_ptr<Program> prog = parser->Parse();

    vector<unique_ptr<Expression>> exprs;
    exprs.push_back(make_unique<AssignmentExpression>(
        make_unique<SimpleVar>("a"),
        make_unique<IntExpression>(5)));

    exprs.push_back(make_unique<OpExpression>(
        make_unique<VarExpression>(make_unique<SimpleVar>("a")),
        make_unique<IntExpression>(1),
        BinOp::Plus
        ));

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<SeqExpression>(move(exprs)));

    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, LetFunDecs)
{
    CreateFromString("let var a := 5 function f() : int = g(a) function g(i : int) = f() in f() end");
    unique_ptr<Program> prog = parser->Parse();

    vector<FunDec> fundecs;

    vector<unique_ptr<Expression>> args;
    args.push_back(make_unique<VarExpression>(make_unique<SimpleVar>("a")));

    fundecs.push_back(FunDec("f", vector<Field>(), "int", make_unique<CallExpression>("g", move(args))));

    fundecs.push_back(FunDec("g", { Field("i", "int") }, "", make_unique<CallExpression>("f", vector<unique_ptr<Expression>>())));

    vector<unique_ptr<Declaration>> decs;
    decs.push_back(make_unique<VarDeclaration>("a", "", make_unique<IntExpression>(5)));
    decs.push_back(make_unique<FunctionDeclaration>(move(fundecs)));

    unique_ptr<Program> target = make_unique<Program>(make_unique<LetExpression>(
        move(decs),
        make_unique<CallExpression>("f", vector<unique_ptr<Expression>>())));

    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, EmptyLet)
{
    CreateFromString("let in end");
    unique_ptr<Program> prog = parser->Parse();
    unique_ptr<Program> target = make_unique<Program>(
        make_unique<LetExpression>(vector<unique_ptr<Declaration>>(), make_unique<SeqExpression>(vector<unique_ptr<Expression>>())));
    AssertThatAstsMatch(*target->expression, *prog->expression);
}

TEST_F(ParserTest, TypeDecs)
{
    CreateFromString("let type tree = {key: int, children: treelist} type treelist = {head: tree, tail: treelist} in end");
    unique_ptr<Program> prog = parser->Parse();

    vector<TyDec> tyDecs;
    tyDecs.push_back(TyDec("tree", make_unique<RecordType>( vector<Field>{ Field("key", "int") , Field("children", "treelist") } )));
    tyDecs.push_back(TyDec("treelist", make_unique<RecordType>( vector<Field>{ Field("head", "tree"), Field("tail", "treelist") } )));

    vector<unique_ptr<Declaration>> decls;
    decls.push_back(make_unique<TypeDeclaration>(move(tyDecs)));

    unique_ptr<Program> target = make_unique<Program>(
        make_unique<LetExpression>(move(decls), make_unique<SeqExpression>(vector<unique_ptr<Expression>>())));
    
    AssertThatAstsMatch(*target->expression, *prog->expression);
}
