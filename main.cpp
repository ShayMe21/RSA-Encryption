/*
A simple pogram that implements RSA Encryption.
User inputs values p,q,e and m. Validations are placed so enforce legitimate values.
The output will be the resulting ciphertext from the calculation using the inputs provided.
........
Tested data:
p=11, q=3, e=7, m=5, c=14
p=17, q=11, e=7, m=88, c=11
..........
Shayan Memari (18096125)
*/

#include <iostream>
#include <math.h>

using namespace std;

//returns true if the number is a prime.
bool isPrime(int number)
{
	if ( ( (!(number & 1)) && number != 2 ) || (number < 2) || (number % 3 == 0 && number != 3) )
		return (false);
	for( int k = 1; 36*k*k-12*k < number;++k)

		if ( (number % (6*k+1) == 0) || (number % (6*k-1) == 0) )

			return (false);
	return true;
}


int getP(){
    bool valid;
    int p;
    do
    {
        cout << "Enter p: ";
        cin >> p;
        if (isPrime(p) && p > 0){
            valid=true;
        }
        else{
            cout << "\nInvalid value. Input must be prime number.\n";
        }

    } while  (!valid);
    return p;
}

int getQ(){
    bool valid=false;
    int q;
    do
    {
        cout << "Enter q: ";
        cin >> q;
        if (isPrime(q)){
            valid=true;
        }
        else{
            cout << "\nInvalid value. Input must be prime number.\n";
        }

    } while  (!valid);
    return q;
}

//When gcd(a,b) is ==1. If relatively prime then Returns true.
bool isRelativelyPrime (int a, int b) { // Assumes a, b > 0
   return (a<b) ? isRelativelyPrime(b,a) : !(a%b) ? (b==1) : isRelativelyPrime (b, a%b);
}

int getE(int phi){
    bool valid=false;
    int e;
    do
    {
        cout << "Enter e: ";
        cin >> e;
        if (1<e && e<phi && isRelativelyPrime(e, phi) == true){
            valid=true;
        }
        else{
            cout << "\nInvalid value. Value must be between 1 and " << phi << " and relatively prime to " << phi << ".\n";
        }

    } while  (!valid);
    return e;
}

int getM(){
    bool valid=false;
    int m;
    do
    {
        cout << "Enter m: ";
        cin >> m;
        if (m >= 0){
            valid=true;
        }
        else{
            cout << "\nInvalid value.\n";
        }

    } while  (!valid);
    return m;
}

//Returns the function: C=M^e mod n
int mod(int base, int exp,  int mod)
{
    int x = 1;
    int i;
    int power = base % mod;

    for (i = 0; i < sizeof(int) * 8; i++) {
        int least_sig_bit = 0x00000001 & (exp >> i);
        if (least_sig_bit)
            x = (x * power) % mod;
        power = (power * power) % mod;
    }
    return x;
}


int main()
{
    int p = getP();
    int q = getQ();
    while (p == q){ //Enforce P and Q have to be different prime numbers.
        cout << "\nP and Q cannot be the same!\n";
        q = getQ();
    }
    int n = p * q;
    int phin = (p - 1) * (q - 1);
    int e = getE(phin);
    int m = getM();
    int c = mod(m, e, n);
    cout << "\nC = " << c;

    //To Keep the screen Open.
    int stop;
    cin >> stop;
}
