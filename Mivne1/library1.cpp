//
//  library1.cpp
//  Mivne1
//
//  Created by Aviad Rom on 5/3/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#include "library1.h"
#include "DS.h"

void*       Init(){
    Statistics* ds=new Statistics();
    return (void*)ds;
}

StatusType AddCourse(void *DS, int courseID, int size){
    return (((Statistics*)DS)->AddCourse(courseID,size));
}

StatusType RemoveCourse(void *DS,int courseID){
    return (((Statistics*)DS)->RemoveCourse(courseID));
}

StatusType AddStudent(void *DS, int studentID){
    return (((Statistics*)DS)->AddStudent(studentID));
}

StatusType RemoveStudent(void *DS,int studentID){
    return (((Statistics*)DS)->RemoveStudent(studentID));
}

StatusType TakeCourse(void *DS, int studentID, int courseID){
    return (((Statistics*)DS)->TakeCourse(studentID, courseID));
}

StatusType LeaveCourse(void *DS, int studentID, int courseID){
    return (((Statistics*)DS)->LeaveCourse(studentID, courseID));
}

StatusType EnlargeCourse(void *DS, int courseID, int extrasize){
    return (((Statistics*)DS)->EnlargeCourse(courseID, extrasize));
}

StatusType GetAllCourses(void *DS, int ***courses, int**coursesSize, int *numOfCourses){
    return (((Statistics*)DS)->GetAllCourses(courses, coursesSize, numOfCourses));
}

void        Quit(void** DS){
    Statistics* ds= (Statistics*)*DS;
    delete ds;
    DS = NULL;
}