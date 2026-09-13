// ECE 209: Fall 2026
// Program 1: polynomial arithmetic

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// GLOBAL CONSTANTS
const int MAX_DEGREE = 10; // highest degree of polynomial in this program
const int POLY_SIZE = 22;
// Each coefficient is a rational number = two integers
// For coefficient i, index is 2*i for numerator and 2*i+1 for denominator

// ========== FUNCTION DECLARATIONS ==========
// DO NOT write function definitions here -- see the function definition templates
// after the main function

// A rational number is represented as an array of two integers: numerator and denominator.
// The numerator may be positive, negative, or zero.
// The denominator must be positive and non-zero.
int reduceRational(int x[]);                               // reduce rational number x to its canonical form
int addRational(const int x[], const int y[], int sum[]);  // sum = x + y
int subRational(const int x[], const int y[], int diff[]); // diff = x - y
int mulRational(const int x[], const int y[], int prod[]); // prod = xy
int divRational(const int x[], const int y[], int quot[]); // quot = x/y (there is no remainder)

// Polynomials are represented as fixed-size integer arrays, so the array lengths
// are not needed in the functions. Return value is status code, described with each function.

int addPoly(const int p1[], const int p2[], int sum[]);        // sum <- p1 + p2
int subPoly(const int p1[], const int p2[], int diff[]);       // diff <- p1 - p2
int mulPoly(const int p1[], const int p2[], int prod[]);       // prod <- p1 * p2
int divPoly(const int p1[], const int p2[], int q[], int r[]); // p1/p2, quot <- quotient, r <- remainder
int evalPoly(const int p[], const int x[], int val[]);         // val <- p(x), where x and val are rational numbers

// ---------------------------------------------------------------------------------------------------------------
// These functions are provided for you. See the implementations after the
// functions that you write, but DO NOT CHANGE these definitions.

int gcd(int a, int b); // returns greatest common divisor (or 0 if either is zero)

void printRational(const int x[]);                     // print number as integer or as (a/b)
int readRational(int x[]);                             // read number as integer or as (a/b)
int strToRational(const char *s, char **end, int x[]); // get rational number from head of string

void printPoly(const int p[]);         // print to standard output
int readPoly(int p[]);                 // read from standard input
int strToPoly(const char *s, int p[]); // read polynomial from string

void performOperation(char option);

// =====================================================================
// MAIN FUNCTION -- user interface
// User chooses an operation, enters polyonmial(s), and sees result.

int main()
{
    char userInput[3] = "";

    // print menu and get user choice
    char option = '\0';
    printf("POLYNOMIAL ARITHMETIC\n");
    printf("e = evaluate\n");
    printf("+ = add\n");
    printf("- = subtract\n");
    printf("* = multipy\n");
    printf("/ = divide\n");
    printf("\nOperation: ");
    fflush(stdout);
    fgets(userInput, 3, stdin);
    option = userInput[0];
    performOperation(option);
    return 0;
}

// =====================================================================
// FUNCTION DEFINITION TEMPLATES
// Complete the definition of each function, as described in the program specification.

const int NOT_IMPLEMENTED = 666;

// replace rational number x with its canonical form
// returns 0 if success, 1 if error
int reduceRational(int x[])
{
    //reduce fraction to lowest terms
    //check for zero denominator
    if (x[1] == 0)
    {
        return 1; // error: denominator is zero
    }
    // ensure denominator is positive
    if (x[1] < 0)
    {
        x[0] = -x[0];
        x[1] = -x[1];
    }
    // zero numerator, set denominator to 1
    if (x[0] == 0)
    {
        x[1] = 1;
        return 0; // success
    }
    // find gcd for numerator and denominator
    int divisor = gcd(x[0], x[1]);
    x[0] /= divisor;
    x[1] /= divisor;
    return 0; // success
}

// sum = x + y
// compute the addition of two rational numbers, placing (reduced) result in sum
// returns 0 if success, 1 if error
int addRational(const int x[], const int y[], int sum[])
{
    if (x[1] == 0 || y[1] == 0)
    {
        return 1; // error: denominator is zero
    }
    sum[0] = x[0] * y[1] + y[0] * x[1]; // numerator
    sum[1] = x[1] * y[1]; // denominator
    reduceRational(sum);
    return 0; // success
}

// diff = x - y
// compute the subtraction of two rational numbers, placing (reduced) difference in diff
// returns 0 if success, 1 if error
int subRational(const int x[], const int y[], int diff[])
{
    if (x[1] == 0 || y[1] == 0)
    {
        return 1; // error: denominator is zero
    }
    diff[0] = x[0] * y[1] - y[0] * x[1]; // numerator
    diff[1] = x[1] * y[1]; // denominator
    reduceRational(diff);
    return 0; // success
}

// prod = xy
// compute the multiplication of two rational numbers, placing (reduced) product in diff
// returns 0 if success, 1 if error
int mulRational(const int x[], const int y[], int prod[])
{
    if (x[1] == 0 || y[1] == 0)
    {
        return 1; // error: denominator is zero
    }
    prod[0] = x[0] * y[0]; // numerator
    prod[1] = x[1] * y[1]; // denominator
    reduceRational(prod);
    return 0; // success
}

// quot = x/y (there is no remainder -- result is always a rational number)
// compute the division of two rational numbers, placing (reduced) quotient in quot
// returns 0 if success, 2 if divide-by-zero, 1 if any other error
int divRational(const int x[], const int y[], int quot[])
{
    return NOT_IMPLEMENTED;
}

// Polynomials are represented as fixed-size integer arrays, so the array lengths
// are not needed in the functions. Return value is status code, described with each function.
// All coefficients and variable values are rational numbers.

// val <- p(x)
// evaluate the polynomial p(x) with a given value of x
// reduced result is placed in val
// returns 0 if success, 1 if error
int evalPoly(const int p[], const int x[], int val[])
{
    return NOT_IMPLEMENTED;
}

// sum <- p1 + p2
// compute the addition of two polynomials, with the (reduced) sum placed in sum
// returns 0 if success, 1 if error
int addPoly(const int p1[], const int p2[], int sum[])
{
    for (int i = 0; i <= MAX_DEGREE; ++i){
        int x[2] = {p1[2*i], p1[2*i+1]}; // coefficient of x^i in p1
        int y[2] = {p2[2*i], p2[2*i+1]}; // coefficient of x^i in p2
        int s[2]; // empty array to hold the sum of coefficients

        if (addRational(x, y, s) != 0) { // also runs addRational to add the coefficients
            return 1; // error in rational addition
        }
        sum[2*i] = s[0]; // store numerator into sum 
        sum[2*i+1] = s[1]; // store denominator into sum
    }
    return 0; // success
}

// diff <- p1 - p2
// compute the subtraction of two polynomials, with the (reduced) different placed in diff
// returns 0 if success, 1 if error
int subPoly(const int p1[], const int p2[], int diff[])
{
    for (int i = 0; i <= MAX_DEGREE; ++i){
        int x[2] = {p1[2*i], p1[2*i+1]}; // coefficient of x^i in p1
        int y[2] = {p2[2*i], p2[2*i+1]}; // coefficient of x^i in p2
        int s[2]; // empty array to hold the difference of coefficients

        if (subRational(x, y, s) != 0) { // also runs subRational to subtract the coefficients
            return 1; // error in rational subtraction
        }
        diff[2*i] = s[0]; // store numerator into diff 
        diff[2*i+1] = s[1]; // store denominator into diff
    }
    return 0; // success
}

// prod <- p1 * p2
// compute the multiplication of two polynomials, with the (reduced) product placed in prod
// returns 0 if success, 2 if result degree is too large, 1 if any other error
int mulPoly(const int p1[], const int p2[], int prod[])
{
    for (int k = 0; k <= MAX_DEGREE; ++k){ // initialize all coefficients of prod to 0/1
        prod[2*k] = 0; // initialize numerator to 0
        prod[2*k+1] = 1; // initialize denominator to 1
    }
    for (int i = 0; i <= MAX_DEGREE; ++i){
        int x[2] = {p1[2*i], p1[2*i+1]}; // coefficient of x^i in p1
    
    for (int j = 0; j <= MAX_DEGREE; ++j){
        int y[2] = {p2[2*j], p2[2*j+1]}; // coefficient of x^j in p2
        int term[2]; // p1 x^i term  * p2 x^j term 

        if (mulRational(x, y, term) != 0) { // also runs mulRational to multiply the coefficients
            return 1; // error in rational multiplication
        }
        int k = i + j; // degree of the resulting term
        if (k > MAX_DEGREE) {
            if (term[0] != 0) { // if the term is not zero, then the result degree is too large
                return 2; // result degree is too large
            }
            continue; // if the term is zero, we can ignore it and continue
        }
        int current[2] = {prod[2*k], prod[2*k+1]}; // current coefficient of x^k in prod
        int newSum[2];
        if (addRational(current, term, newSum) != 0) { // add the new term to the existing term in prod
            return 1; // error in rational addition
        }
        prod[2*k] = newSum[0];
        prod[2*k+1] = newSum[1];
    }
}
    return 0; // success
}

// p1/p2, q <- quotient, r <- remainder
// compute the division of two polynomials, with the (reduced) quotient placed in q
// and the (reduced) remainder placed in r
// returns 0 if success, 2 if divide-by-zero, 1 if any other error
int divPoly(const int p1[], const int p2[], int q[], int r[])
{
    return NOT_IMPLEMENTED;
}

// =====================================================================
// PROVIDED FUNCTIONS
// *** DO NOT CHANGE any code beyond this point ***

// user interface
void performOperation(char option)
{
    int p1[POLY_SIZE], p2[POLY_SIZE];     // input polynomials
    int out1[POLY_SIZE], out2[POLY_SIZE]; // output polynomials
    int n1[2], n2[2];                     // temp rational numbers
    int status = 0;                       // error code for function calls

    switch (option)
    {
    case 'e':
        printf("\nEnter polynomial:\n");
        status = readPoly(p1);
        if (status)
        {
            printf("ERROR (%d) reading polynomial\n", status);
            break;
        }
        printf("\nEnter value:\n");
        status = readRational(n1);
        if (status)
        {
            printf("ERROR (%d) reading rational number\n", status);
            break;
        }
        status = evalPoly(p1, n1, n2);
        if (status)
        {
            printf("\nERROR (%d): Unable to evaluate\n", status);
            break;
        }
        printf("\nRESULT = ");
        printRational(n2);
        printf("\n\n");
        break;

    case '+':
    case '-':
    case '*':
        printf("\nEnter first polynomial:\n");
        status = readPoly(p1);
        if (status)
            break;
        printf("\nEnter second polynomial:\n");
        status = readPoly(p2);
        if (status)
            break;
        if (option == '+')
        {
            status = addPoly(p1, p2, out1);
        }
        else if (option == '-')
        {
            status = subPoly(p1, p2, out1);
        }
        else if (option == '*')
        {
            status = mulPoly(p1, p2, out1);
        }
        if (status)
        {
            printf("\nERROR (%d): Unable to evaluate\n", status);
            break;
        }
        printf("\nRESULT = \n");
        printPoly(out1);
        printf("\n\n");
        break;

    case '/':
        printf("\nEnter dividend polynomial:\n");
        status = readPoly(p1);
        if (status)
            break;
        printf("\nEnter divisor polynomial:\n");
        status = readPoly(p2);
        if (status)
            break;
        status = divPoly(p1, p2, out1, out2);
        if (status)
        {
            printf("\nERROR (%d): Unable to evaluate\n", status);
            break;
        }
        printf("\nQUOTIENT = \n");
        printPoly(out1);
        printf("\nREMAINDER = \n");
        printPoly(out2);
        printf("\n\n");
        break;

    default:
        break;
    }
}

// Compute greatest common divisor of two integers.
// Returns 0 if either input argument is zero.
// (This code is easily found/generated, so we'll just give it to you.)
// REF: https://en.wikipedia.org/wiki/Euclidean_algorithm
int gcd(int a, int b)
{
    if ((a == 0) || (b == 0))
        return 0;
    if (a < 0)
        a = -a; // make both numbers positive
    if (b < 0)
        b = -b;
    int tmp = 0;
    while (b)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

void printRational(const int x[])
{ // print number as integer or as (a/b)
    if (x[1] == 0)
        printf("(Illegal)");
    else if (x[1] == 1)
        printf("%d", x[0]);
    else
    {
        if (x[0] < 0)
            printf("-(%d/%d)", -x[0], x[1]);
        else
            printf("(%d/%d)", x[0], x[1]);
    }
}

// extract a non-zero unsigned rational number from the beginning of a string
// format of a rational is "%u" or "(%u/%u)"
// no leading spaces or other characters are allowed, and no spaces within the value
// end stores a pointer to the first character after the rational number
// returns 0 if no error, 1 if error
int strToRational(const char *s, char **end, int r[])
{
    int status = 0;
    if (isdigit(*s))
    {
        r[0] = (int)strtoul(s, end, 10); // digit is numerator, and denominator is 1
        r[1] = 1;
        return status;
    }
    else if (*s == '(')
    {
        // format must be (%u/%u)
        s++;
        r[0] = (int)strtoul(s, end, 10);
        if (!r[0])
            status = 1;
        s = *end;
        if (*s != '/')
            status = 1;
        s++;
        r[1] = (int)strtoul(s, end, 10);
        if (!r[1])
            status = 1;
        s = *end;
        if (*s != ')')
            status = 1;
        else
            *end = (char *)(s + 1); // discards const, but that's ok
    }
    else
    {
        status = 1;       // return 0 to indicate error
        *end = (char *)s; // discards const, but that's ok
    }
    return status;
}

// read rational number -- integer or (a/b) -- from standard input
// may include leading spaces and/or one minus sign
// this will be used for user input, assuming that only one value is entered on the line (consumes LF)
// returns 0 if successful, 1 if error or if anything extra is on the line
// if error, x is set to zero
int readRational(int x[])
{
    char buff[81] = "\0"; // read line from user
    fgets(buff, 80, stdin);
    char *s = buff;
    char *end = s;
    int status = 0;
    int isNegative = 0;
    x[0] = 0;
    x[1] = 1;

    // skip leading spaces and look for minus sign
    // also allow spaces after the minus sign
    while (*s)
    {
        if (*s == '\n')
            break;
        else if (isspace(*s))
            s++;
        else if (*s == '-')
        {
            if (isNegative)
                status = 1; // two minus signs, error
            isNegative = 1;
            s++;
        }
        else
            break;
    }
    if (!*s || (*s == '\n'))
        return 1; // reached end of string with no number

    // extract value
    status = strToRational(s, &end, x);
    return status;
}

int isOne(const int x[])
{
    if (x[1] != 1)
        return 0;
    if ((x[0] == 1) || (x[0] == -1))
        return 1;
    return 0;
}

void printPoly(const int p[])
{
    int i;              // index into polynomial array
    int first_term = 1; // if first term, print sign as minus operator
    for (i = MAX_DEGREE * 2; i >= 0; i -= 2)
    {
        if ((p[i] != 0) || (p[i + 1] == 0)) // if illegal, print it
        {
            // print operator and coefficient
            if (!first_term)
            {
                if (p[i] > 0)
                {
                    printf(" + ");
                    if ((i == 0) || (p[i] != 1) || (p[i + 1] != 1))
                        printRational(&p[i]);
                }
                else
                {
                    int tmp[2];
                    tmp[0] = -p[i];
                    tmp[1] = p[i + 1];
                    printf(" - ");
                    if ((i == 0) || (tmp[0] != 1) || (tmp[1] != 1))
                        printRational(tmp);
                }
            }
            else
            {
                if (p[i] < 0)
                {
                    if ((i == 0) || (p[i] != -1) || (p[i + 1] != 1))
                        printRational(&p[i]);
                    else
                        printf("-");
                }
                else if ((i == 0) || (p[i] != 1) || (p[i + 1] != 1))
                    printRational(&p[i]);
                first_term = 0;
            }
            // print x and exponent
            if (i > 2)
            {
                printf("x^%d", i / 2);
            }
            else if (i == 2)
            {
                printf("x");
            }
        }
    }
    // special case -- nothing printed because coefficients are all zero
    if (first_term)
    {
        printf("0");
    }
}

int strToPoly(const char *s, int p[])
{
    // each term is a sign operator (+ or -), possibly with spaces before and after,
    // followed by an optional rational, followed by an optional x or x^n
    // string ends with a linefeed -- if not present, return error
    // error codes:
    // 0 = success
    // 1 = string error
    // 2 = rational number error
    // 3 = term error
    int status = 0;
    int isNegative = 0;
    int isPositive = 0;
    int firstTerm = 1;
    int i;
    int coeff[2];
    char *next;
    // initialize all coefficients to 0
    for (i = 0; i <= 2 * MAX_DEGREE; i += 2)
    {
        p[i] = 0;
        p[i + 1] = 1;
    }
    // loop will start at the beginning of a polynomial term
    while (!status && *s && (*s != '\n'))
    {
        isPositive = isNegative = 0;
        // skip leading spaces and detect sign operator
        while (isspace(*s))
            ++s;
        if (*s == '-')
        {
            if (isNegative || isPositive)
            {
                status = 1;
                break;
            }
            isNegative = 1;
            ++s;
        }
        else if (*s == '+')
        {
            if (isPositive || isNegative)
            {
                status = 1;
                break;
            }
            isPositive = 1;
            ++s;
        }
        while (isspace(*s))
            ++s;

        // all terms except the first one must have a + or -
        if (!firstTerm && !isNegative && !isPositive)
        {
            status = 1;
            break;
        }
        firstTerm = 0;
        // read coefficient (if present)
        status = strToRational(s, &next, coeff);
        if (status)
        {
            // no number was read
            if (*s == 'x')
            {
                coeff[0] = 1; // missing number means coefficient is 1
                coeff[1] = 1;
                status = 0;
            }
            else
            {
                status = 2; // number error
                break;
            }
        }
        s = next;
        // if number was read and there's no x term, then last term is for exponent 0
        if (!*s || isspace(*s))
        {
            p[0] = isNegative ? -coeff[0] : coeff[0];
            p[1] = coeff[1];
            continue; // back to the top of the loop -- there may be more terms
        }
        // term must have an x
        if (*s != 'x')
        {
            status = 3; // term error
            break;
        }
        // the term may or may not have an exponent
        ++s;
        unsigned long exp = 1;
        if (*s == '^')
        {
            exp = strtoul(++s, &next, 10); // read the exponent
            if (exp > 10)
            {
                status = 3; // term error -- exponent out of range
                break;
            }
            s = next;
        }
        // store coefficient in the proper polynomial position
        p[2 * exp] = isNegative ? -coeff[0] : coeff[0];
        p[2 * exp + 1] = coeff[1];
    }
    return status;
}

// read polynomial from standard input
// for this program, input polynomial must always end with a linefeed
// max number of characters is 220
// max number of characters in a term is 20  (rational # plus variable plus coeff)
int readPoly(int p[])
{
    char buffer[221];
    int status = 0;
    // get polynomial string
    char *s = fgets(buffer, 221, stdin);
    if (!s)
        return 1; // reading error

    status = strToPoly(s, p);
    return status; // success!
}
