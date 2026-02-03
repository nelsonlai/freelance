import { Router } from 'express';
import { RecordController } from '../controllers/recordController';

const router = Router();
const recordController = new RecordController();

// POST /api/v1/records - Create a new record
router.post('/', recordController.createRecord.bind(recordController));

// GET /api/v1/records - Get all records
router.get('/', recordController.getAllRecords.bind(recordController));

// GET /api/v1/records/:id - Get a specific record
router.get('/:id', recordController.getRecordById.bind(recordController));

// PATCH /api/v1/records/:id - Update a record
router.patch('/:id', recordController.updateRecord.bind(recordController));

// DELETE /api/v1/records/:id - Delete a record
router.delete('/:id', recordController.deleteRecord.bind(recordController));

export default router;
