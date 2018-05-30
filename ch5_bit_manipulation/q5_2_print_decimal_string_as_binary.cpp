/*
Given a real number between 0 and 1 (e.g. 0.72) that is passed in as a double, 
print the binary representation. If the number can not be represented accurately
in binary with at most 32 characters, print “ERROR”.
*/

#include <iostream>
#include <string>
#include <limits> // std::numeric_limits
#include <cmath> // std::abs

bool AlmostEqual(double d1, double d2)
{
    return std::abs(d1 - d2) < std::numeric_limits<double>::epsilon();
}

// Recursive method to calculate binary representation of decimal. The basic
// idea is to double the decimal and check if it's >= 1. If it is, we know that
// fractional 2's digit should be 1. We use tail recursion so this function
// could be easily rewritten using a loop. If we cannot accurately (within
// machine double epsilon) represent the decimal number with 32 binary digits,
// we return "ERROR".
void DecToBinary(double dec, std::string & str)
{
    const int MAX_CHARS = 32;
    if (str.size() > MAX_CHARS)
    {
        str = "ERROR";
        return;
    }
    dec *= 2;    
    if (AlmostEqual(dec, 1.0))
    {
        str += '1';
        return;
    }
    if (dec >= 1)
    {
    str += '1';
    dec -= 1;
    }
    else
        str += '0';
    DecToBinary(dec, str);
}

// Input number string must be of the form X.Y (X/Y must be explicitly 0 when
// the number is a pure integer or only a decimal).
std::string DecimalToBinaryString(double num)
{
    if (num >= 1 || num <= 0)
        return "ERROR";

    std::string dec_str;
    DecToBinary(num, dec_str);

    return (dec_str == "ERROR") ? "ERROR" : "0." + dec_str;
}

int main()
{
    double dec  = 0.0000152587890625; // 1/2^16
    double err  = 0.1; // ERROR - binary representation repeats infinitely
    double fail = 0.4999999999999999; // barely fails due to float precision
    double pass = 0.49999999999999999; // barely passes (machine-dependent)

    std::string bin = DecimalToBinaryString(dec);
    std::cout << "Dec = " << dec << "\nBin = " << bin << "\n";
    
    std::string bin_err = DecimalToBinaryString(err);
    std::cout << "Dec = " << err << "\nBin = " << bin_err << "\n";
    
    std::string bin_fail = DecimalToBinaryString(fail);
    std::cout << "Dec = " << fail << "\nBin = " << bin_fail << "\n";
    
    std::string bin_pass = DecimalToBinaryString(pass);
    std::cout << "Dec = " << pass << "\nBin = " << bin_pass << "\n";
}
