/**
 * Seed script: populate DB with Users, Posts, Comments.
 * Idempotence note: This example clears tables each run—OK for teaching, not production.
 */
const { PrismaClient } = require('@prisma/client');
const prisma = new PrismaClient();

async function main() {
  await prisma.comment.deleteMany();
  await prisma.post.deleteMany();
  await prisma.user.deleteMany();

  const alice = await prisma.user.create({
    data: {
      email: 'alice@example.com',
      name: 'Alice'
    },
    include: { posts: true }
  });

  const bob = await prisma.user.create({
    data: { email: 'bob@example.com', name: 'Bob' }
  });

  const publishedPost = await prisma.post.findFirst({ where: { published: true } });
  if (publishedPost) {
    await prisma.comment.create({
      data: {
        content: 'Great write-up!',
        authorId: bob.id,
        postId: publishedPost.id
      }
    });
  }

  console.log('Seed complete:', { alice, bob, publishedPost });
}

main()
  .catch((e) => { console.error(e); process.exit(1); })
  .finally(async () => { await prisma.$disconnect(); });
