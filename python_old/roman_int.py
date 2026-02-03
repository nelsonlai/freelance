

def romanToInt(s: str) -> int:
    # Step 1: Define a dictionary to map Roman numerals to integers
    roman_map = {
        'I': 1,
        'V': 5,
        'X': 10,
        'L': 50,
        'C': 100,
        'D': 500,
        'M': 1000
    }

    total = 0         # This will store the final result
    prev_value = 0    # Used to track the last numeral's value

    # Step 2: Loop through the string from right to left
    for char in reversed(s):
        value = roman_map[char]  # Get the integer value of the Roman numeral

        # Step 3: If current value is less than previous, we subtract (e.g., IV = 5 - 1)
        if value < prev_value:
            total -= value
        else:
            # Otherwise, we add the value
            total += value
            prev_value = value  # Update previous value

    return total  # Return the computed integer
        
def intToRoman(num: int) -> str:
    # Step 1: Create a list of tuples (value, symbol), sorted from largest to smallest
    val_to_roman = [
        (1000, 'M'),
        (900,  'CM'),
        (500,  'D'),
        (400,  'CD'),
        (100,  'C'),
        (90,   'XC'),
        (50,   'L'),
        (40,   'XL'),
        (10,   'X'),
        (9,    'IX'),
        (5,    'V'),
        (4,    'IV'),
        (1,    'I')
    ]

    result = ""

    # Step 2: Loop through each value-symbol pair
    for value, symbol in val_to_roman:
        if num == 0:
            break

        # Step 3: Find how many times the current value fits into num
        count = num // value
        if count > 0:
            result += symbol * count  # Append the symbol count times
            num -= value * count      # Subtract the value from num

    return result

if __name__ == '__main__':
    print(intToRoman(1943))

    