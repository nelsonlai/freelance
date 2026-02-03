"""
Session 10: Automation and Batch Processing - Comprehensive Examples
====================================================================

This script demonstrates automation workflows, batch processing,
and building robust Excel automation systems.
"""

import pandas as pd
import numpy as np
from pathlib import Path
from datetime import datetime, timedelta
import logging
import sys

print("=" * 80)
print("Session 10: Automation and Batch Processing")
print("=" * 80)
print()

# Create output directories
output_dir = Path(__file__).parent / 'sample_files'
output_dir.mkdir(exist_ok=True)

reports_dir = Path(__file__).parent / 'generated_reports'
reports_dir.mkdir(exist_ok=True)

# ==============================================================================
# 1. SETUP LOGGING
# ==============================================================================

print("1. SETTING UP LOGGING")
print("-" * 80)

# Setup logging
log_file = output_dir / f'automation_{datetime.now().strftime("%Y%m%d_%H%M%S")}.log'

logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler(log_file),
        logging.StreamHandler(sys.stdout)
    ]
)

logger = logging.getLogger(__name__)
logger.info("Automation session started")
print(f"✓ Logging configured: {log_file.name}")
print()

# ==============================================================================
# 2. CREATE SAMPLE DATA FILES
# ==============================================================================

print("2. CREATING SAMPLE DATA FILES")
print("-" * 80)

def create_daily_sales_file(date, output_dir):
    """Create daily sales file"""
    np.random.seed(int(date.strftime('%Y%m%d')))
    
    df = pd.DataFrame({
        'Date': [date] * 20,
        'Product': np.random.choice(['Laptop', 'Mouse', 'Keyboard', 'Monitor'], 20),
        'Region': np.random.choice(['North', 'South', 'East', 'West'], 20),
        'Sales': np.random.randint(100, 5000, 20),
        'Quantity': np.random.randint(1, 20, 20)
    })
    
    filename = output_dir / f'daily_sales_{date.strftime("%Y-%m-%d")}.xlsx'
    df.to_excel(filename, index=False)
    return filename

# Create daily files for past week
for i in range(7):
    date = datetime.now().date() - timedelta(days=i)
    file = create_daily_sales_file(date, output_dir)
    logger.info(f"Created: {file.name}")

print(f"✓ Created 7 daily sales files")
print()

# ==============================================================================
# 3. BATCH FILE PROCESSING
# ==============================================================================

print("3. BATCH FILE PROCESSING")
print("-" * 80)

def process_all_files(directory, pattern='daily_sales_*.xlsx'):
    """Process all files matching pattern"""
    logger.info(f"Starting batch processing in {directory}")
    
    files = list(Path(directory).glob(pattern))
    logger.info(f"Found {len(files)} files")
    
    results = []
    for file in sorted(files):
        try:
            logger.info(f"Processing: {file.name}")
            df = pd.read_excel(file)
            
            summary = {
                'File': file.name,
                'Date': df['Date'].iloc[0],
                'Rows': len(df),
                'Total_Sales': df['Sales'].sum(),
                'Total_Quantity': df['Quantity'].sum(),
                'Status': 'Success'
            }
            results.append(summary)
            logger.info(f"  Success: {len(df)} rows, ${df['Sales'].sum():,} in sales")
            
        except Exception as e:
            logger.error(f"  Error with {file.name}: {e}")
            results.append({
                'File': file.name,
                'Status': f'Error: {e}'
            })
    
    return pd.DataFrame(results)

# Process all daily files
df_summary = process_all_files(output_dir)
print("\nProcessing Summary:")
print(df_summary.to_string(index=False))
print()

# ==============================================================================
# 4. AUTOMATED DAILY REPORT GENERATOR
# ==============================================================================

print("4. AUTOMATED DAILY REPORT GENERATOR")
print("-" * 80)

def generate_daily_report(data_dir, output_dir):
    """Generate daily report from latest data"""
    timestamp = datetime.now().strftime('%Y-%m-%d')
    logger.info(f"Generating daily report for {timestamp}")
    
    # Find latest file
    files = sorted(Path(data_dir).glob('daily_sales_*.xlsx'))
    if not files:
        logger.warning("No files found")
        return None
    
    latest_file = files[-1]
    logger.info(f"Using latest file: {latest_file.name}")
    
    # Read data
    df = pd.read_excel(latest_file)
    
    # Calculate metrics
    metrics = {
        'Report_Date': timestamp,
        'Total_Sales': df['Sales'].sum(),
        'Total_Orders': len(df),
        'Average_Order': df['Sales'].mean(),
        'Total_Quantity': df['Quantity'].sum(),
        'Best_Product': df.groupby('Product')['Sales'].sum().idxmax(),
        'Best_Region': df.groupby('Region')['Sales'].sum().idxmax()
    }
    
    logger.info(f"Metrics calculated: ${metrics['Total_Sales']:,} in sales")
    
    # Create report
    report_file = Path(output_dir) / f'daily_report_{timestamp}.xlsx'
    
    with pd.ExcelWriter(report_file) as writer:
        # Summary metrics
        df_metrics = pd.DataFrame([metrics])
        df_metrics.to_excel(writer, sheet_name='Summary', index=False)
        
        # Raw data
        df.to_excel(writer, sheet_name='Raw_Data', index=False)
        
        # By product
        product_summary = df.groupby('Product').agg({
            'Sales': 'sum',
            'Quantity': 'sum'
        }).reset_index()
        product_summary.to_excel(writer, sheet_name='By_Product', index=False)
        
        # By region
        region_summary = df.groupby('Region').agg({
            'Sales': 'sum',
            'Quantity': 'sum'
        }).reset_index()
        region_summary.to_excel(writer, sheet_name='By_Region', index=False)
    
    logger.info(f"Report saved: {report_file.name}")
    print(f"✓ Daily report generated: {report_file.name}")
    print()
    
    return report_file

# Generate daily report
daily_report = generate_daily_report(output_dir, reports_dir)

# ==============================================================================
# 5. WEEKLY CONSOLIDATION
# ==============================================================================

print("5. WEEKLY CONSOLIDATION")
print("-" * 80)

def weekly_consolidation(data_dir, output_dir):
    """Consolidate week's data into single report"""
    logger.info("Starting weekly consolidation")
    
    # Find all files
    files = sorted(Path(data_dir).glob('daily_sales_*.xlsx'))
    logger.info(f"Found {len(files)} daily files")
    
    # Read and combine all files
    all_data = []
    for file in files:
        df = pd.read_excel(file)
        df['Source_File'] = file.name
        all_data.append(df)
        logger.info(f"  Read: {file.name}")
    
    df_week = pd.concat(all_data, ignore_index=True)
    logger.info(f"Combined: {len(df_week)} total rows")
    
    # Weekly analysis
    week_number = datetime.now().isocalendar()[1]
    
    weekly_metrics = {
        'Week_Number': week_number,
        'Year': datetime.now().year,
        'Total_Sales': df_week['Sales'].sum(),
        'Total_Orders': len(df_week),
        'Average_Daily_Sales': df_week.groupby('Date')['Sales'].sum().mean(),
        'Best_Day': df_week.groupby('Date')['Sales'].sum().idxmax(),
        'Days_Covered': df_week['Date'].nunique()
    }
    
    # Save weekly report
    week_file = Path(output_dir) / f'weekly_report_W{week_number}_{datetime.now().year}.xlsx'
    
    with pd.ExcelWriter(week_file) as writer:
        # All data
        df_week.to_excel(writer, sheet_name='All_Data', index=False)
        
        # Weekly metrics
        df_metrics = pd.DataFrame([weekly_metrics])
        df_metrics.to_excel(writer, sheet_name='Weekly_Summary', index=False)
        
        # Daily breakdown
        daily_breakdown = df_week.groupby('Date').agg({
            'Sales': 'sum',
            'Quantity': 'sum'
        }).reset_index()
        daily_breakdown.to_excel(writer, sheet_name='Daily_Breakdown', index=False)
        
        # Product analysis
        product_weekly = df_week.groupby('Product').agg({
            'Sales': 'sum',
            'Quantity': 'sum'
        }).sort_values('Sales', ascending=False).reset_index()
        product_weekly.to_excel(writer, sheet_name='Products', index=False)
    
    logger.info(f"Weekly report saved: {week_file.name}")
    print(f"✓ Weekly consolidation complete: {week_file.name}")
    print(f"  Total sales: ${weekly_metrics['Total_Sales']:,}")
    print(f"  Orders: {weekly_metrics['Total_Orders']:,}")
    print()
    
    return week_file

# Generate weekly report
weekly_report = weekly_consolidation(output_dir, reports_dir)

# ==============================================================================
# 6. ERROR-SAFE FILE PROCESSOR
# ==============================================================================

print("6. ERROR-SAFE FILE PROCESSOR")
print("-" * 80)

def safe_file_processor(input_dir, output_file, pattern='*.xlsx'):
    """Process files with comprehensive error handling"""
    logger.info("Starting safe file processor")
    
    try:
        files = list(Path(input_dir).glob(pattern))
        if not files:
            logger.warning(f"No files found matching {pattern}")
            return False
        
        logger.info(f"Found {len(files)} files")
        
        results = []
        successful = 0
        failed = 0
        
        for file in files:
            if file.name.startswith('~$'):  # Skip temp files
                continue
            
            try:
                logger.info(f"Processing: {file.name}")
                
                # Validate file
                if file.stat().st_size == 0:
                    raise ValueError("File is empty")
                
                # Read
                df = pd.read_excel(file)
                
                if df.empty:
                    raise ValueError("DataFrame is empty")
                
                # Process
                results.append({
                    'File': file.name,
                    'Rows': len(df),
                    'Columns': len(df.columns),
                    'Status': 'Success',
                    'Timestamp': datetime.now()
                })
                
                successful += 1
                logger.info(f"  ✓ Success: {len(df)} rows")
                
            except Exception as e:
                logger.error(f"  ✗ Error: {e}")
                results.append({
                    'File': file.name,
                    'Status': 'Failed',
                    'Error': str(e),
                    'Timestamp': datetime.now()
                })
                failed += 1
        
        # Save results
        df_results = pd.DataFrame(results)
        df_results.to_excel(output_file, index=False)
        
        logger.info(f"Processing complete: {successful} successful, {failed} failed")
        logger.info(f"Results saved: {output_file}")
        
        print(f"✓ Safe processing complete")
        print(f"  Successful: {successful}")
        print(f"  Failed: {failed}")
        print()
        
        return True
        
    except Exception as e:
        logger.error(f"Fatal error: {e}")
        return False

# Run safe processor
results_file = reports_dir / 'processing_results.xlsx'
success = safe_file_processor(output_dir, results_file, 'daily_sales_*.xlsx')

# ==============================================================================
# 7. AUTOMATED CLEANUP
# ==============================================================================

print("7. AUTOMATED CLEANUP")
print("-" * 80)

def cleanup_old_files(directory, days_old=7, pattern='*.xlsx'):
    """Remove files older than specified days"""
    logger.info(f"Cleaning up files older than {days_old} days")
    
    cutoff_date = datetime.now() - timedelta(days=days_old)
    files = Path(directory).glob(pattern)
    
    removed_count = 0
    for file in files:
        file_time = datetime.fromtimestamp(file.stat().st_mtime)
        if file_time < cutoff_date:
            logger.info(f"Removing old file: {file.name}")
            # file.unlink()  # Uncomment to actually delete
            removed_count += 1
            print(f"  Would remove: {file.name} (from {file_time.date()})")
    
    if removed_count == 0:
        logger.info("No old files to remove")
        print("  No old files found")
    
    print(f"✓ Cleanup complete: {removed_count} files would be removed")
    print()
    
    return removed_count

# Run cleanup (demonstration only, files not actually removed)
cleanup_count = cleanup_old_files(output_dir, days_old=30)

# ==============================================================================
# 8. AUTOMATION FRAMEWORK CLASS
# ==============================================================================

print("8. AUTOMATION FRAMEWORK CLASS")
print("-" * 80)

class ExcelAutomationFramework:
    """Complete framework for Excel automation"""
    
    def __init__(self, input_dir, output_dir):
        self.input_dir = Path(input_dir)
        self.output_dir = Path(output_dir)
        self.output_dir.mkdir(exist_ok=True)
        
        # Setup logging
        self.logger = logging.getLogger(self.__class__.__name__)
        self.logger.info("Framework initialized")
    
    def process_files(self, pattern='*.xlsx'):
        """Main processing workflow"""
        self.logger.info(f"Starting workflow for pattern: {pattern}")
        
        files = list(self.input_dir.glob(pattern))
        self.logger.info(f"Found {len(files)} files")
        
        if not files:
            self.logger.warning("No files to process")
            return None
        
        # Process all files
        all_data = []
        for file in files:
            df = self.process_single_file(file)
            if df is not None:
                all_data.append(df)
        
        # Combine results
        if all_data:
            df_final = pd.concat(all_data, ignore_index=True)
            self.save_results(df_final)
            return df_final
        
        return None
    
    def process_single_file(self, file_path):
        """Process individual file"""
        try:
            self.logger.info(f"Processing: {file_path.name}")
            df = pd.read_excel(file_path)
            
            # Add metadata
            df['Source_File'] = file_path.name
            df['Processing_Date'] = datetime.now()
            
            return df
        except Exception as e:
            self.logger.error(f"Error with {file_path.name}: {e}")
            return None
    
    def save_results(self, df):
        """Save processed results"""
        output_file = self.output_dir / f'combined_results_{datetime.now().strftime("%Y%m%d")}.xlsx'
        df.to_excel(output_file, index=False)
        self.logger.info(f"Results saved: {output_file.name}")
        print(f"  ✓ Saved: {output_file.name}")

# Use automation framework
framework = ExcelAutomationFramework(output_dir, reports_dir)
df_result = framework.process_files('daily_sales_*.xlsx')

print(f"✓ Framework processed {len(df_result) if df_result is not None else 0} total rows")
print()

# ==============================================================================
# 9. FILE MONITORING SIMULATION
# ==============================================================================

print("9. FILE MONITORING SIMULATION")
print("-" * 80)

def check_for_new_files(directory, processed_files=None):
    """Check for new files since last check"""
    if processed_files is None:
        processed_files = set()
    
    logger.info("Checking for new files")
    
    current_files = set(f.name for f in Path(directory).glob('*.xlsx') if not f.name.startswith('~$'))
    new_files = current_files - processed_files
    
    if new_files:
        logger.info(f"Found {len(new_files)} new files")
        for file in new_files:
            print(f"  New file detected: {file}")
    else:
        logger.info("No new files")
        print("  No new files found")
    
    print()
    return current_files

# Simulate file monitoring
processed = check_for_new_files(output_dir)

# ==============================================================================
# 10. COMPREHENSIVE AUTOMATION WORKFLOW
# ==============================================================================

print("10. COMPREHENSIVE AUTOMATION WORKFLOW")
print("-" * 80)

def run_automation_workflow():
    """Complete end-to-end automation workflow"""
    logger.info("="*60)
    logger.info("Starting comprehensive automation workflow")
    logger.info("="*60)
    
    workflow_steps = [
        ("Check for new files", lambda: check_for_new_files(output_dir)),
        ("Process batch files", lambda: process_all_files(output_dir)),
        ("Generate daily report", lambda: generate_daily_report(output_dir, reports_dir)),
        ("Weekly consolidation", lambda: weekly_consolidation(output_dir, reports_dir)),
    ]
    
    results = {}
    for step_name, step_func in workflow_steps:
        try:
            logger.info(f"Step: {step_name}")
            result = step_func()
            results[step_name] = "Success"
            print(f"✓ {step_name}: Complete")
        except Exception as e:
            logger.error(f"Step failed: {step_name} - {e}")
            results[step_name] = f"Failed: {e}"
            print(f"✗ {step_name}: Failed")
    
    logger.info("Workflow complete")
    print("\nWorkflow Summary:")
    for step, status in results.items():
        print(f"  {step}: {status}")
    print()
    
    return results

# Run comprehensive workflow
workflow_results = run_automation_workflow()

# ==============================================================================
# SUMMARY
# ==============================================================================

print("=" * 80)
print("SESSION 10 COMPLETE!")
print("=" * 80)
print()
print("What you learned:")
print("✓ Setup logging for automation")
print("✓ Process files in batches")
print("✓ Generate automated daily reports")
print("✓ Create weekly consolidations")
print("✓ Handle errors gracefully")
print("✓ Build reusable automation frameworks")
print("✓ Monitor for new files")
print("✓ Run comprehensive workflows")
print("✓ Implement production-ready automation")
print()
print("Files generated:")
for report_file in sorted(reports_dir.glob('*.xlsx')):
    print(f"  - {report_file.name}")
print()
print("Log file:")
print(f"  - {log_file.name}")
print()
print("Next: Session 11 - Advanced Excel Features")
print("=" * 80)

