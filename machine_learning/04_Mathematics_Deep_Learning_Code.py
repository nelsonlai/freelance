"""
Mathematics of Deep Learning: Code Illustrations
================================================
Implements and plots the main formulas from 04_Mathematics_of_Deep_Learning_Hidden_Layers.md.
No GPU or heavy dependencies: numpy (+ matplotlib for plots).

Run: python 04_Mathematics_Deep_Learning_Code.py
"""

import numpy as np

# ---------------------------------------------------------------------------
# 1. LINEAR (AFFINE) TRANSFORMATION: z = Wx + b
# ---------------------------------------------------------------------------
def demo_linear():
    print("\n" + "=" * 60)
    print("1. LINEAR: z = Wx + b")
    print("=" * 60)
    d, m = 3, 4
    x = np.array([1.0, 2.0, 3.0])
    W = np.random.randn(m, d) * 0.5
    b = np.zeros(m)
    z = W @ x + b
    print("   x:", x)
    print("   z = Wx + b:", z.round(4))

# ---------------------------------------------------------------------------
# 2. ACTIVATION FUNCTIONS
# ---------------------------------------------------------------------------
def sigmoid(z):
    return 1 / (1 + np.exp(-np.clip(z, -500, 500)))

def tanh(z):
    return np.tanh(z)

def relu(z):
    return np.maximum(0, z)

def leaky_relu(z, alpha=0.01):
    return np.where(z >= 0, z, alpha * z)

def gelu_approx(z):
    """GELU approximation: 0.5 * z * (1 + tanh(sqrt(2/pi)(z + 0.044715 z^3)))"""
    return 0.5 * z * (1 + np.tanh(np.sqrt(2 / np.pi) * (z + 0.044715 * z**3)))

def swish(z):
    return z * sigmoid(z)

def softplus(z):
    return np.log(1 + np.exp(np.clip(z, -500, 500)))

def softmax(z, axis=-1):
    e = np.exp(z - np.max(z, axis=axis, keepdims=True))
    return e / e.sum(axis=axis, keepdims=True)

def demo_activations():
    print("\n" + "=" * 60)
    print("2. ACTIVATION FUNCTIONS")
    print("=" * 60)
    z = np.linspace(-3, 3, 7)
    print("   z:      ", z.round(2))
    print("   sigmoid:", sigmoid(z).round(4))
    print("   tanh:   ", tanh(z).round(4))
    print("   ReLU:   ", relu(z).round(4))
    print("   GELU:   ", gelu_approx(z).round(4))
    print("   Swish:  ", swish(z).round(4))
    print("   softmax(z):", softmax(z).round(4), "  sum=", softmax(z).sum())

# ---------------------------------------------------------------------------
# 3. LAYER NORMALIZATION: x_hat = (x - mu) / sqrt(var + eps), y = gamma*x_hat + beta
# ---------------------------------------------------------------------------
def layer_norm(x, eps=1e-5):
    """LayerNorm over last axis. x: (N, d)."""
    mu = x.mean(axis=-1, keepdims=True)
    var = x.var(axis=-1, keepdims=True) + eps
    x_hat = (x - mu) / np.sqrt(var)
    # scale & shift (gamma=1, beta=0 for demo)
    return x_hat

def demo_layer_norm():
    print("\n" + "=" * 60)
    print("3. LAYER NORMALIZATION")
    print("=" * 60)
    x = np.array([[1.0, 2.0, 3.0], [4.0, 5.0, 6.0]])
    x_hat = layer_norm(x)
    print("   x (mean per row=2,5):\n", x)
    print("   x_hat (mean≈0, std≈1 per row):\n", x_hat.round(4))
    print("   per-row mean:", x_hat.mean(axis=1).round(6), " std:", x_hat.std(axis=1).round(4))

# ---------------------------------------------------------------------------
# 4. BATCH NORMALIZATION (over batch axis for one channel)
# ---------------------------------------------------------------------------
def batch_norm_1d(x, eps=1e-5):
    """BatchNorm over axis=0. x: (N, d) -> normalize per column (per feature)."""
    mu = x.mean(axis=0, keepdims=True)
    var = x.var(axis=0, keepdims=True) + eps
    return (x - mu) / np.sqrt(var)

def demo_batch_norm():
    print("\n" + "=" * 60)
    print("4. BATCH NORMALIZATION")
    print("=" * 60)
    x = np.random.randn(5, 3) * 2 + 10  # batch=5, features=3
    x_hat = batch_norm_1d(x)
    print("   x (each column ~ N(10,4)):\n", x.round(2))
    print("   x_hat (per-column mean≈0, std≈1):\n", x_hat.round(4))
    print("   per-column mean:", x_hat.mean(axis=0).round(6), " std:", x_hat.std(axis=0).round(4))

# ---------------------------------------------------------------------------
# 5. DROPOUT: y = (m * x) / p, m ~ Bernoulli(p)
# ---------------------------------------------------------------------------
def dropout(x, p=0.5, training=True):
    if not training or p >= 1:
        return x
    m = (np.random.rand(*x.shape) < p) / p  # keep with prob p, scale by 1/p
    return x * m

def demo_dropout():
    print("\n" + "=" * 60)
    print("5. DROPOUT")
    print("=" * 60)
    x = np.ones(6)
    np.random.seed(42)
    y = dropout(x, p=0.5, training=True)
    print("   x:     ", x)
    print("   mask:  ", (y != 0).astype(int))
    print("   y=x*m/p:", y.round(2), "  (E[y]=E[x] when m~Ber(p), scale 1/p)")

# ---------------------------------------------------------------------------
# 6. 2D CONVOLUTION (cross-correlation): (I*K)_{i,j} = sum_{a,b} I_{i+a,j+b} K_{a,b}
# ---------------------------------------------------------------------------
def conv2d_simple(I, K):
    """2D cross-correlation, no stride/padding. I: (H,W), K: (kH,kW)."""
    H, W = I.shape
    kH, kW = K.shape
    out_H, out_W = H - kH + 1, W - kW + 1
    out = np.zeros((out_H, out_W))
    for i in range(out_H):
        for j in range(out_W):
            out[i, j] = np.sum(I[i : i + kH, j : j + kW] * K)
    return out

def demo_conv2d():
    print("\n" + "=" * 60)
    print("6. 2D CONVOLUTION (cross-correlation)")
    print("=" * 60)
    I = np.arange(16).reshape(4, 4).astype(float)
    K = np.array([[1, 0], [0, -1]])  # edge-ish
    out = conv2d_simple(I, K)
    print("   I (4x4):\n", I)
    print("   K (2x2):\n", K)
    print("   (I*K):\n", out)

# ---------------------------------------------------------------------------
# 7. MAX POOLING and AVERAGE POOLING
# ---------------------------------------------------------------------------
def max_pool2d(x, size=2):
    """2x2 max pool. x: (H,W)."""
    H, W = x.shape
    out = np.zeros((H // size, W // size))
    for i in range(0, H, size):
        for j in range(0, W, size):
            out[i // size, j // size] = x[i : i + size, j : j + size].max()
    return out

def avg_pool2d(x, size=2):
    H, W = x.shape
    out = np.zeros((H // size, W // size))
    for i in range(0, H, size):
        for j in range(0, W, size):
            out[i // size, j // size] = x[i : i + size, j : j + size].mean()
    return out

def demo_pooling():
    print("\n" + "=" * 60)
    print("7. POOLING")
    print("=" * 60)
    x = np.arange(16).reshape(4, 4).astype(float)
    print("   x (4x4):\n", x)
    print("   max_pool 2x2:\n", max_pool2d(x))
    print("   avg_pool 2x2:\n", avg_pool2d(x))

# ---------------------------------------------------------------------------
# 8. RNN: h_t = tanh(W_hh h_{t-1} + W_xh x_t + b)
# ---------------------------------------------------------------------------
def rnn_step(h_prev, x_t, W_hh, W_xh, b):
    return np.tanh(W_hh @ h_prev + W_xh @ x_t + b)

def demo_rnn():
    print("\n" + "=" * 60)
    print("8. RNN STEP: h_t = tanh(W_hh h_{t-1} + W_xh x_t + b)")
    print("=" * 60)
    h_dim, x_dim = 2, 3
    np.random.seed(42)
    W_hh = np.random.randn(h_dim, h_dim) * 0.5
    W_xh = np.random.randn(h_dim, x_dim) * 0.5
    b = np.zeros(h_dim)
    h = np.zeros(h_dim)
    x = np.array([1.0, 0.0, 0.0])
    h = rnn_step(h, x, W_hh, W_xh, b)
    print("   h_0 = 0, x_1 = [1,0,0] -> h_1:", h.round(4))

# ---------------------------------------------------------------------------
# 9. LSTM: forget, input, output gates; cell and hidden
# ---------------------------------------------------------------------------
def lstm_step(h_prev, c_prev, x_t, W_f, W_i, W_c, W_o, b_f, b_i, b_c, b_o):
    """Single LSTM step. All gates: [h_prev; x_t] -> linear -> sigmoid/tanh."""
    hx = np.concatenate([h_prev, x_t])
    f = sigmoid(W_f @ hx + b_f)
    i = sigmoid(W_i @ hx + b_i)
    c_tilde = np.tanh(W_c @ hx + b_c)
    o = sigmoid(W_o @ hx + b_o)
    c = f * c_prev + i * c_tilde
    h = o * np.tanh(c)
    return h, c

def demo_lstm():
    print("\n" + "=" * 60)
    print("9. LSTM: f_t, i_t, c_tilde, o_t -> c_t = f*c_{t-1} + i*c_tilde, h_t = o*tanh(c_t)")
    print("=" * 60)
    h_dim, x_dim = 2, 3
    d = h_dim + x_dim
    np.random.seed(42)
    W_f = np.random.randn(h_dim, d) * 0.3
    W_i, W_c, W_o = np.random.randn(h_dim, d) * 0.3, np.random.randn(h_dim, d) * 0.3, np.random.randn(h_dim, d) * 0.3
    b_f = b_i = b_c = b_o = np.zeros(h_dim)
    h, c = np.zeros(h_dim), np.zeros(h_dim)
    x = np.array([1.0, 0.0, 0.0])
    h, c = lstm_step(h, c, x, W_f, W_i, W_c, W_o, b_f, b_i, b_c, b_o)
    print("   h_0=c_0=0, x_1=[1,0,0] -> h_1:", h.round(4), " c_1:", c.round(4))

# ---------------------------------------------------------------------------
# 10. SCALED DOT-PRODUCT ATTENTION: softmax(Q K^T / sqrt(d_k)) V
# ---------------------------------------------------------------------------
def scaled_dot_product_attention(Q, K, V, d_k=None):
    if d_k is None:
        d_k = Q.shape[-1]
    scores = (Q @ K.T) / np.sqrt(d_k)
    A = softmax(scores, axis=-1)  # softmax over keys (each row sums to 1)
    return A @ V

def demo_attention():
    print("\n" + "=" * 60)
    print("10. SCALED DOT-PRODUCT ATTENTION: softmax(Q K^T / sqrt(d_k)) V")
    print("=" * 60)
    n, m, d_k, d_v = 2, 3, 4, 4
    np.random.seed(42)
    Q = np.random.randn(n, d_k) * 0.5
    K = np.random.randn(m, d_k) * 0.5
    V = np.random.randn(m, d_v) * 0.5
    out = scaled_dot_product_attention(Q, K, V, d_k)
    A = softmax((Q @ K.T) / np.sqrt(d_k), axis=-1)
    print("   Q (n_q x d_k):", Q.shape, " K (n_k x d_k):", K.shape, " V (n_k x d_v):", V.shape)
    print("   Attention weights A (n_q x n_k):\n", A.round(4))
    print("   Output (n_q x d_v):\n", out.round(4))

# ---------------------------------------------------------------------------
# 11. RESIDUAL: y = F(x) + x
# ---------------------------------------------------------------------------
def demo_residual():
    print("\n" + "=" * 60)
    print("11. RESIDUAL: y = F(x) + x")
    print("=" * 60)
    x = np.array([1.0, 2.0, 3.0])
    F = lambda z: 0.1 * z  # tiny "block"
    y = F(x) + x
    print("   x:     ", x)
    print("   F(x):  ", F(x))
    print("   y=F(x)+x:", y)
    print("   Gradient: d/dx (F(x)+x) = dF/dx + I -> gradient flows at least via I.")

# ---------------------------------------------------------------------------
# 12. SINUSOIDAL POSITIONAL ENCODING
# ---------------------------------------------------------------------------
def sinusoidal_pe(pos, d, max_len=100):
    pe = np.zeros(d)
    for i in range(d):
        if i % 2 == 0:
            pe[i] = np.sin(pos / 10000 ** (i / d))
        else:
            pe[i] = np.cos(pos / 10000 ** ((i - 1) / d))
    return pe

def demo_positional_encoding():
    print("\n" + "=" * 60)
    print("12. SINUSOIDAL POSITIONAL ENCODING: sin(pos/10000^(2i/d)), cos(...)")
    print("=" * 60)
    for pos in [0, 1, 10]:
        pe = sinusoidal_pe(pos, d=4)
        print("   pos=%2d -> PE:" % pos, pe.round(4))

# ---------------------------------------------------------------------------
# 13. LOSS FUNCTIONS: MSE, Cross-Entropy
# ---------------------------------------------------------------------------
def mse(y, y_hat):
    return ((y - y_hat) ** 2).mean()

def cross_entropy_logits(logits, target_class):
    """L = -log(softmax(logits)_k) = -logits_k + log(sum_j exp(logits_j))"""
    logits = np.array(logits, dtype=float)
    logits = logits - np.max(logits)
    log_sum_exp = np.log(np.exp(logits).sum())
    return -logits[target_class] + log_sum_exp

def demo_losses():
    print("\n" + "=" * 60)
    print("13. LOSS: MSE, Cross-Entropy")
    print("=" * 60)
    y, y_hat = np.array([1.0, 2.0]), np.array([1.1, 1.8])
    print("   MSE: (1/2)*((1-1.1)^2+(2-1.8)^2) =", mse(y, y_hat).round(4))
    logits = np.array([0.5, 2.0, 0.1])
    print("   CrossEntropy(logits, k=1):", cross_entropy_logits(logits, 1).round(4))

# ---------------------------------------------------------------------------
# 14. ADAM (simplified one-step): m, v, bias correction, update
# ---------------------------------------------------------------------------
def adam_step(g, m, v, t, lr=0.001, b1=0.9, b2=0.999, eps=1e-8):
    m = b1 * m + (1 - b1) * g
    v = b2 * v + (1 - b2) * (g ** 2)
    m_hat = m / (1 - b1 ** t)
    v_hat = v / (1 - b2 ** t)
    upd = lr * m_hat / (np.sqrt(v_hat) + eps)
    return upd, m, v

def demo_adam():
    print("\n" + "=" * 60)
    print("14. ADAM: m_t, v_t, m_hat, v_hat, theta -= lr * m_hat / (sqrt(v_hat)+eps)")
    print("=" * 60)
    g = np.array([0.5, -0.3])
    m, v = np.zeros(2), np.zeros(2)
    upd, m, v = adam_step(g, m, v, t=1)
    print("   g:", g, " -> first step update:", upd.round(6))

# ---------------------------------------------------------------------------
# 15. INITIALIZATION: Xavier, He
# ---------------------------------------------------------------------------
def xavier_init(n_in, n_out):
    limit = np.sqrt(6 / (n_in + n_out))
    return np.random.uniform(-limit, limit, (n_out, n_in))

def he_init(n_in):
    std = np.sqrt(2 / n_in)
    return np.random.randn(10, n_in) * std  # example shape

def demo_init():
    print("\n" + "=" * 60)
    print("15. INIT: Xavier std~sqrt(6/(n_in+n_out)), He std~sqrt(2/n_in)")
    print("=" * 60)
    W_x = xavier_init(5, 3)
    print("   Xavier(5,3) sample std:", np.std(W_x).round(4))
    W_h = he_init(5)
    print("   He(5) sample std:", np.std(W_h).round(4))

# ---------------------------------------------------------------------------
# 16. CHAIN RULE (backprop sketch): dL/dW = dL/da * da/dz * dz/dW
# ---------------------------------------------------------------------------
def demo_chain_rule():
    print("\n" + "=" * 60)
    print("16. CHAIN RULE: dL/dW = (dL/da) * (da/dz) * (dz/dW)")
    print("=" * 60)
    print("   For z=Wx+b, a=ReLU(z), L=MSE(a,y):")
    print("   - dL/da = 2(a-y)/N")
    print("   - da/dz = 1 if z>0 else 0 (diagonal)")
    print("   - dz/dW = x^T  =>  dL/dW = (dL/da * da/dz) @ x^T")

# ---------------------------------------------------------------------------
# RUN ALL
# ---------------------------------------------------------------------------
if __name__ == "__main__":
    print("\n" + "#" * 60)
    print("#  MATHEMATICS OF DEEP LEARNING — CODE ILLUSTRATIONS")
    print("#" * 60)

    demo_linear()
    demo_activations()
    demo_layer_norm()
    demo_batch_norm()
    demo_dropout()
    demo_conv2d()
    demo_pooling()
    demo_rnn()
    demo_lstm()
    demo_attention()
    demo_residual()
    demo_positional_encoding()
    demo_losses()
    demo_adam()
    demo_init()
    demo_chain_rule()

    print("\n" + "#" * 60)
    print("#  END")
    print("#" * 60 + "\n")
