"""
Excel Automation Project Template
==================================

Use this template as a starting point for your Excel automation projects.
"""

import pandas as pd
import numpy as np
from pathlib import Path
from datetime import datetime
import logging
from typing import Dict, List, Optional
import sys

# ==============================================================================
# CONFIGURATION
# ==============================================================================

class Config:
    """Project configuration"""
    # Directories
    BASE_DIR = Path(__file__).parent
    INPUT_DIR = BASE_DIR / 'input'
    OUTPUT_DIR = BASE_DIR / 'output'
    LOG_DIR = BASE_DIR / 'logs'
    
    # File patterns
    INPUT_PATTERN = '*.xlsx'
    OUTPUT_PREFIX = 'processed_'
    
    # Processing options
    SKIP_ERRORS = True
    SAVE_INTERMEDIATE = False
    
    # Create directories
    INPUT_DIR.mkdir(exist_ok=True)
    OUTPUT_DIR.mkdir(exist_ok=True)
    LOG_DIR.mkdir(exist_ok=True)


# ==============================================================================
# LOGGING SETUP
# ==============================================================================

def setup_logging(log_level=logging.INFO):
    """Configure logging for the project"""
    log_file = Config.LOG_DIR / f'project_{datetime.now():%Y%m%d_%H%M%S}.log'
    
    logging.basicConfig(
        level=log_level,
        format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
        handlers=[
            logging.FileHandler(log_file),
            logging.StreamHandler(sys.stdout)
        ]
    )
    
    return logging.getLogger(__name__)


# ==============================================================================
# EXCEL OPERATIONS
# ==============================================================================

class ExcelProcessor:
    """Main class for Excel processing operations"""
    
    def __init__(self, logger=None):
        self.logger = logger or logging.getLogger(__name__)
        self.processed_files = []
        self.errors = []
    
    def read_file(self, file_path: Path, **kwargs) -> Optional[pd.DataFrame]:
        """
        Safely read an Excel file
        
        Args:
            file_path: Path to Excel file
            **kwargs: Additional arguments for pd.read_excel
            
        Returns:
            DataFrame or None if error
        """
        try:
            self.logger.info(f"Reading file: {file_path}")
            df = pd.read_excel(file_path, **kwargs)
            self.logger.info(f"Successfully read {len(df)} rows")
            return df
            
        except Exception as e:
            self.logger.error(f"Error reading {file_path}: {e}")
            self.errors.append((file_path, str(e)))
            return None
    
    def write_file(self, df: pd.DataFrame, file_path: Path, **kwargs) -> bool:
        """
        Safely write DataFrame to Excel
        
        Args:
            df: DataFrame to write
            file_path: Output file path
            **kwargs: Additional arguments for df.to_excel
            
        Returns:
            True if successful, False otherwise
        """
        try:
            self.logger.info(f"Writing file: {file_path}")
            df.to_excel(file_path, index=False, **kwargs)
            self.logger.info(f"Successfully wrote {len(df)} rows")
            self.processed_files.append(file_path)
            return True
            
        except Exception as e:
            self.logger.error(f"Error writing {file_path}: {e}")
            self.errors.append((file_path, str(e)))
            return False
    
    def clean_data(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Clean and preprocess data
        
        Args:
            df: Input DataFrame
            
        Returns:
            Cleaned DataFrame
        """
        self.logger.info("Cleaning data...")
        
        # Remove duplicates
        original_len = len(df)
        df = df.drop_duplicates()
        if len(df) < original_len:
            self.logger.info(f"Removed {original_len - len(df)} duplicates")
        
        # Handle missing values
        missing_count = df.isnull().sum().sum()
        if missing_count > 0:
            self.logger.info(f"Handling {missing_count} missing values")
            # Example: fill with appropriate values
            df = df.fillna(method='ffill')
        
        return df
    
    def transform_data(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Transform data according to business logic
        
        Args:
            df: Input DataFrame
            
        Returns:
            Transformed DataFrame
        """
        self.logger.info("Transforming data...")
        
        # Add your transformation logic here
        # Example transformations:
        
        # 1. Add calculated columns
        # df['Total'] = df['Quantity'] * df['Price']
        
        # 2. Convert data types
        # df['Date'] = pd.to_datetime(df['Date'])
        
        # 3. Create categories
        # df['Category'] = pd.cut(df['Value'], bins=[0, 50, 100, 150], 
        #                         labels=['Low', 'Medium', 'High'])
        
        return df
    
    def aggregate_data(self, df: pd.DataFrame) -> pd.DataFrame:
        """
        Aggregate data for reporting
        
        Args:
            df: Input DataFrame
            
        Returns:
            Aggregated DataFrame
        """
        self.logger.info("Aggregating data...")
        
        # Add your aggregation logic here
        # Example: Group by category and sum
        # summary = df.groupby('Category').agg({
        #     'Quantity': 'sum',
        #     'Total': 'sum'
        # }).reset_index()
        
        return df
    
    def process_file(self, input_file: Path) -> Optional[Path]:
        """
        Complete processing pipeline for a single file
        
        Args:
            input_file: Input Excel file path
            
        Returns:
            Output file path or None if error
        """
        self.logger.info(f"Processing {input_file.name}")
        
        # Read
        df = self.read_file(input_file)
        if df is None:
            return None
        
        # Process
        df = self.clean_data(df)
        df = self.transform_data(df)
        df = self.aggregate_data(df)
        
        # Write
        output_file = Config.OUTPUT_DIR / f"{Config.OUTPUT_PREFIX}{input_file.name}"
        if self.write_file(df, output_file):
            return output_file
        else:
            return None
    
    def process_directory(self, input_dir: Path = None) -> Dict:
        """
        Process all Excel files in a directory
        
        Args:
            input_dir: Input directory path (default: Config.INPUT_DIR)
            
        Returns:
            Dictionary with processing results
        """
        input_dir = input_dir or Config.INPUT_DIR
        files = list(input_dir.glob(Config.INPUT_PATTERN))
        
        self.logger.info(f"Found {len(files)} files to process")
        
        results = {
            'total': len(files),
            'success': 0,
            'failed': 0,
            'output_files': []
        }
        
        for file in files:
            output_file = self.process_file(file)
            if output_file:
                results['success'] += 1
                results['output_files'].append(output_file)
            else:
                results['failed'] += 1
        
        return results
    
    def generate_report(self, results: Dict) -> pd.DataFrame:
        """
        Generate summary report
        
        Args:
            results: Processing results dictionary
            
        Returns:
            Report DataFrame
        """
        report_data = {
            'Metric': [
                'Total Files',
                'Successfully Processed',
                'Failed',
                'Success Rate (%)'
            ],
            'Value': [
                results['total'],
                results['success'],
                results['failed'],
                (results['success'] / results['total'] * 100) if results['total'] > 0 else 0
            ]
        }
        
        return pd.DataFrame(report_data)


# ==============================================================================
# MAIN EXECUTION
# ==============================================================================

def main():
    """Main execution function"""
    # Setup
    logger = setup_logging()
    logger.info("Starting Excel Automation Project")
    logger.info(f"Input directory: {Config.INPUT_DIR}")
    logger.info(f"Output directory: {Config.OUTPUT_DIR}")
    
    # Process
    processor = ExcelProcessor(logger)
    results = processor.process_directory()
    
    # Report
    logger.info("Processing complete!")
    logger.info(f"Successfully processed: {results['success']}/{results['total']} files")
    
    if results['failed'] > 0:
        logger.warning(f"Failed to process: {results['failed']} files")
    
    # Generate report
    report_df = processor.generate_report(results)
    report_file = Config.OUTPUT_DIR / f'processing_report_{datetime.now():%Y%m%d_%H%M%S}.xlsx'
    processor.write_file(report_df, report_file)
    
    logger.info(f"Report saved to: {report_file}")
    
    # Show errors if any
    if processor.errors:
        logger.warning("Errors encountered:")
        for file_path, error in processor.errors:
            logger.warning(f"  {file_path}: {error}")
    
    return results


if __name__ == "__main__":
    results = main()
    sys.exit(0 if results['failed'] == 0 else 1)

