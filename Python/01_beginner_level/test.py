import random

def number_guessing_game(): # a simple number guessing game
    """A simple number guessing game."""
    
    secret_number = random.randint(1, 100)
    attempts = 0
    max_attempts = 7
    
    print("Welcome to the Number Guessing Game!")
    print("I'm thinking of a number between 1 and 100.")
    print(f"You have {max_attempts} attempts to guess it!")
    
    while attempts < max_attempts:
        try:
            guess = int(input(f"\nAttempt {attempts + 1}: Enter your guess: "))
            attempts += 1
            
            if guess == secret_number:
                print(f"Congratulations! You guessed it in {attempts} attempts!")
                break
            elif guess < secret_number:
                print("Too low! Try a higher number.")
            else:
                print("Too high! Try a lower number.")
                
        except ValueError:
            print("Please enter a valid number!")
            attempts -= 1  # Don't count invalid attempts
    
    if attempts >= max_attempts:
        print(f"Game over! The secret number was {secret_number}")

if __name__ == "__main__":
    number_guessing_game()