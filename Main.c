#include <stdio.h>
#include <sqlite3.h>


// Function declarations
void listAllJobTitles(sqlite3* db);
void highAndLowSal(sqlite3* db);
void empCountry(sqlite3* db);
void empGrade(sqlite3* db);
void empNameStartLetter(sqlite3* db);
void salRangeForEacjJobTitle(sqlite3* db);
void empHistory(sqlite3* db);
void empEmail(sqlite3* db);
void empCommission(sqlite3* db);
void empHireDate(sqlite3* db);
void empDeptAddress(sqlite3* db);
void empSal(sqlite3* db);
void empPhoneNumber(sqlite3* db);
void insertNewEmp(sqlite3* db);


static int callback(void* data, int argc, char** argv, char** ColName){

   for(int i = 0; i<argc; i++){
      printf("%s = %s\n", ColName[i], argv[i]);
   }

   return 0;
}

// Main function
int main(int argc, char* argv[]) {

   // Connecting to database
   sqlite3* db;
   int c;

   c = sqlite3_open_v2("EmployeeManagementSystem.db", &db, SQLITE_OPEN_READWRITE, NULL);

   if(c){
      printf("Can't open database! %s\n", sqlite3_errmsg(db));
      return(0);
   } else {
      printf("Connect to database successfully.\n");
   }
   // Finish connecting to the database


   // While loop
   while(1){
       // Main menu presented to the user to choose from
       printf("Welcome to the EmployeeManagementSystem application:\n");
       printf("0) Exit\n");
       printf("1) Lists all the job titles/positions available in the company\n");
       printf("2) Who is having highest and lowest salary?\n");
       printf("3) Which employee is working in which country?\n");
       printf("4) Assign grades to each employee like A for employee who makes between 1000 to 2999, B for 3000 to 5999 CAD, etc?\n");
       printf("5) Which employee's name starts with a letter M or B etc?\n");
       printf("6) Find range of salary for each job title? say for example, president of the company can earn from 20,000 to 40,000 CAD not more than that after all the appraisals\n");
       printf("7) Find history about previous employees like hire date, end date, their department etc?\n");
       printf("8) what is the email address of an employee?\n");
       printf("9) How much commission does an employee get every year?\n");
       printf("10) When was an employee hired?\n");
       printf("11) Complete address of the department where the employee is currently working?\n");
       printf("12) What is the salary of an employee?\n");
       printf("13) What is phone number of an Employee?\n");
       printf("14) Insert a new employee?\n");
       
       // Menu finished

       // Ask user for input
       int inp = 0;
       printf("Enter Input:");
       scanf("%d", &inp);

       // Check the input by the user
       switch(inp){
            case 0:
               return 0;
               break;
           case 1:
               listAllJobTitles(db);
               break;
            case 2:
               highAndLowSal(db);
               break;

            case 3:
               empCountry(db);
               break;

            case 4:
               empGrade(db);
               break;

            case 5:
               empNameStartLetter(db);
               break;

            case 6:
               salRangeForEacjJobTitle(db);
               break;

            case 7:
               empHistory(db);
               break;

            case 8:
               empEmail(db);
               break;
            case 9:
               empCommission(db);
               break;
            case 10:
               empHireDate(db);
               break;
            case 11:
               empDeptAddress(db);
               break;
            case 12:
               empSal(db);
               break;
            case 13:
               empPhoneNumber(db);
               break;
            case 14:
               insertNewEmp(db);
            default:
                printf("Invalid Input!!!");
                break;


       }

   }
    // Close database
   sqlite3_close(db);
}

// Function for menu item 1
void listAllJobTitles(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT Title \
                    FROM Jobs;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 2
void highAndLowSal(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT FirstName, LastName, Max(Salary) \
                    FROM Employees;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }


       // Lowest
       //create SQL statement
       sql = "SELECT FirstName, LastName, Min(Salary) \
                    FROM Employees;";

       //execute SQL statement
       r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");
       }
}

// Function for menu item 3
void empCountry(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT E.FirstName, E.LastName, C.Name \
                    FROM Employees AS E INNER JOIN Departments AS D ON E.DepartmentId = D.Id INNER JOIN Locations AS L \
                    ON L.Id = D.LocationId INNER JOIN Countries AS C ON C.Id = L.CountryId;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 4
void empGrade(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT GradeLevel, Salary, FirstName, LastName \
                    FROM Employees, JobGrades \
                    WHERE Salary BETWEEN LowestSal AND HighestSal;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 5
void empNameStartLetter(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT FirstName \
                    FROM Employees \
                    WHERE FirstName LIKE \"M%\";";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 6
void salRangeForEacjJobTitle(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT * \
                    FROM Jobs;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 7
void empHistory(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT StartDate, EndDate, DepartmentId \
                    FROM JobHistory;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 8
void empEmail(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT Email \
                    FROM Employees \
                    WHERE Id = 100;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 9
void empCommission(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT Salary*CommissionPct \
                    FROM Employees \
                    WHERE CommissionPct IS NOT NULL;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 10
void empHireDate(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT HireDate \
                    FROM Employees \
                    WHERE Id = 100;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}


// Function for menu item 11
void empDeptAddress(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT L.StreetAddress, L.PostalCode, L.City, L.StateProvince \
                    FROM Employees AS E INNER JOIN Departments AS D ON E.DepartmentId = D.Id \
                    INNER JOIN Locations AS L ON L.Id = D.LocationId INNER JOIN Countries AS C ON C.Id = L.CountryId;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 12
void empSal(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT Salary \
                    FROM Employees \
                    WHERE Id = 100;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}


void insertNewEmp(sqlite3* db);
void empPhoneNumber(sqlite3* db){
        char* errMsg = 0;

       //create SQL statement
       char* sql = "SELECT PhoneNumber \
                    FROM Employees \
                    WHERE Id = 100;";

       //execute SQL statement
       int r = sqlite3_exec(db, sql, callback, 0, &errMsg);



       if(r != SQLITE_OK ){
       printf("SQL error: %s\n", errMsg);
       sqlite3_free(errMsg);
       }
       else {
           printf("Query Successful\n\n");

       }
}

// Function for menu item 14
void insertNewEmp(sqlite3* db){
      char* errMsg = 0;

      // inputs from user
      int id = 0; // ID
      char fName[100];// First Name
      char lName[100];// Last Name
      char email[100];//Email
      char phoneNo[100];//Phone Number
      char hireDate[100];//HireDate
      char jobId[10];// Job ID
      int sal = 0;
      float comm_pct = 0;
      int ManagerId;
      int DeptId;

      // Scan inputs from the user
      printf("Enter ID:");
      scanf("%d", &id);
      printf("Enter First Name:");
      scanf("%s", fName);
      printf("Enter Last Name:");
      scanf("%s", lName);
      printf("Enter Email:");
      scanf("%s", email);
      printf("Enter Phone Number:");
      scanf("%s", phoneNo);
      printf("Enter Hire Date:");
      scanf("%s", hireDate);
      printf("Enter Job ID:");
      scanf("%s", jobId);
      printf("Enter Salary:");
      scanf("%d", &sal);
      printf("Enter Commission PCT:");
      scanf("%f", &comm_pct);
      printf("Enter Manager ID:");
      scanf("%d", &ManagerId);
      printf("Enter Department ID:");
      scanf("%d", &DeptId);

      

      // Insert Command
      char* insert_cmd = "INSERT INTO Employees(Id, FirstName, LastName, Email, PhoneNumber, HireDate, JobId, Salary, CommissionPct,\
      ManagerId, DepartmentId) VALUES(%s, %s, %s,%s,%s,%s, %d, %f, %d, %d)";

      char str[1000];
      snprintf(str, insert_cmd, id, fName, lName, email, phoneNo, hireDate, jobId, sal, comm_pct, \
      ManagerId, DeptId);
      printf("%s", str);
}
