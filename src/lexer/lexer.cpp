#include <dominus/lexer/lexer.hpp>

// Helper character classification functions
namespace
{

bool IsAsciiDigit(char character)
{
    return character >= '0' && character <= '9';
}

bool IsWhitespace(char character)
{
    return character == ' '
        || character == '\t'
        || character == '\n'
        || character == '\r'
        || character == '\v'
        || character == '\f';
}

} // namespace

namespace dominus
{

Lexer::Lexer(const SourceManager &sources, SourceId source_id, DiagnosticBag &diagnostics)
    : _source_id(source_id), _source_text(sources.Text(source_id)), _diagnostics(diagnostics)
{
}

bool Lexer::AtEnd() const
{
    return _offset == _source_text.size();
}

char Lexer::Current() const
{
    return _source_text[_offset];
}

Token Lexer::ConsumeSingle(TokenKind token_kind)
{
    const std::size_t begin = _offset;
    ++_offset;

    return Token{
        token_kind,
        SourceSpan{_source_id, begin, _offset}
    };
}

Token Lexer::NextToken()
{
    // Skip any whitespace
    while (!AtEnd() && IsWhitespace(Current()))
    {
        ++_offset;
    }

    // When we reach the end of our source text we are finished
    if (AtEnd())
    {
        return Token{
            TokenKind::EndOfFile,
            SourceSpan{_source_id, _offset, _offset}
        };
    }

    // Scan for an integer literal
    if (IsAsciiDigit(Current()))
    {
        const std::size_t begin = _offset;

        while (!AtEnd() && IsAsciiDigit(Current()))
        {
            ++_offset;
        }

        return Token{
            TokenKind::IntegerLiteral,
            SourceSpan{_source_id, begin, _offset}
        };
    }

    // Scan for valid single character tokens
    switch (Current())
    {
        case '+':
            return ConsumeSingle(TokenKind::Plus);

        case '-':
            return ConsumeSingle(TokenKind::Minus);

        case '*':
            return ConsumeSingle(TokenKind::Star);

        case '/':
            return ConsumeSingle(TokenKind::Slash);

        case '(':
            return ConsumeSingle(TokenKind::LeftParenthesis);

        case ')':
            return ConsumeSingle(TokenKind::RightParenthesis);

        default:
        {
            // Consume and report an unexpected character
            const Token invalid = ConsumeSingle(TokenKind::Invalid);

            _diagnostics.Report(
                DiagnosticCode::UnexpectedCharacter,
                invalid.Span()
            );

            return invalid;
        }
    }

}

} // namespace dominus
