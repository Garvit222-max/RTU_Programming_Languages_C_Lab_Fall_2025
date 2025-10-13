/*
Name: Garvit
Student ID: 241ADB140
File: week5_task4_struct_binary_io.c
Task 4: Binary File Version – Save and load struct in binary format
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
void save_student_binary(Student s,const char *filename);
Student load_student_binary(const char *filename);
long file_size(const char *filename);
int main(void){
Student s1;
strcpy(s1.name,"Alice");
s1.age=21;
s1.gpa=3.75f;
const char *filename="student_bin.dat";
printf("Saving student in binary format...\n");
save_student_binary(s1,filename);
printf("Loading student from binary file...\n");
Student s2=load_student_binary(filename);
printf("Loaded student: %s, %d, GPA %.2f\n",s2.name,s2.age,s2.gpa);
printf("Binary file size: %ld bytes\n",file_size(filename));
return 0;
}
void save_student_binary(Student s,const char *filename){
FILE *fp=fopen(filename,"wb");
if(fp==NULL){
fprintf(stderr,"Error: could not open %s for writing.\n",filename);
exit(EXIT_FAILURE);
}
if(fwrite(&s,sizeof(Student),1,fp)!=1){
fprintf(stderr,"Error: failed to write binary data.\n");
fclose(fp);
exit(EXIT_FAILURE);
}
fclose(fp);
}
Student load_student_binary(const char *filename){
Student s;
FILE *fp=fopen(filename,"rb");
if(fp==NULL){
fprintf(stderr,"Error: could not open %s for reading.\n",filename);
exit(EXIT_FAILURE);
}
if(fread(&s,sizeof(Student),1,fp)!=1){
fprintf(stderr,"Error: failed to read binary data.\n");
fclose(fp);
exit(EXIT_FAILURE);
}
fclose(fp);
return s;
}
long file_size(const char *filename){
FILE *fp=fopen(filename,"rb");
if(fp==NULL)return -1;
fseek(fp,0,SEEK_END);
long size=ftell(fp);
fclose(fp);
return size;
}
