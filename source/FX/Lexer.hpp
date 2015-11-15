#pragma once

#include "ParserNodes.hpp"

namespace ReShade
{
	namespace FX
	{
		class Lexer
		{
		public:
			class Token
			{
				friend class Lexer;

			public:
				enum class Id
				{
					Unknown = -1,
					EndOfStream = 0,

					// Operators
					Exclaim = '!',
					Hash = '#',
					Dollar = '$',
					Percent = '%',
					Ampersand = '&',
					ParenthesisOpen = '(',
					ParenthesisClose = ')',
					Star = '*',
					Plus = '+',
					Comma = ',',
					Minus = '-',
					Dot = '.',
					Slash = '/',
					Colon = ':',
					Semicolon = ';',
					Less = '<',
					Equal = '=',
					Greater = '>',
					Question = '?',
					At = '@',
					BracketOpen = '[',
					BackSlash = '\\',
					BracketClose = ']',
					Caret = '^',
					BraceOpen = '{',
					Pipe = '|',
					BraceClose = '}',
					Tilde = '~',
					ExclaimEqual = 256 /* != */,
					PercentEqual /* %= */,
					AmpersandAmpersand /* && */,
					AmpersandEqual /* &= */,
					StarEqual /* *= */,
					PlusPlus /* ++*/,
					PlusEqual /* += */,
					MinusMinus /* -- */,
					MinusEqual /* -= */,
					Arrow /* -> */,
					Ellipsis /* ... */,
					SlashEqual /* /= */,
					ColonColon /* :: */,
					LessLessEqual /* <<= */,
					LessLess /* << */,
					LessEqual /* <= */,
					EqualEqual /* == */,
					GreaterGreaterEqual /* >>= */,
					GreaterGreater /* >> */,
					GreaterEqual /* >= */,
					CaretEqual /* ^= */,
					PipeEqual /* |= */,
					PipePipe /* || */,

					// Identifier
					Identifier,
					ReservedWord,

					// Literal
					True,
					False,
					IntLiteral,
					UintLiteral,
					FloatLiteral,
					DoubleLiteral,
					StringLiteral,

					// Keywords
					Namespace,
					Struct,
					Technique,
					Pass,
					For,
					While,
					Do,
					If,
					Else,
					Switch,
					Case,
					Default,
					Break,
					Continue,
					Return,
					Discard,
					Extern,
					Static,
					Uniform,
					Volatile,
					Precise,
					In,
					Out,
					InOut,
					Const,
					Linear,
					NoPerspective,
					Centroid,
					NoInterpolation,

					// Types
					Void,
					Bool,
					Bool2,
					Bool2x2,
					Bool3,
					Bool3x3,
					Bool4,
					Bool4x4,
					Int,
					Int2,
					Int2x2,
					Int3,
					Int3x3,
					Int4,
					Int4x4,
					Uint,
					Uint2,
					Uint2x2,
					Uint3,
					Uint3x3,
					Uint4,
					Uint4x4,
					Float,
					Float2,
					Float2x2,
					Float3,
					Float3x3,
					Float4,
					Float4x4,
					Vector,
					Matrix,
					String,
					Texture1D,
					Texture2D,
					Texture3D,
					Sampler1D,
					Sampler2D,
					Sampler3D,
				};

				Token() : mId(Id::Unknown), mLocation(), mRawData(nullptr), mRawDataLength(0)
				{
					memset(&this->mLiteralNumeric, 0, sizeof(this->mLiteralNumeric));
				}

				inline operator Id() const
				{
					return this->mId;
				}

				static std::string GetName(Id id);
				inline std::string GetName() const
				{
					return GetName(this->mId);
				}
				inline std::string GetRawData() const
				{
					return std::string(this->mRawData, this->mRawDataLength);
				}
				inline const Location &GetLocation() const
				{
					return this->mLocation;
				}

				template <typename T>
				T GetLiteral() const;
				template <>
				inline int GetLiteral() const
				{
					return this->mLiteralNumeric.Int;
				}
				template <>
				inline unsigned int GetLiteral() const
				{
					return this->mLiteralNumeric.Uint;
				}
				template <>
				inline float GetLiteral() const
				{
					return this->mLiteralNumeric.Float;
				}
				template <>
				inline double GetLiteral() const
				{
					return this->mLiteralNumeric.Double;
				}
				template <>
				inline std::string GetLiteral() const
				{
					return this->mLiteralString;
				}

			private:
				union NumericLiteral
				{
					int Int;
					unsigned int Uint;
					float Float;
					double Double;
				};

				Id mId;
				Location mLocation;
				const char *mRawData;
				size_t mRawDataLength;
				std::string mLiteralString;
				NumericLiteral mLiteralNumeric;
			};

			/// <summary>
			/// Construct new lexical analyzer for the given input <paramref name="source" /> string.
			/// </summary>
			/// <param name="source">The string to analyze.</param>
			explicit Lexer(const std::string &source);
			Lexer(const Lexer &lexer)
			{
				this->operator=(lexer);
			}

			Lexer &operator=(const Lexer &lexer);

			/// <summary>
			/// Perform lexical analysis on the input string and return the next token in sequence.
			/// </summary>
			/// <returns>The next token in sequence.</returns>
			Token Lex();

		private:
			void ParseIdentifier(Token &token) const;
			void ParseStringLiteral(Token &token) const;
			void ParseNumericLiteral(Token &token) const;
			void ParsePreProcessorDirective();

			std::string mSource;
			const char *mPos, *mEnd;
			bool mCurrentAtLineBegin;
			Location mCurrentLocation;
		};
	}
}