#pragma once

#include <dominus/lexer/token.hpp>
#include <dominus/lexer/token_source.hpp>
#include <dominus/source/source_manager.hpp>
#include <dominus/source/source_span.hpp>

#include <cstddef>
#include <initializer_list>
#include <string>
#include <utility>
#include <vector>

namespace dominus::test
{

struct TokenSpec
{
    dominus::TokenKind kind;
    std::size_t begin;
    std::size_t end;
};

class TestTokenSource final : public dominus::TokenSource
{
    public:
        TestTokenSource(std::string source_text, std::initializer_list<TokenSpec> token_specs)
            : _source_id(_sources.AddSource("test-expression.dom", std::move(source_text)))
        {
            _tokens.reserve(token_specs.size() + 1);

            // Build the token sequence
            for (const TokenSpec &spec : token_specs)
            {
                _tokens.emplace_back(
                    spec.kind,
                    dominus::SourceSpan{_source_id, spec.begin, spec.end}
                );
            }

            // Every token stream ends with EOF
            const std::size_t source_end = _sources.Text(_source_id).size();
            _tokens.emplace_back(
                dominus::TokenKind::EndOfFile,
                dominus::SourceSpan{_source_id, source_end, source_end}
            );
        }

        dominus::Token NextToken() override
        {
            // If we reach the end, send the last token (Should always be EOF)
            if (_current >= _tokens.size())
            {
                return _tokens.back();
            }

            return _tokens[_current++];
        }

        const dominus::SourceManager &Sources() const
        {
            return _sources;
        }

        dominus::SourceId Source() const
        {
            return _source_id;
        }

    private:
        dominus::SourceManager _sources;
        dominus::SourceId _source_id;
        std::vector<dominus::Token> _tokens;
        std::size_t _current = 0;
};

} // namespace dominus::test
