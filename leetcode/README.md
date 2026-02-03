# LeetCode Problem Downloader

This Python script downloads all problems from LeetCode and generates:
- An Excel file (`leetcode_problems.xlsx`) containing problem metadata (ID, title, difficulty, category, etc.)
- Individual PDF files for each problem with detailed descriptions

## Installation

1. Make sure you have Python 3.7+ installed
2. Activate your virtual environment (if using one):
   ```bash
   source venv/bin/activate  # On macOS/Linux
   # or
   venv\Scripts\activate  # On Windows
   ```

3. Install required dependencies:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

Simply run the script:

```bash
python leetcode_downloader.py
```

The script will:
1. Fetch all problems from LeetCode using their GraphQL API
2. Create an Excel file with problem metadata in the `leetcode_problems/` directory
3. Create individual PDF files for each problem in the `leetcode_problems/pdfs/` directory

## Output Structure

```
leetcode_problems/
├── leetcode_problems.xlsx    # Excel file with all problem metadata
└── pdfs/
    ├── 1_Two_Sum.pdf
    ├── 2_Add_Two_Numbers.pdf
    └── ...
```

## Excel File Columns

- **Problem ID**: Frontend question ID
- **Title**: Problem title
- **Difficulty**: Easy, Medium, or Hard
- **Category/Tags**: Comma-separated list of topic tags
- **Acceptance Rate**: Percentage of accepted submissions
- **Paid Only**: Whether the problem requires a premium subscription

## PDF File Contents

Each PDF includes:
- Problem ID and title
- Difficulty level and acceptance rate
- Topic tags
- Problem description (if available)
- Code snippets in various languages (if available)

## Notes

- The script includes rate limiting to be respectful to LeetCode's servers
- Some problems may require authentication to access full details
- PDF generation may take some time for large numbers of problems
- The script handles errors gracefully and continues processing even if some problems fail

## Troubleshooting

If you encounter issues:
- Make sure you have a stable internet connection
- Check that all dependencies are installed correctly
- Some problems may fail to download due to API restrictions - this is normal
- The script will continue processing even if some individual problems fail

