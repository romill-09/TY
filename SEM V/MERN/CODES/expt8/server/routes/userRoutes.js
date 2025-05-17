import express from 'express';
import User from '../models/user.js'; // Import the User model using ES module syntax

const router = express.Router();

// POST route to create a new user
router.post('/', async (req, res) => {
  const { name, age, email, course } = req.body; // Destructure email and course from the request body

  try {
    // Create a new User with name, age, email, and course
    const newUser = new User({ name, age, email, course });
    await newUser.save();  // Save the new user to the database
    res.status(201).json(newUser); // Send back the created user as a response
  } catch (err) {
    res.status(500).json({ message: 'Error creating user', error: err }); // Handle errors
  }
});

// GET route to fetch all users
router.get('/', async (req, res) => {
  try {
    const users = await User.find();  // Fetch all users from the database
    res.json(users);  // Send users as a response
  } catch (err) {
    res.status(500).json({ message: 'Error fetching users', error: err }); // Handle errors
  }
});

export default router; // Use export default for ES module
