/**
 * Users routes: CRUD + counts and eager loading examples.
 */
const express = require('express');
const router = express.Router();
const { prisma } = require('../prisma');


// GET /users
router.get('/', async (req, res, next) => {
  try {
    const users = await prisma.user.findMany({
      select: {
        id: true,
        email: true,
        name: true,
        _count: { select: { posts: true, comments: true } },
        createdAt: true,
      },
      orderBy: { id: 'asc' },
    });
    res.json({ data: users });
  } catch (err) { next(err); }
});

// GET /users/:id
router.get('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    if (!Number.isInteger(id) || Number.isNaN(id)) {
      return res.status(400).json({ error: { message: 'Invalid user id' } });
    }
    const user = await prisma.user.findUnique({
      where: { id },
      include: {
        posts: { orderBy: { createdAt: 'desc' } },
        comments: { orderBy: { createdAt: 'desc' } },
      },
    });
    if (!user) return res.status(404).json({ error: { message: 'User not found' } });
    res.json({ data: user });
  } catch (err) { next(err); }
});

// POST /users  { email, name? }
router.post('/', async (req, res, next) => {
  try {
    const { email, name, password } = req.body;
    const user = await prisma.user.create({ data: { email, name, password } });
    res.status(201).json({ data: user });
  } catch (err) { next(err); }
});

// PATCH /users/:id
router.patch('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    if (!Number.isInteger(id) || Number.isNaN(id)) {
      return res.status(400).json({ error: { message: 'Invalid user id' } });
    }
    const { email, name } = req.body;
    const user = await prisma.user.update({
      where: { id },
      data: { email, name },
      select: { id: true, email: true, name: true, updatedAt: true },
    });
    res.json({ data: user });
  } catch (err) { next(err); }
});

// DELETE /users/:id
router.delete('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    if (!Number.isInteger(id) || Number.isNaN(id)) {
      return res.status(400).json({ error: { message: 'Invalid user id' } });
    }
    await prisma.user.delete({ where: { id } });
    res.status(204).send();
  } catch (err) { next(err); }
});

module.exports = router;
