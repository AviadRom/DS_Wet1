//
//  DS.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//


#define Mivne1_DS_h
#include "library1.h"
#include "AVLTree.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <cstdlib>
using namespace std;

class Statistics{
    AVLTree<Course> Courses;
    int _NumberOfCourses;
    AVLTree<Student> Students;
    
    /*DropAllStudentsFromCourse
     * Description: In-Order iteration on students tree to remove the course from each student's
     *              list of courses.
     * @param CourseID: ID of the course to remove.
     * @param root: root of the students tree
     */
    void DropAllStudentsFromCourse(int courseID,AVLNode<Student>* root){ 
           if (root == NULL){
           	return;
       	}
       	DropAllStudentsFromCourse(courseID, root->_Left);
       	root->_Data.RemoveCourse(&courseID);
       	DropAllStudentsFromCourse(courseID,root->_Right);
    }
    void GetMaxCourseSize(AVLNode<Course>* root,int* maxSize,int* amountOfCourses){
           if (root == NULL){
       		return;
       	}
       	GetMaxCourseSize(root->_Left,maxSize,amountOfCourses);
       	(*amountOfCourses)++;
       	if (root->_Data.GetSize() > *maxSize){
       		*maxSize=root->_Data.GetSize();
       	}
       	GetMaxCourseSize(root->_Right,maxSize,amountOfCourses);
    }

    void GetEnrolledStudents(AVLNode<int>* root,int** courses,int maxSize,int* numOfCourses,int* coursesSize){
       	if (root == NULL){
   			return;
   		}
   		GetEnrolledStudents(root->_Left,courses,maxSize,numOfCourses,coursesSize);
   		++(coursesSize[*numOfCourses]);
   		//currentStudent++;
   		int currentStudent=coursesSize[*numOfCourses];
   		courses[*numOfCourses][currentStudent]=root->_Data;
   		GetEnrolledStudents(root->_Right,courses,maxSize,numOfCourses,coursesSize);
   	}
    void GetCourseId(AVLNode<Course>* root,int **courses, int* coursesSize, int* numOfCourses,int maxSize,bool* allocationErrorFlag){
           if (root==NULL){
       		return;
       	}
       	GetCourseId(root->_Left,courses,coursesSize,numOfCourses,maxSize,allocationErrorFlag);
      	(*numOfCourses)++;
      	//coursesSize[*numOfCourses]=root->_Data.GetActualSize();
       	courses[*numOfCourses]=(int*)malloc((maxSize+1)*sizeof(int));
       	if (courses[*numOfCourses] == NULL){
       		*allocationErrorFlag=true;
     	}
       	courses[*numOfCourses][0]=root->_Data.GetCourseId();
       	for (int i=1;i<=maxSize;i++){
       		courses[*numOfCourses][i]=0;
       	}
       	GetEnrolledStudents(root->_Data.GetEnrolledStudents(),courses,maxSize,numOfCourses,coursesSize);
       	coursesSize[*numOfCourses]=root->_Data.GetActualSize();
       	GetCourseId(root->_Right,courses,coursesSize,numOfCourses,maxSize,allocationErrorFlag);
    }
    void RemoveStudentFromPending(AVLNode<PendCourse>* root,AVLNode<Student>* student){
       	if (root == NULL){
       		return;
       	}
    	RemoveStudentFromPending(root->_Left,student);
       	int currentCourse=root->_Data.GetID();
       	student->_Data.RemoveCourse(&currentCourse);
       	RemoveStudentFromPending(root->_Right,student);
    }

public:
    Statistics():_NumberOfCourses(0){}
    
    
    bool IsCourseExists(int CourseId){
    	Course course(CourseId,0);
    	return Courses.IsIn(&course);
    }

    
    StatusType AddCourse(int CourseID, int Size){
        if (Size < 0){
            return INVALID_INPUT;
        }
    	Course course(CourseID,Size);
    	if (Courses.IsIn(&course)){
    		return FAILURE;
    	}
        try{
            Courses.Insert(&course);
        } catch (bad_alloc& BadAlloc){
            return ALLOCATION_ERROR;
        }
    	return SUCCESS;
    }

    StatusType RemoveCourse(int CourseID){
        Course course(CourseID,0);
    	if (!Courses.IsIn(&course)){
      		return FAILURE;
       	}
       	Courses.Remove(&course);
       	DropAllStudentsFromCourse(CourseID,Students.GetRoot());
       	return SUCCESS;
    }

    StatusType AddStudent(int StudentId){ //TODO Test
        Student student(StudentId);
        if (Students.IsIn(&student)){
            return FAILURE;
        }
        try {
            Students.Insert(&student);
        } catch (bad_alloc& BadAlloc) {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType RemoveStudent(int StudentId){ //TODO Test
        Student student(StudentId);
        AVLNode<Student>* studentNode = Students.Find(&student);
        if (!studentNode) return FAILURE;
        if (studentNode->_Data.GetNumberOfCoursesTaken()){
            return FAILURE;
        }
        RemoveStudentFromPending(studentNode->_Data.GetCoursesPending(),studentNode);
        Students.Remove(&studentNode->_Data);
        return SUCCESS;
    }
    
    StatusType TakeCourse(int StudentID,int CourseID){ //TODO Test
        Student student(StudentID);
        Course course(CourseID,0);
        AVLNode<Student>* studentNode = Students.Find(&student);
        AVLNode<Course>* courseNode = Courses.Find(&course);
        if (!studentNode || !courseNode || courseNode->_Data.IsEnrolled(&StudentID)){
            return FAILURE;
        }
        try{
            if (courseNode->_Data.Enroll(&StudentID)){
                studentNode->_Data.AddCourseTaken(&CourseID);
            }else {
                studentNode->_Data.AddCoursePending(&CourseID,courseNode->_Data.GetQueueTail());
            }
        } catch (bad_alloc& BadAlloc){
            studentNode->_Data.RemoveCourse(&CourseID);
            courseNode->_Data.Leave(&StudentID);
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }
    
    StatusType LeaveCourse(int StudentID,int CourseID){
        Student student(StudentID);
        AVLNode<Student>* studentNode = Students.Find(&student);
        Course course (CourseID,0);
        AVLNode<Course>* courseNode = Courses.Find(&course);
        if (studentNode == NULL || courseNode == NULL){
            return FAILURE;
        }
        try {
            courseNode->_Data.Leave(&StudentID);
        } catch (bad_alloc& BadAlloc){
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }
    
    StatusType EnlargeCourse(int CourseID,int ExtraSize){
        Course course(CourseID,0);
        if (ExtraSize < 0 || !Courses.IsIn(&course)){
            return FAILURE;
        }
        AVLNode<Course>* courseNode = Courses.Find(&course);
        try {
            courseNode->_Data.IncreaseSize(ExtraSize,&Students);
        } catch (bad_alloc& BadAlloc) {
            return ALLOCATION_ERROR;
        }
        return SUCCESS;
    }

    StatusType GetAllCourses(int*** courses, int** coursesSize, int* numOfCourses){
            if (courses==NULL || coursesSize==NULL || numOfCourses==NULL  ){
                return INVALID_INPUT;
            }
            int maxSize=0;
            int amountOfCourses=0;
            GetMaxCourseSize(Courses.GetRoot(),&maxSize,&amountOfCourses);
            *numOfCourses=-1;
            *coursesSize=(int*)malloc(amountOfCourses*sizeof(int));
            if (*coursesSize == NULL){
              	return ALLOCATION_ERROR;
            }
            for (int i=0;i<amountOfCourses;i++){
            	(*coursesSize)[i]=0;
            }
           bool alloctionErrorFlag=false;
            *courses=(int**)malloc(amountOfCourses*sizeof(int*));
            if (*courses == NULL){
            	free(*coursesSize);
            	return ALLOCATION_ERROR;
            }
            GetCourseId(Courses.GetRoot(),*courses,*coursesSize,numOfCourses,maxSize,&alloctionErrorFlag);
        	if (alloctionErrorFlag){
        		for (int j=0;j<*numOfCourses;j++){
        			free((*courses)[j]);
          		}
        		free(numOfCourses);
        		free(coursesSize);
        		return ALLOCATION_ERROR;
        	}
            *numOfCourses=amountOfCourses;

        	return SUCCESS;
        }
    };
