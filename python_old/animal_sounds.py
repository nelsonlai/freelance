import random

# Dictionary of animals and their sounds
animal_sounds = {
    "dog": "bark",
    "cat": "meow",
    "cow": "moo",
    "duck": "quack",
    "horse": "neigh",
    "sheep": "baa",
    "pig": "oink",
    "chicken": "cluck",
    "lion": "roar",
    "frog": "ribbit"
}

print("Welcome to the Animal Sound Quiz!")
print("You will be asked to match the sound to the correct animal.")
print("Type your answer, and press Enter. Let's begin!\n")

score = 0
total_questions = 5
animal_names = list(animal_sounds.keys())
## Explain the range() function -> range(start, end, step)
for i in range(total_questions):
    print(f"Question {i+1}:")
    question_animal = random.choice(animal_names)
    correct_sound = animal_sounds[question_animal]

    # Generate multiple choices
    choices = [correct_sound]       #choices[0] = correct_sound
    while len(choices) < 4:
        fake = random.choice(list(animal_sounds.values()))
        if fake not in choices:
            choices.append(fake)
            
    random.shuffle(choices)

    print(f"What sound does a '{question_animal}' make?")
    for index, choice in enumerate(choices):
        print(f"{index + 1}. {choice}")

    while True:
        try:
            answer = int(input("Enter the number of the correct sound: "))
            if 1 <= answer <= 4:
                break
            else:
                print("Please choose between 1 and 4.")
        except ValueError:
            print("Invalid input. Please enter a number.")

    if choices[answer - 1] == correct_sound:
        print("✅ Correct!\n")
        score += 1
    else:
        print(f"❌ Oops! The correct answer was '{correct_sound}'.\n")

print(f"Your final score is: {score} out of {total_questions}")

if score == total_questions:
    print("🎉 Amazing! You're an animal sound expert!")
elif score >= total_questions // 2:
    print("👍 Great job! You know your animal sounds.")
else:
    print("🐾 Keep practicing! You'll get better.")

# Let them add their own!
add_new = input("\nDo you want to add your own animal and sound? (yes/no): ").strip().lower()
if add_new == "yes":
    new_animal = input("Enter an animal name: ").strip().lower()
    new_sound = input(f"What sound does a '{new_animal}' make? ").strip().lower()
    animal_sounds[new_animal] = new_sound
    print(f"Added: {new_animal} makes '{new_sound}'!")

# Show all
print("\nHere is the full list of animal sounds:")
for a, s in animal_sounds.items():
    print(f"- {a.capitalize()} makes '{s}'")

print("\nThanks for playing the Animal Sound Quiz! 🐶🐱🐮")