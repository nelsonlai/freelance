// Database seed script for testing purposes
// Populates the database with sample questionnaire responses
// Useful for testing the metrics endpoint and verifying functionality

import { PrismaClient } from '@prisma/client';

const prisma = new PrismaClient();

// Sample response data for testing
const sampleResponses = [
  {
    answers: {
      q1: 'A',
      q2: ['X', 'Y'],
      q3: 'This is a great questionnaire system!'
    },
    userAgent: 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36',
    ipHash: 'sample_hash_1'
  },
  {
    answers: {
      q1: 'B',
      q2: ['Z'],
      q3: 'Very useful for collecting feedback.'
    },
    userAgent: 'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36',
    ipHash: 'sample_hash_2'
  },
  {
    answers: {
      q1: 'C',
      q2: ['X', 'Y', 'Z'],
      q3: 'Excellent implementation with good validation.'
    },
    userAgent: 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36',
    ipHash: 'sample_hash_3'
  },
  {
    answers: {
      q1: 'A',
      q2: [],
      q3: 'Simple and effective design.'
    },
    userAgent: 'Mozilla/5.0 (iPhone; CPU iPhone OS 14_7_1 like Mac OS X)',
    ipHash: 'sample_hash_4'
  },
  {
    answers: {
      q1: 'B',
      q2: ['Y'],
      q3: 'Good user experience overall.'
    },
    userAgent: 'Mozilla/5.0 (Android 11; Mobile; rv:91.0) Gecko/91.0',
    ipHash: 'sample_hash_5'
  }
];

async function main() {
  console.log('🌱 Starting database seeding...');

  try {
    // Clear existing data (optional - comment out if you want to keep existing data)
    console.log('🗑️  Clearing existing responses...');
    await prisma.response.deleteMany({});
    console.log('✅ Existing responses cleared');

    // Insert sample responses
    console.log('📝 Inserting sample responses...');
    for (const response of sampleResponses) {
      await prisma.response.create({
        data: response
      });
    }
    console.log(`✅ ${sampleResponses.length} sample responses created`);

    // Verify the data
    const totalResponses = await prisma.response.count();
    console.log(`📊 Total responses in database: ${totalResponses}`);

    // Test metrics endpoint logic
    const responses = await prisma.response.findMany({
      select: { answers: true }
    });

    const counts: any = {
      q1: { A: 0, B: 0, C: 0 },
      q2: { X: 0, Y: 0, Z: 0 }
    };

    responses.forEach((response) => {
      const answers = response.answers as any;
      
      if (answers.q1 && counts.q1[answers.q1] !== undefined) {
        counts.q1[answers.q1]++;
      }
      
      if (answers.q2 && Array.isArray(answers.q2)) {
        answers.q2.forEach((option: string) => {
          if (counts.q2[option] !== undefined) {
            counts.q2[option]++;
          }
        });
      }
    });

    console.log('📈 Sample metrics:');
    console.log('  Total submissions:', totalResponses);
    console.log('  Q1 counts:', counts.q1);
    console.log('  Q2 counts:', counts.q2);

    console.log('🎉 Database seeding completed successfully!');

  } catch (error) {
    console.error('❌ Error during seeding:', error);
    throw error;
  } finally {
    await prisma.$disconnect();
  }
}

// Run the seed function
main()
  .catch((error) => {
    console.error('❌ Seeding failed:', error);
    process.exit(1);
  });
