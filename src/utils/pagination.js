/**
 * Cursor pagination helper.
 * Accepts `take` (1..100, default 10) and `cursor` (last id).
 */
function parsePagination(query) {
  const take = Math.max(1, Math.min(100, Number(query.take) || 10));
  const cursor = query.cursor ? { id: Number(query.cursor) } : undefined;
  return { take, cursor };
}

module.exports = { parsePagination };
