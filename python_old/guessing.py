import random

print("Welcome to the Guessing Game!")
print("Try to guess the number I am thinking of between 1 and 100.")

number = random.randint(1, 100)  # generate random number
guess = -1  # initialize guess to an invalid value

