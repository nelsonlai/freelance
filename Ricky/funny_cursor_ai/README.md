# CSV to Excel

Read multiple CSV files from a directory and write them into a single Excel (`.xlsx`) file. **Each CSV file becomes one sheet** in the workbook.

Available in **Java** and **Python**.

---

## Python

### Requirements

- Python 3.10+
- pip

### Setup

```bash
pip install -r requirements.txt
```

### Run

```bash
# Use current directory as input, output to output.xlsx
python csv_to_excel.py
# or: python3 csv_to_excel.py

# Specify input directory and output file
python csv_to_excel.py /path/to/csv/folder result.xlsx

# Only input directory (output defaults to output.xlsx)
python csv_to_excel.py sample-data
```

Example with sample data:

```bash
python csv_to_excel.py sample-data my-report.xlsx
```

---

## Java

### Requirements

- Java 17 or later
- Maven 3.6+

## Build

```bash
mvn clean package
```

This produces:

- `target/csv-to-excel-1.0.0.jar` — normal JAR (requires classpath)
- `target/csv-to-excel-jar-with-dependencies.jar` — runnable JAR with all dependencies (use this to run)

## Run

**Using the runnable JAR (recommended):**

```bash
# Use current directory as input, output to output.xlsx
java -jar target/csv-to-excel-jar-with-dependencies.jar

# Specify input directory and output file
java -jar target/csv-to-excel-jar-with-dependencies.jar /path/to/csv/folder result.xlsx

# Only input directory (output defaults to output.xlsx)
java -jar target/csv-to-excel-jar-with-dependencies.jar /path/to/csv/folder
```

**Using Maven:**

```bash
mvn exec:java -Dexec.mainClass="com.csvtoexcel.CsvToExcel" -Dexec.args="/path/to/csv/folder result.xlsx"
```

(For `exec:java` you need the `exec-maven-plugin`; the JAR approach above is simpler.)

## Behavior

- **Input:** A directory containing one or more `.csv` files (by name, case-insensitive).
- **Output:** One `.xlsx` file. Sheet names are derived from CSV file names (extension removed, invalid characters replaced, length limited to 31 characters).
- **Encoding:** CSV files are read as UTF-8.
- **Header:** The first row of each CSV is treated as the header and is written as the first row of the corresponding sheet.

## Example

If `./data/` contains `sales.csv`, `inventory.csv`, and `users.csv`, then:

```bash
java -jar target/csv-to-excel-jar-with-dependencies.jar ./data report.xlsx
```

creates `report.xlsx` with three sheets: **sales**, **inventory**, and **users**.

A `sample-data/` folder with example CSVs is included for quick testing (use either Java or Python as above).
