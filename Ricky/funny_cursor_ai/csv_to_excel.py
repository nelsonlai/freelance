#!/usr/bin/env python3
"""
Read multiple CSV files from a directory and write them into a single Excel (.xlsx) file.
Each CSV file becomes one sheet in the workbook.
"""

import argparse
import re
import sys
from pathlib import Path

import pandas as pd

MAX_SHEET_NAME_LENGTH = 31
DEFAULT_OUTPUT = "output.xlsx"


def sanitize_sheet_name(name: str) -> str:
    """Excel sheet names: max 31 chars, no \\ / * ? [ ] :"""
    if name.lower().endswith(".csv"):
        name = name[:-4]
    name = re.sub(r'[\\/*?\[\]:]', "_", name)
    return name[:MAX_SHEET_NAME_LENGTH] if len(name) > MAX_SHEET_NAME_LENGTH else (name or "Sheet")


def list_csv_files(directory: Path) -> list[Path]:
    """Return sorted list of .csv paths in directory."""
    return sorted(directory.glob("*.csv"), key=lambda p: p.name.lower())


def csv_to_excel(input_dir: Path, output_path: Path) -> None:
    csv_files = list_csv_files(input_dir)
    if not csv_files:
        print(f"No CSV files found in: {input_dir}", file=sys.stderr)
        sys.exit(1)

    print(f"Found {len(csv_files)} CSV file(s). Writing to {output_path} ...")

    with pd.ExcelWriter(output_path, engine="openpyxl") as writer:
        for csv_path in csv_files:
            df = pd.read_csv(csv_path, encoding="utf-8")
            sheet_name = sanitize_sheet_name(csv_path.name)
            df.to_excel(writer, sheet_name=sheet_name, index=False)

    print(f"Done. Output: {output_path.resolve()}")


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Read multiple CSV files and integrate them into one Excel file."
    )
    parser.add_argument(
        "input_dir",
        nargs="?",
        default=".",
        help="Directory containing CSV files (default: current directory)",
    )
    parser.add_argument(
        "output",
        nargs="?",
        default=DEFAULT_OUTPUT,
        help=f"Output Excel file (default: {DEFAULT_OUTPUT})",
    )
    args = parser.parse_args()

    input_dir = Path(args.input_dir).resolve()
    if not input_dir.is_dir():
        print(f"Error: Input path is not a directory: {input_dir}", file=sys.stderr)
        sys.exit(1)

    csv_to_excel(input_dir, Path(args.output))


if __name__ == "__main__":
    main()
