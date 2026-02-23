# Introduction to Linux Bash and Shell Scripting

## What is Bash?

**Bash** (Bourne Again Shell) is the default command-line shell on most Linux distributions. It reads your commands, runs programs, supports variables, loops, conditionals, and can run scripts stored in files.

---

## Running Commands and Basic Syntax

### Simple commands

```bash
# Print working directory
pwd

# List files (current directory)
ls

# List with details (long format)
ls -la

# Change directory
cd /home/user
cd ..          # parent directory
cd ~           # home directory
cd -           # previous directory

# Create directory
mkdir mydir
mkdir -p a/b/c  # create parent directories as needed

# Remove empty directory
rmdir mydir

# Remove file (careful: no trash by default)
rm file.txt
rm -r mydir    # recursive (directories)
rm -rf mydir   # force, no prompts (use with caution)
```

### Redirecting input and output

```bash
# Redirect stdout to file (overwrite)
echo "hello" > output.txt

# Append to file
echo "world" >> output.txt

# Redirect stderr
command 2> errors.txt

# Redirect both stdout and stderr
command > output.txt 2>&1
# or in Bash:
command &> output.txt

# Read from file as stdin
command < input.txt

# Pipe: send stdout of one command to stdin of another
ls -l | grep ".txt"
cat file.txt | wc -l
```

---

## Variables

```bash
# Set variable (no spaces around =)
NAME="Alice"
COUNT=42

# Use variable: $NAME or ${NAME}
echo "Hello, $NAME"
echo "Count is ${COUNT}"

# Export so child processes see it
export NAME

# Read-only variable
readonly PI=3.14

# Special variables
echo $?      # exit code of last command (0 = success)
echo $0      # script name
echo $1 $2   # first, second argument
echo $#      # number of arguments
echo $@      # all arguments as list
echo $$      # current shell PID
```

---

## Quotes and Escaping

```bash
# Double quotes: variables and some escapes are expanded
echo "User is $USER and home is $HOME"

# Single quotes: everything literal, no expansion
echo 'Cost is $100'

# Escaping with backslash
echo "She said \"Hello\""
echo line1\
line2   # line continuation
```

---

## Conditionals

### if / then / else

```bash
# Basic if
if [ -f file.txt ]; then
    echo "file.txt exists"
fi

# if-else
if [ -d mydir ]; then
    echo "mydir is a directory"
else
    echo "mydir is not a directory"
fi

# if-elif-else
if [ $COUNT -gt 10 ]; then
    echo "Big"
elif [ $COUNT -gt 0 ]; then
    echo "Small"
else
    echo "Zero or negative"
fi
```

### Test conditions (used inside `[ ]`)

```bash
# File tests
[ -f file ]   # exists and is regular file
[ -d dir ]    # exists and is directory
[ -e path ]   # exists
[ -r file ]   # readable
[ -w file ]   # writable
[ -x file ]   # executable
[ -s file ]   # size > 0

# String tests
[ -z "$VAR" ]   # length is zero
[ -n "$VAR" ]   # length is non-zero
[ "$A" = "$B" ] # equal
[ "$A" != "$B" ]# not equal

# Numeric tests (use -eq, -ne, -lt, -le, -gt, -ge)
[ $a -eq $b ]
[ $a -lt 10 ]
```

### case statement

```bash
case "$1" in
    start)
        echo "Starting..."
        ;;
    stop)
        echo "Stopping..."
        ;;
    restart)
        echo "Restarting..."
        ;;
    *)
        echo "Usage: $0 {start|stop|restart}"
        exit 1
        ;;
esac
```

---

## Loops

### for loop

```bash
# Loop over list
for i in apple banana cherry; do
    echo "Fruit: $i"
done

# Loop over range (Bash)
for i in {1..5}; do
    echo "Number: $i"
done

# C-style for (Bash)
for ((i=0; i<5; i++)); do
    echo "i=$i"
done

# Loop over command output
for f in *.txt; do
    echo "Processing: $f"
done
```

### while loop

```bash
# While condition is true
count=0
while [ $count -lt 5 ]; do
    echo "Count: $count"
    count=$((count + 1))
done

# Read file line by line
while IFS= read -r line; do
    echo "Line: $line"
done < file.txt

# Infinite loop (break with Ctrl+C or break)
while true; do
    echo "Running..."
    sleep 1
done
```

### until loop

```bash
# Run until condition becomes true
count=0
until [ $count -ge 5 ]; do
    echo $count
    count=$((count + 1))
done
```

---

## Functions

```bash
# Define function
greet() {
    echo "Hello, $1"
}
greet "World"

# Function with return (exit code only; use echo for value)
myfunc() {
    local x=10
    echo $x
}
result=$(myfunc)
echo "Result: $result"

# Return exit code
check_file() {
    if [ -f "$1" ]; then
        return 0
    else
        return 1
    fi
}
if check_file "config.txt"; then
    echo "Config exists"
fi
```

---

## Arrays (Bash)

```bash
# Create array
fruits=(apple banana cherry)

# Access by index (0-based)
echo ${fruits[0]}    # apple
echo ${fruits[@]}    # all elements
echo ${#fruits[@]}   # length

# Loop over array
for f in "${fruits[@]}"; do
    echo "$f"
done

# Add element
fruits+=(date)
```

---

## Command Substitution

```bash
# Capture output in variable: $(command) or `command`
DATE=$(date)
echo "Today: $DATE"

FILES=$(ls *.txt)
LINE_COUNT=$(wc -l < file.txt)

# Use in place
echo "There are $(ls | wc -l) items here"
```

---

## Reading User Input

```bash
# Read into variable
read -p "Enter your name: " name
echo "Hello, $name"

# Read multiple values
read -p "Enter first and last: " first last

# Read silently (e.g. password)
read -s -p "Password: " pass
echo
```

---

## Exit Codes and set Options

```bash
# Exit script with code (0 = success)
exit 0
exit 1

# Useful set options (often at top of script)
set -e   # exit on first command failure
set -u   # error on undefined variable
set -o pipefail  # fail pipeline if any command fails

# Example script start
#!/bin/bash
set -euo pipefail
```

---

## Practical Script Examples

### Backup script

```bash
#!/bin/bash
BACKUP_DIR="/backup"
DATE=$(date +%Y%m%d)
tar -czf "$BACKUP_DIR/backup-$DATE.tar.gz" /home/user/docs
echo "Backup done: backup-$DATE.tar.gz"
```

### Find and process files

```bash
#!/bin/bash
for f in /var/log/*.log; do
    if [ -f "$f" ]; then
        echo "--- $f ---"
        tail -n 5 "$f"
    fi
done
```

### Simple menu

```bash
#!/bin/bash
echo "1) Option A"
echo "2) Option B"
echo "3) Quit"
read -p "Choice: " choice
case $choice in
    1) echo "You chose A" ;;
    2) echo "You chose B" ;;
    3) exit 0 ;;
    *) echo "Invalid" ; exit 1 ;;
esac
```

### Check if service is running

```bash
#!/bin/bash
if systemctl is-active --quiet nginx; then
    echo "nginx is running"
else
    echo "nginx is not running"
fi
```

### Loop with timeout

```bash
#!/bin/bash
count=0
max=10
until curl -s -o /dev/null -w "%{http_code}" http://localhost:8080 | grep -q 200; do
    count=$((count + 1))
    if [ $count -ge $max ]; then
        echo "Timeout waiting for server"
        exit 1
    fi
    sleep 2
done
echo "Server is up"
```

### Log rotation simulation

```bash
#!/bin/bash
LOG_DIR="/var/log/myapp"
MAX_FILES=5
cd "$LOG_DIR" || exit 1
ls -t *.log 2>/dev/null | tail -n +$((MAX_FILES + 1)) | xargs -r rm --
echo "Old logs cleaned"
```

### Parse CSV (simple)

```bash
#!/bin/bash
while IFS=',' read -r col1 col2 col3; do
    echo "Column1: $col1, Column2: $col2, Column3: $col3"
done < data.csv
```

### Safe script with usage

```bash
#!/bin/bash
set -euo pipefail

usage() {
    echo "Usage: $0 <input_file> <output_file>"
    exit 1
}

[ $# -eq 2 ] || usage
INPUT="$1"
OUTPUT="$2"
[ -f "$INPUT" ] || { echo "Input file not found: $INPUT"; exit 1; }

# ... do work ...
echo "Done."
```

---

## Running Scripts

```bash
# Make executable once
chmod +x myscript.sh

# Run (from current directory)
./myscript.sh

# Run with bash explicitly (no execute bit needed)
bash myscript.sh

# Pass arguments
./myscript.sh arg1 arg2
```

---

## Next Steps

- Use these patterns in daily tasks and small automations.
- Explore **Ubuntu network tools** from the shell: [03-ubuntu-network-tools.md](03-ubuntu-network-tools.md).
