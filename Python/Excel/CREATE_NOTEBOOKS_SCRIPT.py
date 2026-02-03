"""
Script to Convert Python Scripts to Jupyter Notebooks
====================================================

This script creates Jupyter notebooks from the existing Python scripts
for sessions 3-12.
"""

import json
from pathlib import Path

def create_notebook_from_script(script_path, notebook_path, session_number, session_title):
    """
    Create a Jupyter notebook from a Python script
    """
    # Read the Python script
    with open(script_path, 'r', encoding='utf-8') as f:
        script_content = f.read()
    
    # Create notebook structure
    notebook = {
        "cells": [],
        "metadata": {
            "kernelspec": {
                "display_name": "Python 3",
                "language": "python",
                "name": "python3"
            },
            "language_info": {
                "codemirror_mode": {
                    "name": "ipython",
                    "version": 3
                },
                "file_extension": ".py",
                "mimetype": "text/x-python",
                "name": "python",
                "nbconvert_exporter": "python",
                "pygments_lexer": "ipython3",
                "version": "3.8.0"
            }
        },
        "nbformat": 4,
        "nbformat_minor": 4
    }
    
    # Add title cell
    title_cell = {
        "cell_type": "markdown",
        "metadata": {},
        "source": [
            f"# Session {session_number}: {session_title}\n",
            "\n",
            "Welcome to this interactive session! This notebook contains all the examples from the Python script.\n",
            "\n",
            "## 📋 How to Use This Notebook\n",
            "\n",
            "1. Run cells sequentially using Shift+Enter\n",
            "2. Modify the code and experiment\n",
            "3. Check the output after each cell\n",
            "4. Refer to the markdown guide for detailed explanations\n",
            "\n",
            "## 🚀 Let's Begin!\n"
        ]
    }
    notebook["cells"].append(title_cell)
    
    # Split script into sections based on comment blocks
    sections = script_content.split('# ' + '='*78)
    
    for i, section in enumerate(sections):
        if section.strip():
            lines = section.strip().split('\n')
            
            # Check if this is a section header
            if lines and not lines[0].startswith('#'):
                # This is code - create a code cell
                code_cell = {
                    "cell_type": "code",
                    "execution_count": None,
                    "metadata": {},
                    "outputs": [],
                    "source": [line + '\n' for line in lines]
                }
                notebook["cells"].append(code_cell)
            else:
                # Extract section title if present
                section_title = None
                code_start = 0
                
                for j, line in enumerate(lines):
                    if line.strip() and not line.startswith('#'):
                        code_start = j
                        break
                    if '.' in line and line.strip().startswith('#'):
                        section_title = line.strip('# ').strip()
                
                # Add markdown cell for section title
                if section_title:
                    md_cell = {
                        "cell_type": "markdown",
                        "metadata": {},
                        "source": [f"## {section_title}\n"]
                    }
                    notebook["cells"].append(md_cell)
                
                # Add code cell for the code
                if code_start < len(lines):
                    code_lines = lines[code_start:]
                    if any(line.strip() and not line.startswith('#') for line in code_lines):
                        code_cell = {
                            "cell_type": "code",
                            "execution_count": None,
                            "metadata": {},
                            "outputs": [],
                            "source": [line + '\n' for line in code_lines if line.strip()]
                        }
                        notebook["cells"].append(code_cell)
    
    # Write notebook
    with open(notebook_path, 'w', encoding='utf-8') as f:
        json.dump(notebook, f, indent=2, ensure_ascii=False)
    
    print(f"✓ Created: {notebook_path.name}")

def main():
    """
    Create all notebooks
    """
    base_path = Path(__file__).parent
    
    sessions = [
        (3, "Writing Excel Files", "session_03_writing", "03_writing_excel"),
        (4, "Data Manipulation", "session_04_data_manipulation", "04_data_manipulation"),
        (5, "Formatting and Styling", "session_05_formatting", "05_formatting"),
        (6, "Formulas and Charts", "session_06_formulas_charts", "06_formulas_charts"),
        (7, "Merging and Combining", "session_07_merging", "07_merging"),
        (8, "Advanced Operations", "session_08_advanced_operations", "08_advanced_operations"),
        (9, "Working with Large Files", "session_09_large_files", "09_large_files"),
        (10, "Automation and Batch Processing", "session_10_automation", "10_automation"),
        (11, "Advanced Excel Features", "session_11_advanced_features", "11_advanced_features"),
        (12, "Real-World Projects", "session_12_projects", "12_real_world_projects"),
    ]
    
    print("Creating Jupyter Notebooks from Python Scripts")
    print("=" * 60)
    
    for session_num, title, folder, filename in sessions:
        script_path = base_path / folder / f"{filename}.py"
        notebook_path = base_path / folder / f"{filename}.ipynb"
        
        if script_path.exists():
            try:
                create_notebook_from_script(script_path, notebook_path, session_num, title)
            except Exception as e:
                print(f"✗ Error creating notebook for Session {session_num}: {e}")
        else:
            print(f"⚠ Script not found: {script_path}")
    
    print("\n" + "=" * 60)
    print("✓ Notebook creation complete!")
    print("\nAll sessions now have Jupyter notebooks!")
    print("Run: jupyter notebook to start exploring")

if __name__ == '__main__':
    main()

