#include "Environments.h"

using namespace std;

shared_ptr<TypeEnvironment> TypeEnvironment::GenerateBaseTypeEnvironment()
{
    auto tyEnv = make_shared<TypeEnvironment>();
    tyEnv->BeginScope();
    tyEnv->Insert(SymbolFactory::GenerateSymbol("int"), TypeFactory::MakeIntType());
    tyEnv->Insert(SymbolFactory::GenerateSymbol("string"), TypeFactory::MakeStringType());
    return tyEnv;
}

shared_ptr<ValueEnvironment> ValueEnvironment::GenerateBaseValueEnvironment()
{
    auto valEnv = make_shared<ValueEnvironment>();
    valEnv->BeginScope();
    auto print = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeStringType()}, TypeFactory::MakeUnitType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("print"), print);
    auto flush = make_shared<FunEntry>(vector<Type>{}, TypeFactory::MakeUnitType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("flush"), flush);
    auto getchar = make_shared<FunEntry>(vector<Type>{}, TypeFactory::MakeStringType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("getchar"), getchar);
    auto ord = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeStringType()}, TypeFactory::MakeIntType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("ord"), ord);
    auto chr = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeIntType()}, TypeFactory::MakeStringType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("chr"), chr);
    auto size = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeStringType()}, TypeFactory::MakeIntType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("size"), size);
    auto substring = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeStringType(), TypeFactory::MakeIntType(), TypeFactory::MakeIntType()}, TypeFactory::MakeStringType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("substring"), substring);
    auto concat = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeStringType(), TypeFactory::MakeStringType()}, TypeFactory::MakeStringType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("concat"), concat);
    auto nott = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeIntType()}, TypeFactory::MakeIntType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("not"), nott);
    auto exit = make_shared<FunEntry>(vector<Type>{TypeFactory::MakeIntType()}, TypeFactory::MakeUnitType());
    valEnv->Insert(SymbolFactory::GenerateSymbol("exit"), exit);
    return valEnv;
}
