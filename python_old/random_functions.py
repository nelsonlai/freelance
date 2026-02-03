import random

print("🎲 Welcome to the Random Fun Program!\n")

# 1. random(): returns a float number from 0.0 to 1.0
print("1. A random float from 0.0 to 1.0:", random.random())

# 2. randint(a, b): returns an integer from a to b (inclusive)
print("2. A random number between 1 and 10:", random.randint(1, 10))

# 3. uniform(a, b): returns a float between a and b
print("3. A random float between 5 and 10:", random.uniform(5, 10))

# 4. choice(list): returns a random item from a list
colours = ["red", "blue", "green", "yellow", "purple"]
print("4. A random favourite colour:", random.choice(colours))

# 5. choices(list, k=n): returns a list of n items (with replacement)
animals = ["cat", "dog", "rabbit", "hamster", "parrot"]
print("5. 3 random pets you could have:", random.choices(animals, k=3))

# 6. sample(list, n): returns n unique items (no replacement)
numbers = list(range(1, 21))  # 1 to 20
print("6. 5 unique lucky numbers:", random.sample(numbers, 5))

# 7. shuffle(list): shuffles the list in place
fruits = ["apple", "banana", "cherry", "grape", "orange"]
random.shuffle(fruits)
print("7. Shuffled fruit list:", fruits)

# 8. randrange(start, stop, step): like range() but random
print("8. Random number from 0 to 100 (step 5):", random.randrange(0, 101, 5))

# 9. randint(a, b): returns an integer from a to b (inclusive
print("9. A random number between 1 and 10:", random.randint(1, 10))


# Bonus Game: Silly Story Generator
characters = ["a dragon", "a wizard", "a princess", "a robot", "a monkey"]
places = ["in a castle", "on the moon", "under the sea", "in a jungle", "at school"]
actions = ["danced", "flew", "sang", "fought", "ate ice cream"]

print("\n🧚 Silly Story:")
print("Once upon a time,", random.choice(characters), random.choice(actions), random.choice(places) + ".")