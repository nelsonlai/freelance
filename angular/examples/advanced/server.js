const express = require('express');
const cors = require('cors');

const app = express();
const PORT = process.env.PORT || 4000;

app.use(cors());
app.use(express.json());

// Mock projects data
const projects = {
  tenant1: [
    { id: '1', name: 'Project Alpha', status: 'active', budget: 50000, tenantId: 'tenant1' },
    { id: '2', name: 'Project Beta', status: 'draft', budget: 30000, tenantId: 'tenant1' },
    { id: '3', name: 'Project Gamma', status: 'active', tenantId: 'tenant1' },
    { id: '4', name: 'Project Delta', status: 'archived', budget: 75000, tenantId: 'tenant1' },
  ],
  tenant2: [
    { id: '5', name: 'Project Epsilon', status: 'active', budget: 40000, tenantId: 'tenant2' },
    { id: '6', name: 'Project Zeta', status: 'draft', tenantId: 'tenant2' },
  ],
};

app.get('/api/tenants/:tenantId/projects', (req, res) => {
  const { tenantId } = req.params;
  const tenantProjects = projects[tenantId] || [];
  console.log(`📋 Get projects for tenant: ${tenantId}`);
  res.json(tenantProjects);
});

app.listen(PORT, () => {
  console.log(`Backend listening on http://localhost:${PORT}`);
});

