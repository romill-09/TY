import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import StudentList from './components/StudentList';
import AddStudent from './components/AddStudent';
import UpdateStudent from './components/UpdateStudent';
import DeleteStudent from './components/DeleteStudent';
import './App.css'

function App() {
  return (
    <Router>
      <Routes>
        <Route path="/" element={<StudentList />} />
        <Route path="/add-Student" element = {<AddStudent />} />
        <Route path="/update-Student" element = {<UpdateStudent />} />
        <Route path="/delete-Student" element = {<DeleteStudent />} />
      </Routes>
    </Router>
  )
}

export default App