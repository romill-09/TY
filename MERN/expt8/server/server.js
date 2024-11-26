import express from 'express';
import mongoose from 'mongoose';
import cors from 'cors';
import bodyParser from 'body-parser';
import userRoutes from './routes/userRoutes.js'; // Ensure to add .js for ES modules

// Initialize express app
const app = express();
const PORT = 5000;

// Middleware
app.use(cors());
app.use(bodyParser.json()); // To parse JSON request bodies

// MongoDB connection
mongoose.connect('mongodb+srv://romilcode09:9GajbaerevskP9Gy@cluster0.n7udn.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0', {
  useNewUrlParser: true,
  useUnifiedTopology: true,
})
  .then(() => console.log('MongoDB connected'))
  .catch((err) => console.log('Error connecting to MongoDB:', err));

// Routes
app.use('/api/users', userRoutes);  // Ensure this route is correctly set up in userRoutes.js

// Start server
app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
