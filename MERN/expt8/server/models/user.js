import mongoose from 'mongoose';

// Define User schema
const userSchema = new mongoose.Schema({
  name: { type: String, required: true },
  age: { type: Number, required: true },
  email: { type: String, required: true },
  course: { type: String, required: true }
});

const User = mongoose.model('User', userSchema);

export default User; // Export default using ES module syntax
