#Helper functions

def isPrime(n):
      
    # Corner case
    if n <= 1 :
        return False
  
    # check from 2 to n-1
    for i in range(2, n):
        if n % i == 0:
            return False
  
    return True
  
# Function to print primes
def constructPrimeList(n):
    primesList = []
    for i in range(2, n + 1):
        if isPrime(i):
            primesList.append(i)
    #print(f"Primes List to be tested are:\n{primesList}")
    return primesList




def gcd(a, h):
        while (1):
            temp = a % h
            if (temp == 0):
                return h
            a = h
            h = temp

def Calc_e(p, q):
    e = 2
    phi = (p - 1) * (q - 1)
    while (e < phi):
        if (gcd(e, phi) == 1):
            break
        else:
            e+=1

    return e

def modInverse(a, m):
 
    for x in range(1, m):
        if (((a % m) * (x % m)) % m == 1):
            return x
    return -1