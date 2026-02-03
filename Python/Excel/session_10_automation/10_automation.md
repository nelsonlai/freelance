# Session 10: Automation and Batch Processing - Comprehensive Guide

## Introduction

Automation transforms manual, repetitive Excel tasks into efficient, error-free workflows. This session teaches you how to process multiple files in batches, create automated workflows, schedule report generation, and build robust automation scripts.

## Why Automate Excel Operations?

**Benefits:**
- Save hours/days of manual work
- Eliminate human errors
- Consistent, repeatable processes
- Scale to hundreds/thousands of files
- Free staff for higher-value work

**Common Use Cases:**
- Daily/weekly report generation
- Consolidating branch/region files
- Data validation and cleaning
- Format standardization
- Backup and archiving

## Part 1: Batch File Processing

### Process All Files in Directory

```python
import pandas as pd
from pathlib import Path

def process_all_excel_files(directory):
    """
    Process all Excel files in a directory
    """
    # Find all Excel files
    excel_files = Path(directory).glob('*.xlsx')
    
    results = []
    for file in excel_files:
        print(f"Processing: {file.name}")
        
        try:
            df = pd.read_excel(file)
            
            # Your processing logic
            total = df['Value'].sum()
            count = len(df)
            
            results.append({
                'File': file.name,
                'Rows': count,
                'Total': total,
                'Status': 'Success'
            })
            
        except Exception as e:
            print(f"  Error: {e}")
            results.append({
                'File': file.name,
                'Status': f'Error: {e}'
            })
    
    # Create summary report
    df_summary = pd.DataFrame(results)
    df_summary.to_excel('processing_summary.xlsx', index=False)
    
    return df_summary

# Usage
summary = process_all_excel_files('data_folder/')
print(summary)
```

### Pattern-Based Processing

```python
from pathlib import Path
import pandas as pd

def process_files_by_pattern(directory, pattern='sales_*.xlsx'):
    """
    Process files matching a specific pattern
    """
    files = sorted(Path(directory).glob(pattern))
    
    print(f"Found {len(files)} files matching '{pattern}'")
    
    all_data = []
    for file in files:
        df = pd.read_excel(file)
        df['Source_File'] = file.name
        all_data.append(df)
        print(f"  ✓ {file.name}: {len(df)} rows")
    
    # Combine all
    if all_data:
        df_combined = pd.concat(all_data, ignore_index=True)
        output_file = f'combined_{pattern.replace("*", "all")}'
        df_combined.to_excel(output_file, index=False)
        print(f"\n✓ Saved combined file: {output_file}")
        return df_combined
    
    return None

# Usage
df = process_files_by_pattern('monthly_reports/', 'sales_2024_*.xlsx')
```

### Recursive Directory Processing

```python
from pathlib import Path
import pandas as pd

def process_directory_recursive(root_directory):
    """
    Process all Excel files in directory tree
    """
    results = []
    
    # Walk through all subdirectories
    for file_path in Path(root_directory).rglob('*.xlsx'):
        # Skip temporary Excel files
        if file_path.name.startswith('~$'):
            continue
        
        relative_path = file_path.relative_to(root_directory)
        print(f"Processing: {relative_path}")
        
        try:
            df = pd.read_excel(file_path)
            
            results.append({
                'File': file_path.name,
                'Path': str(relative_path.parent),
                'Rows': len(df),
                'Columns': len(df.columns),
                'Size_KB': file_path.stat().st_size / 1024
            })
            
        except Exception as e:
            print(f"  Error: {e}")
    
    # Save inventory
    df_inventory = pd.DataFrame(results)
    df_inventory.to_excel('file_inventory.xlsx', index=False)
    
    return df_inventory

# Usage
inventory = process_directory_recursive('company_data/')
```

## Part 2: Automated Workflows

### Daily Report Generator

```python
import pandas as pd
from datetime import datetime
from pathlib import Path

def generate_daily_report(data_source, output_dir='reports'):
    """
    Automated daily report generation
    """
    # Create output directory
    Path(output_dir).mkdir(exist_ok=True)
    
    # Generate timestamp
    timestamp = datetime.now().strftime('%Y-%m-%d')
    
    print(f"Generating daily report for {timestamp}")
    
    # Read data
    df = pd.read_excel(data_source)
    
    # Today's data
    df['Date'] = pd.to_datetime(df['Date'])
    today = datetime.now().date()
    df_today = df[df['Date'].dt.date == today]
    
    # Calculate metrics
    metrics = {
        'Total_Sales': df_today['Sales'].sum(),
        'Total_Orders': len(df_today),
        'Average_Order': df_today['Sales'].mean(),
        'Top_Product': df_today.groupby('Product')['Sales'].sum().idxmax()
    }
    
    # Create report
    report_file = Path(output_dir) / f'daily_report_{timestamp}.xlsx'
    
    with pd.ExcelWriter(report_file) as writer:
        # Raw data
        df_today.to_excel(writer, sheet_name='Today_Data', index=False)
        
        # Metrics
        df_metrics = pd.DataFrame([metrics])
        df_metrics.to_excel(writer, sheet_name='Metrics', index=False)
        
        # Summary by product
        product_summary = df_today.groupby('Product').agg({
            'Sales': 'sum',
            'Quantity': 'sum'
        }).reset_index()
        product_summary.to_excel(writer, sheet_name='By_Product', index=False)
    
    print(f"✓ Report saved: {report_file}")
    
    return report_file

# Usage
report = generate_daily_report('sales_database.xlsx')
```

### Weekly Consolidation Workflow

```python
import pandas as pd
from datetime import datetime, timedelta
from pathlib import Path

def weekly_consolidation_workflow(input_dir, output_dir='weekly_reports'):
    """
    Consolidate daily files into weekly report
    """
    Path(output_dir).mkdir(exist_ok=True)
    
    # Calculate date range
    today = datetime.now()
    week_start = today - timedelta(days=today.weekday())
    week_number = week_start.isocalendar()[1]
    
    print(f"Processing Week {week_number} ({week_start.date()})")
    
    # Find this week's files
    daily_files = []
    for i in range(7):
        date = week_start + timedelta(days=i)
        date_str = date.strftime('%Y-%m-%d')
        file_path = Path(input_dir) / f'daily_{date_str}.xlsx'
        
        if file_path.exists():
            daily_files.append(file_path)
            print(f"  Found: {file_path.name}")
    
    if not daily_files:
        print("No files found for this week")
        return None
    
    # Read and combine
    all_data = []
    for file in daily_files:
        df = pd.read_excel(file)
        df['Source_Date'] = pd.to_datetime(file.stem.split('_')[1])
        all_data.append(df)
    
    df_week = pd.concat(all_data, ignore_index=True)
    
    # Weekly analysis
    weekly_metrics = {
        'Week_Number': week_number,
        'Start_Date': week_start.date(),
        'Total_Sales': df_week['Sales'].sum(),
        'Total_Orders': len(df_week),
        'Average_Daily_Sales': df_week.groupby('Source_Date')['Sales'].sum().mean(),
        'Best_Day': df_week.groupby('Source_Date')['Sales'].sum().idxmax()
    }
    
    # Save weekly report
    output_file = Path(output_dir) / f'week_{week_number}_{week_start.year}.xlsx'
    
    with pd.ExcelWriter(output_file) as writer:
        df_week.to_excel(writer, sheet_name='All_Data', index=False)
        
        df_metrics = pd.DataFrame([weekly_metrics])
        df_metrics.to_excel(writer, sheet_name='Weekly_Metrics', index=False)
        
        # Daily breakdown
        daily_summary = df_week.groupby('Source_Date').agg({
            'Sales': 'sum',
            'Order_ID': 'count'
        }).reset_index()
        daily_summary.to_excel(writer, sheet_name='Daily_Breakdown', index=False)
    
    print(f"✓ Weekly report saved: {output_file}")
    
    return output_file

# Usage
weekly_consolidation_workflow('daily_reports/')
```

## Part 3: Scheduling Automation

### Using Schedule Library

```python
import schedule
import time
from datetime import datetime

def daily_job():
    """Job to run daily"""
    print(f"Running daily job at {datetime.now()}")
    # Your daily report logic here
    generate_daily_report('data.xlsx')

def weekly_job():
    """Job to run weekly"""
    print(f"Running weekly job at {datetime.now()}")
    # Your weekly consolidation logic here
    weekly_consolidation_workflow('daily_reports/')

# Schedule jobs
schedule.every().day.at("09:00").do(daily_job)
schedule.every().monday.at("10:00").do(weekly_job)

# Keep running
print("Scheduler started. Press Ctrl+C to exit.")
while True:
    schedule.run_pending()
    time.sleep(60)  # Check every minute
```

### Using Cron (Linux/Mac)

```bash
# Edit crontab
crontab -e

# Add entries:
# Daily at 9 AM
0 9 * * * cd /path/to/project && python daily_report.py

# Weekly on Monday at 10 AM
0 10 * * 1 cd /path/to/project && python weekly_report.py

# First day of month at 8 AM
0 8 1 * * cd /path/to/project && python monthly_report.py
```

### Using Windows Task Scheduler

```python
# Create a batch file: run_daily_report.bat
"""
@echo off
cd C:\path\to\project
python daily_report.py
pause
"""

# Then schedule in Windows Task Scheduler:
# 1. Open Task Scheduler
# 2. Create Basic Task
# 3. Set trigger (daily, weekly, etc.)
# 4. Action: Start a program
# 5. Program: C:\path\to\run_daily_report.bat
```

## Part 4: Error Handling and Logging

### Robust Batch Processor

```python
import pandas as pd
from pathlib import Path
import logging
from datetime import datetime

# Setup logging
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler(f'automation_{datetime.now().strftime("%Y%m%d")}.log'),
        logging.StreamHandler()
    ]
)
logger = logging.getLogger(__name__)

def robust_batch_processor(input_dir, output_file):
    """
    Batch processor with comprehensive error handling and logging
    """
    logger.info(f"Starting batch processing from {input_dir}")
    
    files = list(Path(input_dir).glob('*.xlsx'))
    logger.info(f"Found {len(files)} files to process")
    
    results = []
    successful = 0
    failed = 0
    
    for file in files:
        try:
            logger.info(f"Processing: {file.name}")
            
            # Validate file
            if file.stat().st_size == 0:
                raise ValueError("File is empty")
            
            # Process
            df = pd.read_excel(file)
            
            if df.empty:
                raise ValueError("DataFrame is empty")
            
            # Your processing logic
            summary = {
                'File': file.name,
                'Rows': len(df),
                'Columns': len(df.columns),
                'Status': 'Success',
                'Processed_At': datetime.now()
            }
            
            results.append(summary)
            successful += 1
            logger.info(f"  ✓ Successfully processed: {len(df)} rows")
            
        except Exception as e:
            logger.error(f"  ✗ Error processing {file.name}: {e}")
            results.append({
                'File': file.name,
                'Status': 'Failed',
                'Error': str(e),
                'Processed_At': datetime.now()
            })
            failed += 1
    
    # Save results
    df_results = pd.DataFrame(results)
    df_results.to_excel(output_file, index=False)
    
    logger.info(f"Processing complete: {successful} successful, {failed} failed")
    logger.info(f"Results saved to: {output_file}")
    
    return df_results

# Usage
results = robust_batch_processor('data/', 'processing_results.xlsx')
```

## Part 5: Command-Line Interface

### Using argparse

```python
import argparse
import pandas as pd
from pathlib import Path

def main():
    # Create parser
    parser = argparse.ArgumentParser(
        description='Batch process Excel files'
    )
    
    # Add arguments
    parser.add_argument(
        'input_dir',
        help='Input directory containing Excel files'
    )
    parser.add_argument(
        '-o', '--output',
        default='combined.xlsx',
        help='Output file name (default: combined.xlsx)'
    )
    parser.add_argument(
        '-p', '--pattern',
        default='*.xlsx',
        help='File pattern to match (default: *.xlsx)'
    )
    parser.add_argument(
        '--chunk-size',
        type=int,
        default=10000,
        help='Chunk size for large files'
    )
    
    # Parse arguments
    args = parser.parse_args()
    
    # Process files
    files = list(Path(args.input_dir).glob(args.pattern))
    print(f"Found {len(files)} files")
    
    all_data = []
    for file in files:
        df = pd.read_excel(file)
        all_data.append(df)
    
    if all_data:
        df_combined = pd.concat(all_data, ignore_index=True)
        df_combined.to_excel(args.output, index=False)
        print(f"✓ Saved: {args.output}")

if __name__ == '__main__':
    main()

# Usage:
# python script.py data_folder/
# python script.py data_folder/ -o output.xlsx
# python script.py data_folder/ -p "sales_*.xlsx"
```

## Part 6: Email Notifications

### Send Email with Report

```python
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders

def send_report_email(report_file, recipient, subject='Daily Report'):
    """
    Send email with Excel report attached
    """
    # Email configuration
    sender = 'your_email@gmail.com'
    password = 'your_app_password'  # Use app-specific password
    
    # Create message
    msg = MIMEMultipart()
    msg['From'] = sender
    msg['To'] = recipient
    msg['Subject'] = subject
    
    # Email body
    body = f"""
    Hello,
    
    Please find attached the {subject} for {datetime.now().strftime('%Y-%m-%d')}.
    
    Best regards,
    Automated Report System
    """
    msg.attach(MIMEText(body, 'plain'))
    
    # Attach file
    with open(report_file, 'rb') as f:
        part = MIMEBase('application', 'octet-stream')
        part.set_payload(f.read())
        encoders.encode_base64(part)
        part.add_header(
            'Content-Disposition',
            f'attachment; filename={Path(report_file).name}'
        )
        msg.attach(part)
    
    # Send email
    try:
        server = smtplib.SMTP('smtp.gmail.com', 587)
        server.starttls()
        server.login(sender, password)
        server.send_message(msg)
        server.quit()
        print(f"✓ Email sent to {recipient}")
        return True
    except Exception as e:
        print(f"✗ Failed to send email: {e}")
        return False

# Usage
send_report_email('daily_report.xlsx', 'manager@company.com')
```

## Part 7: Monitoring and Alerts

### File Monitoring

```python
import time
from pathlib import Path
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler

class ExcelFileHandler(FileSystemEventHandler):
    """Handle new Excel files"""
    
    def on_created(self, event):
        if event.src_path.endswith('.xlsx'):
            print(f"New file detected: {event.src_path}")
            # Process the new file
            self.process_file(event.src_path)
    
    def process_file(self, file_path):
        """Process newly created file"""
        try:
            import pandas as pd
            df = pd.read_excel(file_path)
            print(f"  Processed: {len(df)} rows")
            # Your processing logic
        except Exception as e:
            print(f"  Error: {e}")

# Setup monitoring
path_to_watch = 'incoming_files/'
event_handler = ExcelFileHandler()
observer = Observer()
observer.schedule(event_handler, path_to_watch, recursive=False)
observer.start()

print(f"Monitoring {path_to_watch} for new files...")

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    observer.stop()

observer.join()
```

## Part 8: Complete Automation Framework

### Production-Ready Framework

```python
import pandas as pd
from pathlib import Path
from datetime import datetime
import logging
import sys

class ExcelAutomationFramework:
    """
    Complete framework for Excel automation
    """
    
    def __init__(self, config):
        self.config = config
        self.setup_logging()
        
    def setup_logging(self):
        """Setup logging"""
        log_file = f'automation_{datetime.now().strftime("%Y%m%d")}.log'
        logging.basicConfig(
            level=logging.INFO,
            format='%(asctime)s - %(levelname)s - %(message)s',
            handlers=[
                logging.FileHandler(log_file),
                logging.StreamHandler(sys.stdout)
            ]
        )
        self.logger = logging.getLogger(__name__)
    
    def process_files(self, input_dir, output_file):
        """Main processing logic"""
        self.logger.info(f"Starting automation workflow")
        
        try:
            # Find files
            files = list(Path(input_dir).glob('*.xlsx'))
            self.logger.info(f"Found {len(files)} files")
            
            # Process
            all_data = []
            for file in files:
                df = self.process_single_file(file)
                if df is not None:
                    all_data.append(df)
            
            # Combine and save
            if all_data:
                df_final = pd.concat(all_data, ignore_index=True)
                df_final.to_excel(output_file, index=False)
                self.logger.info(f"Saved combined file: {output_file}")
                
                # Send notification
                if self.config.get('send_email'):
                    self.send_notification(output_file)
                
                return True
            else:
                self.logger.warning("No data to process")
                return False
                
        except Exception as e:
            self.logger.error(f"Automation failed: {e}")
            return False
    
    def process_single_file(self, file_path):
        """Process individual file"""
        try:
            self.logger.info(f"Processing: {file_path.name}")
            df = pd.read_excel(file_path)
            
            # Your processing logic here
            
            return df
        except Exception as e:
            self.logger.error(f"Error with {file_path.name}: {e}")
            return None
    
    def send_notification(self, report_file):
        """Send completion notification"""
        self.logger.info("Sending notification...")
        # Email sending logic here

# Usage
config = {
    'send_email': True,
    'email_recipient': 'manager@company.com'
}

framework = ExcelAutomationFramework(config)
success = framework.process_files('data/', 'combined_report.xlsx')
```

## Best Practices

1. **Logging** - Always log operations
2. **Error Handling** - Catch and handle errors gracefully
3. **Validation** - Validate files before processing
4. **Progress Tracking** - Show progress for long operations
5. **Notifications** - Alert on completion/errors
6. **Idempotency** - Safe to re-run
7. **Testing** - Test with sample data first
8. **Documentation** - Document workflows
9. **Monitoring** - Track success/failure rates
10. **Backups** - Keep original files

## Summary

You've learned how to:
- ✅ Process files in batches
- ✅ Build automated workflows
- ✅ Schedule report generation
- ✅ Handle errors and log operations
- ✅ Create command-line interfaces
- ✅ Send email notifications
- ✅ Monitor file systems
- ✅ Build production automation frameworks

## Next Steps

In Session 11, you'll learn advanced Excel features including working with macros, images, hyperlinks, and integration with other formats.

