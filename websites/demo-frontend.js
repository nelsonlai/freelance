// ========== Canvas Drawing ==========
const canvas = document.getElementById('myCanvas');
const ctx = canvas.getContext('2d');
ctx.fillStyle = '#3584e4';
ctx.fillRect(10, 10, 80, 40);
ctx.fillStyle = '#e01b24';
ctx.beginPath();
ctx.arc(150, 75, 30, 0, Math.PI * 2);
ctx.fill();
ctx.fillStyle = '#333';
ctx.font = '14px sans-serif';
ctx.fillText('Canvas Demo', 180, 80);

// ========== Range input display ==========
const volume = document.getElementById('volume');
const volumeValue = document.getElementById('volumeValue');
volume.addEventListener('input', () => {
    volumeValue.textContent = volume.value;
});

// ========== Form submit (prevent default, show data) ==========
document.getElementById('demoForm').addEventListener('submit', (e) => {
    e.preventDefault();
    const formData = new FormData(e.target);
    const data = Object.fromEntries(formData.entries());
    document.getElementById('output').textContent = 'Form data (prevented submit):\n' + JSON.stringify(data, null, 2);
});

// ========== DOM & Events: Click counter ==========
let clickCount = 0;
const clickBtn = document.getElementById('clickBtn');
const clickCounter = document.getElementById('clickCounter');
clickBtn.addEventListener('click', () => {
    clickCount++;
    clickCounter.textContent = `Clicks: ${clickCount}`;
    document.getElementById('output').textContent = `Button clicked ${clickCount} time(s)!`;
});

// ========== Toggle highlight ==========
document.getElementById('toggleHighlight').addEventListener('click', () => {
    const output = document.getElementById('output');
    output.classList.toggle('highlight');
});

// ========== Data attributes demo ==========
const dataDiv = document.querySelector('[data-user-id]');
console.log('Data attributes:', dataDiv?.dataset.userId, dataDiv?.dataset.role);

// ========== Fetch API ==========
const output = document.getElementById('output');

const mockUsers = [
    { id: 1, name: "Alice", email: "alice@example.com" },
    { id: 2, name: "Bob", email: "bob@example.com" }
];
const mockPost = { id: 1, title: "Sample Post", body: "This is mock data (shown when API unavailable)." };

async function fetchData(url, fallbackData) {
    output.textContent = 'Loading...';
    try {
        const response = await fetch(url);
        if (!response.ok) throw new Error(`HTTP ${response.status}`);
        const data = await response.json();
        output.textContent = JSON.stringify(data, null, 2);
    } catch (err) {
        output.textContent = 'Using mock data (API unavailable from file:// or offline):\n\n' +
            JSON.stringify(fallbackData, null, 2);
    }
}

document.getElementById('fetchUsers').addEventListener('click', () => {
    fetchData('https://jsonplaceholder.typicode.com/users?_limit=2', mockUsers);
});

document.getElementById('fetchPost').addEventListener('click', () => {
    fetchData('https://jsonplaceholder.typicode.com/posts/1', mockPost);
});
