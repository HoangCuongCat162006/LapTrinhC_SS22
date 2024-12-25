#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

int readStudentsFromFile(const char *filename, Student students[], int *count) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        *count = 0;
        return 0;
    }
    *count = fread(students, sizeof(Student), 100, file);
    fclose(file);
    return 1;
}

void writeStudentsToFile(const char *filename, Student students[], int count) {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(students, sizeof(Student), count, file);
        fclose(file);
    }
}

void printStudents(Student students[], int count) {
    printf("Danh sach sinh vien:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent(Student students[], int *count) {
    if (*count >= 100) {
        printf("Danh sach sinh vien da day.\n");
        return;
    }
    Student newStudent;
    printf("Nhap ID: ");
    scanf("%d", &newStudent.id);
    printf("Nhap Ten: ");
    scanf(" %s", newStudent.name);
    printf("Nhap Tuoi: ");
    scanf("%d", &newStudent.age);
    students[*count] = newStudent;
    (*count)++;
    printf("Them sinh vien thanh cong.\n");
}

void editStudent(Student students[], int count) {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Nhap Ten moi: ");
            scanf(" %s", students[i].name);
            printf("Nhap Tuoi moi: ");
            scanf("%d", &students[i].age);
            printf("Sua thong tin sinh vien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void deleteStudent(Student students[], int *count) {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Xoa sinh vien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

void searchStudent(Student students[], int count) {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("Thong tin sinh vien: ID: %d, Ten: %s, Tuoi: %d\n", students[i].id, students[i].name, students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien voi ID: %d\n", id);
}

// Ham sap xep danh sach sinh vien
void sortStudents(Student students[], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("Sap xep danh sach sinh vien thanh cong.\n");
}

int main() {
    Student students[100];
    int count = 0;
    const char *filename = "students.dat";

    readStudentsFromFile(filename, students, &count);

    while (1) {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudents(students, count);
                break;
            case 2:
                addStudent(students, &count);
                writeStudentsToFile(filename, students, count);
                break;
            case 3:
                editStudent(students, count);
                writeStudentsToFile(filename, students, count);
                break;
            case 4:
                deleteStudent(students, &count);
                writeStudentsToFile(filename, students, count);
                break;
            case 5:
                searchStudent(students, count);
                break;
            case 6:
                sortStudents(students, count);
                writeStudentsToFile(filename, students, count);
                break;
            case 7:
                printf("Thoat chuong trinh.\n");
                return 0;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }
}

