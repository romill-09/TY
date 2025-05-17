import React, { useState, useEffect } from 'react';
import {
  Card,
  CardContent,
  Typography,
  TextField,
  Button,
  List,
  ListItem,
  ListItemText,
  Box,
  Container,
} from '@mui/material';
import { PersonAdd, Group } from '@mui/icons-material';
import axios from 'axios';

const UserForm = () => {
  const [users, setUsers] = useState([]);
  const [name, setName] = useState('');
  const [age, setAge] = useState('');
  const [email, setEmail] = useState('');
  const [course, setCourse] = useState('');

  // Fetch users from the backend
  const fetchUsers = async () => {
    try {
      const response = await axios.get('http://localhost:5000/api/users');
      setUsers(response.data);
    } catch (error) {
      console.error('Error fetching users:', error);
    }
  };

  // Submit user to the backend
  const handleSubmit = async (e) => {
    e.preventDefault();
    if (name && age && email && course) {
      try {
        // Post user data to the backend
        const newUser = { name, age, email, course };
        await axios.post('http://localhost:5000/api/users', newUser);

        // Clear the form fields
        setName('');
        setAge('');
        setEmail('');
        setCourse('');

        // Refresh the users list after submission
        fetchUsers();
      } catch (error) {
        console.error('Error submitting user:', error);
      }
    }
  };

  // Fetch users on initial load
  useEffect(() => {
    fetchUsers();
  }, []);

  return (
    <Container maxWidth="sm" sx={{ minHeight: '100vh', display: 'flex', alignItems: 'center', justifyContent: 'center' }}>
      <Card sx={{ width: '100%', bgcolor: 'background.paper' }}>
        <CardContent>
          <Typography variant="h5" component="div" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
            <PersonAdd /> Add New User
          </Typography>
          <Box component="form" onSubmit={handleSubmit} sx={{ mt: 2 }}>
            <TextField
              fullWidth
              label="Name"
              value={name}
              onChange={(e) => setName(e.target.value)}
              required
              margin="normal"
            />
            <TextField
              fullWidth
              label="Age"
              type="number"
              value={age}
              onChange={(e) => setAge(e.target.value)}
              required
              inputProps={{ min: 0, max: 150 }}
              margin="normal"
            />
            <TextField
              fullWidth
              label="Email"
              type="email"
              value={email}
              onChange={(e) => setEmail(e.target.value)}
              required
              margin="normal"
            />
            <TextField
              fullWidth
              label="Course"
              value={course}
              onChange={(e) => setCourse(e.target.value)}
              required
              margin="normal"
            />
            <Button
              type="submit"
              variant="contained"
              color="primary"
              fullWidth
              sx={{ mt: 2 }}
            >
              Submit
            </Button>
          </Box>

          <Box sx={{ mt: 4 }}>
            <Typography variant="h6" gutterBottom sx={{ display: 'flex', alignItems: 'center', gap: 1 }}>
              <Group /> Users List
            </Typography>
            {users.length === 0 ? (
              <Typography color="text.secondary" align="center">
                No users added yet
              </Typography>
            ) : (
              <List sx={{ maxHeight: 200, overflow: 'auto', border: 1, borderColor: 'divider', borderRadius: 1 }}>
                {users.map((user, index) => (
                  <ListItem key={index} divider>
                    <ListItemText
                      primary={user.name}
                      secondary={`${user.age} years old, ${user.email}, ${user.course}`}
                    />
                  </ListItem>
                ))}
              </List>
            )}
          </Box>
        </CardContent>
      </Card>
    </Container>
  );
};

export default UserForm;
