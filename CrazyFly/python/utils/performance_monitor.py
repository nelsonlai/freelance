"""
Performance Monitoring System for Quadrotor Control System
=========================================================

This module provides a comprehensive performance monitoring system
for tracking system metrics, resource usage, and real-time performance
analysis.

Key Features:
- Real-time system metrics monitoring
- CPU, memory, and network usage tracking
- Control loop performance analysis
- Latency and jitter measurement
- Performance bottleneck detection
- Resource usage alerts
- Performance data visualization
- Historical performance analysis
- Performance reporting and export

The performance monitor enables comprehensive tracking and analysis
of system performance for optimization and debugging.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import numpy as np
import time
import threading
import psutil
import os
from typing import Dict, List, Tuple, Optional, Any, Callable
from dataclasses import dataclass, field
from enum import Enum
from pathlib import Path
import logging
from datetime import datetime
import json
import matplotlib.pyplot as plt
from collections import deque
import statistics

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class MetricType(Enum):
    """Enumeration of metric types."""
    CPU_USAGE = "cpu_usage"
    MEMORY_USAGE = "memory_usage"
    NETWORK_IO = "network_io"
    DISK_IO = "disk_io"
    CONTROL_LATENCY = "control_latency"
    SENSOR_LATENCY = "sensor_latency"
    COMMUNICATION_LATENCY = "communication_latency"
    THREAD_COUNT = "thread_count"
    PROCESS_COUNT = "process_count"
    TEMPERATURE = "temperature"
    BATTERY_LEVEL = "battery_level"
    CUSTOM = "custom"


class AlertLevel(Enum):
    """Enumeration of alert levels."""
    INFO = "info"
    WARNING = "warning"
    ERROR = "error"
    CRITICAL = "critical"


@dataclass
class PerformanceMetric:
    """
    Performance metric data structure.
    
    Attributes:
        name (str): Metric name
        value (float): Metric value
        unit (str): Unit of measurement
        timestamp (float): Timestamp in seconds
        metric_type (MetricType): Type of metric
        metadata (Dict[str, Any]): Additional metadata
    """
    name: str
    value: float
    unit: str
    timestamp: float
    metric_type: MetricType
    metadata: Dict[str, Any] = field(default_factory=dict)


@dataclass
class PerformanceAlert:
    """
    Performance alert data structure.
    
    Attributes:
        metric_name (str): Name of the metric that triggered the alert
        alert_level (AlertLevel): Alert level
        message (str): Alert message
        timestamp (float): Timestamp when alert was triggered
        threshold (float): Threshold that was exceeded
        current_value (float): Current value that triggered the alert
    """
    metric_name: str
    alert_level: AlertLevel
    message: str
    timestamp: float
    threshold: float
    current_value: float


@dataclass
class PerformanceConfig:
    """
    Performance monitoring configuration.
    
    Attributes:
        update_interval (float): Update interval in seconds
        history_length (int): Number of historical data points to keep
        enable_cpu_monitoring (bool): Enable CPU monitoring
        enable_memory_monitoring (bool): Enable memory monitoring
        enable_network_monitoring (bool): Enable network monitoring
        enable_disk_monitoring (bool): Enable disk monitoring
        enable_control_monitoring (bool): Enable control loop monitoring
        alert_thresholds (Dict[str, float]): Alert thresholds for metrics
        enable_alerts (bool): Enable performance alerts
        enable_logging (bool): Enable performance logging
        log_file (str): Performance log file path
    """
    update_interval: float = 1.0
    history_length: int = 1000
    enable_cpu_monitoring: bool = True
    enable_memory_monitoring: bool = True
    enable_network_monitoring: bool = True
    enable_disk_monitoring: bool = False
    enable_control_monitoring: bool = True
    alert_thresholds: Dict[str, float] = field(default_factory=dict)
    enable_alerts: bool = True
    enable_logging: bool = True
    log_file: str = "performance.log"


class PerformanceCollector:
    """
    Performance data collector.
    
    This class collects various system performance metrics
    using the psutil library and custom timing measurements.
    """
    
    def __init__(self):
        """Initialize performance collector."""
        self.cpu_times = deque(maxlen=2)
        self.network_io = deque(maxlen=2)
        self.disk_io = deque(maxlen=2)
        
        # Initialize baseline measurements
        self._initialize_baselines()
        
        logger.info("Performance collector initialized")
    
    def _initialize_baselines(self):
        """Initialize baseline measurements."""
        self.cpu_times.append(psutil.cpu_times_percent())
        self.network_io.append(psutil.net_io_counters())
        self.disk_io.append(psutil.disk_io_counters())
    
    def collect_cpu_metrics(self) -> Dict[str, float]:
        """
        Collect CPU performance metrics.
        
        Returns:
            Dict[str, float]: CPU metrics
        """
        cpu_times = psutil.cpu_times_percent()
        self.cpu_times.append(cpu_times)
        
        if len(self.cpu_times) >= 2:
            # Calculate CPU usage change
            prev_times = self.cpu_times[0]
            curr_times = self.cpu_times[1]
            
            total_prev = sum(prev_times)
            total_curr = sum(curr_times)
            
            if total_prev > 0:
                cpu_usage = ((total_curr - total_prev) / total_prev) * 100
            else:
                cpu_usage = 0.0
        else:
            cpu_usage = 0.0
        
        return {
            'cpu_percent': psutil.cpu_percent(interval=0.1),
            'cpu_count': psutil.cpu_count(),
            'cpu_freq': psutil.cpu_freq().current if psutil.cpu_freq() else 0.0,
            'cpu_usage_change': cpu_usage
        }
    
    def collect_memory_metrics(self) -> Dict[str, float]:
        """
        Collect memory performance metrics.
        
        Returns:
            Dict[str, float]: Memory metrics
        """
        memory = psutil.virtual_memory()
        
        return {
            'memory_percent': memory.percent,
            'memory_used': memory.used / (1024**3),  # GB
            'memory_available': memory.available / (1024**3),  # GB
            'memory_total': memory.total / (1024**3),  # GB
            'memory_free': memory.free / (1024**3),  # GB
            'swap_percent': psutil.swap_memory().percent if hasattr(psutil, 'swap_memory') else 0.0
        }
    
    def collect_network_metrics(self) -> Dict[str, float]:
        """
        Collect network performance metrics.
        
        Returns:
            Dict[str, float]: Network metrics
        """
        network_io = psutil.net_io_counters()
        self.network_io.append(network_io)
        
        if len(self.network_io) >= 2:
            # Calculate network I/O rates
            prev_io = self.network_io[0]
            curr_io = self.network_io[1]
            
            bytes_sent_rate = (curr_io.bytes_sent - prev_io.bytes_sent) / 1024  # KB/s
            bytes_recv_rate = (curr_io.bytes_recv - prev_io.bytes_recv) / 1024  # KB/s
            packets_sent_rate = curr_io.packets_sent - prev_io.packets_sent
            packets_recv_rate = curr_io.packets_recv - prev_io.packets_recv
        else:
            bytes_sent_rate = 0.0
            bytes_recv_rate = 0.0
            packets_sent_rate = 0.0
            packets_recv_rate = 0.0
        
        return {
            'bytes_sent_rate': bytes_sent_rate,
            'bytes_recv_rate': bytes_recv_rate,
            'packets_sent_rate': packets_sent_rate,
            'packets_recv_rate': packets_recv_rate,
            'bytes_sent_total': network_io.bytes_sent / (1024**3),  # GB
            'bytes_recv_total': network_io.bytes_recv / (1024**3),  # GB
            'packets_sent_total': network_io.packets_sent,
            'packets_recv_total': network_io.packets_recv
        }
    
    def collect_disk_metrics(self) -> Dict[str, float]:
        """
        Collect disk performance metrics.
        
        Returns:
            Dict[str, float]: Disk metrics
        """
        disk_io = psutil.disk_io_counters()
        self.disk_io.append(disk_io)
        
        if len(self.disk_io) >= 2:
            # Calculate disk I/O rates
            prev_io = self.disk_io[0]
            curr_io = self.disk_io[1]
            
            read_bytes_rate = (curr_io.read_bytes - prev_io.read_bytes) / 1024  # KB/s
            write_bytes_rate = (curr_io.write_bytes - prev_io.write_bytes) / 1024  # KB/s
            read_count_rate = curr_io.read_count - prev_io.read_count
            write_count_rate = curr_io.write_count - prev_io.write_count
        else:
            read_bytes_rate = 0.0
            write_bytes_rate = 0.0
            read_count_rate = 0.0
            write_count_rate = 0.0
        
        # Disk usage
        disk_usage = psutil.disk_usage('/')
        
        return {
            'read_bytes_rate': read_bytes_rate,
            'write_bytes_rate': write_bytes_rate,
            'read_count_rate': read_count_rate,
            'write_count_rate': write_count_rate,
            'disk_percent': disk_usage.percent,
            'disk_used': disk_usage.used / (1024**3),  # GB
            'disk_free': disk_usage.free / (1024**3),  # GB
            'disk_total': disk_usage.total / (1024**3)  # GB
        }
    
    def collect_process_metrics(self) -> Dict[str, float]:
        """
        Collect process performance metrics.
        
        Returns:
            Dict[str, float]: Process metrics
        """
        current_process = psutil.Process()
        
        return {
            'process_cpu_percent': current_process.cpu_percent(),
            'process_memory_percent': current_process.memory_percent(),
            'process_memory_rss': current_process.memory_info().rss / (1024**2),  # MB
            'process_memory_vms': current_process.memory_info().vms / (1024**2),  # MB
            'process_threads': current_process.num_threads(),
            'process_open_files': len(current_process.open_files()),
            'process_connections': len(current_process.connections())
        }
    
    def collect_system_metrics(self) -> Dict[str, float]:
        """
        Collect general system metrics.
        
        Returns:
            Dict[str, float]: System metrics
        """
        return {
            'thread_count': threading.active_count(),
            'process_count': len(psutil.pids()),
            'load_average': psutil.getloadavg()[0] if hasattr(psutil, 'getloadavg') else 0.0,
            'boot_time': psutil.boot_time(),
            'uptime': time.time() - psutil.boot_time()
        }


class PerformanceAnalyzer:
    """
    Performance data analyzer.
    
    This class analyzes performance data to detect trends,
    bottlenecks, and anomalies.
    """
    
    def __init__(self, history_length: int = 1000):
        """
        Initialize performance analyzer.
        
        Args:
            history_length (int): Length of historical data to keep
        """
        self.history_length = history_length
        self.metric_history: Dict[str, deque] = {}
        self.analysis_results: Dict[str, Any] = {}
        
        logger.info("Performance analyzer initialized")
    
    def add_metric(self, metric: PerformanceMetric):
        """
        Add a metric to the analyzer.
        
        Args:
            metric (PerformanceMetric): Performance metric
        """
        if metric.name not in self.metric_history:
            self.metric_history[metric.name] = deque(maxlen=self.history_length)
        
        self.metric_history[metric.name].append(metric)
    
    def analyze_metric(self, metric_name: str) -> Dict[str, Any]:
        """
        Analyze a specific metric.
        
        Args:
            metric_name (str): Name of the metric to analyze
            
        Returns:
            Dict[str, Any]: Analysis results
        """
        if metric_name not in self.metric_history:
            return {}
        
        history = list(self.metric_history[metric_name])
        if not history:
            return {}
        
        values = [metric.value for metric in history]
        timestamps = [metric.timestamp for metric in history]
        
        # Basic statistics
        stats = {
            'count': len(values),
            'mean': statistics.mean(values),
            'median': statistics.median(values),
            'std': statistics.stdev(values) if len(values) > 1 else 0.0,
            'min': min(values),
            'max': max(values),
            'range': max(values) - min(values)
        }
        
        # Trend analysis
        if len(values) >= 2:
            # Linear trend
            x = np.array(timestamps)
            y = np.array(values)
            coeffs = np.polyfit(x, y, 1)
            trend_slope = coeffs[0]
            trend_intercept = coeffs[1]
            
            # R-squared
            y_pred = coeffs[0] * x + coeffs[1]
            ss_res = np.sum((y - y_pred) ** 2)
            ss_tot = np.sum((y - np.mean(y)) ** 2)
            r_squared = 1 - (ss_res / ss_tot) if ss_tot > 0 else 0.0
            
            stats.update({
                'trend_slope': trend_slope,
                'trend_intercept': trend_intercept,
                'r_squared': r_squared,
                'trend_direction': 'increasing' if trend_slope > 0 else 'decreasing' if trend_slope < 0 else 'stable'
            })
        
        # Anomaly detection
        if len(values) >= 3:
            # Simple outlier detection using z-score
            mean_val = statistics.mean(values)
            std_val = statistics.stdev(values)
            
            outliers = []
            for i, value in enumerate(values):
                z_score = abs((value - mean_val) / std_val) if std_val > 0 else 0.0
                if z_score > 2.0:  # 2 standard deviations
                    outliers.append({
                        'index': i,
                        'value': value,
                        'z_score': z_score,
                        'timestamp': timestamps[i]
                    })
            
            stats['outliers'] = outliers
            stats['outlier_count'] = len(outliers)
        
        # Performance indicators
        if len(values) >= 10:
            # Moving averages
            window_size = min(10, len(values))
            recent_values = values[-window_size:]
            stats['moving_average'] = statistics.mean(recent_values)
            
            # Volatility
            if len(recent_values) > 1:
                stats['volatility'] = statistics.stdev(recent_values)
            else:
                stats['volatility'] = 0.0
        
        return stats
    
    def analyze_all_metrics(self) -> Dict[str, Dict[str, Any]]:
        """
        Analyze all metrics.
        
        Returns:
            Dict[str, Dict[str, Any]]: Analysis results for all metrics
        """
        results = {}
        for metric_name in self.metric_history:
            results[metric_name] = self.analyze_metric(metric_name)
        
        self.analysis_results = results
        return results
    
    def detect_bottlenecks(self) -> List[Dict[str, Any]]:
        """
        Detect performance bottlenecks.
        
        Returns:
            List[Dict[str, Any]]: List of detected bottlenecks
        """
        bottlenecks = []
        
        # Analyze all metrics first
        self.analyze_all_metrics()
        
        # Check for high CPU usage
        if 'cpu_percent' in self.analysis_results:
            cpu_stats = self.analysis_results['cpu_percent']
            if cpu_stats.get('mean', 0) > 80.0:
                bottlenecks.append({
                    'type': 'high_cpu_usage',
                    'metric': 'cpu_percent',
                    'severity': 'high' if cpu_stats['mean'] > 90.0 else 'medium',
                    'value': cpu_stats['mean'],
                    'threshold': 80.0,
                    'description': f"High CPU usage: {cpu_stats['mean']:.1f}%"
                })
        
        # Check for high memory usage
        if 'memory_percent' in self.analysis_results:
            memory_stats = self.analysis_results['memory_percent']
            if memory_stats.get('mean', 0) > 85.0:
                bottlenecks.append({
                    'type': 'high_memory_usage',
                    'metric': 'memory_percent',
                    'severity': 'high' if memory_stats['mean'] > 95.0 else 'medium',
                    'value': memory_stats['mean'],
                    'threshold': 85.0,
                    'description': f"High memory usage: {memory_stats['mean']:.1f}%"
                })
        
        # Check for high latency
        for metric_name in self.metric_history:
            if 'latency' in metric_name.lower():
                latency_stats = self.analysis_results.get(metric_name, {})
                if latency_stats.get('mean', 0) > 0.1:  # 100ms threshold
                    bottlenecks.append({
                        'type': 'high_latency',
                        'metric': metric_name,
                        'severity': 'high' if latency_stats['mean'] > 0.5 else 'medium',
                        'value': latency_stats['mean'],
                        'threshold': 0.1,
                        'description': f"High latency in {metric_name}: {latency_stats['mean']:.3f}s"
                    })
        
        return bottlenecks
    
    def generate_report(self) -> Dict[str, Any]:
        """
        Generate a comprehensive performance report.
        
        Returns:
            Dict[str, Any]: Performance report
        """
        # Analyze all metrics
        analysis = self.analyze_all_metrics()
        
        # Detect bottlenecks
        bottlenecks = self.detect_bottlenecks()
        
        # Generate summary
        total_metrics = len(self.metric_history)
        total_data_points = sum(len(history) for history in self.metric_history.values())
        
        report = {
            'timestamp': time.time(),
            'summary': {
                'total_metrics': total_metrics,
                'total_data_points': total_data_points,
                'bottleneck_count': len(bottlenecks),
                'critical_bottlenecks': len([b for b in bottlenecks if b['severity'] == 'high'])
            },
            'analysis': analysis,
            'bottlenecks': bottlenecks,
            'recommendations': self._generate_recommendations(bottlenecks)
        }
        
        return report
    
    def _generate_recommendations(self, bottlenecks: List[Dict[str, Any]]) -> List[str]:
        """
        Generate recommendations based on bottlenecks.
        
        Args:
            bottlenecks (List[Dict[str, Any]]): Detected bottlenecks
            
        Returns:
            List[str]: List of recommendations
        """
        recommendations = []
        
        for bottleneck in bottlenecks:
            if bottleneck['type'] == 'high_cpu_usage':
                recommendations.append("Consider optimizing CPU-intensive operations or reducing update frequency")
            elif bottleneck['type'] == 'high_memory_usage':
                recommendations.append("Consider implementing memory cleanup or reducing data retention")
            elif bottleneck['type'] == 'high_latency':
                recommendations.append("Consider optimizing communication or reducing data transfer size")
        
        return recommendations


class PerformanceMonitor:
    """
    Main performance monitoring class.
    
    This class provides comprehensive performance monitoring
    functionality with real-time data collection and analysis.
    """
    
    def __init__(self, config: PerformanceConfig = None):
        """
        Initialize performance monitor.
        
        Args:
            config (PerformanceConfig): Performance monitoring configuration
        """
        self.config = config or PerformanceConfig()
        
        # Initialize components
        self.collector = PerformanceCollector()
        self.analyzer = PerformanceAnalyzer(self.config.history_length)
        
        # Monitoring state
        self.monitoring = False
        self.monitor_thread = None
        self.start_time = None
        
        # Alert system
        self.alerts: List[PerformanceAlert] = []
        self.alert_callbacks: List[Callable] = []
        
        # Performance logging
        self.log_file = None
        if self.config.enable_logging:
            self.log_file = open(self.config.log_file, 'w')
        
        logger.info("Performance monitor initialized")
    
    def start_monitoring(self):
        """Start performance monitoring."""
        if self.monitoring:
            logger.warning("Performance monitoring is already running")
            return
        
        self.monitoring = True
        self.start_time = time.time()
        self.monitor_thread = threading.Thread(target=self._monitoring_loop, daemon=True)
        self.monitor_thread.start()
        
        logger.info("Performance monitoring started")
    
    def stop_monitoring(self):
        """Stop performance monitoring."""
        if not self.monitoring:
            logger.warning("Performance monitoring is not running")
            return
        
        self.monitoring = False
        if self.monitor_thread and self.monitor_thread.is_alive():
            self.monitor_thread.join(timeout=5.0)
        
        # Close log file
        if self.log_file:
            self.log_file.close()
            self.log_file = None
        
        logger.info("Performance monitoring stopped")
    
    def _monitoring_loop(self):
        """Main monitoring loop."""
        while self.monitoring:
            try:
                # Collect system metrics
                self._collect_system_metrics()
                
                # Check for alerts
                self._check_alerts()
                
                # Sleep for update interval
                time.sleep(self.config.update_interval)
                
            except Exception as e:
                logger.error(f"Error in monitoring loop: {e}")
    
    def _collect_system_metrics(self):
        """Collect all system metrics."""
        timestamp = time.time()
        
        # CPU metrics
        if self.config.enable_cpu_monitoring:
            cpu_metrics = self.collector.collect_cpu_metrics()
            for name, value in cpu_metrics.items():
                metric = PerformanceMetric(
                    name=f"cpu_{name}",
                    value=value,
                    unit="%" if "percent" in name else "count" if "count" in name else "MHz",
                    timestamp=timestamp,
                    metric_type=MetricType.CPU_USAGE
                )
                self.analyzer.add_metric(metric)
                self._log_metric(metric)
        
        # Memory metrics
        if self.config.enable_memory_monitoring:
            memory_metrics = self.collector.collect_memory_metrics()
            for name, value in memory_metrics.items():
                metric = PerformanceMetric(
                    name=f"memory_{name}",
                    value=value,
                    unit="%" if "percent" in name else "GB",
                    timestamp=timestamp,
                    metric_type=MetricType.MEMORY_USAGE
                )
                self.analyzer.add_metric(metric)
                self._log_metric(metric)
        
        # Network metrics
        if self.config.enable_network_monitoring:
            network_metrics = self.collector.collect_network_metrics()
            for name, value in network_metrics.items():
                metric = PerformanceMetric(
                    name=f"network_{name}",
                    value=value,
                    unit="KB/s" if "rate" in name else "GB" if "total" in name else "packets/s",
                    timestamp=timestamp,
                    metric_type=MetricType.NETWORK_IO
                )
                self.analyzer.add_metric(metric)
                self._log_metric(metric)
        
        # Disk metrics
        if self.config.enable_disk_monitoring:
            disk_metrics = self.collector.collect_disk_metrics()
            for name, value in disk_metrics.items():
                metric = PerformanceMetric(
                    name=f"disk_{name}",
                    value=value,
                    unit="KB/s" if "rate" in name else "GB" if "used" in name or "free" in name or "total" in name else "%",
                    timestamp=timestamp,
                    metric_type=MetricType.DISK_IO
                )
                self.analyzer.add_metric(metric)
                self._log_metric(metric)
        
        # Process metrics
        process_metrics = self.collector.collect_process_metrics()
        for name, value in process_metrics.items():
            metric = PerformanceMetric(
                name=f"process_{name}",
                value=value,
                unit="%" if "percent" in name else "MB" if "memory" in name else "count",
                timestamp=timestamp,
                metric_type=MetricType.CUSTOM
            )
            self.analyzer.add_metric(metric)
            self._log_metric(metric)
        
        # System metrics
        system_metrics = self.collector.collect_system_metrics()
        for name, value in system_metrics.items():
            metric = PerformanceMetric(
                name=f"system_{name}",
                value=value,
                unit="count" if "count" in name else "seconds",
                timestamp=timestamp,
                metric_type=MetricType.CUSTOM
            )
            self.analyzer.add_metric(metric)
            self._log_metric(metric)
    
    def _log_metric(self, metric: PerformanceMetric):
        """Log a performance metric."""
        if self.log_file:
            log_entry = {
                'timestamp': datetime.fromtimestamp(metric.timestamp).isoformat(),
                'name': metric.name,
                'value': metric.value,
                'unit': metric.unit,
                'type': metric.metric_type.value
            }
            self.log_file.write(json.dumps(log_entry) + '\n')
            self.log_file.flush()
    
    def _check_alerts(self):
        """Check for performance alerts."""
        if not self.config.enable_alerts:
            return
        
        # Get current metrics
        for metric_name in self.analyzer.metric_history:
            if metric_name in self.config.alert_thresholds:
                threshold = self.config.alert_thresholds[metric_name]
                current_metrics = list(self.analyzer.metric_history[metric_name])
                
                if current_metrics:
                    current_value = current_metrics[-1].value
                    
                    if current_value > threshold:
                        alert = PerformanceAlert(
                            metric_name=metric_name,
                            alert_level=AlertLevel.WARNING if current_value < threshold * 1.5 else AlertLevel.ERROR,
                            message=f"{metric_name} exceeded threshold: {current_value:.2f} > {threshold:.2f}",
                            timestamp=time.time(),
                            threshold=threshold,
                            current_value=current_value
                        )
                        
                        self.alerts.append(alert)
                        self._notify_alert_callbacks(alert)
    
    def add_alert_callback(self, callback: Callable):
        """
        Add an alert callback function.
        
        Args:
            callback (Callable): Alert callback function
        """
        self.alert_callbacks.append(callback)
        logger.debug("Added alert callback")
    
    def _notify_alert_callbacks(self, alert: PerformanceAlert):
        """Notify alert callbacks."""
        for callback in self.alert_callbacks:
            try:
                callback(alert)
            except Exception as e:
                logger.error(f"Error in alert callback: {e}")
    
    def get_current_metrics(self) -> Dict[str, float]:
        """
        Get current metric values.
        
        Returns:
            Dict[str, float]: Current metric values
        """
        current_metrics = {}
        
        for metric_name, history in self.analyzer.metric_history.items():
            if history:
                current_metrics[metric_name] = history[-1].value
        
        return current_metrics
    
    def get_metric_history(self, metric_name: str) -> List[PerformanceMetric]:
        """
        Get metric history.
        
        Args:
            metric_name (str): Name of the metric
            
        Returns:
            List[PerformanceMetric]: Metric history
        """
        return list(self.analyzer.metric_history.get(metric_name, []))
    
    def get_performance_report(self) -> Dict[str, Any]:
        """
        Get a comprehensive performance report.
        
        Returns:
            Dict[str, Any]: Performance report
        """
        return self.analyzer.generate_report()
    
    def get_alerts(self, level: AlertLevel = None) -> List[PerformanceAlert]:
        """
        Get performance alerts.
        
        Args:
            level (AlertLevel): Filter by alert level (optional)
            
        Returns:
            List[PerformanceAlert]: List of alerts
        """
        if level is None:
            return self.alerts.copy()
        else:
            return [alert for alert in self.alerts if alert.alert_level == level]
    
    def clear_alerts(self):
        """Clear all alerts."""
        self.alerts.clear()
        logger.info("Cleared all performance alerts")
    
    def export_data(self, file_path: str = None) -> bool:
        """
        Export performance data to file.
        
        Args:
            file_path (str): Output file path (optional)
            
        Returns:
            bool: True if exported successfully
        """
        if file_path is None:
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            file_path = f"performance_data_{timestamp}.json"
        
        try:
            export_data = {
                'metadata': {
                    'export_time': datetime.now().isoformat(),
                    'monitor_start_time': self.start_time,
                    'total_metrics': len(self.analyzer.metric_history)
                },
                'metrics': {},
                'alerts': [asdict(alert) for alert in self.alerts],
                'report': self.get_performance_report()
            }
            
            # Export metric history
            for metric_name, history in self.analyzer.metric_history.items():
                export_data['metrics'][metric_name] = [
                    {
                        'timestamp': metric.timestamp,
                        'value': metric.value,
                        'unit': metric.unit,
                        'type': metric.metric_type.value
                    }
                    for metric in history
                ]
            
            with open(file_path, 'w') as f:
                json.dump(export_data, f, indent=2)
            
            logger.info(f"Exported performance data to {file_path}")
            return True
            
        except Exception as e:
            logger.error(f"Failed to export performance data: {e}")
            return False
    
    def plot_metrics(self, metric_names: List[str] = None, save_path: str = None):
        """
        Plot performance metrics.
        
        Args:
            metric_names (List[str]): Metrics to plot (if None, plot all)
            save_path (str): Path to save the plot (optional)
        """
        if not metric_names:
            metric_names = list(self.analyzer.metric_history.keys())
        
        fig, axes = plt.subplots(len(metric_names), 1, figsize=(12, 3 * len(metric_names)))
        if len(metric_names) == 1:
            axes = [axes]
        
        for i, metric_name in enumerate(metric_names):
            if metric_name in self.analyzer.metric_history:
                history = self.analyzer.metric_history[metric_name]
                timestamps = [metric.timestamp for metric in history]
                values = [metric.value for metric in history]
                
                axes[i].plot(timestamps, values, label=metric_name)
                axes[i].set_title(f"{metric_name} Over Time")
                axes[i].set_xlabel("Time")
                axes[i].set_ylabel("Value")
                axes[i].grid(True)
                axes[i].legend()
        
        plt.tight_layout()
        
        if save_path:
            plt.savefig(save_path)
            logger.info(f"Saved performance plot to {save_path}")
        else:
            plt.show()


# Example usage
if __name__ == "__main__":
    """
    Example usage of the performance monitor.
    
    This demonstrates how to set up and use the performance
    monitor for tracking system performance.
    """
    
    # Create performance monitor configuration
    config = PerformanceConfig(
        update_interval=2.0,
        history_length=500,
        enable_cpu_monitoring=True,
        enable_memory_monitoring=True,
        enable_network_monitoring=True,
        enable_disk_monitoring=True,
        alert_thresholds={
            'cpu_cpu_percent': 80.0,
            'memory_memory_percent': 85.0
        },
        enable_alerts=True,
        enable_logging=True
    )
    
    # Create performance monitor
    monitor = PerformanceMonitor(config)
    
    # Add alert callback
    def alert_callback(alert):
        print(f"ALERT: {alert.message}")
    
    monitor.add_alert_callback(alert_callback)
    
    # Start monitoring
    monitor.start_monitoring()
    
    try:
        # Simulate some work
        for i in range(30):
            # Simulate CPU-intensive work
            if i % 5 == 0:
                # Simulate high CPU usage
                for _ in range(1000000):
                    _ = 1 + 1
            
            # Print current metrics every 10 seconds
            if i % 5 == 0:
                current_metrics = monitor.get_current_metrics()
                print(f"Current metrics: {current_metrics}")
            
            time.sleep(2)
        
        # Generate performance report
        report = monitor.get_performance_report()
        print(f"Performance report: {report['summary']}")
        
        # Export data
        monitor.export_data("performance_export.json")
        
        # Plot metrics
        monitor.plot_metrics(save_path="performance_plot.png")
        
    except KeyboardInterrupt:
        print("\nStopping performance monitor...")
    
    finally:
        # Stop monitoring
        monitor.stop_monitoring()
        
        print("Performance monitoring completed!")
