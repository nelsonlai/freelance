// Exercise 1: Event-Driven Calculator
// This exercise demonstrates event handling with a calculator application

console.log("=== Exercise 1: Event-Driven Calculator ===");

// Calculator class with event handling
class Calculator {
    constructor() {
        this.display = '0';
        this.previousValue = null;
        this.operation = null;
        this.waitingForNewValue = false;
        this.eventListeners = {};
    }
    
    addEventListener(event, handler) {
        if (!this.eventListeners[event]) {
            this.eventListeners[event] = [];
        }
        this.eventListeners[event].push(handler);
    }
    
    dispatchEvent(event, data = {}) {
        if (this.eventListeners[event]) {
            this.eventListeners[event].forEach(handler => {
                handler({ ...data, calculator: this });
            });
        }
    }
    
    // Calculator operations
    inputDigit(digit) {
        if (this.waitingForNewValue) {
            this.display = digit;
            this.waitingForNewValue = false;
        } else {
            this.display = this.display === '0' ? digit : this.display + digit;
        }
        
        this.dispatchEvent('displayChanged', { display: this.display });
    }
    
    inputDecimal() {
        if (this.waitingForNewValue) {
            this.display = '0.';
            this.waitingForNewValue = false;
        } else if (this.display.indexOf('.') === -1) {
            this.display += '.';
        }
        
        this.dispatchEvent('displayChanged', { display: this.display });
    }
    
    inputOperation(nextOperation) {
        const inputValue = parseFloat(this.display);
        
        if (this.previousValue === null) {
            this.previousValue = inputValue;
        } else if (this.operation) {
            const currentValue = this.previousValue || 0;
            const newValue = this.performCalculation(currentValue, inputValue, this.operation);
            
            this.display = String(newValue);
            this.previousValue = newValue;
            
            this.dispatchEvent('calculationPerformed', { 
                operation: this.operation, 
                result: newValue 
            });
        }
        
        this.waitingForNewValue = true;
        this.operation = nextOperation;
        
        this.dispatchEvent('operationChanged', { operation: nextOperation });
    }
    
    performCalculation(firstValue, secondValue, operation) {
        switch (operation) {
            case '+':
                return firstValue + secondValue;
            case '-':
                return firstValue - secondValue;
            case '*':
                return firstValue * secondValue;
            case '/':
                return secondValue !== 0 ? firstValue / secondValue : 0;
            case '=':
                return secondValue;
            default:
                return secondValue;
        }
    }
    
    clear() {
        this.display = '0';
        this.previousValue = null;
        this.operation = null;
        this.waitingForNewValue = false;
        
        this.dispatchEvent('cleared');
        this.dispatchEvent('displayChanged', { display: this.display });
    }
    
    calculate() {
        if (this.operation && this.previousValue !== null) {
            const inputValue = parseFloat(this.display);
            const newValue = this.performCalculation(this.previousValue, inputValue, this.operation);
            
            this.display = String(newValue);
            this.previousValue = null;
            this.operation = null;
            this.waitingForNewValue = true;
            
            this.dispatchEvent('calculationPerformed', { 
                operation: this.operation, 
                result: newValue 
            });
            this.dispatchEvent('displayChanged', { display: this.display });
        }
    }
}

// Calculator UI class
class CalculatorUI {
    constructor(calculator) {
        this.calculator = calculator;
        this.setupEventListeners();
    }
    
    setupEventListeners() {
        // Display change listener
        this.calculator.addEventListener('displayChanged', (event) => {
            console.log(`Display updated: ${event.display}`);
        });
        
        // Operation change listener
        this.calculator.addEventListener('operationChanged', (event) => {
            console.log(`Operation changed to: ${event.operation}`);
        });
        
        // Calculation performed listener
        this.calculator.addEventListener('calculationPerformed', (event) => {
            console.log(`Calculation performed: ${event.result}`);
        });
        
        // Clear listener
        this.calculator.addEventListener('cleared', () => {
            console.log('Calculator cleared');
        });
    }
    
    simulateButtonPress(buttonValue) {
        console.log(`\nButton pressed: ${buttonValue}`);
        
        if (buttonValue >= '0' && buttonValue <= '9') {
            this.calculator.inputDigit(buttonValue);
        } else if (buttonValue === '.') {
            this.calculator.inputDecimal();
        } else if (['+', '-', '*', '/'].includes(buttonValue)) {
            this.calculator.inputOperation(buttonValue);
        } else if (buttonValue === '=') {
            this.calculator.calculate();
        } else if (buttonValue === 'C') {
            this.calculator.clear();
        }
    }
}

// Test the calculator
console.log("Testing calculator functionality...");

const calculator = new Calculator();
const calculatorUI = new CalculatorUI(calculator);

// Test sequence: 5 + 3 * 2 = 16
console.log("\n=== Test Sequence: 5 + 3 * 2 ===");
calculatorUI.simulateButtonPress('5');
calculatorUI.simulateButtonPress('+');
calculatorUI.simulateButtonPress('3');
calculatorUI.simulateButtonPress('*');
calculatorUI.simulateButtonPress('2');
calculatorUI.simulateButtonPress('=');

// Test sequence: Clear and start over
console.log("\n=== Test Sequence: Clear and 10 / 2 ===");
calculatorUI.simulateButtonPress('C');
calculatorUI.simulateButtonPress('1');
calculatorUI.simulateButtonPress('0');
calculatorUI.simulateButtonPress('/');
calculatorUI.simulateButtonPress('2');
calculatorUI.simulateButtonPress('=');

// Test sequence: Decimal operations
console.log("\n=== Test Sequence: Decimal operations ===");
calculatorUI.simulateButtonPress('C');
calculatorUI.simulateButtonPress('3');
calculatorUI.simulateButtonPress('.');
calculatorUI.simulateButtonPress('1');
calculatorUI.simulateButtonPress('4');
calculatorUI.simulateButtonPress('*');
calculatorUI.simulateButtonPress('2');
calculatorUI.simulateButtonPress('=');

// Test sequence: Error handling (division by zero)
console.log("\n=== Test Sequence: Division by zero ===");
calculatorUI.simulateButtonPress('C');
calculatorUI.simulateButtonPress('5');
calculatorUI.simulateButtonPress('/');
calculatorUI.simulateButtonPress('0');
calculatorUI.simulateButtonPress('=');

// Advanced calculator with history
class AdvancedCalculator extends Calculator {
    constructor() {
        super();
        this.history = [];
    }
    
    performCalculation(firstValue, secondValue, operation) {
        const result = super.performCalculation(firstValue, secondValue, operation);
        
        // Add to history
        this.history.push({
            firstValue,
            secondValue,
            operation,
            result,
            timestamp: new Date().toISOString()
        });
        
        this.dispatchEvent('historyUpdated', { history: this.history });
        
        return result;
    }
    
    getHistory() {
        return this.history;
    }
    
    clearHistory() {
        this.history = [];
        this.dispatchEvent('historyCleared');
    }
}

// Test advanced calculator
console.log("\n=== Testing Advanced Calculator with History ===");

const advancedCalculator = new AdvancedCalculator();
const advancedUI = new CalculatorUI(advancedCalculator);

// Add history listener
advancedCalculator.addEventListener('historyUpdated', (event) => {
    console.log(`History updated. Total entries: ${event.history.length}`);
    const lastEntry = event.history[event.history.length - 1];
    console.log(`Last calculation: ${lastEntry.firstValue} ${lastEntry.operation} ${lastEntry.secondValue} = ${lastEntry.result}`);
});

advancedCalculator.addEventListener('historyCleared', () => {
    console.log('History cleared');
});

// Perform calculations to build history
console.log("\nBuilding calculation history...");
advancedUI.simulateButtonPress('7');
advancedUI.simulateButtonPress('+');
advancedUI.simulateButtonPress('3');
advancedUI.simulateButtonPress('=');

advancedUI.simulateButtonPress('5');
advancedUI.simulateButtonPress('*');
advancedUI.simulateButtonPress('4');
advancedUI.simulateButtonPress('=');

advancedUI.simulateButtonPress('1');
advancedUI.simulateButtonPress('0');
advancedUI.simulateButtonPress('/');
advancedUI.simulateButtonPress('2');
advancedUI.simulateButtonPress('=');

console.log("\nFinal history:");
advancedCalculator.getHistory().forEach((entry, index) => {
    console.log(`${index + 1}. ${entry.firstValue} ${entry.operation} ${entry.secondValue} = ${entry.result}`);
});

console.log("\n=== Event-Driven Calculator Summary ===");
console.log("✓ Calculator class with event-driven architecture");
console.log("✓ Event listeners for display, operations, and calculations");
console.log("✓ Calculator UI with event simulation");
console.log("✓ Advanced calculator with history tracking");
console.log("✓ Event handling for user interactions");
console.log("✓ Real-time updates and notifications");
console.log("✓ Error handling for edge cases");
