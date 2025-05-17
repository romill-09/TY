import React from 'react';
import axios from 'axios';
import { useNavigate } from 'react-router-dom';

const URL = "http://localhost:3000/students";

const DeleteStudent = ({ studentId, onStudentDeleted }) => {
  const navigate = useNavigate();

  const handleDelete = async () => {
    try {
      await axios.delete(`${URL}/${studentId}`);
      onStudentDeleted(studentId);
      navigate('/');
    } catch (error) {
      console.error('Error deleting student:', error);
    }
  };

  return (
    <button onClick={handleDelete}>Delete</button>
  );
};

export default DeleteStudent;
