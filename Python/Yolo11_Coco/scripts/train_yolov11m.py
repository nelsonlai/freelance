#!/usr/bin/env python3
"""
Train Ultralytics YOLOv11m on the COCO dataset stored in ./data/coco.

Example:
    python scripts/train_yolov11m.py --epochs 150 --imgsz 1280 --device 0
"""
from __future__ import annotations

import argparse
from pathlib import Path

import torch
from ultralytics import YOLO


def choose_default_device() -> str:
    if torch.cuda.is_available():
        return "cuda:0"
    if getattr(torch.backends, "mps", None) and torch.backends.mps.is_available():
        return "mps"
    return "cpu"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Train YOLOv11m on COCO")
    parser.add_argument("--data", type=Path, default=Path("./data/coco/data.yaml"))
    parser.add_argument("--weights", type=str, default="yolo11m.pt")
    parser.add_argument("--epochs", type=int, default=100)
    parser.add_argument("--batch", type=int, default=64)
    parser.add_argument("--imgsz", type=int, default=960)
    parser.add_argument(
        "--device",
        type=str,
        default=choose_default_device(),
        help="Training device (auto-detects CUDA, then MPS, then CPU)",
    )
    parser.add_argument(
        "--project",
        type=Path,
        default=Path("runs/train"),
        help="Output directory that Ultralytics will use",
    )
    parser.add_argument(
        "--name",
        type=str,
        default="yolo11m-coco",
        help="Training run name under the project directory",
    )
    parser.add_argument(
        "--resume",
        action="store_true",
        help="Resume training from the latest checkpoint when available",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    data_yaml = args.data

    if not data_yaml.exists():
        raise FileNotFoundError(
            f"Could not find {data_yaml}. Run scripts/setup_coco.py first."
        )

    model = YOLO(args.weights)
    results = model.train(
        data=str(data_yaml),
        epochs=args.epochs,
        imgsz=args.imgsz,
        batch=args.batch,
        device=args.device,
        project=str(args.project),
        name=args.name,
        resume=args.resume,
    )

    print(results)
    print(f"[success] Training artifacts saved under {args.project/args.name}")


if __name__ == "__main__":
    main()

