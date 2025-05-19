# Academic Personnel Management System in C++

This repository demonstrates an **Object-Oriented Personnel Management System** in C++ that manages data for both **students** and **teachers**. The program is menu-driven and allows persistent storage using file handling.

---

## About the Code

This project showcases fundamental Object-Oriented Programming concepts in C++ by simulating an academic personnel system where users can:

- Add new teacher and student records
- Display all or categorized records
- Identify outstanding teachers and students
- Save and retrieve data using file I/O

The system differentiates behavior using runtime polymorphism and employs dynamic memory allocation to handle objects.

---

## How It Works

1. **person** is an abstract base class with common attributes (`name`, `cnic`) and pure virtual functions for polymorphic behavior.
2. **teacher** and **student** inherit from `person` and implement their own versions of input/output methods.
3. The system uses dynamic polymorphism to operate on `person*` pointers and determine the object type using `typeid`.
4. Data is stored to and loaded from a file (`personinfo.txt`) using standard file streams (`ofstream`, `ifstream`).

---

## Class Breakdown

| Class Name | Description |
|------------|-------------|
| `person`   | Abstract base class with common properties like name and CNIC. Defines pure virtual methods for I/O and behavior. |
| `teacher`  | Inherits from `person`. Adds fields like number of publications and academic field. Overrides virtual methods. |
| `student`  | Inherits from `person`. Adds fields like CGPA and degree. Overrides virtual methods. |
| `main()`   | Menu-driven interface for creating, displaying, saving, and reading records. |

---

## Menu Options

Create Teacher Obj To Store Data

Create Student Obj To Store Data

Display Record

Display Stats

Teacher Display

Student Display

Save Data to file

Read Data from file

Exit


---

## Sample Code

Below is a sample flow of how this program works:

```cpp
person* p = new teacher();
p->setter();       // Enter name, CNIC, publications, and field
p->getter();       // Display teacher info
if (p->outstanding()) {
    cout << "Outstanding Teacher";
}

ofstream file("personinfo.txt");
p->savetofile(file);   // Save teacher data to file
file.close();

```
## Data Storage Format

Example data stored in personinfo.txt:

T John Doe

12345-6789012-3

10

Computer Science

S Jane Smith

98765-4321098-7

3.6

Software Engineering
```
