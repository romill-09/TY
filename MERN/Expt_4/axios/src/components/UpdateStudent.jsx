import React, { useState, useEffect } from 'react';
import axios from 'axios';
import { useNavigate, useLocation } from 'react-router-dom';
import "../updatestudent.css";

const URL = "http://localhost:3000/students";

const UpdateStudent = () => {
  const navigate = useNavigate();
  const location = useLocation();
  const { studentName } = location.state || {};

  const [name, setName] = useState('');
  const [age, setAge] = useState('');

  useEffect(() => {
    const fetchStudent = async () => {
      try {
        const response = await axios.get(URL);
        const student = response.data.find(student => student.name === studentName);
        if (student) {
          setName(student.name);
          setAge(student.age);
        }
      } catch (error) {
        console.error('Error fetching student data:', error);
      }
    };
    fetchStudent();
  }, [studentName]);

  const handleSubmit = async (e) => {
    e.preventDefault();
    try {
      const response = await axios.get(URL);
      const students = response.data;
      const student = students.find(student => student.name === studentName);

      if (student) {
        await axios.put(`${URL}/${student.id}`, { name, age });
        navigate('/');
      }
    } catch (error) {
      console.error('Error updating student:', error);
    }
  };

  return (
    <div>
      <h2>Update Student</h2>
      <form onSubmit={handleSubmit}>
        <div>
          <label>Name:</label>
          <input 
            type="text" 
            value={name} 
            onChange={(e) => setName(e.target.value)} 
            required 
          />
        </div>
        <div>
          <label>Age:</label>
          <input 
            type="number" 
            value={age} 
            onChange={(e) => setAge(e.target.value)} 
            required 
          />
        </div>
        <button type="submit">Update Student</button>
      </form>
    </div>
  );
};

export default UpdateStudent;
