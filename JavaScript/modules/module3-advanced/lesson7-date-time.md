# Lesson 7: Date and Time

## 🎯 Learning Objectives

By the end of this lesson, you will be able to:

- Create and manipulate Date objects
- Format dates for display
- Work with timestamps
- Calculate time differences
- Handle time zones
- Create date utilities

## 📚 Working with Dates

### Creating Dates
```javascript
// Current date and time
const now = new Date();

// Specific date
const specificDate = new Date('2023-12-25');
const dateWithTime = new Date('2023-12-25T10:30:00');

// Date from timestamp
const timestamp = 1703505000000;
const dateFromTimestamp = new Date(timestamp);
```

### Date Methods
```javascript
const date = new Date();

console.log(date.getFullYear()); // 2023
console.log(date.getMonth()); // 11 (0-based)
console.log(date.getDate()); // 25
console.log(date.getHours()); // 10
console.log(date.getMinutes()); // 30
console.log(date.getSeconds()); // 0
```

### Formatting Dates
```javascript
function formatDate(date) {
    const options = {
        year: 'numeric',
        month: 'long',
        day: 'numeric',
        hour: '2-digit',
        minute: '2-digit'
    };
    
    return date.toLocaleDateString('en-US', options);
}

// Usage
const formatted = formatDate(new Date());
console.log(formatted); // "December 25, 2023 at 10:30 AM"
```

## 🎯 Practice Exercises

### Exercise 1: Date Calculator
Create a utility for date calculations:

**Solution:**
```javascript
class DateCalculator {
    static daysBetween(date1, date2) {
        const timeDiff = Math.abs(date2.getTime() - date1.getTime());
        return Math.ceil(timeDiff / (1000 * 3600 * 24));
    }
    
    static addDays(date, days) {
        const result = new Date(date);
        result.setDate(result.getDate() + days);
        return result;
    }
    
    static isWeekend(date) {
        const day = date.getDay();
        return day === 0 || day === 6; // Sunday or Saturday
    }
    
    static formatRelative(date) {
        const now = new Date();
        const diffInSeconds = Math.floor((now - date) / 1000);
        
        if (diffInSeconds < 60) return 'Just now';
        if (diffInSeconds < 3600) return `${Math.floor(diffInSeconds / 60)} minutes ago`;
        if (diffInSeconds < 86400) return `${Math.floor(diffInSeconds / 3600)} hours ago`;
        if (diffInSeconds < 2592000) return `${Math.floor(diffInSeconds / 86400)} days ago`;
        
        return date.toLocaleDateString();
    }
}

// Usage
const today = new Date();
const tomorrow = DateCalculator.addDays(today, 1);
console.log('Days between:', DateCalculator.daysBetween(today, tomorrow));
console.log('Is weekend:', DateCalculator.isWeekend(today));
console.log('Relative time:', DateCalculator.formatRelative(today));
```

## 🎯 Key Takeaways

1. **Date objects** represent specific moments in time
2. **Date methods** access different parts of dates
3. **toLocaleDateString** formats dates for display
4. **Timestamps** are milliseconds since epoch
5. **Date calculations** enable time-based features

---

**Next Lesson**: [Lesson 8: Regular Expressions](./lesson8-regex.md)
