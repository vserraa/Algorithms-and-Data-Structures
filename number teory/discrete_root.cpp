//solves equation of the form x^k = b mod m where m is a prime number
//since m is prime we know that at least one primitive root exists
//we need discrete_log function and a primitive root
//generator returns any primitive root
//if you need all solutions for this
//use the fact that x = g^(yo + i*phi(n)/gcd(k, phi(n))) for all integers i

int discrete_root(int k, int b, int mod){
	int pr = generator(mod);
	ll newbase = fexp(pr, k, mod);
	ll y = discrete_log(newbase, b, mod);
	return y == -1 ? -1 : fexp(pr, y, mod);
}