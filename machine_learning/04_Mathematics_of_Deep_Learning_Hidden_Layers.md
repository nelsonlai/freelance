# Mathematics of Deep Learning: Hidden Layers

A comprehensive reference for the mathematical operations and formulas used in the hidden layers of neural networks.

---

## 1. Linear (Affine) Transformation

The core of most layers: a linear map followed by an optional bias.

### Formula

For input \(\mathbf{x} \in \mathbb{R}^d\), weights \(\mathbf{W} \in \mathbb{R}^{m \times d}\), bias \(\mathbf{b} \in \mathbb{R}^m\):

$$
\mathbf{z} = \mathbf{W} \mathbf{x} + \mathbf{b}
\quad \Leftrightarrow \quad
z_i = \sum_{j=1}^{d} W_{ij} x_j + b_i
$$

- **Matrix view:** \(\mathbf{z} = \mathbf{W}\mathbf{x} + \mathbf{b}\)
- **Batch of \(N\) samples:** \(\mathbf{X} \in \mathbb{R}^{N \times d} \;\Rightarrow\; \mathbf{Z} = \mathbf{X}\mathbf{W}^\top + \mathbf{b}\) (broadcast)

### Jacobian (for backprop)

$$
\frac{\partial \mathbf{z}}{\partial \mathbf{x}} = \mathbf{W}^\top
\,,\qquad
\frac{\partial \mathbf{z}}{\partial \mathbf{W}} = \mathbf{x}^\top
\,,\qquad
\frac{\partial \mathbf{z}}{\partial \mathbf{b}} = \mathbf{I}
$$

---

## 2. Activation Functions

Apply a **non-linear** function \(\sigma\) element-wise: \(\mathbf{a} = \sigma(\mathbf{z})\). Without \(\sigma\), stacking linear layers would be equivalent to one linear layer.

### 2.1 Sigmoid

$$
\sigma(z) = \frac{1}{1 + e^{-z}} = \frac{e^z}{1 + e^z}
$$

- **Range:** \((0,\ 1)\)
- **Derivative:** \(\sigma'(z) = \sigma(z)\,\big(1 - \sigma(z)\big)\)
- **Issue:** Saturates for \(|z|\) large; gradients vanish.

### 2.2 Hyperbolic Tangent (Tanh)

$$
\tanh(z) = \frac{e^z - e^{-z}}{e^z + e^{-z}} = \frac{e^{2z} - 1}{e^{2z} + 1}
$$

- **Range:** \((-1,\ 1)\)
- **Derivative:** \(\dfrac{d}{dz}\tanh(z) = 1 - \tanh^2(z)\)
- **Relation:** \(\tanh(z) = 2\sigma(2z) - 1\)

### 2.3 ReLU (Rectified Linear Unit)

$$
\mathrm{ReLU}(z) = \max(0,\, z) =
\begin{cases}
  z   & z \geq 0 \\[2pt]
  0   & z < 0
\end{cases}
$$

- **Derivative:** \(\dfrac{d}{dz}\,\mathrm{ReLU}(z) = \mathbf{1}_{z>0}\)
- **Pros:** No saturation for \(z > 0\); sparse; fast.
- **Con:** “Dead” neurons if \(z \leq 0\) always (gradient 0).

### 2.4 Leaky ReLU

$$
\mathrm{LeakyReLU}(z;\; \alpha) =
\begin{cases}
  z       & z \geq 0 \\[2pt]
  \alpha z & z < 0
\end{cases}
\,,\qquad \alpha \in (0,\,1) \ \ \text{(e.g. } 0.01\text{)}
$$

- **Derivative:** \(1\) if \(z \geq 0\), else \(\alpha\). Helps avoid dead neurons.

### 2.5 Parametric ReLU (PReLU)

Same as Leaky ReLU but \( \alpha \) is **learned** per channel or per element.

### 2.6 GELU (Gaussian Error Linear Unit)

$$
\mathrm{GELU}(z) = z \cdot \Phi(z) = z \cdot \frac{1}{2}\left(1 + \operatorname{erf}\Big(\frac{z}{\sqrt{2}}\Big)\right)
$$

where \(\Phi\) is the standard normal CDF and
\(\displaystyle \operatorname{erf}(x) = \frac{2}{\sqrt{\pi}} \int_0^x e^{-t^2} \, dt\).

- **Approximation:** \(\mathrm{GELU}(z) \approx \dfrac{z}{2}\left(1 + \tanh\big(\sqrt{2/\pi}\,(z + 0.044715\, z^3)\big)\right)\)
- Used in BERT, GPT, and many Transformers.

### 2.7 Swish / SiLU (Sigmoid Linear Unit)

$$
\mathrm{Swish}(z) = z \cdot \sigma(z) = \frac{z}{1 + e^{-z}}
$$

- **Derivative:** \(\sigma(z) + z \cdot \sigma(z)\big(1 - \sigma(z)\big) = \sigma(z) + z\,\sigma(z) - z\,\sigma^2(z)\)

### 2.8 Softplus (smooth ReLU)

$$
\mathrm{Softplus}(z) = \ln(1 + e^z)
$$

- **Derivative:** \(\sigma(z)\). Approximates ReLU but is smooth.

### 2.9 Softmax (often in output, sometimes in hidden)

For vector \(\mathbf{z} \in \mathbb{R}^K\):

$$
\mathrm{softmax}(z_i) = \frac{e^{z_i}}{\displaystyle\sum_{j=1}^{K} e^{z_j}}
$$

- **Range:** \((0,\ 1)\), and \(\displaystyle\sum_i \mathrm{softmax}(z_i) = 1\)
- **Numerically stable:** \(\mathrm{softmax}(z_i) = \dfrac{e^{z_i - \max_j z_j}}{\sum_j e^{z_j - \max_k z_k}}\)

---

## 3. Normalization Layers

Normalize statistics over certain dimensions, then scale and shift with learned parameters.

### 3.1 Batch Normalization (BatchNorm)

Over the **batch** dimension. For a layer output \(\mathbf{x} \in \mathbb{R}^{N \times C \times H \times W}\) (or \(N \times C\) for 1D):

**Per channel \(c\):**

$$
\hat{x}_{n,c} = \frac{x_{n,c} - \mu_c}{\sqrt{\sigma_c^2 + \epsilon}}
\,,\qquad
\mu_c = \frac{1}{N}\sum_n x_{n,c}
\,,\qquad
\sigma_c^2 = \frac{1}{N}\sum_n (x_{n,c} - \mu_c)^2
$$

**Output (scale & shift, learned \(\gamma_c,\, \beta_c\)):**

$$
y_{n,c} = \gamma_c \,\hat{x}_{n,c} + \beta_c
$$

- **At inference:** use running mean and variance from training.
- **Gradient:** involves \(\dfrac{\partial \hat{x}}{\partial x}\), \(\dfrac{\partial \hat{x}}{\partial \mu}\), \(\dfrac{\partial \hat{x}}{\partial \sigma^2}\).

### 3.2 Layer Normalization (LayerNorm)

Over the **feature** dimension. For \(\mathbf{x} \in \mathbb{R}^{N \times d}\), for each row \(\mathbf{x}_n\):

$$
\hat{x}_{n,i} = \frac{x_{n,i} - \mu_n}{\sqrt{\sigma_n^2 + \epsilon}}
\,,\qquad
\mu_n = \frac{1}{d}\sum_{i=1}^d x_{n,i}
\,,\qquad
\sigma_n^2 = \frac{1}{d}\sum_{i=1}^d (x_{n,i} - \mu_n)^2
$$

$$
y_{n,i} = \gamma_i \,\hat{x}_{n,i} + \beta_i
$$

- Used heavily in Transformers (after attention and after FFN).

### 3.3 Instance Normalization

Normalize over spatial dimensions for each sample and channel (e.g. per \( (H,W) \) for each \( (n,c) \)). Common in style transfer and some GANs.

### 3.4 Group Normalization

Split channels into groups; normalize within each group for each sample. Between BatchNorm and LayerNorm in how the axes are grouped.

---

## 4. Dropout

**Training:** for each element, keep with probability \(p\), else set to 0; then **scale** so expected value is unchanged:

$$
m_i \sim \mathrm{Bernoulli}(p)
\,,\qquad
y_i = \frac{m_i \cdot x_i}{p}
$$

- **Inference:** usually no dropout, or equivalently use \(y_i = x_i\) (no mask, no scaling).

**Variants:** DropConnect (drop weights), spatial dropout (drop whole channels or 2D maps).

---

## 5. Convolution (CNN Hidden Layers)

### 5.1 2D Discrete Convolution (Cross-Correlation)

Filter \(\mathbf{K} \in \mathbb{R}^{k_h \times k_w}\), input \(\mathbf{I} \in \mathbb{R}^{H \times W}\):

$$
(\mathbf{I} * \mathbf{K})_{i,j}
\;=\; \sum_{a=0}^{k_h-1} \sum_{b=0}^{k_w-1} I_{i+a,\,j+b} \cdot K_{a,b}
$$

(Strict convolution would flip \(\mathbf{K}\); in deep learning the “convolution” is usually this cross-correlation.)

### 5.2 With Stride and Padding

- **Stride \(s\):** output indices \((i,\,j)\) correspond to input starts \((s \cdot i,\ s \cdot j)\).
- **Padding \(p\):** pad \(\mathbf{I}\) with \(p\) on each side (e.g. zeros), then apply the formula.

**Output size (1D analogue for one dim):**

$$
H_{\mathrm{out}} = \left\lfloor \frac{H_{\mathrm{in}} + 2p - k}{s} \right\rfloor + 1
$$

### 5.3 Multi-Channel (3D)

Input \(\mathbf{I} \in \mathbb{R}^{C_{\mathrm{in}} \times H \times W}\), filters \(\mathbf{K} \in \mathbb{R}^{C_{\mathrm{out}} \times C_{\mathrm{in}} \times k_h \times k_w}\):

$$
(\mathbf{I} * \mathbf{K})_{c,i,j}
\;=\; \sum_{c'=1}^{C_{\mathrm{in}}} \sum_{a,b} I_{c',\,i+a,\,j+b} \cdot K_{c,c',a,b}
$$

### 5.4 1D Convolution (sequences)

For \(\mathbf{x} \in \mathbb{R}^{C \times L}\), kernel \(\mathbf{K} \in \mathbb{R}^{C_{\mathrm{out}} \times C \times k}\):

$$
(\mathbf{x} * \mathbf{K})_{c,\ell}
\;=\; \sum_{c'=1}^{C} \sum_{a=0}^{k-1} x_{c',\,\ell+a} \cdot K_{c,c',a}
$$

---

## 6. Pooling

### 6.1 Max Pooling

$$
y_{i,j} = \max_{(a,b) \in \mathcal{R}_{i,j}} x_{a,b}
$$

\(\mathcal{R}_{i,j}\) is the local window (e.g. \(2 \times 2\)) for output position \((i,\,j)\).

### 6.2 Average Pooling

$$
y_{i,j} = \frac{1}{|\mathcal{R}_{i,j}|} \sum_{(a,b) \in \mathcal{R}_{i,j}} x_{a,b}
$$

### 6.3 Global Average Pooling (GAP)

$$
y_c = \frac{1}{H \cdot W} \sum_{i=1}^{H} \sum_{j=1}^{W} x_{c,i,j}
$$

One value per channel; often used before the classifier in CNNs.

---

## 7. Recurrent Layers (RNN, LSTM)

### 7.1 Vanilla RNN

$$
\mathbf{h}_t = \sigma_h\big( \mathbf{W}_{hh} \mathbf{h}_{t-1} + \mathbf{W}_{xh} \mathbf{x}_t + \mathbf{b}_h \big)
$$

- \(\mathbf{h}_t \in \mathbb{R}^h\): hidden state at time \(t\)
- \(\sigma_h\): often \(\tanh\)
- Unrolling over time gives a product of Jacobians \(\dfrac{\partial \mathbf{h}_t}{\partial \mathbf{h}_{t-k}} \propto \mathbf{W}_{hh}^k\), leading to vanishing/exploding gradients.

### 7.2 LSTM

**Gates and cell (all vectors in \(\mathbb{R}^h\)):**

$$
\begin{aligned}
  \mathbf{f}_t       &= \sigma_g\big( \mathbf{W}_f [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_f \big) && \text{(forget)} \\[4pt]
  \mathbf{i}_t       &= \sigma_g\big( \mathbf{W}_i [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_i \big) && \text{(input)} \\[4pt]
  \tilde{\mathbf{c}}_t &= \tanh\big( \mathbf{W}_c [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_c \big) && \text{(cell candidate)} \\[4pt]
  \mathbf{o}_t       &= \sigma_g\big( \mathbf{W}_o [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_o \big) && \text{(output)}
\end{aligned}
$$

**Cell and hidden:**

$$
\mathbf{c}_t = \mathbf{f}_t \odot \mathbf{c}_{t-1} + \mathbf{i}_t \odot \tilde{\mathbf{c}}_t
\,,\qquad
\mathbf{h}_t = \mathbf{o}_t \odot \tanh(\mathbf{c}_t)
$$

- \(\sigma_g\): sigmoid (outputs in \((0,\ 1)\))
- \([\mathbf{a};\; \mathbf{b}]\): concatenation; \(\odot\): element-wise product

### 7.3 GRU (Gated Recurrent Unit)

$$
\begin{aligned}
  \mathbf{z}_t       &= \sigma_g\big( \mathbf{W}_z [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_z \big) && \text{(update gate)} \\[4pt]
  \mathbf{r}_t      &= \sigma_g\big( \mathbf{W}_r [\mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b}_r \big) && \text{(reset gate)} \\[4pt]
  \tilde{\mathbf{h}}_t &= \tanh\big( \mathbf{W} [\mathbf{r}_t \odot \mathbf{h}_{t-1};\; \mathbf{x}_t] + \mathbf{b} \big) \\[4pt]
  \mathbf{h}_t      &= (1 - \mathbf{z}_t) \odot \mathbf{h}_{t-1} + \mathbf{z}_t \odot \tilde{\mathbf{h}}_t
\end{aligned}
$$

---

## 8. Attention (Transformer Hidden Layers)

### 8.1 Scaled Dot-Product Attention

For **Query** \(\mathbf{Q} \in \mathbb{R}^{n \times d_k}\), **Key** \(\mathbf{K} \in \mathbb{R}^{m \times d_k}\), **Value** \(\mathbf{V} \in \mathbb{R}^{m \times d_v}\):

$$
\mathrm{Attention}(\mathbf{Q},\, \mathbf{K},\, \mathbf{V})
\;=\; \mathrm{softmax}\left( \frac{\mathbf{Q} \mathbf{K}^\top}{\sqrt{d_k}} \right) \mathbf{V}
$$

- \(\mathbf{Q}\mathbf{K}^\top \in \mathbb{R}^{n \times m}\): scores; \(\dfrac{1}{\sqrt{d_k}}\) reduces variance of dot products for large \(d_k\).
- **Softmax** over the last dimension (over keys): \(\mathbf{A} = \mathrm{softmax}\left( \dfrac{\mathbf{Q}\mathbf{K}^\top}{\sqrt{d_k}} \right) \in \mathbb{R}^{n \times m}\)
- **Output:** \(\mathbf{A} \mathbf{V} \in \mathbb{R}^{n \times d_v}\)

### 8.2 Multi-Head Attention

$$
\begin{aligned}
  \mathrm{head}_i &= \mathrm{Attention}\big( \mathbf{Q} \mathbf{W}_i^Q,\; \mathbf{K} \mathbf{W}_i^K,\; \mathbf{V} \mathbf{W}_i^V \big) \\[4pt]
  \mathrm{MultiHead}(\mathbf{Q},\,\mathbf{K},\,\mathbf{V}) &= \mathrm{Concat}(\mathrm{head}_1,\, \ldots,\, \mathrm{head}_h)\, \mathbf{W}^O
\end{aligned}
$$

- \(\mathbf{W}_i^Q \in \mathbb{R}^{d \times d_k}\), \(\mathbf{W}_i^K \in \mathbb{R}^{d \times d_k}\), \(\mathbf{W}_i^V \in \mathbb{R}^{d \times d_v}\), \(\mathbf{W}^O \in \mathbb{R}^{h d_v \times d}\).

### 8.3 Causal (Masked) Attention

For autoregressive (GPT-style) models, mask out future positions so position \(i\) cannot attend to \(j > i\):

$$
A_{i,j} =
\begin{cases}
  \dfrac{\exp(q_i^\top k_j \,/\, \sqrt{d_k})}{\sum_{j' \leq i} \exp(q_i^\top k_{j'} \,/\, \sqrt{d_k})} & j \leq i \\[8pt]
  0 & j > i
\end{cases}
$$

---

## 9. Feed-Forward (MLP) Block in Transformers

After (multi-head) attention, a Transformer block typically uses:

$$
\mathbf{F} = \mathbf{X} + \mathrm{Attention}\big(\mathrm{LayerNorm}(\mathbf{X})\big)
\,,\qquad
\mathbf{Y} = \mathbf{F} + \mathrm{MLP}\big(\mathrm{LayerNorm}(\mathbf{F})\big)
$$

**MLP:** two linear layers with a non-linearity in between (often GELU):

$$
\mathrm{MLP}(\mathbf{x}) = \mathbf{W}_2 \, \sigma(\mathbf{W}_1 \mathbf{x} + \mathbf{b}_1) + \mathbf{b}_2
$$

- Commonly \(\mathrm{hidden\ dim} = 4 \times d\) (e.g. BERT, GPT-2).

---

## 10. Residual (Skip) Connections

$$
\mathbf{y} = \mathcal{F}(\mathbf{x}) + \mathbf{x}
$$

- \(\mathcal{F}\): a block (conv, attention, MLP, etc.).
- **Gradient:** \(\dfrac{\partial \mathbf{y}}{\partial \mathbf{x}} = \dfrac{\partial \mathcal{F}}{\partial \mathbf{x}} + \mathbf{I}\), so at least an identity term; helps with vanishing gradients in deep nets.

**Projection** when dimensions differ: \(\mathbf{y} = \mathcal{F}(\mathbf{x}) + \mathbf{W}_s \mathbf{x}\).

---

## 11. Positional Encoding (Transformers)

Transformers have no recurrence, so **position** is injected via additive encodings.

### 11.1 Sinusoidal

For position \(\mathrm{pos}\) and dimension \(i\) (with \(d\) the model dimension):

$$
PE_{(\mathrm{pos},\, 2i)}   = \sin\left( \frac{\mathrm{pos}}{10000^{2i/d}} \right)
\,,\qquad
PE_{(\mathrm{pos},\, 2i+1)} = \cos\left( \frac{\mathrm{pos}}{10000^{2i/d}} \right)
$$

- \(\mathbf{x}_{\mathrm{pos}} := \mathbf{x}_{\mathrm{pos}} + PE_{\mathrm{pos}}\) before the first layer.

### 11.2 Learned Positional Embeddings

\(PE \in \mathbb{R}^{L_{\max} \times d}\) learned; \(\mathbf{x} := \mathbf{x} + PE[\mathrm{pos}]\). Used in BERT and many others.

---

## 12. Backpropagation and the Chain Rule

For a composition \(L = \ell \circ \sigma \circ \mathbf{W} \circ \cdots\):

$$
\frac{\partial L}{\partial \mathbf{W}}
\;=\; \frac{\partial L}{\partial \mathbf{a}} \cdot \frac{\partial \mathbf{a}}{\partial \mathbf{z}} \cdot \frac{\partial \mathbf{z}}{\partial \mathbf{W}}
$$

- **Chain rule:** multiply gradients from output to input.
- **Element-wise activations:** \(\dfrac{\partial \mathbf{a}}{\partial \mathbf{z}}\) is diagonal (Jacobian).
- **Linear:** \(\dfrac{\partial \mathbf{z}}{\partial \mathbf{W}} = \mathbf{x}^\top\), \(\dfrac{\partial \mathbf{z}}{\partial \mathbf{x}} = \mathbf{W}^\top\).

---

## 13. Loss Functions (Gradients Into Hidden Layers)

### 13.1 Mean Squared Error (MSE)

$$
L = \frac{1}{N} \sum_{i=1}^{N} (y_i - \hat{y}_i)^2
$$

- \(\dfrac{\partial L}{\partial \hat{y}_i} = \dfrac{2}{N}(y_i - \hat{y}_i)\).

### 13.2 Cross-Entropy (Classification)

For one label \(k \in \{1,\,\ldots,\, K\}\), logits \(\mathbf{z}\), \(p_i = \mathrm{softmax}(z_i)\):

$$
L = -\log p_k = -z_k + \log \sum_{j=1}^{K} e^{z_j}
$$

- \(\dfrac{\partial L}{\partial z_i} = p_i - \mathbf{1}_{i=k}\), i.e. \(\mathbf{p} - \mathbf{e}_k\) (one-hot for \(k\)).

### 13.3 Binary Cross-Entropy (BCE)

$$
L = -\frac{1}{N}\sum_i \Big[ y_i \log \hat{p}_i + (1-y_i) \log(1-\hat{p}_i) \Big]
\,,\qquad \hat{p}_i = \sigma(z_i)
$$

- \(\dfrac{\partial L}{\partial z_i} = \dfrac{1}{N}(\hat{p}_i - y_i)\).

---

## 14. Parameter Updates (Optimizers)

### 14.1 Stochastic Gradient Descent (SGD)

$$
\boldsymbol{\theta}_{t+1} = \boldsymbol{\theta}_t - \eta \,\mathbf{g}_t
\,,\qquad
\mathbf{g}_t = \nabla_{\boldsymbol{\theta}} L
$$

### 14.2 SGD with Momentum

$$
\mathbf{v}_t = \mu \,\mathbf{v}_{t-1} + \mathbf{g}_t
\,,\qquad
\boldsymbol{\theta}_{t+1} = \boldsymbol{\theta}_t - \eta \,\mathbf{v}_t
$$

- \(\mu \in [0,\ 1)\), e.g. 0.9.

### 14.3 Adam

$$
\begin{aligned}
  \mathbf{m}_t   &= \beta_1 \mathbf{m}_{t-1} + (1-\beta_1) \mathbf{g}_t && \text{(1st moment)} \\[4pt]
  \mathbf{v}_t   &= \beta_2 \mathbf{v}_{t-1} + (1-\beta_2) \,\mathbf{g}_t^2 && \text{(2nd moment, elem.-wise)} \\[4pt]
  \hat{\mathbf{m}}_t &= \frac{\mathbf{m}_t}{1 - \beta_1^t}
  \,,\qquad \hat{\mathbf{v}}_t = \frac{\mathbf{v}_t}{1 - \beta_2^t} && \text{(bias correction)} \\[4pt]
  \boldsymbol{\theta}_{t+1} &= \boldsymbol{\theta}_t - \eta \;\frac{\hat{\mathbf{m}}_t}{\sqrt{\hat{\mathbf{v}}_t} + \epsilon}
\end{aligned}
$$

- Typical: \(\beta_1 = 0.9\), \(\beta_2 = 0.999\), \(\epsilon = 10^{-8}\).

---

## 15. Regularization

### 15.1 L2 (Weight Decay)

$$
L_{\mathrm{total}} = L_{\mathrm{data}} + \frac{\lambda}{2} \sum_i W_i^2
$$

- Gradient: \(\nabla_{W_i} L_{\mathrm{total}} = \nabla_{W_i} L_{\mathrm{data}} + \lambda W_i\). Often implemented as an extra term in the optimizer (e.g. Adam’s `weight_decay`).

### 15.2 L1 (Sparsity)

$$
L_{\mathrm{total}} = L_{\mathrm{data}} + \lambda \sum_i |W_i|
$$

- \(\dfrac{\partial |W_i|}{\partial W_i} = \mathrm{sign}(W_i)\); encourages exact zeros.

---

## 16. Weight Initialization

### 16.1 Xavier (Glorot)

For linear \(\mathbf{z} = \mathbf{W}\mathbf{x}\), to keep variance of \(\mathbf{z}\) similar to \(\mathbf{x}\):

$$
W_{ij} \sim \mathcal{U}\left( -\sqrt{\frac{6}{n_{\mathrm{in}} + n_{\mathrm{out}}}}\,,\; \sqrt{\frac{6}{n_{\mathrm{in}} + n_{\mathrm{out}}}} \;\right)
$$

or Gaussian with the same variance. Often used with \(\tanh\).

### 16.2 He (Kaiming)

For ReLU (which zeros half the activations, doubling variance of the other half):

$$
W_{ij} \sim \mathcal{N}\left( 0,\; \sqrt{\frac{2}{n_{\mathrm{in}}}} \;\right)
$$

- **Fan-in:** \(n_{\mathrm{in}}\); for Conv, \(n_{\mathrm{in}} = C_{\mathrm{in}} \cdot k_h \cdot k_w\).

---

## 17. Summary Table

| Category | Main formulas |
|----------|----------------|
| **Linear** | \(\mathbf{z} = \mathbf{W}\mathbf{x} + \mathbf{b}\) |
| **Activations** | Sigmoid, Tanh, ReLU, LeakyReLU, GELU, Swish, Softplus, Softmax |
| **Normalization** | BatchNorm, LayerNorm (mean, variance, \(\hat{x}\), \(\gamma \hat{x} + \beta\)) |
| **Dropout** | \(m \sim \mathrm{Ber}(p)\), \(y = m \cdot x \,/\, p\) |
| **Convolution** | \((\mathbf{I} * \mathbf{K})_{i,j} = \sum_{a,b} I_{i+a,j+b} K_{a,b}\) |
| **Pooling** | Max, Average, Global Average |
| **RNN** | \(\mathbf{h}_t = \sigma_h(\mathbf{W}_{hh}\mathbf{h}_{t-1} + \mathbf{W}_{xh}\mathbf{x}_t + \mathbf{b})\) |
| **LSTM** | \(\mathbf{f},\,\mathbf{i},\,\mathbf{o},\,\tilde{\mathbf{c}}\); \(\mathbf{c}_t = \mathbf{f} \odot \mathbf{c}_{t-1} + \mathbf{i} \odot \tilde{\mathbf{c}}_t\); \(\mathbf{h}_t = \mathbf{o} \odot \tanh(\mathbf{c}_t)\) |
| **Attention** | \(\mathrm{softmax}(\mathbf{Q}\mathbf{K}^\top \!/ \sqrt{d_k})\, \mathbf{V}\) |
| **Residual** | \(\mathbf{y} = \mathcal{F}(\mathbf{x}) + \mathbf{x}\) |
| **Positional** | Sinusoidal \(\sin/\cos(\mathrm{pos}/10000^{2i/d})\) or learned |
| **Loss** | MSE, Cross-Entropy, BCE |
| **Optimizer** | SGD, Momentum, Adam (\(\mathbf{m}\), \(\mathbf{v}\), bias correction) |
| **Regularization** | L2, L1 |
| **Init** | Xavier, He |

---

## 18. Companion Code

The file **`04_Mathematics_Deep_Learning_Code.py`** implements and illustrates many of the formulas above in plain NumPy (no PyTorch/TensorFlow). Run:

```bash
python 04_Mathematics_Deep_Learning_Code.py
```

It demonstrates: linear map, activations (Sigmoid, Tanh, ReLU, GELU, Swish, Softplus, Softmax), LayerNorm, BatchNorm, dropout, 2D convolution, max/avg pooling, one RNN step, one LSTM step, scaled dot-product attention, residual connection, sinusoidal PE, MSE and cross-entropy, one Adam step, Xavier/He init, and the chain rule.

---

*Part of the teaching project on deep learning and machine learning.*
