/**
 * Comments routes: standalone CRUD with relations.
 */
const express = require('express');
const router = express.Router();
const { prisma } = require('../prisma');

// GET /comments
router.get('/', async (req, res, next) => {
  try {
    const comments = await prisma.comment.findMany({
      include: { author: true, post: true },
      orderBy: { id: 'asc' },
    });
    res.json({ data: comments });
  } catch (err) { next(err); }
});

// GET /comments/:id
router.get('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const comment = await prisma.comment.findUnique({
      where: { id },
      include: { author: true, post: true },
    });
    if (!comment) return res.status(404).json({ error: { message: 'Comment not found' } });
    res.json({ data: comment });
  } catch (err) { next(err); }
});

// POST /comments  { content, postId, authorId|authorEmail }
router.post('/', async (req, res, next) => {
  try {
    const { content, authorId, authorEmail, postId } = req.body;
    if (!content || !postId) {
      const e = new Error('content and postId are required'); e.status = 400; throw e;
    }
    const author = authorId
      ? { connect: { id: Number(authorId) } }
      : (authorEmail ? { connect: { email: authorEmail } } : null);
    if (!author) { const e = new Error('authorId or authorEmail is required'); e.status = 400; throw e; }

    const created = await prisma.comment.create({
      data: { content, post: { connect: { id: Number(postId) } }, author },
      include: { author: true, post: true },
    });
    res.status(201).json({ data: created });
  } catch (err) { next(err); }
});

// PATCH /comments/:id
router.patch('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const { content } = req.body;
    const updated = await prisma.comment.update({
      where: { id },
      data: { content },
      select: { id: true, content: true, updatedAt: true },
    });
    res.json({ data: updated });
  } catch (err) { next(err); }
});

// DELETE /comments/:id
router.delete('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    await prisma.comment.delete({ where: { id } });
    res.status(204).send();
  } catch (err) { next(err); }
});

module.exports = router;
