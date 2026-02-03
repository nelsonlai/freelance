const express = require('express');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

app.use(cors());
app.use(express.json());

// Mock metrics data
app.get('/api/metrics/summary', (req, res) => {
  const metrics = [
    { id: '1', label: 'Total Users', value: 1234, delta: 12 },
    { id: '2', label: 'Active Projects', value: 56, delta: -3 },
    { id: '3', label: 'Revenue', value: 98765, delta: 8 },
    { id: '4', label: 'Tasks Completed', value: 234, delta: 15 },
  ];
  console.log('📊 Metrics requested');
  res.json(metrics);
});

// Mock projects data
app.get('/api/projects', (req, res) => {
  const projects = [
    { name: 'Project Alpha', status: 'active' },
    { name: 'Project Beta', status: 'completed' },
    { name: 'Project Gamma', status: 'active' },
    { name: 'Project Delta', status: 'pending' },
  ];
  console.log('📁 Projects requested');
  res.json(projects);
});

app.listen(PORT, () => {
  console.log(`Backend listening on http://localhost:${PORT}`);
});

