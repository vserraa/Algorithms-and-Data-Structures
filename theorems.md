## How to compute modular inverse of x mod n when n is not prime
. Let a * x + b * n = 1

. a is modular inverse of x mod n

. You can compute a using extended euclides algorithm

## How to solve a.x = b mod n

. p = gcd(a, n)

. Equation only has solution if p | b

. Let a' = a/p, b' = b/p, n' = n/p

. x = (1/a') * b' mod n'