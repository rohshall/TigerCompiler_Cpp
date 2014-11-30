#include "Tokens.h"

Token::Token(PrimativeToken primToken) throw(TokenException)
	: m_type(primToken)
{
	ThrowIfInproperInit();
}

Token::Token(PrimativeToken primToken, const std::string& value) throw(TokenException)
	: m_type(primToken)
	, m_value(value)
{
	ThrowIfInproperInit();
}

bool Token::HasValue() const
{
	return !m_value.empty();
}

PrimativeToken Token::GetTokenType() const
{
	return m_type;
}

const std::string& Token::UseValue() const
{
	return m_value;
}

void Token::ThrowIfInproperInit() throw(TokenException)
{
	switch(m_type)
	{
	case PrimativeToken::Number:
	case PrimativeToken::Location:
		if (!HasValue())
		{
			throw TokenException();
		}
		break;
	default:
		if (HasValue())
		{
			throw TokenException();
		}
		break;
	}
}