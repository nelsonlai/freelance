"""
Interactive Blockchain Demo

This script provides an interactive demonstration of the blockchain.
Run this to see the blockchain in action with various scenarios.
"""

from blockchain import Blockchain, Wallet, Transaction
import time


def scenario_1_basic_usage():
    """Demonstrate basic blockchain operations."""
    print("\n" + "="*80)
    print("SCENARIO 1: Basic Blockchain Operations")
    print("="*80)
    
    blockchain = Blockchain(difficulty=3, mining_reward=50.0)
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    
    print(f"\nCreated blockchain with difficulty {blockchain.difficulty}")
    print(f"Created wallets: {alice.name} and {bob.name}")
    
    # Mine first block
    print("\n--- Mining first block (Alice gets reward) ---")
    blockchain.mine_pending_transactions(alice.address)
    
    # Add transaction
    print("\n--- Adding transaction ---")
    blockchain.add_transaction(alice.create_transaction(bob.address, 20.0))
    
    # Mine second block
    print("\n--- Mining second block (Bob gets reward) ---")
    blockchain.mine_pending_transactions(bob.address)
    
    # Show results
    blockchain.print_chain()
    blockchain.print_balances()
    
    print(f"Blockchain valid: {blockchain.is_chain_valid()}")


def scenario_2_multiple_transactions():
    """Demonstrate multiple transactions in one block."""
    print("\n" + "="*80)
    print("SCENARIO 2: Multiple Transactions in One Block")
    print("="*80)
    
    blockchain = Blockchain(difficulty=3, mining_reward=100.0)
    wallets = [Wallet(f"User{i}") for i in range(1, 6)]
    
    print(f"\nCreated {len(wallets)} wallets")
    
    # Mine first block
    print("\n--- Mining first block ---")
    blockchain.mine_pending_transactions(wallets[0].address)
    
    # Add multiple transactions
    print("\n--- Adding multiple transactions ---")
    blockchain.add_transaction(wallets[0].create_transaction(wallets[1].address, 10.0))
    blockchain.add_transaction(wallets[0].create_transaction(wallets[2].address, 15.0))
    blockchain.add_transaction(wallets[0].create_transaction(wallets[3].address, 20.0))
    blockchain.add_transaction(wallets[1].create_transaction(wallets[4].address, 5.0))
    
    # Mine block with all transactions
    print("\n--- Mining block with all transactions ---")
    blockchain.mine_pending_transactions(wallets[1].address)
    
    blockchain.print_chain()
    blockchain.print_balances()


def scenario_3_insufficient_balance():
    """Demonstrate transaction validation (insufficient balance)."""
    print("\n" + "="*80)
    print("SCENARIO 3: Transaction Validation - Insufficient Balance")
    print("="*80)
    
    blockchain = Blockchain(difficulty=3, mining_reward=50.0)
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    
    # Mine first block
    blockchain.mine_pending_transactions(alice.address)
    
    print(f"\nAlice's balance: {blockchain.get_balance(alice.address)}")
    print(f"Bob's balance: {blockchain.get_balance(bob.address)}")
    
    # Try to send more than available
    print("\n--- Attempting to send 100 coins (Alice only has 50) ---")
    success = blockchain.add_transaction(alice.create_transaction(bob.address, 100.0))
    print(f"Transaction accepted: {success}")
    
    blockchain.print_balances()


def scenario_4_chain_validation():
    """Demonstrate chain validation and tampering detection."""
    print("\n" + "="*80)
    print("SCENARIO 4: Chain Validation and Tampering Detection")
    print("="*80)
    
    blockchain = Blockchain(difficulty=3, mining_reward=50.0)
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    
    # Create some blocks
    blockchain.mine_pending_transactions(alice.address)
    blockchain.add_transaction(alice.create_transaction(bob.address, 20.0))
    blockchain.mine_pending_transactions(bob.address)
    
    print("\n--- Initial state ---")
    print(f"Chain valid: {blockchain.is_chain_valid()}")
    blockchain.print_chain()
    
    # Tamper with a block
    print("\n--- Tampering with block 1 (changing transaction amount) ---")
    original_amount = blockchain.chain[1].transactions[0].amount
    blockchain.chain[1].transactions[0].amount = 999999.0
    print(f"Changed transaction amount from {original_amount} to 999999.0")
    
    # Recalculate hash (this would normally happen automatically)
    blockchain.chain[1].hash = blockchain.chain[1].calculate_hash()
    
    print(f"Chain valid after tampering: {blockchain.is_chain_valid()}")
    print("(Expected: False - tampering detected!)")


def scenario_5_mining_difficulty():
    """Demonstrate the effect of mining difficulty."""
    print("\n" + "="*80)
    print("SCENARIO 5: Mining Difficulty Comparison")
    print("="*80)
    
    difficulties = [2, 3, 4]
    
    for difficulty in difficulties:
        print(f"\n--- Testing difficulty {difficulty} ---")
        blockchain = Blockchain(difficulty=difficulty, mining_reward=50.0)
        alice = Wallet("Alice")
        
        start_time = time.time()
        blockchain.mine_pending_transactions(alice.address)
        elapsed = time.time() - start_time
        
        print(f"Block mined in {elapsed:.4f} seconds")
        print(f"Nonce: {blockchain.get_latest_block().nonce}")
        print(f"Hash: {blockchain.get_latest_block().hash}")


def scenario_6_transaction_history():
    """Demonstrate viewing transaction history."""
    print("\n" + "="*80)
    print("SCENARIO 6: Transaction History")
    print("="*80)
    
    blockchain = Blockchain(difficulty=3, mining_reward=100.0)
    alice = Wallet("Alice")
    bob = Wallet("Bob")
    charlie = Wallet("Charlie")
    
    # Create transactions
    blockchain.mine_pending_transactions(alice.address)
    blockchain.add_transaction(alice.create_transaction(bob.address, 30.0))
    blockchain.add_transaction(alice.create_transaction(charlie.address, 20.0))
    blockchain.mine_pending_transactions(bob.address)
    blockchain.add_transaction(bob.create_transaction(charlie.address, 10.0))
    blockchain.mine_pending_transactions(charlie.address)
    
    print("\n--- Full Blockchain History ---")
    blockchain.print_chain()
    
    print("\n--- Transaction Summary ---")
    total_transactions = sum(len(block.transactions) for block in blockchain.chain)
    print(f"Total blocks: {len(blockchain.chain)}")
    print(f"Total transactions: {total_transactions}")
    
    # Count transactions per address
    print("\n--- Transactions per Address ---")
    for address in [alice.address, bob.address, charlie.address]:
        count = sum(
            len([tx for tx in block.transactions if tx.sender == address or tx.recipient == address])
            for block in blockchain.chain
        )
        print(f"{address[:8]}...: {count} transactions")


def interactive_menu():
    """Interactive menu for running different scenarios."""
    scenarios = {
        '1': ('Basic Blockchain Operations', scenario_1_basic_usage),
        '2': ('Multiple Transactions', scenario_2_multiple_transactions),
        '3': ('Insufficient Balance Validation', scenario_3_insufficient_balance),
        '4': ('Chain Validation & Tampering Detection', scenario_4_chain_validation),
        '5': ('Mining Difficulty Comparison', scenario_5_mining_difficulty),
        '6': ('Transaction History', scenario_6_transaction_history),
        '7': ('Run All Scenarios', None)
    }
    
    while True:
        print("\n" + "="*80)
        print("BLOCKCHAIN DEMONSTRATION MENU")
        print("="*80)
        for key, (name, _) in scenarios.items():
            print(f"  {key}. {name}")
        print("  0. Exit")
        print("="*80)
        
        choice = input("\nSelect a scenario (0-7): ").strip()
        
        if choice == '0':
            print("Goodbye!")
            break
        elif choice == '7':
            for key in ['1', '2', '3', '4', '5', '6']:
                scenarios[key][1]()
                input("\nPress Enter to continue to next scenario...")
        elif choice in scenarios:
            scenarios[choice][1]()
            input("\nPress Enter to continue...")
        else:
            print("Invalid choice. Please try again.")


if __name__ == "__main__":
    print("="*80)
    print("BLOCKCHAIN INTERACTIVE DEMONSTRATION")
    print("="*80)
    print("\nThis demo showcases various blockchain features:")
    print("  - Block creation and mining")
    print("  - Transaction handling")
    print("  - Chain validation")
    print("  - Tampering detection")
    print("  - Mining difficulty")
    print("  - Transaction history")
    
    interactive_menu()
