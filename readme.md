---

# 📚 Library Management System  

A **C++ console-based application** for managing library books, issuing, and user interactions. Supports both **Students** and **Librarians**.  

---

## ✨ Features  

✅ **View Available Books** – Check all books in the library.  
✅ **Search Books** 🔍 – Find books by name or ID.  
✅ **Issue Books 📖** – Students can borrow books.  
✅ **Return & Reissue 📦** – Manage issued books.  
✅ **Librarian Mode 🔐** – Modify book records, issue books, and change system settings.  

---

## 📂 Project Structure  

```
📦 Library Management System/
 ├── 📜 library_management.cpp   # Main C++ source file
 ├── 📄 book_details.txt         # Stores available books
 ├── 📄 issue.txt                # Tracks issued books
 ├── 🔑 software_detail.dat      # Stores librarian password
 ├── 📖 README.md                # Documentation
 ├── ⚙️ library_management.exe   # Compiled executable
```

---

## ⚙️ How to Build & Run  

### 1️⃣ Compile the Code  
Use `g++` to compile:  

```sh
g++ library_management.cpp -o library_management.exe -lcurses
```

### 2️⃣ Run the Program  
Execute the compiled file:  

```sh
./library_management.exe
```

**Note:**  
- Ensure your system supports `<curses.h>` (Linux/macOS).  
- Windows users may need `<conio.h>` or adjust UI-related functions.  

---

## 📝 Usage  

🔹 **Student Mode**  
   - 📋 View the list of books.  
   - 🔍 Search books by name or ID.  

🔹 **Librarian Mode**  
   - 📝 Add or modify books.  
   - 📚 Issue and manage books.  
   - 🔄 Reissue or return books.  
   - 🔑 Change application password.  

🎯 **Navigation:** Choose Student/Librarian mode from the main menu.  

---

## 🔮 Future Improvements  

🚀 **Better Error Handling** – Improve file I/O operations.  
📊 **Enhanced UI** – Make it more interactive.  
🗄️ **Database Support** – Store data in a structured format.  


---
