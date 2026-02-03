"""
Blockchain Implementation in Python

This module implements a basic blockchain with:
- Block structure with cryptographic hashing
- Proof of Work (mining)
- Transaction handling
- Chain validation
- Wallet functionality
"""

import hashlib
import json
import time
from typing import List, Dict, Optional
from datetime import datetime
from collections import defaultdict


class Transaction:
    """Represents a transaction in the blockchain."""
    
    def __init__(self, sender: str, recipient: str, amount: float, signature: str = ""):
        self.sender = sender
        self.recipient = recipient
        self.amount = amount
        self.timestamp = time.time()
        self.signature = signature
    
    def to_dict(self) -> Dict:
        """Convert transaction to dictionary."""
        return {
            'sender': self.sender,
            'recipient': self.recipient,
            'amount': self.amount,
            'timestamp': self.timestamp,
            'signature': self.signature
        }
    
    def __repr__(self):
        return f"Transaction({self.sender} -> {self.recipient}: {self.amount})"


class Block:
    """Represents a block in the blockchain."""
    
    def __init__(self, index: int, transactions: List[Transaction], 
                 previous_hash: str, nonce: int = 0):
        self.index = index
        self.timestamp = time.time()
        self.transactions = transactions
        self.previous_hash = previous_hash
        self.nonce = nonce
        self.hash = self.calculate_hash()
    
    def calculate_hash(self) -> str:
        """Calculate the hash of the block."""
        block_string = json.dumps({
            'index': self.index,
            'timestamp': self.timestamp,
            'transactions': [tx.to_dict() for tx in self.transactions],
            'previous_hash': self.previous_hash,
            'nonce': self.nonce
        }, sort_keys=True)
        return hashlib.sha256(block_string.encode()).hexdigest()
    
    def mine_block(self, difficulty: int):
        """Mine the block using Proof of Work."""
        target = "0" * difficulty
        while self.hash[:difficulty] != target:
            self.nonce += 1
            self.hash = self.calculate_hash()
        print(f"Block mined: {self.hash}")
    
    def to_dict(self) -> Dict:
        """Convert block to dictionary."""
        return {
            'index': self.index,
            'timestamp': self.timestamp,
            'transactions': [tx.to_dict() for tx in self.transactions],
            'previous_hash': self.previous_hash,
            'nonce': self.nonce,
            'hash': self.hash
        }
    
    def __repr__(self):
        return f"Block(Index: {self.index}, Hash: {self.hash[:16]}...)"


class Blockchain:
    """Main blockchain class implementing core functionality."""
    
    def __init__(self, difficulty: int = 4, mining_reward: float = 100.0):
        self.chain: List[Block] = [self.create_genesis_block()]
        self.pending_transactions: List[Transaction] = []
        self.difficulty = difficulty
        self.mining_reward = mining_reward
        self.balances: Dict[str, float] = defaultdict(float)
    
    def create_genesis_block(self) -> Block:
        """Create the first block (genesis block) in the chain."""
        genesis_transaction = Transaction(
            sender="0",  # System
            recipient="Genesis",
            amount=0.0
        )
        return Block(0, [genesis_transaction], "0", 0)
    
    def get_latest_block(self) -> Block:
        """Get the most recent block in the chain."""
        return self.chain[-1]
    
    def add_transaction(self, transaction: Transaction) -> bool:
        """Add a transaction to the pending transactions list."""
        # Validate transaction
        if transaction.sender == transaction.recipient:
            print("Error: Sender and recipient cannot be the same")
            return False
        
        if transaction.amount <= 0:
            print("Error: Transaction amount must be positive")
            return False
        
        # Check balance (for non-mining transactions)
        if transaction.sender != "0":  # "0" represents system/mining reward
            if self.balances[transaction.sender] < transaction.amount:
                print(f"Error: Insufficient balance. Available: {self.balances[transaction.sender]}")
                return False
        
        self.pending_transactions.append(transaction)
        print(f"Transaction added: {transaction.sender} -> {transaction.recipient}: {transaction.amount}")
        return True
    
    def mine_pending_transactions(self, mining_reward_address: str) -> Block:
        """Mine pending transactions and add block to chain."""
        # Add mining reward transaction
        reward_transaction = Transaction(
            sender="0",  # System
            recipient=mining_reward_address,
            amount=self.mining_reward
        )
        self.pending_transactions.append(reward_transaction)
        
        # Create new block
        block = Block(
            index=len(self.chain),
            transactions=self.pending_transactions.copy(),
            previous_hash=self.get_latest_block().hash
        )
        
        # Mine the block
        print(f"Mining block {block.index}...")
        start_time = time.time()
        block.mine_block(self.difficulty)
        mining_time = time.time() - start_time
        print(f"Block mined in {mining_time:.2f} seconds")
        
        # Add block to chain
        self.chain.append(block)
        
        # Update balances
        self.update_balances(block)
        
        # Clear pending transactions
        self.pending_transactions = []
        
        return block
    
    def update_balances(self, block: Block):
        """Update account balances based on block transactions."""
        for transaction in block.transactions:
            if transaction.sender != "0":  # Not a mining reward
                self.balances[transaction.sender] -= transaction.amount
            self.balances[transaction.recipient] += transaction.amount
    
    def get_balance(self, address: str) -> float:
        """Get the balance of an address."""
        return self.balances[address]
    
    def is_chain_valid(self) -> bool:
        """Validate the integrity of the blockchain."""
        for i in range(1, len(self.chain)):
            current_block = self.chain[i]
            previous_block = self.chain[i - 1]
            
            # Check if current block hash is valid
            if current_block.hash != current_block.calculate_hash():
                print(f"Block {i} has invalid hash")
                return False
            
            # Check if block points to previous block
            if current_block.previous_hash != previous_block.hash:
                print(f"Block {i} has invalid previous hash")
                return False
            
            # Check if block meets difficulty requirement
            target = "0" * self.difficulty
            if current_block.hash[:self.difficulty] != target:
                print(f"Block {i} does not meet difficulty requirement")
                return False
        
        return True
    
    def get_chain_info(self) -> Dict:
        """Get information about the blockchain."""
        return {
            'chain_length': len(self.chain),
            'pending_transactions': len(self.pending_transactions),
            'difficulty': self.difficulty,
            'mining_reward': self.mining_reward,
            'is_valid': self.is_chain_valid()
        }
    
    def print_chain(self):
        """Print the entire blockchain."""
        print("\n" + "="*80)
        print("BLOCKCHAIN")
        print("="*80)
        for block in self.chain:
            print(f"\nBlock {block.index}")
            print(f"  Timestamp: {datetime.fromtimestamp(block.timestamp).strftime('%Y-%m-%d %H:%M:%S')}")
            print(f"  Previous Hash: {block.previous_hash[:16]}...")
            print(f"  Hash: {block.hash}")
            print(f"  Nonce: {block.nonce}")
            print(f"  Transactions ({len(block.transactions)}):")
            for tx in block.transactions:
                print(f"    - {tx.sender} -> {tx.recipient}: {tx.amount}")
        print("="*80 + "\n")
    
    def print_balances(self):
        """Print all account balances."""
        print("\n" + "="*80)
        print("ACCOUNT BALANCES")
        print("="*80)
        for address, balance in self.balances.items():
            if balance > 0 or address == "Genesis":
                print(f"  {address}: {balance}")
        print("="*80 + "\n")


class Wallet:
    """Simple wallet implementation for managing addresses."""
    
    def __init__(self, name: str):
        self.name = name
        self.address = self.generate_address()
    
    @staticmethod
    def generate_address() -> str:
        """Generate a simple address (in real implementation, use public key)."""
        import random
        import string
        return ''.join(random.choices(string.ascii_letters + string.digits, k=16))
    
    def create_transaction(self, recipient: str, amount: float) -> Transaction:
        """Create a transaction from this wallet."""
        return Transaction(
            sender=self.address,
            recipient=recipient,
            amount=amount,
            signature=f"signed_by_{self.name}"  # Simplified signature
        )
    
    def __repr__(self):
        return f"Wallet({self.name}, Address: {self.address[:8]}...)"


def main():
    """Demonstration of blockchain functionality."""
    print("="*80)
    print("BLOCKCHAIN DEMONSTRATION")
    print("="*80)
    
    # Create blockchain
    blockchain = Blockchain(difficulty=4, mining_reward=100.0)
    
    # Create wallets
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    charlie = Wallet("Charlie")
    
    print(f"\nCreated wallets:")
    print(f"  {alice}")
    print(f"  {bob}")
    print(f"  {charlie}")
    
    # Mine first block (Alice gets mining reward)
    print("\n" + "-"*80)
    print("Mining Block 1 (Genesis + Mining Reward for Alice)")
    print("-"*80)
    blockchain.mine_pending_transactions(alice.address)
    
    # Add some transactions
    print("\n" + "-"*80)
    print("Adding Transactions")
    print("-"*80)
    blockchain.add_transaction(alice.create_transaction(bob.address, 50.0))
    blockchain.add_transaction(alice.create_transaction(charlie.address, 25.0))
    blockchain.add_transaction(bob.create_transaction(charlie.address, 10.0))
    
    # Mine second block
    print("\n" + "-"*80)
    print("Mining Block 2 (Bob gets mining reward)")
    print("-"*80)
    blockchain.mine_pending_transactions(bob.address)
    
    # Add more transactions
    print("\n" + "-"*80)
    print("Adding More Transactions")
    print("-"*80)
    blockchain.add_transaction(charlie.create_transaction(alice.address, 5.0))
    blockchain.add_transaction(bob.create_transaction(alice.address, 15.0))
    
    # Mine third block
    print("\n" + "-"*80)
    print("Mining Block 3 (Charlie gets mining reward)")
    print("-"*80)
    blockchain.mine_pending_transactions(charlie.address)
    
    # Display blockchain
    blockchain.print_chain()
    
    # Display balances
    blockchain.print_balances()
    
    # Validate chain
    print("\n" + "-"*80)
    print("Validating Blockchain")
    print("-"*80)
    is_valid = blockchain.is_chain_valid()
    print(f"Blockchain is valid: {is_valid}")
    
    # Display chain info
    print("\n" + "-"*80)
    print("Blockchain Information")
    print("-"*80)
    info = blockchain.get_chain_info()
    for key, value in info.items():
        print(f"  {key}: {value}")
    
    # Demonstrate tampering detection
    print("\n" + "-"*80)
    print("Testing Tampering Detection")
    print("-"*80)
    print("Attempting to tamper with block 1...")
    blockchain.chain[1].transactions[0].amount = 999999.0
    is_valid_after_tamper = blockchain.is_chain_valid()
    print(f"Blockchain is valid after tampering: {is_valid_after_tamper}")
    print("(Expected: False - tampering detected!)")
    
    print("\n" + "="*80)
    print("DEMONSTRATION COMPLETE")
    print("="*80)


if __name__ == "__main__":
    main()
