import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

async function main() {
  console.log('🌱 Seeding database with demo data...');

  // Clear existing data
  await prisma.record.deleteMany();

  // Create demo records
  const demoRecords = [
    {
      username: 'admin',
      email: 'admin@demo.com',
      password: 'Admin123!@#',
    },
    {
      username: 'user1',
      email: 'user1@demo.com',
      password: 'User1Pass!',
    },
    {
      username: 'demo_user',
      email: 'demo@example.com',
      password: 'DemoPass123!',
    },
  ];

  for (const record of demoRecords) {
    await prisma.record.create({
      data: record,
    });
    console.log(`✅ Created record: ${record.username}`);
  }

  console.log('🎉 Database seeded successfully!');
}

main()
  .catch((e) => {
    console.error('❌ Error seeding database:', e);
    process.exit(1);
  })
  .finally(async () => {
    await prisma.$disconnect();
  });
