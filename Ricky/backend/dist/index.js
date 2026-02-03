import dotenv from 'dotenv';
dotenv.config();
import app from './server/app.js';
const port = Number(process.env.PORT || 4000);
app.listen(port, () => {
    console.log(`API listening on http://localhost:${port}`);
});
//# sourceMappingURL=index.js.map