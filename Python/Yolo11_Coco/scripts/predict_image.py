#!/usr/bin/env python3
"""
Run inference on a single image using trained YOLOv11 weights and save/display results.

Example:
    python scripts/predict_image.py --weights runs/train/yolo11m-coco/weights/best.pt \\
        --source samples/bus.jpg --save --show
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
    parser = argparse.ArgumentParser(description="Predict objects in an image with YOLO")
    parser.add_argument("--weights", type=Path, required=True, help="Model weights path")
    parser.add_argument("--source", type=Path, required=True, help="Image to predict")
    parser.add_argument(
        "--save_dir",
        type=Path,
        default=Path("runs/predict"),
        help="Where to save annotated results",
    )
    parser.add_argument(
        "--conf",
        type=float,
        default=0.45,
        help="Confidence threshold for detections",
    )
    parser.add_argument(
        "--device",
        type=str,
        default=choose_default_device(),
        help="Inference device (auto-detects CUDA>MPS>CPU)",
    )
    parser.add_argument(
        "--show",
        action="store_true",
        help="Display the prediction window (requires GUI backend)",
    )
    parser.add_argument(
        "--save",
        action="store_true",
        help="Persist annotated image to the save_dir",
    )
    return parser.parse_args()


def format_result(result) -> str:
    """Return a readable summary for a single ultralytics result object."""
    parts = [f"image: {result.path}", f"detections: {len(result.boxes)}"]
    for box in result.boxes:
        cls = int(box.cls)
        conf = float(box.conf)
        xyxy = box.xyxy.squeeze().tolist()
        parts.append(f"  - cls={cls} conf={conf:.2f} box={xyxy}")
    return "\n".join(parts)


def main() -> None:
    args = parse_args()
    weights: Path = args.weights
    source: Path = args.source

    if not weights.exists():
        raise FileNotFoundError(f"Weights not found: {weights}")
    if not source.exists():
        raise FileNotFoundError(f"Image not found: {source}")

    model = YOLO(str(weights))
    results = model.predict(
        source=str(source),
        conf=args.conf,
        device=args.device,
        save=args.save,
        save_dir=str(args.save_dir),
        show=args.show,
    )

    for res in results:
        print(format_result(res))

    if args.save:
        print(f"[success] Annotated images saved to {args.save_dir}")


if __name__ == "__main__":
    main()

