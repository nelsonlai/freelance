# Deep Learning: Comprehensive Description and Neural Network Architectures

## 1. What Is Deep Learning?

**Deep learning** is a subset of machine learning based on **artificial neural networks** with many layers (“deep” networks). These models learn **hierarchical representations** of data: early layers capture low-level patterns (edges, textures, local shapes), and deeper layers combine them into higher-level, abstract concepts (objects, scenes, meanings).

### Core Ideas

- **Neurons and layers:** A neuron computes a weighted sum of its inputs, adds a bias, and passes the result through a **non-linear activation function** (ReLU, Sigmoid, etc.). Layers are stacked so the output of one becomes the input of the next.
- **Learning:** The network is trained by **minimizing a loss function** (e.g. cross-entropy, MSE) using **gradient descent**. **Backpropagation** computes the gradient of the loss with respect to every parameter; an **optimizer** (SGD, Adam) updates the weights.
- **Depth:** More layers allow more levels of abstraction and, in principle, more complex functions—at the cost of more data, compute, and risk of overfitting.

### Deep Learning vs. Traditional ML

| Aspect | Traditional ML | Deep Learning |
|--------|----------------|---------------|
| Features | Hand-designed (feature engineering) | Often learned from raw or lightly processed data |
| Data | Can work with smaller datasets | Usually needs large amounts of data |
| Compute | Typically less | Often requires GPUs and long training |
| Best for | Tabular, small/medium data, interpretability | Images, text, speech, sequences, large data |

---

## 2. Multilayer Perceptron (MLP)

### What It Is

An **MLP** is a **fully connected** (dense) neural network: each neuron in one layer is connected to every neuron in the next. It is the simplest and most generic deep architecture.

### Architecture

```
Input Layer  →  Hidden Layer 1  →  Hidden Layer 2  →  ...  →  Output Layer
   (n)              (h1)                (h2)                    (classes or 1)
```

- **Input layer:** One unit per input feature (no activation, or identity).
- **Hidden layers:** Each unit: \( y = f(Wx + b) \), where \( f \) is ReLU, Sigmoid, Tanh, etc.
- **Output layer:**  
  - **Regression:** one linear unit.  
  - **Classification:** one unit per class + Softmax (or one unit + Sigmoid for binary).

### How It Works

1. **Forward pass:** Data flows layer by layer; each layer applies \( Wx + b \) and an activation.
2. **Loss:** Compare predictions to targets (e.g. cross-entropy, MSE).
3. **Backpropagation:** Compute \( \frac{\partial L}{\partial W} \) for every \( W \).
4. **Update:** \( W \leftarrow W - \alpha \frac{\partial L}{\partial W} \) (or via Adam, etc.).

### Strengths and Limitations

- **Strengths:** Simple, flexible, works for tabular data and general vector inputs; easy to implement.
- **Limitations:** No built-in notion of **spatial structure** (images) or **temporal order** (sequences); all inputs are treated as a flat vector. For images and sequences, **CNN** and **RNN/Transformers** are usually better.

### Typical Use Cases

- Tabular classification/regression
- Small images or flattened vectors when CNN is overkill
- Final “head” on top of CNN/RNN/Transformer embeddings

---

## 3. Convolutional Neural Networks (CNN) — for Images

### What It Is

A **CNN** uses **convolutional layers** that slide small **filters (kernels)** over the input. This exploits **translation invariance**: the same pattern (e.g. an edge) is detected regardless of where it appears in the image.

### Main Building Blocks

#### Convolutional Layer

- **Filter:** A small matrix (e.g. 3×3, 5×5) of learnable weights.
- **Operation:** At each position, compute the element-wise product of the filter with the local patch and sum → one value in the **feature map**.
- **Multiple filters:** Each filter produces one feature map; many filters → many channels.
- **Stride:** How many pixels the filter moves each step (1 = dense; 2 = downsample).
- **Padding:** Extra pixels around the border to control output size.

#### Pooling Layer

- **Max pooling:** Replace a small region (e.g. 2×2) with its maximum → reduces size and adds slight invariance to small shifts.
- **Average pooling:** Replace with the mean.

#### Typical CNN Layout

```
Input (H×W×C) → [Conv → ReLU → Pool] × N → Flatten → Dense → Output
```

Example: **LeNet, AlexNet, VGG, ResNet** — all follow this pattern with different depths and tricks (batch norm, skip connections, etc.).

### How It Works (Intuition)

1. **Early layers:** Detect edges, corners, simple textures (low-level).
2. **Middle layers:** Combine them into parts (e.g. eyes, wheels).
3. **Late layers:** Combine parts into objects (e.g. face, car).
4. **Classifier:** Flatten and pass through an MLP to get class scores.

### Strengths and Limitations

- **Strengths:** Parameter sharing (fewer parameters than a fully connected net on raw pixels); good at images and any data with local, grid-like structure (e.g. some time series).
- **Limitations:** Not designed for long-range dependencies across the whole input or for **sequential order** in the same way as RNNs/Transformers. For pure sequences, RNN/LSTM or Transformers are preferred.

### Typical Use Cases

- Image classification, object detection, segmentation
- Medical imaging, satellite imagery
- Sometimes used for 1D signals (e.g. audio, time series) via 1D convolutions

---

## 4. Recurrent Neural Networks (RNN) and LSTM — for Sequences

### What They Are

**RNNs** process **sequences** (time series, text, audio) by maintaining a **hidden state** that is updated at each time step as new inputs arrive. The same weights are reused across time (**recurrence**).

### Vanilla RNN

- **Update:** \( h_t = f(W_{hh} h_{t-1} + W_{xh} x_t + b) \)
- **Output (optional):** \( y_t = W_{hy} h_t \) (e.g. predict next token or a label at the end).
- **Problem:** **Vanishing/exploding gradients** when the sequence is long; the signal has to pass through many repeated multiplications by \( W_{hh} \), so it often dies or blows up.

### Long Short-Term Memory (LSTM)

**LSTM** fixes the long-range dependency problem with **gates** that control what is stored, forgotten, and read from the **cell state** \( c_t \).

#### Main Components

- **Forget gate:** \( f_t = \sigma(W_f [h_{t-1}, x_t] + b_f) \) — how much of \( c_{t-1} \) to forget.
- **Input gate:** \( i_t = \sigma(W_i [h_{t-1}, x_t] + b_i) \), \( \tilde{c}_t = \tanh(W_c [h_{t-1}, x_t] + b_c) \) — what to add to the cell.
- **Cell update:** \( c_t = f_t \odot c_{t-1} + i_t \odot \tilde{c}_t \).
- **Output gate:** \( o_t = \sigma(W_o [h_{t-1}, x_t] + b_o) \), \( h_t = o_t \odot \tanh(c_t) \).

Here \( \sigma \) is Sigmoid, \( \odot \) is element-wise product. The cell \( c_t \) acts as a “memory” that can carry information over many steps with less gradient decay.

### How It Works (Intuition)

- At each step \( t \), the model sees \( x_t \) and the previous hidden state \( h_{t-1} \) (and in LSTM, \( c_{t-1} \)).
- It decides what to remember, what to forget, and what to output.
- The final \( h_T \) (or a sequence of \( h_t \)) is used for prediction (e.g. classification, next-step prediction).

### Strengths and Limitations

- **Strengths:** Natural for sequences and variable length; LSTM handles long-range dependencies better than vanilla RNN.
- **Limitations:** Sequential by design — step \( t \) must wait for \( t-1 \), so **hard to parallelize** over time. For very long sequences and when maximum accuracy is needed, **Transformers** often outperform.

### Typical Use Cases

- Text classification, sentiment, named-entity recognition (when used as a feature extractor)
- Time-series forecasting, speech, video
- Machine translation and sequence-to-sequence (often replaced by Transformers today)

---

## 5. Transformers (GPT, BERT, etc.)

### What They Are

**Transformers** are built around **self-attention**: at each position, the model computes a weighted combination of **all** other positions. There is **no recurrence**; the only “memory” is the set of representations at all positions. This allows **full parallelization** over the sequence and often better modeling of long-range dependencies.

### Self-Attention (Simplified)

For each token, we compute:

- **Query** \( q = W_Q x \)
- **Key** \( k = W_K x \)
- **Value** \( v = W_V x \)

For a given query \( q_i \), we score against all keys \( k_j \), normalize with Softmax, and take a weighted sum of values \( v_j \):

\[
\text{Attention}(q_i, K, V) = \sum_j \text{softmax}\left(\frac{q_i^\top k_j}{\sqrt{d_k}}\right) v_j
\]

So each position can “attend to” every other position. **Multi-head attention** runs several such mechanisms in parallel and concatenates the outputs.

### Architecture (High Level)

- **Input:** Token embeddings + positional encodings (to inject order, since there is no recurrence).
- **Encoder/Decoder blocks:** Each block typically has:
  - **Multi-head self-attention**
  - **Add & Norm** (residual + layer norm)
  - **Feed-forward (MLP)**
  - **Add & Norm**
- **Decoder-only (GPT-style):** Only decoder blocks, with **masked** self-attention (each position sees only past tokens) → good for **generation**.
- **Encoder-only (BERT-style):** Only encoder blocks, full self-attention → good for **understanding** and **classification/feature extraction**.
- **Encoder–Decoder (T5, original Transformer):** Both; cross-attention from decoder to encoder → good for **translation, summarization**.

### GPT (Decoder-Only)

- **Model:** Decoder-only Transformer; each token attends only to previous tokens.
- **Training:** Next-token prediction (language modeling).
- **Use:** **Text generation**, completion, chat; can be adapted via fine-tuning or prompting for QA, summarization, etc.
- **Examples:** GPT-2, GPT-3, GPT-4, LLaMA.

### BERT (Encoder-Only)

- **Model:** Encoder-only Transformer; each token attends to all tokens (within length limits).
- **Training:** **Masked language modeling (MLM)** — predict randomly masked tokens — plus often **next-sentence prediction (NSP)**.
- **Use:** **Classification** (sentiment, NLI, etc.), **feature extraction** (use [CLS] or token representations), **NER, QA**, and as a backbone for many NLP tasks.
- **Examples:** BERT, RoBERTa, ALBERT, DeBERTa.

### How It Works (Intuition)

- **Self-attention:** Lets each token “look at” the whole context and decide what is relevant.
- **No recurrence:** All positions can be computed in parallel → fast on GPUs.
- **Positional encoding:** Adds information about order so the model knows sequence structure.

### Strengths and Limitations

- **Strengths:** State-of-the-art on many NLP and some vision tasks; highly parallel; excellent long-range modeling; huge ecosystem of pre-trained models (Hugging Face).
- **Limitations:** **Quadratic** cost in sequence length (for full self-attention); needs a lot of data and compute for pre-training; can be overkill for small, simple tasks.

### Typical Use Cases

- **GPT-style:** Text generation, dialogue, code generation, creative writing.
- **BERT-style:** Text classification, NLI, NER, QA, search, sentence embeddings, fine-tuning for domain tasks.

---

## 6. Summary: When to Use Which

| Model | Best For | Input Structure | Main Idea |
|-------|----------|-----------------|-----------|
| **MLP** | Tabular, generic vectors | Flat feature vector | Fully connected; no inductive bias for space or time |
| **CNN** | Images, grid-like data | Grids (H×W×C) | Convolutions + pooling; translation invariance |
| **RNN/LSTM** | Sequences (text, time, speech) | Ordered sequence | Recurrence; hidden state over time; LSTM gates for long memory |
| **Transformers** | Text, sometimes vision, long sequences | Token/sequence | Self-attention over all positions; parallel; GPT=generate, BERT=understand |

---

## 7. How to Use the Python Code

The file **`03_Deep_Learning_Models.py`** contains runnable examples:

1. **MLP:** Build and train a small MLP on a toy or tabular dataset with PyTorch.
2. **CNN:** Build and train a CNN on **MNIST** (or similar) with PyTorch.
3. **RNN/LSTM:** Build and train an RNN/LSTM on **sequence data** with PyTorch.
4. **Transformers:** Use the **Hugging Face `transformers`** library to:
   - **GPT-2:** Generate text.
   - **BERT:** Extract features or run a classification pipeline.

**Dependencies:** `torch`, `torchvision`, `transformers`. Install:

```bash
pip install torch torchvision transformers
# or: pip install -r requirements.txt
```

**Run:**

```bash
python 03_Deep_Learning_Models.py
```

**Note:** First run will download MNIST (~10MB) for the CNN demo, and GPT-2 / BERT / DistilBERT (~500MB+) for the Transformers demo. For **GPU:** install a CUDA-enabled PyTorch build if you have a compatible GPU; the code will run on CPU (or MPS on Apple Silicon) otherwise.

---

*Part of the teaching project on feature engineering, deep learning, and machine learning.*
