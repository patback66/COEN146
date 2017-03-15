#Matthew Koken
#COEN146 Lab 6
import math

#determine if the number is a prime
def isPrime(num):
    #any number >2 and even is not prime. 0 and 1 are not primes
    if((num % 2 == 0 and num > 2) or (num == 0) or (num == 1)):
        return False
    #check the rest up until the sqrt(num) -> if any num%i fails, it isn't prime
    return all(num % i for i in range(2, int(math.sqrt(num)+1)))

done = False
p = input("Prime number p=")
#MAKE THE USER INPUT A PRIME
while(done != True):
    if(isPrime(p)):
        done = True
    else:
        p = input("That wasn't a prime! Prime number p=")

r = input("Primitive root(r) of p=")
a = input("Alice's private key=")
b = input("Bob's private key=")
x = (pow(r,a) % p) #alice's public key (x = r^a mod p)
y = (pow(r,b) % p) #bob's public key (y = r^b mod p)
print("Values exchanged")
ka = (pow(y,a) % p) #alice's shared private key (ka = y^a mod p)
kb = (pow(x,b) % p) #bob's sahred private key (kb = x^b mod p)
if (ka == kb): #the keys checked out! They are the same!
    print("ka = kb, and the shared secret is " + str(ka))
else:
    print("Oh no! The keys aren't symmetric!")
