/**
 * Central error handler.
 * For production, avoid leaking stack traces.
 */
function errorHandler(err, req, res, next) {
  console.error('[ErrorHandler]', err);
  const status = err.status || 500;
  res.status(status).json({
    error: {
      message: err.message || 'Internal Server Error',
      stack: process.env.NODE_ENV === 'development' ? err.stack : undefined,
    },
  });
}

module.exports = { errorHandler };
