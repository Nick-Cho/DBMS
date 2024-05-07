# C++ B+ Tree Relational Database Management System 

## Build and Run Steps
Used CMake to build project
1. Register the cmake.sh script using ```chmod +x ./build/cmake.sh``` from the root directory
2. Run ```./cmake.sh``` in the build directory
3. Create and empty file with a .db file extension
4. Run ```DBMS.exe [file_path]```

## Usage
<img width="832" alt="image" src="https://github.com/Nick-Cho/DBMS/assets/65980644/410ccec2-39bd-4cd3-8965-a804178f0925">

### Main features of the project are:
1. Developed using C/C++ design principles
2. Basic CRUD SQL functionality with a console interface: <br>
  ### i. Create a new record: insert {index} {name} {email}; <br>
   Creates a Row object in the Table instantiated by the file supplied, inserts it into the B+ Tree, and serializes it into memory. **O(logN) amortized**
  ```
   db > insert 1 user user@gmail.com
  ```
  | Parameter | Type |	Description           |
  |-----------|------|------------------------|
  | id |	int |	any number                    |
  | username |	string |	32 character length |
  | email |	string |	255 character length    |

  ### ii. Read a record: select <br>
   Returns all the rows ordered by primary key (id). O(N)
  ```
    db > select
  ```
   
   iii. Delete a record: delete from db where id={index} (to be implemented) <br>
4. Bottom layer uses B+ Tree structure with binary storage table structure <br>
5. Structure currently fixed for name and email
<br>
The following figure is the architecture diagram of sqlite: <br>
<br>
<img width="315" alt="image" src="https://github.com/Nick-Cho/DBMS/assets/65980644/fd44253c-6a0f-413a-bac1-15ec5b4c60b8"> <br>
Referring to the picture above, the main development steps are as follows: <br>

Create a console dialog interactive program (REPL: read-execute-print loop);
Create a simple lexical analyzer to parse SQL statements;
Write the CURD function to implement the addition, deletion, modification and query operations of the database;
Create a B+ tree index engine to perform database indexing and disk read and write operations. The data table will be stored in binary form.





 
