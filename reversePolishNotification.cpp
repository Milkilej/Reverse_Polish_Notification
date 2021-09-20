#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

struct TestCase { std::string name{}; std::ostringstream failures{}; };
template <typename T> void operator | (TestCase& testCase, T&& testBody) {
    testBody(); auto failures = testCase.failures.str();
    if (failures.empty()) std::cout << testCase.name << ": SUCCESS\n";
    else std::cerr << testCase.name << ": FAILURE\n" << failures;
}
void addFailure(std::ostream& os, const char* file, unsigned line, const char* condition) {
    os << file << ":" << line << ": Failed: " << condition << "\n";
}
#define TEST(name) TestCase name{#name}; name | [&, &failures = name.failures]
#define EXPECT(cond) if (cond) {} else addFailure(failures, __FILE__, __LINE__, #cond)
#define ASSERT(cond) if (cond) {} else return addFailure(failures, __FILE__, __LINE__, #cond)

#include <string>
#include <vector>
#include <stdlib.h>

enum class Notation{Infix, Postfix};

class RPN{

    std::string str_val;

    void checkingString()
    {
        std::string a, b, z;
        std::string str_res;
        char temp_char{ '\0' };
        for(char&c:str_val)
        {
            if(isdigit(c))
            {
                str_res += c;

            }
            else
            {
                if(temp_char == '\0') 
                {
                    temp_char= c;
                    str_res += ' ';
                }
                else 
                {
                    str_res += ' ';
                    str_res += temp_char;
                    temp_char = c;
                    str_res += ' ';
                }
            }   
        }
        if (temp_char != '\0')
        {
            str_res += ' ';
            str_res += temp_char;
            str_res += ' ';
        } else 
        {
            str_res += ' ';
        }
        str_val = str_res;
        std::cout << "wynik: " << str_val << std::endl;
    }

    public:

    void load(const std::string& value){
        str_val = value;
    }

    std::string get(Notation notation){
        checkingString();
        return str_val;
    }

    int result()
    {
        int result = 0;
        for(char& c: str_val)
        {
            if(isdigit(c))
            {
                result += atoi(str_val.c_str());
                str_val.replace(c);
            }
            else 
            {
                if(c == '+')
                {
                    
                }
            }
        }
        result = atoi(str_val.c_str());
        return result;
    }


};

int main() 
{
    TEST(WhenGivenTwoNumbersInStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("1+1");
        EXPECT(rpn.result()==2);
    };

    TEST(WhenGivenOneNumbersInStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("342");
        EXPECT(rpn.result()==342);
    };

    TEST(WhenGivenDoubledNumbersWithDifferentSignsInStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("342+10-23");
        EXPECT(rpn.get(Notation::Postfix)=="342 10 + 23 - ");
    };

    TEST(WhenGivenDoubledNumbersWithNegativeInStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("10-23");
        EXPECT(rpn.get(Notation::Postfix)=="10 23 - ");
    };
    TEST(WhenGivenDoubledNumbersInStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("10+23");
        EXPECT(rpn.get(Notation::Postfix)=="10 23 + ");
    };

    TEST(WhenGivenStringThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("10");
        EXPECT(rpn.get(Notation::Postfix)=="10 ");
    };

    TEST(WhenGivenStringOnePlusTwoPlusOneThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("1+2+1");

        EXPECT(rpn.get(Notation::Postfix)=="1 2 + 1 + ");
    };

    TEST(WhenGivenStringOnePlusTwoThenWantResultInPostfix)
    {
        RPN rpn;
        rpn.load("1+2");

        EXPECT(rpn.get(Notation::Postfix)=="1 2 + ");
    };

    TEST(WhenOneIsSendAsArgumentThenReturnOne)
    {
        RPN rpn;
        rpn.load("1");
        EXPECT(rpn.get(Notation::Postfix)=="1 ");
    };

}
