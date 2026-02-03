import { Router } from 'express';
import { RecordController } from '../controllers/userController';

const router = Router();
const userController = new UserController();

// POST /api/v1/records - Create a new record
router.post('/', userController.createRecord.bind(userController));

// GET /api/v1/records - Get all records
router.get('/', userController.getAllRecords.bind(userController));

// GET /api/v1/records/:id - Get a specific record
router.get('/:id', userController.getRecordById.bind(userController));

// PATCH /api/v1/records/:id - Update a record
router.patch('/:id', userController.updateRecord.bind(userController));

// DELETE /api/v1/records/:id - Delete a record
router.delete('/:id', userController.deleteRecord.bind(userController));

export default router;
