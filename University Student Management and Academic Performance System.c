#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ----------------- CONSTANTS -----------------
#define MAX_STUDENTS 50
#define MAX_COURSES 10

// ----------------- GLOBAL ARRAYS -----------------

// Courses information
char courseIDs[MAX_COURSES][50];       // Stores course ID strings
char courseNames[MAX_COURSES][50];     // Stores course name strings
int courseCreditHours[MAX_COURSES];    // Stores credit hours per course
int courseMaximumMarks[MAX_COURSES];   // Stores maximum marks per course
int totalCourses = 0;                  // Current number of courses

// Students information
char studentIDs[MAX_STUDENTS][50];       // Stores student IDs
char studentNames[MAX_STUDENTS][50];     // Stores student names
int totalStudents = 0;                    // Current number of students

// Enrollment, marks and attendance
int enrollment[MAX_STUDENTS][MAX_COURSES];   // 1 if student enrolled in course, 0 otherwise
int studentMarks[MAX_STUDENTS][MAX_COURSES]; // Marks obtained
int studentAttendance[MAX_STUDENTS][MAX_COURSES]; // Attendance percentage

// ----------------- UTILITY FUNCTIONS -----------------

// Find course index by ID
int findCourseIndexByID(char courseID[]) {
    for (int i = 0; i < totalCourses; i++) {
        if (strcmp(courseIDs[i], courseID) == 0) {
            return i; // Found
        }
    }
    return -1; // Not found
}

// Find student index by ID
int findStudentIndexByID(char studentID[]) {
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(studentIDs[i], studentID) == 0) {
            return i; // Found
        }
    }
    return -1; // Not found
}

// ----------------- COURSE MANAGEMENT -----------------

// Add a new course
void addCourse() {
    if (totalCourses >= MAX_COURSES) {
        printf("Maximum number of courses reached.\n");
        return;
    }

    char newCourseID[50];
    char newCourseName[50];
    int newCourseCreditHours;
    int newCourseMaximumMarks;

    printf("Enter Course ID: ");
    scanf("%s", newCourseID);

    if (findCourseIndexByID(newCourseID) != -1) {
        printf("Course ID already exists.\n");
        return;
    }

    strcpy(courseIDs[totalCourses], newCourseID);

    printf("Enter Course Name: ");
    scanf("%s", newCourseName);
    strcpy(courseNames[totalCourses], newCourseName);

    printf("Enter Credit Hours: ");
    scanf("%d", &newCourseCreditHours);
    courseCreditHours[totalCourses] = newCourseCreditHours;

    printf("Enter Maximum Marks: ");
    scanf("%d", &newCourseMaximumMarks);
    courseMaximumMarks[totalCourses] = newCourseMaximumMarks;

    totalCourses++;
    printf("Course added successfully.\n");
}

// ----------------- STUDENT MANAGEMENT -----------------

// Add a new student and enroll them in courses
void addStudent() {
    if (totalStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    char newStudentID[50];
    char newStudentName[50];

    printf("Enter Student ID: ");
    scanf("%s", newStudentID);

    if (findStudentIndexByID(newStudentID) != -1) {
        printf("Student ID already exists.\n");
        return;
    }

    strcpy(studentIDs[totalStudents], newStudentID);

    printf("Enter Student Name: ");
    scanf("%s", newStudentName);
    strcpy(studentNames[totalStudents], newStudentName);

    // Initialize enrollment, marks and attendance for the new student
    for (int courseIndex = 0; courseIndex < MAX_COURSES; courseIndex++) {
        enrollment[totalStudents][courseIndex] = 0;
        studentMarks[totalStudents][courseIndex] = 0;
        studentAttendance[totalStudents][courseIndex] = 0;
    }

    // Enroll student in courses
    int numberOfCoursesToEnroll;
    printf("How many courses to enroll the student in? ");
    scanf("%d", &numberOfCoursesToEnroll);

    for (int i = 0; i < numberOfCoursesToEnroll; i++) {
        char courseIDToEnroll[50];
        printf("Enter Course ID to enroll: ");
        scanf("%s", courseIDToEnroll);

        int courseIndex = findCourseIndexByID(courseIDToEnroll);
        if (courseIndex == -1) {
            printf("Invalid Course ID. Skipping.\n");
        } else {
            enrollment[totalStudents][courseIndex] = 1;
            printf("Enrolled in course: %s\n", courseIDToEnroll);
        }
    }

    totalStudents++;
    printf("Student added successfully.\n");
}

// ----------------- MARKS AND ATTENDANCE -----------------

// Update marks for a student
void updateStudentMarks() {
    char studentID[50];
    char courseID[50];

    printf("Enter Student ID: ");
    scanf("%s", studentID);
    int studentIndex = findStudentIndexByID(studentID);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter Course ID: ");
    scanf("%s", courseID);
    int courseIndex = findCourseIndexByID(courseID);
    if (courseIndex == -1) {
        printf("Course not found.\n");
        return;
    }

    if (!enrollment[studentIndex][courseIndex]) {
        printf("Student is not enrolled in this course.\n");
        return;
    }

    int marksObtained;
    printf("Enter marks obtained: ");
    scanf("%d", &marksObtained);

    if (marksObtained < 0 || marksObtained > courseMaximumMarks[courseIndex]) {
        printf("Invalid marks.\n");
        return;
    }

    studentMarks[studentIndex][courseIndex] = marksObtained;
    printf("Marks updated successfully.\n");
}

// Update attendance for a student
void updateStudentAttendance() {
    char studentID[50];
    char courseID[50];

    printf("Enter Student ID: ");
    scanf("%s", studentID);
    int studentIndex = findStudentIndexByID(studentID);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("Enter Course ID: ");
    scanf("%s", courseID);
    int courseIndex = findCourseIndexByID(courseID);
    if (courseIndex == -1) {
        printf("Course not found.\n");
        return;
    }

    if (!enrollment[studentIndex][courseIndex]) {
        printf("Student is not enrolled in this course.\n");
        return;
    }

    int attendancePercentage;
    printf("Enter attendance percentage (0-100): ");
    scanf("%d", &attendancePercentage);

    if (attendancePercentage < 0 || attendancePercentage > 100) {
        printf("Invalid attendance percentage.\n");
        return;
    }

    studentAttendance[studentIndex][courseIndex] = attendancePercentage;
    printf("Attendance updated successfully.\n");
}

// ----------------- GPA CALCULATION -----------------

// Calculate weighted GPA for a student
float calculateStudentGPA(int studentIndex) {
    float totalGradePoints = 0;
    float totalCreditHours = 0;

    for (int courseIndex = 0; courseIndex < totalCourses; courseIndex++) {
        if (enrollment[studentIndex][courseIndex]) {
            float courseGPA = ((float)studentMarks[studentIndex][courseIndex] / courseMaximumMarks[courseIndex]) * 4.0;
            totalGradePoints += courseGPA * courseCreditHours[courseIndex];
            totalCreditHours += courseCreditHours[courseIndex];
        }
    }

    if (totalCreditHours == 0) return 0;
    return totalGradePoints / totalCreditHours;
}

// ----------------- REPORTS -----------------

// Display detailed report for a student
void displayStudentReport() {
    char studentID[50];
    printf("Enter Student ID: ");
    scanf("%s", studentID);

    int studentIndex = findStudentIndexByID(studentID);
    if (studentIndex == -1) {
        printf("Student not found.\n");
        return;
    }

    printf("\n--- Student Report ---\n");
    printf("ID: %s   Name: %s\n", studentIDs[studentIndex], studentNames[studentIndex]);
    printf("Course\tMarks\tAttendance\tStatus\n");

    for (int courseIndex = 0; courseIndex < totalCourses; courseIndex++) {
        if (enrollment[studentIndex][courseIndex]) {
            char status[10];
            if (studentMarks[studentIndex][courseIndex] >= 50 && studentAttendance[studentIndex][courseIndex] >= 75)
                strcpy(status, "Pass");
            else
                strcpy(status, "Fail");

            printf("%s\t%d\t%d%%\t%s\n", courseIDs[courseIndex], studentMarks[studentIndex][courseIndex],
                   studentAttendance[studentIndex][courseIndex], status);
        }
    }

    printf("\nGPA: %.2f\n", calculateStudentGPA(studentIndex));
}

// Display report for a course
void displayCourseReport() {
    char courseID[50];
    printf("Enter Course ID: ");
    scanf("%s", courseID);

    int courseIndex = findCourseIndexByID(courseID);
    if (courseIndex == -1) {
        printf("Course not found.\n");
        return;
    }

    printf("\n--- Course Report: %s ---\n", courseID);
    printf("Student\tMarks\tAttendance\n");

    int highestMarks = -1, lowestMarks = 9999, totalMarks = 0, totalAttendance = 0, studentCount = 0;

    for (int studentIndex = 0; studentIndex < totalStudents; studentIndex++) {
        if (enrollment[studentIndex][courseIndex]) {
            int marksObtained = studentMarks[studentIndex][courseIndex];
            int attendancePercent = studentAttendance[studentIndex][courseIndex];

            printf("%s\t%d\t%d%%\n", studentNames[studentIndex], marksObtained, attendancePercent);

            if (marksObtained > highestMarks) highestMarks = marksObtained;
            if (marksObtained < lowestMarks) lowestMarks = marksObtained;
            totalMarks += marksObtained;
            totalAttendance += attendancePercent;
            studentCount++;
        }
    }

    if (studentCount > 0) {
        printf("\nHighest Marks: %d\nLowest Marks: %d\nAverage Marks: %.2f\nAverage Attendance: %.2f%%\n",
               highestMarks, lowestMarks, (float)totalMarks / studentCount, (float)totalAttendance / studentCount);
    }
}

// Display topper student
void displayTopper() {
    float bestGPA = -1;
    char topperName[50];

    for (int studentIndex = 0; studentIndex < totalStudents; studentIndex++) {
        float gpa = calculateStudentGPA(studentIndex);
        if (gpa > bestGPA) {
            bestGPA = gpa;
            strcpy(topperName, studentNames[studentIndex]);
        }
    }

    printf("\nTopper: %s  GPA: %.2f\n", topperName, bestGPA);
}

// Display attendance warning list
void displayAttendanceWarning() {
    printf("\n--- Attendance Warning List ---\n");
    for (int studentIndex = 0; studentIndex < totalStudents; studentIndex++) {
        for (int courseIndex = 0; courseIndex < totalCourses; courseIndex++) {
            if (enrollment[studentIndex][courseIndex] && studentAttendance[studentIndex][courseIndex] < 75) {
                printf("Student ID: %s  Name: %s  Course: %s  Attendance: %d%%\n",
                       studentIDs[studentIndex], studentNames[studentIndex],
                       courseIDs[courseIndex], studentAttendance[studentIndex][courseIndex]);
            }
        }
    }
}

// ----------------- MENU -----------------
void displayMenu() {
    while (1) {
        printf("\n--- UNIVERSITY STUDENT MANAGEMENT SYSTEM ---\n");
        printf("1. Add Course\n");
        printf("2. Add Student\n");
        printf("3. Update Marks\n");
        printf("4. Update Attendance\n");
        printf("5. Display Student Report\n");
        printf("6. Display Course Report\n");
        printf("7. Show Topper\n");
        printf("8. Attendance Warning List\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: addCourse(); break;
            case 2: addStudent(); break;
            case 3: updateStudentMarks(); break;
            case 4: updateStudentAttendance(); break;
            case 5: displayStudentReport(); break;
            case 6: displayCourseReport(); break;
            case 7: displayTopper(); break;
            case 8: displayAttendanceWarning(); break;
            case 9: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
}

// ----------------- MAIN FUNCTION -----------------
int main() {
    printf("WELCOME TO UNIVERSITY STUDENT MANAGEMENT SYSTEM\n");
    displayMenu();
    return 0;
}
