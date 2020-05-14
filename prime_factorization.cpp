/*
***************************
*                         *
* Author: Swaraj Deep     *
*                         *
***************************
*/

#include <iostream>
#include <vector>
#include <array>
#define ll long long

using namespace std;

// In this function we check for each possible divisor
vector<pair<ll, ll>> trial_division(ll n)
{
    vector<pair<ll, ll>> factorization;
    for (ll d = 2; d * d <= n; ++d)
    {
        ll count = 0;
        while (n % d == 0)
        {
            n /= d;
            count++;
        }
        if (count)
        {
            factorization.push_back({d, count});
        }
    }
    if (n > 1)
    {
        factorization.push_back({n, 1});
    }
    return factorization;
}

// We first check 2 as a candidate so that we have to only consider 50% of the numbers (wheel factorization)
vector<pair<ll, ll>> trial_division_optimized(ll n)
{
    vector<pair<ll, ll>> factorization;
    int count = 0;
    while (n % 2 == 0)
    {
        count++;
        n /= 2;
    }
    if (count)
    {
        factorization.push_back({2, count});
    }
    for (ll d = 3; d * d <= n; d += 2)
    {
        count = 0;
        while (n % d == 0)
        {
            count++;
            n /= d;
        }
        if (count)
        {
            factorization.push_back({d, count});
        }
    }
    if (n > 1)
    {
        factorization.push_back({n, 1});
    }
    return factorization;
}

// The above approach can be extended i.e. if the number is not divisible by 3 then we ignore the multiples of 3 in the future computations. So we only need to check the numbers 5,7,11,13,17,19,23,…. We can observe a pattern of these remaining numbers. We need to check all numbers with d mod 6 = 1 and d mod 6 = 5. So this leaves us with only 33.3% percent of the numbers to check.
vector<pair<ll, ll>> trial_division_more_optimized(ll n)
{
    vector<pair<ll, ll>> factorization;
    int count = 0;
    for (int d : {2, 3, 5})
    {
        count = 0;
        while (n % d == 0)
        {
            count++;
            n /= d;
        }
        if (count)
        {
            factorization.push_back({d, count});
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for (ll d = 7; d * d <= n; d += increments[i++])
    {
        count = 0;
        while (n % d == 0)
        {
            count++;
            n /= d;
        }
        if (count)
        {
            factorization.push_back({d, count});
        }
        if (i == 8)
        {
            i = 0;
        }
    }
    if (n > 1)
    {
        factorization.push_back({n, 1});
    }
    return factorization;
}
// Extending the wheel factorization with more and more primes will leave exactly the primes to check. So a good way of checking is just to precompute all prime numbers with the Sieve of Eratosthenes until sqrt (n) and test them individually.
