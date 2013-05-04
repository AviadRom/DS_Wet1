//
//  DS.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_DS_h
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
    
    //NOTE THAT I CHANGED "unsignStudent" TO THIS NAME.MUCH MORE READABLE.
    void DropAllStudentsFromCourse(int courseID,AVLNode<Student>* root){ 
           if (root == NULL){
       		return;
       	}
       	DropAllStudentsFromCourse(courseID, root->_Left);
       	root->_Data.removeCourse(&courseID);
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

    void GetSubscribedStudents(AVLNode<int>* root,int*** courses,int maxSize,int numOfCourses,int** coursesSize){
   		if (root == NULL){
   			return;
   		}
   		GetSubscribedStudents(root->_Left,courses,maxSize,numOfCourses,coursesSize);
   		int currentStudent=++(*coursesSize)[numOfCourses];
   		*(courses[numOfCourses][currentStudent])=root->_Data;
   		GetSubscribedStudents(root->_Right,courses,maxSize,numOfCourses,coursesSize);
   	}
    void VisitAllCourses(AVLNode<Course>* root,int ***courses, int**coursesSize, int *numOfCourses,int maxSize,int* flag){
       	if (root==NULL){
       		return;
       	}
       	VisitAllCourses(root->_Left,courses,coursesSize,numOfCourses,maxSize,flag);
      	(*numOfCourses)++;
       	(*courses)[*numOfCourses]=(int*)malloc(maxSize*sizeof(int));
       	if ((*courses)[*numOfCourses] == NULL){
       		*flag=1;
     	}
       	for (int i=0;i<maxSize;i++){
       		courses[*numOfCourses][i]=NULL;
       	}
       	GetSubscribedStudents(root->_Data.GetEnrolledStudents(),courses,maxSize,*numOfCourses,coursesSize);
       	VisitAllCourses(root->_Right,courses,coursesSize,numOfCourses,maxSize,flag);
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
            studentNode->_Data.removeCourse(&CourseID);
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
            numOfCourses=(int*)malloc(sizeof(int));
            if (numOfCourses == NULL){
            	return ALLOCATION_ERROR;
            }
            *numOfCourses=-1;
            coursesSize=(int**)malloc(amountOfCourses*sizeof(int));
            if (coursesSize == NULL){
            	free(numOfCourses);
            	return ALLOCATION_ERROR;
            }
            int flag=0;								//This flag states ALLOCATION ERROR in the function VisitAllCourses.
            VisitAllCourses(Courses.GetRoot(),courses,coursesSize,numOfCourses,maxSize,&flag);
        	if (flag){
        		for (int j=0;j<*numOfCourses;j++){
        			free((*courses)[j]);
          		}
        		free(numOfCourses);
        		free(coursesSize);
        		return ALLOCATION_ERROR;
        	}
            return SUCCESS;
        }

    	AVLNode<Student>* GetStudentTreeRoot(){
    		return Students.GetRoot();
    	}
};


#endif
