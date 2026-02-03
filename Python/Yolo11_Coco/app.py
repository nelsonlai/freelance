#!/usr/bin/env python3
"""
Gradio deployment for YOLOv11m COCO model.

Features:
- Upload or drag an image
- Animated spinner while predictions run
- Display original + annotated image plus detection metadata
"""
from __future__ import annotations

from functools import lru_cache
from pathlib import Path
from typing import Any, Dict, List

import gradio as gr
import numpy as np
from PIL import Image
from ultralytics import YOLO

DEFAULT_WEIGHTS = Path("runs/train/yolo11m-coco/weights/best.pt")
SPINNER_HTML = """
<div class="spinner"></div>
<style>
.spinner {
  border: 6px solid #e0e0e0;
  border-top: 6px solid #ff6a00;
  border-radius: 50%;
  width: 52px;
  height: 52px;
  animation: spin 0.9s linear infinite;
  margin: 12px auto;
}
@keyframes spin {
  0% { transform: rotate(0deg); }
  100% { transform: rotate(360deg); }
}
</style>
"""


@lru_cache(maxsize=2)
def load_model(weights_path: str) -> YOLO:
    path = Path(weights_path).expanduser()
    if not path.exists():
        raise FileNotFoundError(
            f"Could not locate weights at {path}. Train the model or update the path."
        )
    return YOLO(str(path))


def summarize_result(result) -> List[Dict[str, Any]]:
    out = []
    names = result.names
    for box in result.boxes:
        cls_id = int(box.cls)
        out.append(
            {
                "class_id": cls_id,
                "class_name": names.get(cls_id, "unknown"),
                "confidence": round(float(box.conf), 4),
                "xyxy": [round(float(v), 2) for v in box.xyxy.squeeze().tolist()],
            }
        )
    return out


def run_inference(image: Image.Image, conf: float, weights: str):
    model = load_model(weights)
    results = model.predict(image, conf=conf)
    if not results:
        raise RuntimeError("No results returned from YOLO prediction.")

    result = results[0]
    annotated = Image.fromarray(result.plot()[:, :, ::-1])
    metadata = summarize_result(result)
    return annotated, metadata, gr.update(visible=False)


def build_interface() -> gr.Blocks:
    with gr.Blocks(title="YOLOv11m COCO Demo") as demo:
        gr.Markdown(
            "### YOLOv11m COCO\nUpload an image to run inference with the Ultralytics "
            "YOLOv11m model trained on COCO."
        )

        with gr.Row():
            with gr.Column(scale=1):
                image_input = gr.Image(type="pil", label="Input image", height=360)
                conf_slider = gr.Slider(
                    minimum=0.1,
                    maximum=0.9,
                    value=0.25,
                    step=0.05,
                    label="Confidence threshold",
                )
                weight_box = gr.Textbox(
                    value=str(DEFAULT_WEIGHTS),
                    label="Weights path",
                    placeholder="runs/train/yolo11m-coco/weights/best.pt",
                )
                predict_btn = gr.Button("Predict", variant="primary")
                spinner = gr.HTML(SPINNER_HTML, visible=False)
            with gr.Column(scale=1):
                with gr.Tab("Original"):
                    original_view = gr.Image(type="pil", label="Original", height=360)
                with gr.Tab("Prediction"):
                    prediction_view = gr.Image(
                        type="pil", label="Annotated prediction", height=360
                    )
                metadata_view = gr.JSON(label="Detections")

        # Ensure the original preview mirrors uploads
        image_input.change(fn=lambda img: img, inputs=image_input, outputs=original_view)

        # Show spinner immediately, then run inference
        predict_btn.click(
            fn=lambda: gr.update(visible=True), inputs=None, outputs=spinner
        ).then(
            fn=run_inference,
            inputs=[image_input, conf_slider, weight_box],
            outputs=[prediction_view, metadata_view, spinner],
        )

        gr.Examples(
            examples=[["bus.jpg"], ["toothbrush.jpg"]],
            inputs=image_input,
            label="Sample images (stored in project root)",
        )

    return demo


if __name__ == "__main__":
    build_interface().queue().launch()

