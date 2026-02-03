import random

def generate_question():
    num1 = random.randint(1, 10)
    num2 = random.randint(1, 10)
    operator = random.choice(['+', '-', '*', '/', '**'])

    # Ensure no division by zero and integer division only
    if operator == '/':
        question = f"What is {num1} {operator} {num2}?"
        answer = num1 / num2
    elif operator == '**':
        question = f"What is {num1} {operator} {num2}?"
        answer = num1 ** num2
    elif operator == '+':
        question = f"What is {num1} {operator} {num2}?"
        answer = num1 + num2
    elif operator == '-':
        question = f"What is {num1} {operator} {num2}?"
        answer = num1 - num2
    else:  # '*'
        question = f"What is {num1} {operator} {num2}?"
        answer = num1 * num2

    return question, answer

def run_quiz():
    print("🎯 Welcome to the Math Quiz!")
    score = 0

    for i in range(5):  # Ask 5 questions i in 0, 1, 2, 3, 4
        print(f"\nQuestion {i + 1}:")   ## new line <==> \n
        question, correct_answer = generate_question()
        print(question)

        try:
            user_answer = int(input("Your answer: "))
            if user_answer == correct_answer:
                print("✅ Correct!")
                score += 1
            else:
                delta = user_answer - correct_answer
                print(f"❌ Wrong. The correct answer was {correct_answer}. Your answer was off by {delta}.")
        except ValueError:
            print("⚠️ Please enter a valid number.")

    print(f"\nYour score: {score}/5")

    # Feedback using if/elif/else
    if score == 5:
        print("🏆 Excellent work!")
    elif score >= 3:
        print("👍 Good job! Keep practicing!")
    else:
        print("📘 Try again and don't give up!")

def main():
    while True:
        run_quiz()
        play_again = input("\nDo you want to play again? (yes/no): ").strip().lower()

        if play_again == 'no':
            print("👋 Thanks for playing! Goodbye!")
            break
        elif play_again != 'yes':
            print("🤖 I didn't understand that. Exiting the quiz.")
            break

# Run the program
main()