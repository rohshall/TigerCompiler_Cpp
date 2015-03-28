#include "ErrorCodes.h"
#include <map>

const char* ErrorCodes::GetAssociatedMessage(ErrorCode error)
{
    static const std::map<ErrorCode, const char*> errors
    {
        {ErrorCode::Err0, "Err0 - Unidentified Variable"},
        {ErrorCode::Err1, "Err1 - attempt to get field of non-record or use of non-existant field"},
        {ErrorCode::Err2, "Err2 - Attempt to subscript non-array type"},
        {ErrorCode::Err3, "Err3 - Attempt to subscript with non-int"},
        {ErrorCode::Err4, "Err4 - Attempt to get type of array of non-array type"},
        {ErrorCode::Err5, "Err5 - attempt to call non-existant function"},
        {ErrorCode::Err6, "Err6 - attempt to call non function"},
        {ErrorCode::Err7, "Err7 - Incorrect number of arguments given"},
        {ErrorCode::Err8, "Err8 - Type of argument does not match"},
        {ErrorCode::Err9, "Err9 - Left and right types do not match"},
        {ErrorCode::Err10, "Err10 - Attempt to use binary op on non int or string"},
        {ErrorCode::Err11, "Err11 - attempt to create instance of record of non existing type"},
        {ErrorCode::Err12, "Err12 - Type mismatch in AssignmentExpression"},
        {ErrorCode::Err13, "Err13 - If condition of non-int type"},
        {ErrorCode::Err14, "Err14 - If-then-else where then and else branch types do not match"},
        {ErrorCode::Err15, "Err15 - while expression with non-integer test"},
        {ErrorCode::Err16, "Err16 - for expression with ranges not of int type"},
        {ErrorCode::Err17, "Err17 - for expression with body of non unit type"},
        {ErrorCode::Err18, "Err18 - Can not use non-int type for size of array"},
        {ErrorCode::Err19, "Err19 - Attempt to use non-existant type for type of array"},
        {ErrorCode::Err20, "Err20 - Init for array does not match type of array"},
        {ErrorCode::Err21, "Err21 - Use of non-existant type in type annotation in var declaration"},
        {ErrorCode::Err22, "Err22 - Un-matched types in var declaration"},
        {ErrorCode::Err23, "Err23 - Must use long form of var dec if init expression is nil"},
        {ErrorCode::Err24, "Err24 - Attempt to make record with non existant type"},
        {ErrorCode::Err25, "Err25 - Type checking arraytype with non bound name for type"},
        {ErrorCode::Err26, "Err26 - Record lacks enough fields"},
        {ErrorCode::Err27, "Err27 - Record type mismatch"},
        {ErrorCode::Err28, "Err28 - Record position name mismatch"},
        {ErrorCode::Err29, "Err29 - Type is of non record type"},
        {ErrorCode::Err30, "Err30 - Formal argument is of non-existant type"},
        {ErrorCode::Err31, "Err31 - Listed result type of function does not exist"},
        {ErrorCode::Err32, "Err32 - Actual calculated type of function does not match listed type"},
        {ErrorCode::Err33, "Err33 - Expected binary operator"},
        {ErrorCode::Err34, "Err34 - Unclosed parenthesis"},
        {ErrorCode::Err35, "Err35 - If without then"},
        {ErrorCode::Err36, "Err36 - Expected do after condition of while"},
        {ErrorCode::Err37, "Err37 - Expected a variable declaration at start of for"},
        {ErrorCode::Err38, "Err38 - Variable in for loop not assigned initial value"},
        {ErrorCode::Err39, "Err39 - Expected to in for loop"},
        {ErrorCode::Err40, "Err40 - Expected do after header of for loop"},
        {ErrorCode::Err41, "Err41 - Expected in following declaration section of let expression"},
        {ErrorCode::Err42, "Err42 - Expected end following let expression"},
        {ErrorCode::Err43, "Err43 - Malformed LValue"},
        {ErrorCode::Err44, "Err44 - Unclosed paren following call expression"},
        {ErrorCode::Err45, "Err45 - Unclosed brace following record"},
        {ErrorCode::Err46, "Err46 - Unclosed bracket following array"},
        {ErrorCode::Err47, "Err47 - Expected field following ."},
        {ErrorCode::Err48, "Err48 - Exprected ] following subscript"},
        {ErrorCode::Err49, "Err49 - Expected = after id in type fields"},
        {ErrorCode::Err50, "Err50 - Expected Identifier naming type declaration"},
        {ErrorCode::Err51, "Err51 - Expected = after name in TypeDeclaration"},
        {ErrorCode::Err52, "Err52 - Expected Identifier following keyword var"},
        {ErrorCode::Err53, "Err53 - No assignment operator following Var declaration"},
        {ErrorCode::Err54, "Err54 - Error parsing function. Expected keyword function"},
        {ErrorCode::Err55, "Err55 - Expected id to follow function keyword for declaration"},
        {ErrorCode::Err56, "Err56 - Expected ( following name for function declaration"},
        {ErrorCode::Err57, "Err57 - Expected ) following parameter list for function declaration"},
        {ErrorCode::Err58, "Err58 - Expected type literal for type annotation"},
        {ErrorCode::Err59, "Err59 - Expected = to preceed body of function"},
        {ErrorCode::Err60, "Err60 - Unclosed brace following Record declaration"},
        {ErrorCode::Err61, "Err61 - Expected keyword of following array"},
        {ErrorCode::Err62, "Err62 - Expected type literal for array type"},
        {ErrorCode::Err63, "Err63 - Invalid type, assuming array of int"},
        {ErrorCode::Err64, "Err64 - Expected colon after id in type fields"},
        {ErrorCode::Err65, "Err65 - Expected type literal for type annotation following id :"}
    };

    auto err = errors.find(error);
    if (err == end(errors))
    {
        throw CompilerErrorException("Use of an error code that does not have an associated message\nHave you added a new error code to ErrorCodes.h without adding a message in ErrorCode.cpp or vice versa?");
    }
    return err->second;
}
