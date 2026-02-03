// API Base URL
const API_BASE_URL = '/api';

// Tab switching functionality
document.addEventListener('DOMContentLoaded', () => {
    initializeTabs();
    initializeTasks();
    initializeUsers();
});

function initializeTabs() {
    const tabButtons = document.querySelectorAll('.tab-button');
    const tabContents = document.querySelectorAll('.tab-content');

    tabButtons.forEach(button => {
        button.addEventListener('click', () => {
            const targetTab = button.getAttribute('data-tab');

            // Remove active class from all buttons and contents
            tabButtons.forEach(btn => btn.classList.remove('active'));
            tabContents.forEach(content => content.classList.remove('active'));

            // Add active class to clicked button and corresponding content
            button.classList.add('active');
            document.getElementById(`${targetTab}-section`).classList.add('active');
        });
    });
}

// ==================== TASKS API ====================

function initializeTasks() {
    // Fetch tasks on load
    fetchTasks();

    // Create task form
    document.getElementById('create-task-form').addEventListener('submit', handleCreateTask);

    // Refresh button
    document.getElementById('fetch-tasks-btn').addEventListener('click', fetchTasks);
}

async function fetchTasks() {
    try {
        showLoading('tasks-list');
        
        // Demonstrate GET request
        const response = await fetch(`${API_BASE_URL}/tasks`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        const data = await response.json();
        displayResponse('GET', `${API_BASE_URL}/tasks`, data);

        if (data.success) {
            displayTasks(data.data);
        } else {
            showError('tasks-list', 'Failed to fetch tasks');
        }
    } catch (error) {
        showError('tasks-list', `Error: ${error.message}`);
        console.error('Error fetching tasks:', error);
    }
}

async function handleCreateTask(e) {
    e.preventDefault();
    
    const formData = new FormData(e.target);
    const taskData = {
        title: formData.get('title'),
        description: formData.get('description') || undefined,
        completed: formData.get('completed') === 'on',
    };

    try {
        // Demonstrate POST request
        const response = await fetch(`${API_BASE_URL}/tasks`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(taskData),
        });

        const data = await response.json();
        displayResponse('POST', `${API_BASE_URL}/tasks`, data);

        if (data.success) {
            showSuccess('Task created successfully!');
            e.target.reset();
            fetchTasks();
        } else {
            showError('tasks-list', 'Failed to create task');
        }
    } catch (error) {
        showError('tasks-list', `Error: ${error.message}`);
        console.error('Error creating task:', error);
    }
}

async function updateTask(id, taskData) {
    try {
        // Demonstrate PUT request
        const response = await fetch(`${API_BASE_URL}/tasks/${id}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(taskData),
        });

        const data = await response.json();
        displayResponse('PUT', `${API_BASE_URL}/tasks/${id}`, data);

        if (data.success) {
            showSuccess('Task updated successfully!');
            fetchTasks();
        } else {
            showError('tasks-list', 'Failed to update task');
        }
    } catch (error) {
        showError('tasks-list', `Error: ${error.message}`);
        console.error('Error updating task:', error);
    }
}

async function deleteTask(id) {
    if (!confirm('Are you sure you want to delete this task?')) {
        return;
    }

    try {
        // Demonstrate DELETE request
        const response = await fetch(`${API_BASE_URL}/tasks/${id}`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        const data = await response.json();
        displayResponse('DELETE', `${API_BASE_URL}/tasks/${id}`, data);

        if (response.ok) {
            showSuccess('Task deleted successfully!');
            fetchTasks();
        } else {
            showError('tasks-list', 'Failed to delete task');
        }
    } catch (error) {
        showError('tasks-list', `Error: ${error.message}`);
        console.error('Error deleting task:', error);
    }
}

async function testOptionsRequest(endpoint) {
    try {
        // Demonstrate OPTIONS request (CORS preflight)
        const response = await fetch(`${API_BASE_URL}/${endpoint}`, {
            method: 'OPTIONS',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        displayResponse('OPTIONS', `${API_BASE_URL}/${endpoint}`, {
            status: response.status,
            statusText: response.statusText,
            headers: Object.fromEntries(response.headers.entries()),
        });
    } catch (error) {
        console.error('Error with OPTIONS request:', error);
    }
}

function displayTasks(tasks) {
    const container = document.getElementById('tasks-list');
    
    if (!tasks || tasks.length === 0) {
        container.innerHTML = '<div class="empty-state">No tasks found. Create one above!</div>';
        return;
    }

    container.innerHTML = tasks.map(task => `
        <div class="item-card">
            <div class="item-header">
                <div>
                    <div class="item-title">${escapeHtml(task.title)}</div>
                    <div class="item-meta">
                        ID: ${task.id} | 
                        Created: ${new Date(task.createdAt).toLocaleString()} |
                        <span class="badge ${task.completed ? 'badge-success' : 'badge-secondary'}">
                            ${task.completed ? 'Completed' : 'Pending'}
                        </span>
                    </div>
                </div>
            </div>
            ${task.description ? `<div class="item-description">${escapeHtml(task.description)}</div>` : ''}
            <div class="item-actions">
                <button class="btn btn-warning btn-sm" onclick="handleEditTask('${task.id}')">
                    Edit (PUT)
                </button>
                <button class="btn btn-danger btn-sm" onclick="deleteTask('${task.id}')">
                    Delete (DELETE)
                </button>
                <button class="btn btn-secondary btn-sm" onclick="testOptionsRequest('tasks')">
                    Test OPTIONS
                </button>
            </div>
        </div>
    `).join('');
}

function handleEditTask(id) {
    const title = prompt('Enter new title:');
    if (!title) return;

    const description = prompt('Enter new description (optional):');
    const completed = confirm('Is this task completed?');

    updateTask(id, {
        title,
        description: description || undefined,
        completed,
    });
}

// ==================== USERS API ====================

function initializeUsers() {
    // Fetch users on load
    fetchUsers();

    // Create user form
    document.getElementById('create-user-form').addEventListener('submit', handleCreateUser);

    // Refresh button
    document.getElementById('fetch-users-btn').addEventListener('click', fetchUsers);
}

async function fetchUsers() {
    try {
        showLoading('users-list');
        
        // Demonstrate GET request
        const response = await fetch(`${API_BASE_URL}/users`, {
            method: 'GET',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        const data = await response.json();
        displayResponse('GET', `${API_BASE_URL}/users`, data);

        if (data.success) {
            displayUsers(data.data);
        } else {
            showError('users-list', 'Failed to fetch users');
        }
    } catch (error) {
        showError('users-list', `Error: ${error.message}`);
        console.error('Error fetching users:', error);
    }
}

async function handleCreateUser(e) {
    e.preventDefault();
    
    const formData = new FormData(e.target);
    const userData = {
        name: formData.get('name'),
        email: formData.get('email'),
        age: formData.get('age') ? parseInt(formData.get('age')) : undefined,
    };

    try {
        // Demonstrate POST request
        const response = await fetch(`${API_BASE_URL}/users`, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(userData),
        });

        const data = await response.json();
        displayResponse('POST', `${API_BASE_URL}/users`, data);

        if (data.success) {
            showSuccess('User created successfully!');
            e.target.reset();
            fetchUsers();
        } else {
            showError('users-list', 'Failed to create user');
        }
    } catch (error) {
        showError('users-list', `Error: ${error.message}`);
        console.error('Error creating user:', error);
    }
}

async function updateUser(id, userData) {
    try {
        // Demonstrate PUT request
        const response = await fetch(`${API_BASE_URL}/users/${id}`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(userData),
        });

        const data = await response.json();
        displayResponse('PUT', `${API_BASE_URL}/users/${id}`, data);

        if (data.success) {
            showSuccess('User updated successfully!');
            fetchUsers();
        } else {
            showError('users-list', 'Failed to update user');
        }
    } catch (error) {
        showError('users-list', `Error: ${error.message}`);
        console.error('Error updating user:', error);
    }
}

async function deleteUser(id) {
    if (!confirm('Are you sure you want to delete this user?')) {
        return;
    }

    try {
        // Demonstrate DELETE request
        const response = await fetch(`${API_BASE_URL}/users/${id}`, {
            method: 'DELETE',
            headers: {
                'Content-Type': 'application/json',
            },
        });

        const data = await response.json();
        displayResponse('DELETE', `${API_BASE_URL}/users/${id}`, data);

        if (response.ok) {
            showSuccess('User deleted successfully!');
            fetchUsers();
        } else {
            showError('users-list', 'Failed to delete user');
        }
    } catch (error) {
        showError('users-list', `Error: ${error.message}`);
        console.error('Error deleting user:', error);
    }
}

function displayUsers(users) {
    const container = document.getElementById('users-list');
    
    if (!users || users.length === 0) {
        container.innerHTML = '<div class="empty-state">No users found. Create one above!</div>';
        return;
    }

    container.innerHTML = users.map(user => `
        <div class="item-card">
            <div class="item-header">
                <div>
                    <div class="item-title">${escapeHtml(user.name)}</div>
                    <div class="item-meta">
                        ID: ${user.id} | 
                        Email: ${escapeHtml(user.email)} |
                        ${user.age ? `Age: ${user.age} | ` : ''}
                        Created: ${new Date(user.createdAt).toLocaleString()}
                    </div>
                </div>
            </div>
            <div class="item-actions">
                <button class="btn btn-warning btn-sm" onclick="handleEditUser('${user.id}')">
                    Edit (PUT)
                </button>
                <button class="btn btn-danger btn-sm" onclick="deleteUser('${user.id}')">
                    Delete (DELETE)
                </button>
                <button class="btn btn-secondary btn-sm" onclick="testOptionsRequest('users')">
                    Test OPTIONS
                </button>
            </div>
        </div>
    `).join('');
}

function handleEditUser(id) {
    const name = prompt('Enter new name:');
    if (!name) return;

    const email = prompt('Enter new email:');
    if (!email) return;

    const age = prompt('Enter new age (optional):');

    updateUser(id, {
        name,
        email,
        age: age ? parseInt(age) : undefined,
    });
}

// ==================== UTILITY FUNCTIONS ====================

function showLoading(containerId) {
    const container = document.getElementById(containerId);
    container.innerHTML = '<p class="loading">Loading...</p>';
}

function showError(containerId, message) {
    const container = document.getElementById(containerId);
    container.innerHTML = `<div class="error">${escapeHtml(message)}</div>`;
}

function showSuccess(message) {
    // Create a temporary success message
    const successDiv = document.createElement('div');
    successDiv.className = 'success';
    successDiv.textContent = message;
    document.querySelector('.container').insertBefore(
        successDiv,
        document.querySelector('.tabs')
    );
    
    setTimeout(() => {
        successDiv.remove();
    }, 3000);
}

function displayResponse(method, url, data) {
    const responseCard = document.getElementById('response-card');
    const responseContent = document.getElementById('response-content');
    
    responseCard.style.display = 'block';
    responseContent.textContent = JSON.stringify({
        method,
        url,
        timestamp: new Date().toISOString(),
        response: data,
    }, null, 2);
    
    // Scroll to response
    responseCard.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
}

function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}

// Make functions available globally for onclick handlers
window.deleteTask = deleteTask;
window.handleEditTask = handleEditTask;
window.deleteUser = deleteUser;
window.handleEditUser = handleEditUser;
window.testOptionsRequest = testOptionsRequest;

