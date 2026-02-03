#!/usr/bin/env python3
"""
Download and extract the COCO 2017 dataset plus the default Ultralytics data.yaml
into ./data/coco so it can be consumed by YOLOv11 training scripts.

Example usage:
    python scripts/setup_coco.py --root ./data/coco --splits train val test

This script avoids re-downloading files that already exist and prints clear
progress so users can track long operations.
"""
from __future__ import annotations

import argparse
import tarfile
from pathlib import Path
from typing import Iterable, Optional
from urllib.request import urlretrieve

COCO_BASE_URL = "http://images.cocodataset.org"
COCO_SPLITS = {
    "train": "zips/train2017.zip",
    "val": "zips/val2017.zip",
    "test": "zips/test2017.zip",
    "annotations": "annotations/annotations_trainval2017.zip",
}

DATA_YAML_URL = (
    "https://raw.githubusercontent.com/ultralytics/ultralytics/main/ultralytics/"
    "cfg/datasets/coco.yaml"
)

# Ultralytics assets release containing COCO labels (segments)
LABELS_SEGMENTS_URL = (
    "https://github.com/ultralytics/assets/releases/download/v0.0.0/"
    "coco2017labels-segments.zip"
)


def download_file(url: str, destination: Path) -> None:
    destination.parent.mkdir(parents=True, exist_ok=True)
    if destination.exists():
        print(f"[skip] {destination.name} already exists")
        return
    print(f"[download] {url} -> {destination}")
    urlretrieve(url, destination)
    print(f"[done] {destination}")


def extract_archive(
    archive_path: Path, dest_dir: Path, marker: Optional[Path] = None
) -> None:
    marker = marker or dest_dir
    if marker.exists():
        print(f"[skip] {marker} already exists")
        return

    print(f"[extract] {archive_path.name} into {dest_dir}")
    dest_dir.mkdir(parents=True, exist_ok=True)

    if archive_path.suffix == ".zip":
        import zipfile

        with zipfile.ZipFile(archive_path, "r") as zf:
            zf.extractall(dest_dir)
    elif archive_path.suffix in {".tar", ".gz"}:
        with tarfile.open(archive_path, "r:*") as tf:
            tf.extractall(dest_dir)
    else:
        raise ValueError(f"Unsupported archive format: {archive_path}")


def ensure_coco_structure(root: Path, splits: Iterable[str]) -> None:
    downloads_dir = root / "downloads"
    extracts_dir = root
    for split in splits:
        uri = COCO_SPLITS.get(split)
        if uri is None:
            raise ValueError(f"Unknown split '{split}'")

        archive_path = downloads_dir / Path(uri).name
        download_file(f"{COCO_BASE_URL}/{uri}", archive_path)

        marker_name = "annotations" if split == "annotations" else Path(uri).stem
        marker_path = root / marker_name
        extract_archive(archive_path, extracts_dir, marker=marker_path)
        print(f"[ready] {marker_path}")


def ensure_data_yaml(root: Path) -> None:
    yaml_path = root / "data.yaml"
    download_file(DATA_YAML_URL, yaml_path)


def ensure_labels_segments(root: Path) -> None:
    """
    Download and extract COCO2017 labels (segments) under root/labels/*.
    Keeps the archive in root/downloads for reuse.
    """
    downloads_dir = root / "downloads"
    archive_path = downloads_dir / "coco2017labels-segments.zip"
    download_file(LABELS_SEGMENTS_URL, archive_path)
    marker = root / "labels"
    extract_archive(archive_path, root, marker=marker)
    print(f"[ready] {marker}")


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Prepare COCO dataset for YOLOv11")
    parser.add_argument(
        "--root",
        default=Path("./data/coco"),
        type=Path,
        help="Target directory where COCO data will be stored",
    )
    parser.add_argument(
        "--splits",
        nargs="+",
        default=["train", "val", "test", "annotations"],
        help="Dataset splits to download",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    root: Path = args.root

    print(f"[info] Preparing COCO at {root.resolve()}")
    print("[step] Downloading ZIP archives (stored under downloads/ for reuse)")
    ensure_coco_structure(root, args.splits)
    print("[step] Downloading labels (segments)")
    ensure_labels_segments(root)
    print("[step] Fetching data.yaml definition")
    ensure_data_yaml(root)
    print("[success] COCO dataset ready! Archives remain in downloads/ for reuse.")


if __name__ == "__main__":
    main()

