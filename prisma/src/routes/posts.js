/**
 * Posts routes: CRUD, cursor pagination, select/include, interactive transaction.
 */
const express = require('express');
const router = express.Router();
const { prisma } = require('../prisma');
const { parsePagination } = require('../utils/pagination');

module.exports = router;

// GET /posts?take=&cursor=&published=&authorEmail=
router.get('/', async (req, res, next) => {
  try {
    const { take, cursor } = parsePagination(req.query);
    const where = {};
    if (req.query.published === 'true') where.published = true;
    if (req.query.published === 'false') where.published = false;
    if (req.query.authorEmail) where.author = { is: { email: req.query.authorEmail } };

    const items = await prisma.post.findMany({
      where,
      take,
      ...(cursor ? { skip: 1, cursor } : {}),
      orderBy: { id: 'asc' },
      select: {
        id: true, title: true, published: true, authorId: true,
        createdAt: true, updatedAt: true,
      },
    });
    const nextCursor = items.length === take ? items[items.length - 1].id : null;
    res.json({ data: items, nextCursor });
  } catch (err) { next(err); }
});

// GET /posts/:id
router.get('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const post = await prisma.post.findUnique({
      where: { id },
      include: { author: true, comments: { orderBy: { createdAt: 'desc' } } },
    });
    if (!post) return res.status(404).json({ error: { message: 'Post not found' } });
    res.json({ data: post });
  } catch (err) { next(err); }
});

// POST /posts  { title, content?, authorEmail? }
router.post('/', async (req, res, next) => {
  try {
    const { title, content, authorEmail } = req.body;
    const post = await prisma.post.create({
      data: {
        title,
        content,
        author: authorEmail ? { connect: { email: authorEmail } } : undefined,
      },
      include: { author: true },
    });
    res.status(201).json({ data: post });
  } catch (err) { next(err); }
});

// PATCH /posts/:id
router.patch('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    const { title, content, published, authorEmail } = req.body;
    const post = await prisma.post.update({
      where: { id },
      data: {
        title,
        content,
        published,
        author: authorEmail ? { connect: { email: authorEmail } } : undefined,
      },
      select: { id: true, title: true, published: true, updatedAt: true },
    });
    res.json({ data: post });
  } catch (err) { next(err); }
});

// POST /posts/:id/publish — business rule via interactive transaction
router.post('/:id/publish', async (req, res, next) => {
  const id = Number(req.params.id);
  try {
    const result = await prisma.$transaction(async (tx) => {
      const p = await tx.post.findUnique({ where: { id } });
      if (!p) { const e = new Error('Post not found'); e.status = 404; throw e; }
      if (!p.content || p.content.trim().length === 0) {
        const e = new Error('Cannot publish a post without content');
        e.status = 400; throw e;
      }
      return await tx.post.update({
        where: { id },
        data: { published: true },
        select: { id: true, title: true, published: true },
      });
    });
    res.json({ data: result });
  } catch (err) { next(err); }
});

// DELETE /posts/:id
router.delete('/:id', async (req, res, next) => {
  try {
    const id = Number(req.params.id);
    await prisma.post.delete({ where: { id } });
    res.status(204).send();
  } catch (err) { next(err); }
});

// GET /posts/:id/comments
router.get('/:id/comments', async (req, res, next) => {
  try {
    const postId = Number(req.params.id);
    const comments = await prisma.comment.findMany({
      where: { postId },
      orderBy: { createdAt: 'desc' },
      include: { author: { select: { id: true, email: true, name: true } } },
    });
    res.json({ data: comments });
  } catch (err) { next(err); }
});

// POST /posts/:id/comments  { authorId|authorEmail, content }
router.post('/:id/comments', async (req, res, next) => {
  try {
    const postId = Number(req.params.id);
    const { authorId, authorEmail, content } = req.body;
    if (!content || !content.trim()) { const e = new Error('Comment content is required'); e.status = 400; throw e; }
    let author;
    if (authorId) author = { connect: { id: Number(authorId) } };
    else if (authorEmail) author = { connect: { email: authorEmail } };
    else { const e = new Error('authorId or authorEmail is required'); e.status = 400; throw e; }
    const created = await prisma.comment.create({
      data: { content, post: { connect: { id: postId } }, author },
      include: { author: true, post: true },
    });
    res.status(201).json({ data: created });
  } catch (err) { next(err); }
});

module.exports = router;
