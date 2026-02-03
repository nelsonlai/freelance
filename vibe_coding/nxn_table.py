def print_nxn_table(n):
    """
    Print an NxN multiplication table with proper formatting.
    """
    # Calculate the width needed for formatting
    max_value = n * n
    width = len(str(max_value)) + 1
    
    # Print header row
    print(f"{'':>{width}}", end="")
    for i in range(1, n + 1):
        print(f"{i:>{width}}", end="")
    print()
    
    # Print separator line
    print(f"{'':>{width}}", end="")
    print("-" * (width * n))
    
    # Print table rows
    for i in range(1, n + 1):
        # Print row header
        print(f"{i:>{width}}|", end="")
        
        # Print table values
        for j in range(1, n + 1):
            print(f"{i * j:>{width}}", end="")
        print()


def main():
    try:
        n = int(input("Enter the size of the NxN table: "))
        
        if n <= 0:
            print("Error: N must be a positive integer.")
            return
        
        print(f"\n{n}x{n} Multiplication Table:\n")
        print_nxn_table(n)
        
    except ValueError:
        print("Error: Please enter a valid integer.")


if __name__ == "__main__":
    main()

