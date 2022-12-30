#define ll long long int
#define baselength 12
#define mybase 1000000000000 /* mybase = 10^baselength */
#define N 2               /* digits before decimal = baselength * N */
#define M 100000         /* number of digits after decimal = baselength * M */

#include <iostream>
#include <math.h>
ll *createNum()
{
    return (ll *)calloc(N + M, sizeof(ll));
}
void divide(ll *num, ll x)
{
    ll remainder = 0;
    for (int i = 0; i < N + M; i++)
    {
        ll temp = (remainder * mybase + num[i]);
        num[i] = temp / x;
        remainder = temp % x;
    }
}
void print_helper(ll number)
{
    // this function prints the digits properly . say the digit is 123 then we print 00000123
    int arr[baselength];
    for (int i = baselength - 1; i >= 0; i--)
    {
        arr[i] = number % 10;
        number /= 10;
    }
    for (int i = 0; i < baselength; i++)
        std::cout << arr[i];
}
void print(ll *num)
{
    int i = 0;
    while (num[i] == 0 && i < N - 1)
    {
        i++;
    }
    while (i < N)
    {
        std::cout << " ";
        print_helper(num[i]);
        i++;
    }
    int t = N + M;
    while (!num[t - 1] && t >= N)
        t--;

    // if t == M there is no need to print the decimal point
    if (t != M)
    {
        std::cout << ".";
        while (i < t)
        {
            print_helper(num[i]);

            std::cout << ' ';
            i++;
        }
    }
    std::cout << std::endl;
}
void add(ll *num1, ll *num2)
{
    ll carry = 0;
    ll temp;
    for (int i = N + M - 1; i >= 0; i--)
    {
        temp = num1[i] + num2[i] + carry;
        num1[i] = temp % mybase;
        carry = temp >= mybase;
    }
}
void subtract(ll *num1, ll *num2)
{
    ll carry = 0;
    ll temp;
    for (int i = N + M - 1; i >= 0; i--)
    {
        temp = num1[i] - num2[i] - carry;
        num1[i] = (temp + mybase) % mybase;
        carry = temp < 0;
    }
}
ll *divide2(ll *num, ll x)
{
    ll *newNum = createNum();
    ll remainder = 0;
    ll temp;
    for (int i = 0; i < N + M; i++)
    {
        temp = (remainder * mybase + num[i]);
        newNum[i] = temp / x;
        remainder = temp % x;
    }
    return newNum;
}
void multiply(ll *num, ll x)
{
    ll carry = 0;
    ll temp;
    for (int i = N + M - 1; i >= 0; i--)
    {
        temp = num[i] * x + carry;
        num[i] = temp % mybase;
        carry = temp / mybase;
    }
}
ll *arctanofrec(ll x)
{
    ll xx = x * x;
    ll *ans = createNum();
    ll *term = createNum();
    term[N - 1] = 1;
    divide(term, x);
    ll maxloops = ((int)(((double)(N + M)) / log10(xx))) + 1;
    
    for (int i = 0; i < maxloops; i++)
    {
        ll *temp_res = divide2(term, 2 * i + 1);
        if (i % 2 == 0)
        {
            add(ans, temp_res);
        }
        else
        {
            subtract(ans, temp_res);
        }
        free(temp_res);
        divide(term, xx);
    }
    free(term);
    return ans;
}
int main()
{
    clock_t tStart = clock();
    ll *pi = createNum();
    ll *number1 = arctanofrec(5);
    ll *number2 = arctanofrec(239);
    multiply(number2, 4);
    multiply(number1, 16);
    add(pi, number1);
    subtract(pi, number2);
    free(number1);
    free(number2);
    //print(pi);
    printf("Time taken : %.6fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
    std::cout << "Digits Calculated : " << baselength * M << std::endl;

    return 0;
}
