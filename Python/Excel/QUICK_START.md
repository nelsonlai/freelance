# Quick Start Guide - Python Excel Operations Course

Get up and running in 10 minutes!

## ⚡ 5-Step Quick Start

### Step 1: Install Python (if needed)
```bash
# Check Python version (need 3.8+)
python3 --version

# If not installed, download from python.org
```

### Step 2: Create Virtual Environment
```bash
# Navigate to course directory
cd /path/to/Excel

# Create virtual environment
python3 -m venv venv

# Activate it
# On macOS/Linux:
source venv/bin/activate

# On Windows:
venv\Scripts\activate
```

### Step 3: Install Dependencies
```bash
# Install all required packages
pip install -r requirements.txt

# Verify installation
python -c "import pandas; import openpyxl; print('✓ All libraries installed!')"
```

### Step 4: Generate Sample Data
```bash
# Create sample Excel files
cd sample_data
python create_sample_data.py
cd ..
```

### Step 5: Run Your First Script
```bash
# Navigate to Session 1
cd session_01_introduction

# Run the example script
python 01_setup_and_basics.py

# Success! You're ready to learn!
```

## 🎯 Next Steps

### For Self-Paced Learning
1. Read `session_01_introduction/README.md`
2. Study `01_setup_and_basics.md`
3. Run `01_setup_and_basics.py`
4. Open `01_setup_and_basics.ipynb` in Jupyter
5. Complete exercises in `exercises/`

### For Classroom Students
1. Attend Session 1 class
2. Follow along with demonstrations
3. Complete assigned exercises
4. Start homework projects

### For Instructors
1. Review `COURSE_OVERVIEW.md`
2. Customize materials for your class
3. Test all example scripts
4. Prepare your first lecture

## 🐛 Troubleshooting

### "Command not found: python3"
- Try `python` instead of `python3`
- Install Python from python.org

### "Permission denied" errors
- Use `sudo` on macOS/Linux (if needed)
- Run as Administrator on Windows

### Import errors
- Make sure virtual environment is activated
- Run `pip install -r requirements.txt` again

### "File not found" errors
- Check you're in the correct directory
- Use `pwd` (macOS/Linux) or `cd` (Windows) to verify

## 📚 Course Structure at a Glance

```
Module 1 (Foundations)
├── Session 1: Introduction & Setup
├── Session 2: Reading Excel Files
└── Session 3: Writing Excel Files

Module 2 (Data Operations)
├── Session 4: Data Manipulation
├── Session 5: Formatting & Styling
├── Session 6: Formulas & Charts (+ Mid-term)
└── Session 7: Merging Files

Module 3 (Advanced)
├── Session 8: Advanced Operations
├── Session 9: Large Files
├── Session 10: Automation
└── Session 11: Advanced Features

Module 4 (Capstone)
└── Session 12: Projects & Best Practices (+ Final)
```

## 💡 Learning Tips

1. **Practice regularly** - Code every day, even for 15 minutes
2. **Experiment** - Modify examples and see what happens
3. **Ask questions** - No question is too basic
4. **Build projects** - Apply concepts to real problems
5. **Help others** - Teaching reinforces learning

## 🎓 What You'll Build

By the end of this course, you'll have built:
- ✅ Data extraction and analysis tools
- ✅ Automated report generators
- ✅ Excel dashboards with charts
- ✅ File consolidation systems
- ✅ Production-ready automation tools
- ✅ Your own custom Excel projects

## 📞 Need Help?

- Check session README files
- Review markdown guides
- Run example scripts
- Try exercise solutions
- Ask in class/forums

## 🚀 Ready?

You're all set! Start with Session 1 and enjoy learning Python Excel operations!

```bash
cd session_01_introduction
cat README.md  # or open in your text editor
```

**Happy learning!** 🐍📊✨

