print("🐾 Welcome to the Favourite Animals Program!")

# Step 1: Create a list
favourite_animals = ["dog", "cat", "rabbit"]

# Step 2: Show the list
print("\nYour current favourite animals are:")
for animal in favourite_animals:
    print("- " + animal)

# Step 3: Add a new animal
new_animal = input("\nWhat's another animal you like? ")
favourite_animals.append(new_animal)

# Step 4: Show updated list
print("\nUpdated list of your favourite animals:")
for animal in favourite_animals:
    print("- " + animal)

# Step 5: Ask if they want to remove one
remove_animal = input("\nIs there one animal you want to remove from the list? (type the name or 'no'): ").lower()

if remove_animal != "no":
    if remove_animal in favourite_animals:
        favourite_animals.remove(remove_animal)
        print(f"\n✅ Removed '{remove_animal}' from the list.")
    else:
        print(f"\n⚠️ Oops! '{remove_animal}' is not in your list.")

# Step 6: Final list
print("\n🎉 Here's your final list of favourite animals:")
for animal in favourite_animals:
    print("- " + animal)

print("\nThanks for using the program!")