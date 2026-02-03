## Ultralytics Installation Guide (Ubuntu, Windows, macOS Apple Silicon)

This guide shows how to install the official `ultralytics` package via pip and how to decide whether you need CUDA. CUDA is optional and only required for NVIDIA GPU acceleration on Linux/Windows PCs with NVIDIA GPUs. Apple Silicon uses Metal (MPS) instead of CUDA.

### 1) Prerequisites

- Python 3.8–3.12 recommended - (3.10)
- pip up to date

Update pip:

```bash
python -m pip install --upgrade pip
```

Optional but recommended: use a virtual environment.

```bash
# Ubuntu/macOS
python -m venv .venv && source .venv/bin/activate
# Windows (PowerShell)
python -m venv .venv; .\.venv\Scripts\Activate.ps1
```

### 2) Install Ultralytics

Works on all platforms the same way:

```bash
python -m pip install ultralytics
```

To include common extras (OpenCV, etc.), you can also:

```bash
python -m pip install "ultralytics[all]"
```

### 3) Verify Installation

Run:

```bash
python -c "import ultralytics, torch; print('ultralytics', ultralytics.__version__, '| torch', torch.__version__)"
```

You should see versions printed without errors.

### 4) Do I need CUDA?

- If you have an NVIDIA GPU (Windows/Ubuntu): CUDA enables much faster training/inference.
- If you’re on macOS Apple Silicon (M1/M2/M3): No CUDA; PyTorch uses Apple’s Metal (MPS).
- If you’re on CPU-only hardware: CUDA is not applicable.

#### Quick checks

- Ubuntu/Windows with NVIDIA GPU:

  - Check driver: `nvidia-smi` (should show GPU details if installed).
  - Check PyTorch sees CUDA:
    ```bash
    python -c "import torch; print('cuda_available=', torch.cuda.is_available())"
    ```
  - If `cuda_available=False` and you have an NVIDIA GPU, install a CUDA-enabled PyTorch build from the official selector: `https://pytorch.org/get-started/locally/`
    - Example (CUDA 12.x, Linux):
      ```bash
      python -m pip install --index-url https://download.pytorch.org/whl/cu121 torch torchvision torchaudio
      ```
    - Example (CUDA 12.x, Windows):
      ```bash
      python -m pip install --index-url https://download.pytorch.org/whl/cu121 torch torchvision torchaudio
      ```
    - Then reinstall Ultralytics if needed:
      ```bash
      python -m pip install --upgrade ultralytics
      ```
- macOS Apple Silicon (M1/M2/M3):

  - No CUDA. Ensure PyTorch is the MPS-enabled build (default for Apple Silicon):
    ```bash
    python -c "import torch; print('mps_available=', hasattr(torch.backends, 'mps') and torch.backends.mps.is_available())"
    ```
  - In Ultralytics scripts you can set `--device mps` or allow auto-detection if implemented.

### 5) Troubleshooting

- Multiple Pythons: confirm you’re using the intended interpreter:
  ```bash
  which python  # Ubuntu/macOS
  Get-Command python  # Windows PowerShell
  ```
- Permissions issues on Ubuntu/macOS:
  - Prefer virtual environments; avoid `sudo pip`.
- Conflicting OpenCV builds:
  ```bash
  python -m pip install --upgrade --force-reinstall opencv-python
  ```
- Clean reinstall (last resort):
  ```bash
  python -m pip uninstall -y ultralytics torch torchvision torchaudio
  python -m pip install ultralytics
  ```

### 6) Minimal Sanity Test

After install:

```bash
yolo checks
```

Or quick Python:

```bash
python - << 'PY'
from ultralytics import YOLO
import torch
print('torch.cuda.is_available =', torch.cuda.is_available())
print('mps.available =', hasattr(torch.backends, 'mps') and torch.backends.mps.is_available())
model = YOLO('yolo11n.pt')  # downloads small model
res = model.predict(source='https://ultralytics.com/images/bus.jpg', imgsz=640)
print('ok, predictions:', len(res))
PY
```

If this completes without errors, your installation is good.

### 7) COCO 2017 Dataset Layout (images and labels)

When using the built-in COCO 2017 dataset with Ultralytics, images are stored in split-named folders and YOLO-format labels are stored under a parallel `labels` tree:

```
./data/coco/
├── train2017/                # training images (*.jpg)
├── val2017/                  # validation images (*.jpg)
├── test2017/                 # test images (*.jpg)
├── annotations/              # official COCO JSONs (instances_*.json, etc.)
└── labels/                   # YOLO TXT labels mirroring image splits
    ├── train2017/            # labels for train images (*.txt)
    ├── val2017/              # labels for val images (*.txt)
    └── test2017/             # optional labels for test (usually none)
```

Notes:

- `scripts/setup_coco.py` downloads/extracts:
  - Images into `./data/coco/train2017`, `./data/coco/val2017`, `./data/coco/test2017`
  - COCO JSONs into `./data/coco/annotations`
  - Segmented YOLO labels into `./data/coco/labels/...`
- Some archives include a top-level `coco/` folder. If you see `./data/coco/coco/labels/...`, move the inner `labels` up one level:
  ```bash
  mv ./data/coco/coco/labels ./data/coco/labels
  rmdir ./data/coco/coco 2>/dev/null || true
  ```
- Ultralytics’ default `coco.yaml` maps to this layout; our training script points to `./data/coco/data.yaml`.

### 8) Adjusting `data.yaml` to match your folders

Ultralytics datasets are controlled by three keys in `data.yaml`:

```
path: coco               # root folder for the dataset (relative to data.yaml)
train: train2017.txt     # images for training (relative to 'path' if it's a file name)
val: val2017.txt         # images for validation
test: test-dev2017.txt   # (optional) images for test
```

You can set each split in one of three ways:

- A directory containing images (e.g., `train: train2017`)
- A text file with absolute/relative image paths, one per line (e.g., `train: train2017.txt`)
- A list of directories or txt files (e.g., `train: [dirA, dirB]`)

Common edits:

1) Move dataset under `./data/coco` (recommended)

```
path: ./data/coco
train: train2017.txt
val: val2017.txt
test: test2017.txt
```

2) Point directly to image folders instead of txt files

```
path: ./data/coco
train: train2017
val: val2017
test: test2017
```

3) Use absolute paths (no need for `path`)

```
train: /abs/path/to/train/images
val: /abs/path/to/val/images
test: /abs/path/to/test/images
```

Labels location:

- YOLO looks for labels under a parallel `labels/<split>` directory relative to each split’s images.
- If your images are in `./data/coco/train2017`, labels should be in `./data/coco/labels/train2017`.
- If you use txt files with absolute image paths, ensure the corresponding label files exist in a mirrored `labels/...` structure.

Tip:

- Keep `data.yaml` next to your dataset root or use absolute paths to avoid confusion.
- After editing, run a quick check:
  ```
  yolo data=./data/coco/data.yaml task=detect mode=checks
  ```
