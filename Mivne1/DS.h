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
using namespace std;

class DS{
    AVLTree<Course> Courses;
    int _NumberOfCourses;
    AVLTree<Student> Students;
    
    void DropAllStudentsFromCourse(int courseID,AVLNode<Student>* root){ //Refactored the name
                                                                      //to improve readability
       	if (root == NULL){
       		return;
       	}
       	DropAllStudentsFromCourse(courseID, root->_Left);
       	root->_Data.removeCourse(&courseID);
       	DropAllStudentsFromCourse(courseID,root->_Right);
    }

public:
    DS():_NumberOfCourses(0){}
    
    StatusType AddCourse(int CourseID, int Size){
        if (Size < 0){
            return INVALID_INPUT;
        }
    	Course course(CourseID,Size);		//how to check if allocation error occured?how to check if DS is NULL?
    	if (Courses.IsIn(&course)){
    		return FAILURE;
    	}
    	Courses.Insert(&course);
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
//TODO check if student is pending for course
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
        return SUCCESS;
    }
    
    StatusType GetAllCourses(void *DS, int ***courses, int**coursesSize, int *numOfCourses){
        return SUCCESS;
    }

};


#endif
