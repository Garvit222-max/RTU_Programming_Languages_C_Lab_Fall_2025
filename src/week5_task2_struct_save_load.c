/*
Name: Garvit
Student ID: 241ADB140
File: week5_task2_struct_save_load.c
Task 2: Save and load structured records from a file
Week 5 – Files & Modular Programming
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_LEN 50
typedef struct {
char name[MAX_NAME_LEN];
int age;
float gpa;
} Student;
void save_student(Student s, const char *filename);
Student load_student(const char *filename);
int main(void){
Student s1;
strcpy(s1.name,"Alice");
s1.age=21;
s1.gpa=3.75f;
const char *filename="student.txt";
printf("Saving student to file...\n");
save_student(s1,filename);
printf("Loading student from file...\n");
Student s2=load_student(filename);
printf("Loaded student: %s, %d, GPA %.2f\n",s2.name,s2.age,s2.gpa);
return 0;
}
void save_student(Student s,const char *filename){
FILE *fp=fopen(filename,"w");
if(fp==NULL){
fprintf(stderr,"Error: could not open %s for writing.\n",filename);
exit(EXIT_FAILURE);
}
if(fprintf(fp,"%s %d %.2f\n",s.name,s.age,s.gpa)<0){
fprintf(stderr,"Error: failed to write to file %s.\n",filename);
fclose(fp);
exit(EXIT_FAILURE);
}
fclose(fp);
}
Student load_student(const char *filename){
Student s;
FILE *fp=fopen(filename,"r");
if(fp==NULL){
fprintf(stderr,"Error: could not open %s for reading.\n",filename);
exit(EXIT_FAILURE);
}
if(fscanf(fp,"%49s %d %f",s.name,&s.age,&s.gpa)!=3){
fprintf(stderr,"Error: invalid file format or read failure.\n");
fclose(fp);
exit(EXIT_FAILURE);
}
fclose(fp);
return s;
}
