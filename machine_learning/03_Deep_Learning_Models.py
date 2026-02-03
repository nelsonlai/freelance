"""
Deep Learning Models: MLP, CNN, RNN/LSTM, Transformers (GPT, BERT)
=================================================================
Runnable examples using PyTorch and Hugging Face Transformers.

Requirements: torch, transformers
Install: pip install torch transformers

First run of GPT-2 and BERT will download pre-trained weights (~500MB+).
"""

import numpy as np

# ---------------------------------------------------------------------------
# 1. MLP (Multilayer Perceptron) — PyTorch
# ---------------------------------------------------------------------------

def demo_mlp():
    """Build and train a simple MLP on synthetic classification data."""
    import torch
    import torch.nn as nn
    from torch.utils.data import DataLoader, TensorDataset
    from sklearn.datasets import make_classification
    from sklearn.model_selection import train_test_split
    from sklearn.preprocessing import StandardScaler

    print("\n" + "=" * 60)
    print("1. MLP (Multilayer Perceptron)")
    print("=" * 60)

    # Data: 20 features, 2 classes, 1000 samples
    X, y = make_classification(n_samples=1000, n_features=20, n_informative=15, n_classes=2, random_state=42)
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)

    X_train = torch.FloatTensor(X_train)
    y_train = torch.LongTensor(y_train)
    X_test = torch.FloatTensor(X_test)
    y_test = torch.LongTensor(y_test)

    # Model: Input(20) -> Hidden(64) -> Hidden(32) -> Output(2)
    class MLP(nn.Module):
        def __init__(self, input_size=20, hidden1=64, hidden2=32, num_classes=2):
            super().__init__()
            self.layers = nn.Sequential(
                nn.Linear(input_size, hidden1),
                nn.ReLU(),
                nn.Linear(hidden1, hidden2),
                nn.ReLU(),
                nn.Linear(hidden2, num_classes),
            )

        def forward(self, x):
            return self.layers(x)

    model = MLP()
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.01)

    # Training (3 epochs for demo)
    model.train()
    for epoch in range(3):
        optimizer.zero_grad()
        logits = model(X_train)
        loss = criterion(logits, y_train)
        loss.backward()
        optimizer.step()
        pred = logits.argmax(dim=1)
        acc = (pred == y_train).float().mean().item()
        print(f"   Epoch {epoch+1}: loss={loss.item():.4f}, train_acc={acc:.4f}")

    # Evaluate
    model.eval()
    with torch.no_grad():
        logits = model(X_test)
        pred = logits.argmax(dim=1)
        acc = (pred == y_test).float().mean().item()
    print(f"   Test accuracy: {acc:.4f}")
    print("   Example: first 5 predictions:", pred[:5].tolist(), "| true:", y_test[:5].tolist())


# ---------------------------------------------------------------------------
# 2. CNN (Convolutional Neural Network) — PyTorch, MNIST
# ---------------------------------------------------------------------------

def demo_cnn():
    """Build and train a CNN on MNIST (images of digits)."""
    import torch
    import torch.nn as nn
    from torch.utils.data import DataLoader
    from torchvision import datasets, transforms

    print("\n" + "=" * 60)
    print("2. CNN (Convolutional Neural Network) for Images")
    print("=" * 60)

    # MNIST: 28x28 grayscale, 10 classes. Download on first run.
    transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0.1307,), (0.3081,))])
    train_set = datasets.MNIST("./data", train=True, download=True, transform=transform)
    train_loader = DataLoader(train_set, batch_size=64, shuffle=True, num_workers=0)

    # Model: Conv -> ReLU -> Pool -> Conv -> ReLU -> Pool -> Flatten -> Linear
    class CNN(nn.Module):
        def __init__(self):
            super().__init__()
            self.conv = nn.Sequential(
                nn.Conv2d(1, 16, kernel_size=5, padding=2),  # 28x28 -> 28x28
                nn.ReLU(),
                nn.MaxPool2d(2),   # 28x28 -> 14x14
                nn.Conv2d(16, 32, kernel_size=5, padding=2), # 14x14 -> 14x14
                nn.ReLU(),
                nn.MaxPool2d(2),  # 14x14 -> 7x7
            )
            self.fc = nn.Linear(32 * 7 * 7, 10)

        def forward(self, x):
            x = self.conv(x)
            x = x.view(x.size(0), -1)
            return self.fc(x)

    model = CNN()
    criterion = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

    # Training (2 epochs for demo; increase for better accuracy)
    model.train()
    for epoch in range(2):
        total, correct = 0, 0
        for batch_idx, (data, target) in enumerate(train_loader):
            if batch_idx >= 100:  # limit for quick demo
                break
            optimizer.zero_grad()
            logits = model(data)
            loss = criterion(logits, target)
            loss.backward()
            optimizer.step()
            pred = logits.argmax(dim=1)
            total += target.size(0)
            correct += (pred == target).sum().item()
        print(f"   Epoch {epoch+1}: loss={loss.item():.4f}, train_acc={correct/total:.4f}")

    # One batch inference example
    model.eval()
    data, target = next(iter(DataLoader(train_set, batch_size=5)))
    with torch.no_grad():
        logits = model(data)
        pred = logits.argmax(dim=1)
    print("   Sample predictions (first 5):", pred.tolist(), "| true:", target[:5].tolist())


# ---------------------------------------------------------------------------
# 3. RNN and LSTM — PyTorch, Sequence Data
# ---------------------------------------------------------------------------

def demo_rnn_lstm():
    """Build and train an RNN and an LSTM on synthetic sequence data."""
    import torch
    import torch.nn as nn

    print("\n" + "=" * 60)
    print("3. RNN / LSTM for Sequences")
    print("=" * 60)

    # Synthetic: (N, seq_len, input_size). Target = 1 if first feature increases from t=0 to t=end else 0
    # (a simple temporal rule so RNN/LSTM can learn sequence structure)
    np.random.seed(42)
    N, seq_len, input_size = 200, 10, 5
    X = np.random.rand(N, seq_len, input_size).astype(np.float32)
    y = (X[:, -1, 0] > X[:, 0, 0]).astype(np.int64)

    X_t = torch.FloatTensor(X)
    y_t = torch.LongTensor(y)

    # --- RNN ---
    class RNN(nn.Module):
        def __init__(self, input_size, hidden_size, num_layers, num_classes):
            super().__init__()
            self.rnn = nn.RNN(input_size, hidden_size, num_layers, batch_first=True)
            self.fc = nn.Linear(hidden_size, num_classes)

        def forward(self, x):
            out, h_n = self.rnn(x)  # h_n: (num_layers, batch, hidden)
            return self.fc(h_n[-1])  # use last layer's hidden state

    # --- LSTM ---
    class LSTM(nn.Module):
        def __init__(self, input_size, hidden_size, num_layers, num_classes):
            super().__init__()
            self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
            self.fc = nn.Linear(hidden_size, num_classes)

        def forward(self, x):
            out, (h_n, c_n) = self.lstm(x)
            return self.fc(h_n[-1])

    for name, Model in [("RNN", RNN), ("LSTM", LSTM)]:
        model = Model(input_size=input_size, hidden_size=32, num_layers=2, num_classes=2)
        criterion = nn.CrossEntropyLoss()
        optimizer = torch.optim.Adam(model.parameters(), lr=0.01)

        model.train()
        for epoch in range(5):
            optimizer.zero_grad()
            logits = model(X_t)
            loss = criterion(logits, y_t)
            loss.backward()
            optimizer.step()
            acc = (logits.argmax(dim=1) == y_t).float().mean().item()
            print(f"   {name} Epoch {epoch+1}: loss={loss.item():.4f}, acc={acc:.4f}")

        model.eval()
        with torch.no_grad():
            pred = model(X_t).argmax(dim=1)
        print(f"   {name} final train accuracy: {(pred == y_t).float().mean().item():.4f}")
    print("   (LSTM often handles longer sequences and long-range dependencies better than RNN.)")


# ---------------------------------------------------------------------------
# 4. Transformers: GPT-2 and BERT — Hugging Face
# ---------------------------------------------------------------------------

def demo_transformers():
    """Use pre-trained GPT-2 (text generation) and BERT (classification / features)."""
    print("\n" + "=" * 60)
    print("4. Transformers: GPT-2 and BERT")
    print("=" * 60)

    # --- 4a. GPT-2: Text Generation ---
    print("\n4a. GPT-2 (decoder-only, causal LM) — Text Generation")
    try:
        from transformers import pipeline, AutoModelForCausalLM, AutoTokenizer

        generator = pipeline("text-generation", model="gpt2", max_new_tokens=25)
        out = generator("The future of artificial intelligence is", do_sample=True, num_return_sequences=1)
        print("   Prompt: 'The future of artificial intelligence is'")
        print("   Generated:", out[0]["generated_text"][:200] + "..." if len(out[0]["generated_text"]) > 200 else out[0]["generated_text"])
    except Exception as e:
        print("   [Skipped: install 'transformers' and run with internet to download gpt2.]", e)

    # --- 4b. BERT: Sentiment (classification) and Feature Extraction ---
    print("\n4b. BERT (encoder-only) — Sentiment Classification")
    try:
        from transformers import pipeline, AutoModel, AutoTokenizer
        import torch

        classifier = pipeline("sentiment-analysis", model="distilbert-base-uncased-finetuned-sst-2-english")
        result = classifier("I love learning deep learning!")
        print("   Input: 'I love learning deep learning!'")
        print("   Result:", result)

        print("\n4c. BERT — Feature Extraction (embedding of [CLS] token)")
        model = AutoModel.from_pretrained("bert-base-uncased")
        tokenizer = AutoTokenizer.from_pretrained("bert-base-uncased")
        text = "Deep learning uses neural networks with many layers."
        inputs = tokenizer(text, return_tensors="pt", padding=True, truncation=True)
        with torch.no_grad():
            outputs = model(**inputs)
        # [CLS] representation: (batch, seq_len, hidden) -> take (batch, hidden)
        cls_embedding = outputs.last_hidden_state[:, 0, :]  # (1, 768) for BERT-base
        print("   Input:", text)
        print("   [CLS] embedding shape:", cls_embedding.shape)
        print("   First 5 dims:", cls_embedding[0, :5].tolist())
    except Exception as e:
        print("   [Skipped: install 'transformers' and run with internet to download BERT.]", e)


# ---------------------------------------------------------------------------
# RUN ALL
# ---------------------------------------------------------------------------

if __name__ == "__main__":
    print("\n" + "#" * 60)
    print("#  DEEP LEARNING MODELS — MLP, CNN, RNN/LSTM, Transformers")
    print("#" * 60)

    demo_mlp()
    demo_cnn()
    demo_rnn_lstm()
    demo_transformers()

    print("\n" + "#" * 60)
    print("#  END")
    print("#" * 60 + "\n")
