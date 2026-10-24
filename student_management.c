#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

// Structure to store student details
typedef struct {
    int roll_no;
    char name[50];
    char department[30];
    float cgpa;
} Student;

// Function prototypes
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n============================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM (CLI)      \n");
        printf("============================================\n");
        printf("  1. Add New Student Record\n");
        printf("  2. Display All Student Records\n");
        printf("  3. Search Student by Roll Number\n");
        printf("  4. Update Student Record\n");
        printf("  5. Delete Student Record\n");
        printf("  6. Exit\n");
        printf("--------------------------------------------\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            printf("\n[Error] Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
            default:
                printf("\n[Error] Invalid choice! Please select 1-6.\n");
        }
    }
    return 0;
}

// 1. Add a new student record to the file
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("\n[Error] Could not open file!\n");
        return;
    }

    Student s;
    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number : ");
    scanf("%d", &s.roll_no);
    printf("Enter Full Name   : ");
    scanf(" %[^\n]s", s.name);
    printf("Enter Department  : ");
    scanf(" %[^\n]s", s.department);
    printf("Enter CGPA        : ");
    scanf("%f", &s.cgpa);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("\n[Success] Student record added successfully!\n");
}

// 2. Display all student records in a formatted table
void displayStudents() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Info] No records found yet. Add a student first!\n");
        return;
    }

    Student s;
    int count = 0;

    printf("\n------------------------------------------------------------------\n");
    printf("%-10s %-25s %-18s %-8s\n", "Roll No", "Name", "Department", "CGPA");
    printf("------------------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-10d %-25s %-18s %-8.2f\n", s.roll_no, s.name, s.department, s.cgpa);
        count++;
    }
    printf("------------------------------------------------------------------\n");
    printf("Total Records: %d\n", count);

    fclose(fp);
}

// 3. Search for a specific student by Roll Number
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Info] No records available to search.\n");
        return;
    }

    int target_roll, found = 0;
    Student s;

    printf("\nEnter Roll Number to search: ");
    scanf("%d", &target_roll);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == target_roll) {
            printf("\n[Record Found]\n");
            printf("  Roll Number : %d\n", s.roll_no);
            printf("  Name        : %s\n", s.name);
            printf("  Department  : %s\n", s.department);
            printf("  CGPA        : %.2f\n", s.cgpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n[Not Found] No student found with Roll Number %d.\n", target_roll);
    }

    fclose(fp);
}

// 4. Update an existing student's details
void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "rb+");
    if (fp == NULL) {
        printf("\n[Info] No records available to update.\n");
        return;
    }

    int target_roll, found = 0;
    Student s;

    printf("\nEnter Roll Number to update: ");
    scanf("%d", &target_roll);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == target_roll) {
            printf("\nCurrent Name: %s | Dept: %s | CGPA: %.2f\n", s.name, s.department, s.cgpa);
            printf("Enter New Full Name  : ");
            scanf(" %[^\n]s", s.name);
            printf("Enter New Department : ");
            scanf(" %[^\n]s", s.department);
            printf("Enter New CGPA       : ");
            scanf("%f", &s.cgpa);

            fseek(fp, -sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            printf("\n[Success] Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n[Not Found] Roll Number %d does not exist.\n", target_roll);
    }

    fclose(fp);
}

// 5. Delete a student record by Roll Number
void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("\n[Info] No records available to delete.\n");
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    int target_roll, found = 0;
    Student s;

    printf("\nEnter Roll Number to delete: ");
    scanf("%d", &target_roll);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.roll_no == target_roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) {
        printf("\n[Success] Student with Roll Number %d deleted successfully!\n", target_roll);
    } else {
        printf("\n[Not Found] Roll Number %d does not exist.\n", target_roll);
    }
}
