const express = require('express');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

app.use(cors());
app.use(express.json());

app.post('/api/contact', (req, res) => {
  const data = req.body ?? {};
  console.log('📩 Registration received:', data);

  res.json({
    message: 'Registration payload received by backend.',
    receivedAt: new Date().toISOString(),
    data,
  });
});

app.listen(PORT, () => {
  console.log(`Backend listening on http://localhost:${PORT}`);
});
