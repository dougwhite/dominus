#include <dominus/lexer/lexer.hpp>

#include <stdexcept>

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

Lexer::Lexer(const SourceManager &sources, SourceId source_id) : _source_id(source_id), _source_text(sources.Text(source_id))
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

    // Scan for a plus sign
    if (Current() == '+')
    {
        const std::size_t begin = _offset;
        ++_offset;

        return Token{
            TokenKind::Plus,
            SourceSpan{_source_id, begin, _offset}
        };
    }

    throw std::logic_error("Lexeme not yet implemented");
}

} // namespace dominus
