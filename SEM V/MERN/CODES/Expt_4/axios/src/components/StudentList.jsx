import React, { useState, useEffect } from "react";
import axios from "axios";
import { Link } from "react-router-dom";
import "../studentlist.css";

const URL = "http://localhost:3000/students";

const StudentList = () => {
  const [students, setStudents] = useState([]);

  useEffect(() => {
    const fetchStudents = async () => {
      try {
        const response = await axios.get(URL);
        setStudents(response.data);
      } catch (error) {
        console.error("Error fetching students:", error);
      }
    };
    fetchStudents();
  }, []);

  const handleDelete = async (name) => {
    try {
      const response = await axios.get(URL);
      const student = response.data.find(student => student.name === name);
      if (student) {
        await axios.delete(`${URL}/${student.id}`);
        setStudents(students.filter((student) => student.name !== name));
      }
    } catch (error) {
      console.error("Error deleting student:", error);
    }
  };

  return (
    <>
      <div className="student-data">
        <h1>Student List</h1>
        {students.length > 0 ? (
          <table className="student-table">
            <thead>
              <tr>
                <th>Name</th>
                <th>Age</th>
                <th>Actions</th>
              </tr>
            </thead>
            <tbody>
              {students.map((student) => (
                <tr key={student.id}>
                  <td>{student.name}</td>
                  <td>{student.age}</td>
                  <td>
                    <Link
                      to="/update-student"
                      state={{ studentName: student.name }}
                      className="btn btn-secondary"
                    >
                      Edit
                    </Link>
                    <button
                      onClick={() => handleDelete(student.name)}
                      className="btn btn-danger"
                    >
                      Delete
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>
        ) : (
          <p>No students found.</p>
        )}
      </div>

      <div>
        <Link to="/add-student" className="btn btn-primary">
          Add New Student
        </Link>
      </div>
    </>
  );
};

export default StudentList;
