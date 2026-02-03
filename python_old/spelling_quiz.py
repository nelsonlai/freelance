import random

# List of simple words for Grade 4
word_bank = [
    # Fruits & Vegetables
    "apple", "banana", "grape", "orange", "lemon", "cherry", "carrot", "tomato", "potato", "lettuce",
    "onion", "cabbage", "peach", "plum", "pear", "kiwi", "mango", "strawberry", "blueberry", "pineapple",
    "broccoli", "pumpkin", "cucumber", "avocado", "watermelon",

    # Animals
    "monkey", "tiger", "lion", "zebra", "giraffe", "elephant", "bear", "fox", "rabbit", "panda",
    "puppy", "kitten", "mouse", "dolphin", "shark", "whale", "eagle", "parrot", "penguin", "owl",

    # School & Learning
    "pencil", "eraser", "notebook", "paper", "marker", "crayon", "chalk", "desk", "chair", "ruler",
    "board", "teacher", "student", "school", "lesson", "homework", "project", "backpack", "glue", "scissors",

    # Sports
    "soccer", "basketball", "tennis", "baseball", "volleyball", "golf", "ping-pong", "skateboard", "snowboard", "hockey",
    "boxing", "judo", "karate", "pilates", "yoga", "dancing", "gymnastics", "running", "swimming", "jumping",

    # Nature
    "mountain", "lake", "river", "ocean", "forest", "desert", "snow", "rain", "clouds", "sun",
    "moon", "star", "planet", "galaxy", "universe", "nature", "wildlife", "trees", "flowers", "birds",

    # Space
    "sun", "moon", "planet", "star", "galaxy", "universe", "space", "cosmos", "stars", "planets",
    "galaxies", "universes", "space", "cosmos", "stars", "planets", "galaxies", "universes", "space", "cosmos"
]

def hide_letters(word):
    # Hide 2 random letters with underscores
    word = list(word)
    indexes = random.sample(range(len(word)), 2)
    for i in indexes:
        word[i] = "_"
    return "".join(word)

def run_spelling_quiz():
    print("📚 Welcome to the Spelling Quiz Game!")
    score = 0

    for i in range(5):
        print(f"\nQuestion {i + 1}:")
        original_word = random.choice(word_bank)
        puzzle_word = hide_letters(original_word)
        print(f"Spell this word: {puzzle_word}")

        user_guess = input("Your answer: ").strip().lower()
        if user_guess == original_word:
            print("✅ Correct!")
            score += 1
        else:
            print(f"❌ Oops! The correct spelling is: {original_word}")

    print(f"\nYour final score: {score}/5")
    if score == 5:
        print("🏆 You are a spelling champion!")
    elif score >= 3:
        print("👍 Great effort! Keep practicing.")
    else:
        print("📘 Don't worry, spelling gets better with practice!")

def main():
    while True:
        run_spelling_quiz()
        again = input("\nDo you want to try another round? (yes/no): ").strip().lower()
        if again == 'no':
            print("👋 Thanks for playing! See you next time.")
            break
        elif again != 'yes':
            print("🤖 I didn’t understand that. Ending the game.")
            break

# Start the game
main()