// Exceptions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

// implement a custom exception
struct CustomException : public _exception 
{
    const char* what() const throw () 
    {
        return "custom_exception";
    }
};

bool do_even_more_custom_application_logic()
{   
    std::cout << "Running Even More Custom Application Logic." << std::endl;

    // logic_error exception thrown 
    throw std::logic_error("Logic error!");

    return true;
}
void do_custom_application_logic()
{
    //  Wrapped the call to do_even_more_custom_application_logic()
    //  with an exception handler that catches std::exception, displays
    //  a message and the exception.what(), then continues processing
    std::cout << "Running Custom Application Logic." << std::endl;

    try
    {
        if (do_even_more_custom_application_logic())
        {
            std::cout << "Even More Custom Application Logic Succeeded." << std::endl;
        }
        
    }
    catch (std::exception& x)
    {
        std::cout << "EXCEPTION OCCURRED!\t" << x.what() << " Caught in do_even_more_custom_application_logic function." << std::endl;
    }

    //  Throw a custom exception derived from std::exception
    //  and catch it explicitly in main
    throw CustomException();
    std::cout << "Leaving Custom Application Logic." << std::endl;

}

float divide(float num, float den)
{
    // Throw an exception to deal with divide by zero errors using
    //  a standard C++ defined exception
    if (den == 0) 
    {
        throw std::runtime_error("Dividing by zero!");
    }
    else 
    {
        return (num / den);
    }

}

void do_division() noexcept
{
    float numerator = 10.0f;
    float denominator = 0;

    //  create an exception handler to capture ONLY the exception thrown
    //  by divide.
    try
    {
        auto result = divide(numerator, denominator);
        std::cout << "divide(" << numerator << ", " << denominator << ") = " << result << std::endl;
    }
    catch (std::runtime_error& x)
    {
        std::cout << "EXCEPTION OCCURRED!\t" << x.what() << " Occurred in do_division function." << std::endl;
    }
}

int main()
{
    std::cout << "Exceptions Tests!" << std::endl;

    //  Create exception handlers that catch multiple exception types and also
    //  catches uncaught exceptions
    try
    {
        do_division();
        do_custom_application_logic();
    }
    // catch if custom exception occurred
    catch (CustomException& x)
    {
        std::cout << "Exception: " << x.what() << std::endl;
    }
    // catch if std::exception occurred
    catch (std::exception& x)
    {
        std::cout << "Exception: " << x.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Exception: UNCAUGHT EXCEPTION!" << std::endl;
    }

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu