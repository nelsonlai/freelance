"""
Setup script for OCPP 2.1 Implementation

This script allows the OCPP 2.1 implementation to be installed as a Python package.
"""

from setuptools import setup, find_packages
import os

# Read the README file
def read_readme():
    with open("README.md", "r", encoding="utf-8") as fh:
        return fh.read()

# Read requirements
def read_requirements():
    with open("requirements.txt", "r", encoding="utf-8") as fh:
        return [line.strip() for line in fh if line.strip() and not line.startswith("#")]

setup(
    name="ocpp-2.1-implementation",
    version="1.0.0",
    author="OCPP Implementation Team",
    author_email="team@ocpp-implementation.com",
    description="A comprehensive OCPP 2.1 implementation with CSMS server and CP client",
    long_description=read_readme(),
    long_description_content_type="text/markdown",
    url="https://github.com/ocpp-implementation/ocpp-2.1",
    packages=find_packages(),
    classifiers=[
        "Development Status :: 4 - Beta",
        "Intended Audience :: Developers",
        "Intended Audience :: Education",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.8",
        "Programming Language :: Python :: 3.9",
        "Programming Language :: Python :: 3.10",
        "Programming Language :: Python :: 3.11",
        "Topic :: Communications",
        "Topic :: Education",
        "Topic :: Internet :: WWW/HTTP :: Dynamic Content",
        "Topic :: Software Development :: Libraries :: Python Modules",
        "Topic :: System :: Networking",
    ],
    python_requires=">=3.8",
    install_requires=read_requirements(),
    extras_require={
        "dev": [
            "pytest>=7.4.0",
            "pytest-asyncio>=0.21.0",
            "pytest-cov>=4.1.0",
            "black>=23.0.0",
            "flake8>=6.0.0",
            "mypy>=1.5.0",
            "pre-commit>=3.3.0",
        ],
        "docs": [
            "sphinx>=7.0.0",
            "sphinx-rtd-theme>=1.3.0",
            "myst-parser>=2.0.0",
        ],
        "optional": [
            "redis>=4.6.0",
            "celery>=5.3.0",
            "prometheus-client>=0.17.0",
            "grafana-api>=1.0.3",
            "elasticsearch>=8.8.0",
            "kafka-python>=2.0.2",
        ],
    },
    entry_points={
        "console_scripts": [
            "ocpp-csms-server=examples.csms_server_example:main",
            "ocpp-cp-client=examples.cp_client_example:main",
            "ocpp-integration-test=examples.integration_test:main",
        ],
    },
    include_package_data=True,
    package_data={
        "ocpp": ["schemas/*.json"],
    },
    keywords="ocpp, charging, electric vehicle, evse, csms, charge point",
    project_urls={
        "Bug Reports": "https://github.com/ocpp-implementation/ocpp-2.1/issues",
        "Source": "https://github.com/ocpp-implementation/ocpp-2.1",
        "Documentation": "https://ocpp-implementation.readthedocs.io/",
    },
)
