#ifndef V0HHFITTER_STRING_TOOLS_H
#define V0HHFITTER_STRING_TOOLS_H 1

// STL include
#include <iosfwd>
#include <sstream>
#include <string>

// ROOT 
#include "Rtypes.h"

// Local include
#include "Exceptions.h"


/*
   M M Reid - 22.01.2012
   string_tools class: Aids user to find and replace parts or all of a string
   given some initial consideration; before, after or all instances.
   Also removes bad characters.
 */

class string_tools {

    public:

        string_tools() {};
        virtual ~string_tools() {};

        void replaceAll(std::string& str, const std::string& from, const std::string& to);
        void replaceAfter(std::string& str, const std::string& text);
        void replaceBefore(std::string& str, const std::string& text);

        // removes any of the following &|()][#><%"' from the string
        std::string removeBadChars(const std::string& input) const;
        // lowercase characters to uppercase
        std::string to_upper(const std::string& input) const;
        // uppercase characters to lowercase
        std::string to_lower(const std::string& input) const;
        // whitespace removed from left
        std::string& lwstrip(std::string& s) ;
        // whitespace removed from right
        std::string& rwstrip(std::string& s) ;
        // trailing and leading whitespace removed
        std::string& removeWhiteSp(std::string& s);
        // returns vector of strings split by some delimiter, ',' for example
        std::vector<std::string> split(const std::string& str, const std::string& separator) const;
        // returns vector of strings split by some delimiter, ',' for example

        void split(std::vector<std::string>& t, const std::string& str, const std::string& separator) ;
        // checks if string is made of digits
        bool is_digit(const std::string& s) const;
        // checks if chars in string are alphabetic
        bool is_alpha(const std::string& s) const;
        // checks if string (str) contrains a sub string (substr)
        bool contains(const std::string& str, const std::string& substr) const;
        // checks that string values are ascii defined
        bool is_ascii(const std::string& str) const;
        // check if char is ascii
        friend bool invalidChar( char c ) ;
        // removes non-ascii characters from string
        void stripUnicode(std::string & str);

        // Convert numerical type to string, no saftey check though
        template <class T>
            inline std::string to_string (const T& t) {
                std::ostringstream ss;
                ss << t;
                if( is_digit( ss.str() ) && !is_alpha( ss.str() ) ) {
                    return ss.str();
                } else {
                    throw V0hhFit::GeneralException( "string_tools::to_string",
                            "Converted string is not a number." );
                }
            };

        // Convert string to type, again no saftey catch.
        template <class T>
            inline T to_number (const std::string& s) {
                double x(0.0);
                if( !is_digit( s ) || is_alpha( s ) ) {
                    throw V0hhFit::GeneralException( "string_tools::to_number",
                            "Input string is not a number." );
                } else {

                    std::istringstream i(s);
                    if (!(i >> x)) {
                        return 0;
                    }
                }
                return x;
            }; 

    private:
        ClassDef( string_tools, 1);

};

// global functions
bool invalidChar( char c) ;

/*
 * class Splitter: Splits strings into parts based on
 *   a separator character.
 */
class Splitter {

    public:
        // Constructor: str is the string to be tokenized, separator
        // is a single character. At each occurrence of separator,
        // the string will be split.
        Splitter(const std::string& str, const std::string& separator )
            : m_s( str ), m_sep( separator ), m_p( 0 ), m_q( 0 ) {}

        // next(): Return the next token
        std::string next()
        {
            m_q = m_s.find( m_sep, m_p );
            std::string tmp( m_s, m_p, m_q - m_p );
            m_p = m_q + 1;
            if ( m_q == std::string::npos )
                m_p = m_q;
            return tmp;
        }

        // good(): indicate that the splitter state is good (i.e.
        // the end of the string has not been reached)
        bool good() { return m_p != std::string::npos; }

    private:
        ClassDef( Splitter, 1 );

        std::string m_s; // ref. to the string being tokenized
        std::string m_sep; // separator character
        std::string::size_type m_p; // p, q: tokenizer state
        std::string::size_type m_q; // as positions in the string

}; // class Splitter

#endif // V0HHFITTER_STRING_TOOLS_H
