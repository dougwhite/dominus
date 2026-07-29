#include <dominus/lexer/lexer.hpp>

namespace dominus
{

Lexer::Lexer(const SourceManager &sources, SourceId source_id) : _sources(sources), _source_id(source_id)
{
}

Token Lexer::NextToken()
{
    return Token{
        TokenKind::EndOfFile,
        SourceSpan{_source_id, 0, 0}
    };
}

} // namespace dominus
