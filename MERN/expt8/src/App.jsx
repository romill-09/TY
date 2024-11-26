import React, { useState, useEffect } from "react";
import axios from "axios";
import { ThemeProvider, createTheme } from "@mui/material/styles";
import CssBaseline from "@mui/material/CssBaseline";
import "./App.css";
import UserForm from "./UserForm"; // Import UserForm component

const theme = createTheme();

function App() {
  const [users, setUsers] = useState([]);

  // Fetch users from backend
  const fetchUsers = async () => {
    try {
      const response = await axios.get("http://localhost:5000/api/users");
      setUsers(response.data);
    } catch (error) {
      console.error("Error fetching users:", error);
    }
  };

  // Fetch users on initial load
  useEffect(() => {
    fetchUsers();
  }, []);

  return (
    <>
      <UserForm /> {/* Add the UserForm component here */}
    </>
  );
}

export default App;
