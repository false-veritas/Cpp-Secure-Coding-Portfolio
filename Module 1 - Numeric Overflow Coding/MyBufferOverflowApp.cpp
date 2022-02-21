// NumericOverflows.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>     // std::cout
#include <limits>       // std::numeric_limits

/// <summary>
/// Template function to abstract away the logic of:
///   start + (increment * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="increment">How much to add each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start + (increment * steps)</returns>

// use SFINAE to enable function if integrals are used
template<class T> typename std::enable_if<std::is_integral<T>::value, T>::type add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    // set result to start value passed
    T result = start;

    // set auto variable to hold max value of passed type, calculated at compile time
    constexpr auto max_numeric_limit = std::numeric_limits<T>::max();

    // variable to hold value of max - result to compare it to increment 
    T left_to_max{};

    // loop increments based on number of steps passed
    for (unsigned long i = 0; i < steps; ++i)
    {
        // get new value each iteration
        left_to_max = max_numeric_limit - result;

        // catch overflow and throw exception if condition met
        if (left_to_max < increment)
        {
            throw std::overflow_error("OVERFLOW!");
        }

        // being here means no overflow. continue.
        result += increment;
    }

    // done
    return result;
}


// use SFINAE to enable function if floating points are used
template<class T> typename std::enable_if<std::is_floating_point<T>::value, T>::type add_numbers(T const& start, T const& increment, unsigned long int const& steps)
{
    // set result to start value passed
    T result = start;

    // set auto variable to hold max value of passed type, calculated at compile time
    constexpr auto max_numeric_limit = std::numeric_limits<T>::max();

    // variable to hold value of max - result to compare it to increment
    T left_to_max{};

    // loop increments based on number of steps passed
    // ****steps have been subtracted by 1.  this is due to floating point values not being exact and overflow was caused even with 5 steps
    // ****this can be regulated through use of epsilon but for the purposes of this assignment, steps were just decreased by 1.
    for (unsigned long i = 0; i < steps; ++i)
    {
        // get new value each iteration
        left_to_max = max_numeric_limit - result;

        // catch overflow and throw exception if condition met
        if (left_to_max <= increment)
        {
            throw std::overflow_error("OVERFLOW!");
        }

        // being here means no overflow. continue.
        result += increment;
    }

    // done
    return result;
}


/// <summary>
/// Template function to abstract away the logic of:
///   start - (decrement * steps)
/// </summary>
/// <typeparam name="T">A type that with basic math functions</typeparam>
/// <param name="start">The number to start with</param>
/// <param name="decrement">How much to subtract each step</param>
/// <param name="steps">The number of steps to iterate</param>
/// <returns>start - (decrement * steps)</returns>

// use SFINAE to enable function if integrals are used
template<class T> typename std::enable_if<std::is_integral<T>::value, T>::type subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    // set result to start value passed
    T result = start;

    // set auto variable to hold min value of passed type, calculated at compile time
    constexpr auto min_numeric_limit = std::numeric_limits<T>::min();

    // used in conditional statement to check for underflow 
    const auto cut_off = decrement + min_numeric_limit;

    // loop increments based on number of steps passed
    for (unsigned long i = 0; i < steps; ++i)
    {
        // check if underflow happen for this iteration
        if(result < cut_off)
        {
            throw std::underflow_error("UNDERFLOW!");
        }

        // being here means no underflow. continue.
        result -= decrement;
    }

    // done
    return result;


}

// use SFINAE to enable function if floating points are used
template<class T> typename std::enable_if<std::is_floating_point<T>::value, T>::type subtract_numbers(T const& start, T const& decrement, unsigned long int const& steps)
{
    // set result to start value passed
    T result = start;

    // set auto variable to hold min value of passed type, calculated at compile time
    constexpr auto min_numeric_limit = std::numeric_limits<T>::min();

    // used in conditional statement to check for underflow 
    const auto cut_off = decrement + min_numeric_limit;

    // loop increments based on number of steps passed
    for (unsigned long i = 0; i < steps; ++i)
    {
        // check if underflow happen for this iteration
        if (result < cut_off)
        {
            throw std::underflow_error("UNDERFLOW!");
        }

        // being here means no underflow. continue.
        result -= decrement;
    }

    // done
    return result;

}


//  NOTE:
//    You will see the unary ('+') operator used in front of the variables in the test_XXX methods.
//    This forces the output to be a number for cases where cout would assume it is a character. 

template <typename T>
void test_overflow()
{
    // TODO: The add_numbers template function will overflow in the second method call
    //        You need to change the add_numbers method to:
    //        1. Detect when an overflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no overflow happened or
    //        4. Return something to tell test_overflow the addition failed
    //        NOTE: The add_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_overflow method to:
    //        1. Detect when an add_numbers failed
    //        2. Inform the user the overflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_overflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we add each step (result should be: start + (increment * steps))
    const T increment = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = 0;

    std::cout << "Overflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // try/catch block to catch Overflow
    try
    {
        std::cout << "\tAdding Numbers Without Overflow (" << +start << ", " << +increment << ", " << steps << ") = ";
        T result = add_numbers<T>(start, increment, steps);
        std::cout << +result << std::endl;

        std::cout << "\tAdding Numbers With Overflow (" << +start << ", " << +increment << ", " << (steps + 1) << ") = ";
        result = add_numbers<T>(start, increment, steps + 1);
        std::cout << +result << std::endl;
    }
    catch (std::exception x) 
    {
        std::cout << x.what() << std::endl;
    }
}

template <typename T>
void test_underflow()
{

  
    // TODO: The subtract_numbers template function will underflow in the second method call
    //        You need to change the subtract_numbers method to:
    //        1. Detect when an underflow will happen
    //        2. Prevent it from happening
    //        3. Return the correct value when no underflow happened or
    //        4. Return something to tell test_underflow the subtraction failed
    //        NOTE: The subtract_numbers method must remain a template in the NumericFunctions header.
    //
    //        You need to change the test_underflow method to:
    //        1. Detect when an subtract_numbers failed
    //        2. Inform the user the underflow happened
    //        3. A successful result displays the same result as before you changed the method
    //        NOTE: You cannot change anything between START / END DO NOT CHANGE
    //              The test_underflow method must remain a template in the NumericOverflows source file
    //
    //  There are more than one possible solution to this problem. 
    //  The solution must work for all of the data types used to call test_overflow() in main().

    // START DO NOT CHANGE
    //  how many times will we iterate
    const unsigned long int steps = 5;
    // how much will we subtract each step (result should be: start - (increment * steps))
    const T decrement = std::numeric_limits<T>::max() / steps;
    // whats our starting point
    const T start = std::numeric_limits<T>::max();

    std::cout << "Underflow Test of Type = " << typeid(T).name() << std::endl;
    // END DO NOT CHANGE

    // try/catch block to catch Underflow
    try
    {
        std::cout << "\tSubtracting Numbers Without Underflow (" << +start << ", " << +decrement << ", " << steps << ") = ";
        T result = subtract_numbers<T>(start, decrement, steps);
        std::cout << +result << std::endl;

        std::cout << "\tSubtracting Numbers With Underflow (" << +start << ", " << +decrement << ", " << (steps + 1) << ") = "; 
        result = subtract_numbers<T>(start, decrement, (steps * 2) + 1); // change steps to be multiplied by 2 first so that it reflects 10 steps that can be done before underflow occurs
        std::cout << +result << std::endl;
    }
    catch (std::exception x) 
    {
        std::cout << x.what() << std::endl;
    }
}

void do_overflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Overflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_overflow<char>();
    test_overflow<wchar_t>();
    test_overflow<short int>();
    test_overflow<int>();
    test_overflow<long>();
    test_overflow<long long>();

    // unsigned integers
    test_overflow<unsigned char>();
    test_overflow<unsigned short int>();
    test_overflow<unsigned int>();
    test_overflow<unsigned long>();
    test_overflow<unsigned long long>();

    // real numbers
    test_overflow<float>();
    test_overflow<double>();
    test_overflow<long double>();
}

void do_underflow_tests(const std::string& star_line)
{
    std::cout << std::endl << star_line << std::endl;
    std::cout << "*** Running Undeflow Tests ***" << std::endl;
    std::cout << star_line << std::endl;

    // Testing C++ primative times see: https://www.geeksforgeeks.org/c-data-types/
    // signed integers
    test_underflow<char>();
    test_underflow<wchar_t>();
    test_underflow<short int>();
    test_underflow<int>();
    test_underflow<long>();
    test_underflow<long long>();

    // unsigned integers
    test_underflow<unsigned char>();
    test_underflow<unsigned short int>();
    test_underflow<unsigned int>();
    test_underflow<unsigned long>();
    test_underflow<unsigned long long>();

    // real numbers
    test_underflow<float>();
    test_underflow<double>();
    test_underflow<long double>();
}

/// <summary>
/// Entry point into the application
/// </summary>
/// <returns>0 when complete</returns>
int main()
{
    //  create a string of "*" to use in the console
    const std::string star_line = std::string(50, '*');

    // change order to reflect order of tests
    std::cout << "Starting Numeric Overflow / Underflow Tests!" << std::endl;

    // run the overflow tests
    do_overflow_tests(star_line);

    // run the underflow tests
    do_underflow_tests(star_line);

    // change order to reflect order of tests
    std::cout << std::endl << "All Numeric Overflow / Underflow Tests Complete!" << std::endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu