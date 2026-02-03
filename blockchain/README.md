# Blockchain Implementation in Python

A comprehensive implementation of blockchain technology in Python, demonstrating core concepts including block structure, cryptographic hashing, Proof of Work mining, transaction handling, and chain validation.

## 📚 Documentation

- **[BLOCKCHAIN_GUIDE.md](BLOCKCHAIN_GUIDE.md)** - Comprehensive guide to blockchain technology covering theory, concepts, and implementation details.

## 🚀 Quick Start

### Prerequisites

- Python 3.7 or higher
- No external dependencies required (uses only Python standard library)

### Installation

1. Clone or download this repository
2. Navigate to the project directory:
   ```bash
   cd blockchain
   ```

### Running the Demo

#### Option 1: Run the main demonstration
```bash
python blockchain.py
```

This will run a complete demonstration showing:
- Blockchain creation
- Wallet creation
- Transaction processing
- Block mining
- Chain validation
- Tampering detection

#### Option 2: Run interactive scenarios
```bash
python demo.py
```

This provides an interactive menu with multiple scenarios:
1. Basic Blockchain Operations
2. Multiple Transactions
3. Insufficient Balance Validation
4. Chain Validation & Tampering Detection
5. Mining Difficulty Comparison
6. Transaction History
7. Run All Scenarios

## 📖 Code Structure

### `blockchain.py`

Main implementation file containing:

- **`Transaction`** - Represents a transaction between addresses
- **`Block`** - Represents a block in the blockchain with mining capability
- **`Blockchain`** - Main blockchain class with full functionality
- **`Wallet`** - Simple wallet for managing addresses and creating transactions

### `demo.py`

Interactive demonstration script with multiple scenarios showcasing different blockchain features.

## 🔑 Key Features

### 1. Block Structure
- Index, timestamp, transactions
- Previous block hash (chain linking)
- Nonce for Proof of Work
- Cryptographic hash (SHA-256)

### 2. Proof of Work (Mining)
- Configurable difficulty (number of leading zeros)
- Automatic nonce adjustment
- Mining reward system

### 3. Transaction Handling
- Transaction creation and validation
- Balance checking
- Transaction broadcasting
- Transaction history

### 4. Chain Validation
- Hash integrity checking
- Previous hash verification
- Difficulty requirement validation
- Tampering detection

### 5. Wallet System
- Address generation
- Transaction creation
- Balance tracking

## 💡 Usage Examples

### Basic Usage

```python
from blockchain import Blockchain, Wallet

# Create blockchain
blockchain = Blockchain(difficulty=4, mining_reward=100.0)

# Create wallets
alice = Wallet("Alice")
bob = Wallet("Bob")

# Mine first block (Alice gets reward)
blockchain.mine_pending_transactions(alice.address)

# Add transaction
blockchain.add_transaction(
    alice.create_transaction(bob.address, 50.0)
)

# Mine second block (Bob gets reward)
blockchain.mine_pending_transactions(bob.address)

# Check balances
print(f"Alice: {blockchain.get_balance(alice.address)}")
print(f"Bob: {blockchain.get_balance(bob.address)}")

# Validate chain
print(f"Chain valid: {blockchain.is_chain_valid()}")
```

### Advanced Usage

```python
# Create blockchain with custom settings
blockchain = Blockchain(
    difficulty=5,        # Higher difficulty = harder mining
    mining_reward=50.0   # Mining reward amount
)

# Add multiple transactions
for i in range(10):
    blockchain.add_transaction(
        sender.create_transaction(recipient.address, 10.0)
    )

# Mine block with all transactions
blockchain.mine_pending_transactions(miner.address)

# Display blockchain
blockchain.print_chain()
blockchain.print_balances()

# Get chain information
info = blockchain.get_chain_info()
print(info)
```

## 🔒 Security Features

1. **Cryptographic Hashing**: SHA-256 ensures data integrity
2. **Chain Linking**: Each block references previous block's hash
3. **Tampering Detection**: Any modification invalidates the chain
4. **Transaction Validation**: Balance checking prevents double-spending
5. **Proof of Work**: Mining difficulty prevents spam and attacks

## 📊 Understanding the Output

### Block Information
```
Block 1
  Timestamp: 2024-01-15 10:30:45
  Previous Hash: 0000000000000000...
  Hash: 0000a1b2c3d4e5f6...
  Nonce: 12345
  Transactions (2):
    - 0 -> Alice: 100.0
    - Alice -> Bob: 50.0
```

### Balance Information
```
ACCOUNT BALANCES
  Alice: 50.0
  Bob: 50.0
```

## 🧪 Testing Scenarios

The `demo.py` script includes several test scenarios:

1. **Basic Operations**: Simple blockchain usage
2. **Multiple Transactions**: Batch transaction processing
3. **Validation**: Insufficient balance detection
4. **Security**: Tampering detection demonstration
5. **Mining**: Difficulty impact on mining time
6. **History**: Transaction tracking and history

## 📝 Notes

- This is an educational implementation for learning purposes
- Real blockchain systems are more complex (networking, consensus, etc.)
- Signatures are simplified (real implementations use ECDSA)
- No networking layer (single-node implementation)
- Mining difficulty is simplified (real systems use dynamic difficulty)

## 🔧 Customization

### Adjust Mining Difficulty
```python
blockchain = Blockchain(difficulty=6)  # Higher = harder
```

### Change Mining Reward
```python
blockchain = Blockchain(mining_reward=200.0)
```

### Access Individual Blocks
```python
block = blockchain.chain[0]  # Get first block
print(block.hash)
print(block.transactions)
```

## 📚 Learning Resources

1. Read `BLOCKCHAIN_GUIDE.md` for comprehensive theory
2. Study the code in `blockchain.py`
3. Run different scenarios in `demo.py`
4. Modify the code to experiment
5. Try implementing additional features:
   - Merkle trees
   - Different consensus mechanisms
   - Network layer
   - Smart contracts

## 🤝 Contributing

This is an educational project. Feel free to:
- Experiment with the code
- Add new features
- Improve documentation
- Share your modifications

## 📄 License

This project is provided for educational purposes. Feel free to use and modify as needed.

## 🙏 Acknowledgments

This implementation demonstrates core blockchain concepts inspired by:
- Bitcoin's blockchain architecture
- Ethereum's transaction model
- General blockchain principles

---

**Happy Learning!** 🚀

For questions or issues, refer to the comprehensive guide in `BLOCKCHAIN_GUIDE.md`.
