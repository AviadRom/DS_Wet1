//
//  Student.h
//  Mivne1
//
//  Created by Aviad Rom on 4/22/13.
//  Copyright (c) 2013 Aviad Rom. All rights reserved.
//

#ifndef Mivne1_Student_h
#define Mivne1_Student_h
#include "AVLTree.h"
#include "LList.h"
#include "PendCourse.h"

class Student {
    int _ID;
    AVLTree<int> _CoursesTaken;
    AVLTree<PendCourse> _CoursesPending;
    int _NumberOfCoursesTaken;
public:
    Student():_ID(-1),_NumberOfCoursesTaken(0){}
    
    Student(int ID):_ID(ID){}
    
    ~Student(){}
    
    /*GetID
     * Description: Getter to _ID property of the student
     */
    int GetID(){
        return _ID;
    }
    
    /* AddCourseTaken
     * Description: Adds a course ID to the _CoursesTaken tree.
     * @param CourseID: pointer to course's ID element.
     * @return: true if added successfully.
     *          false if invalid pointer was provided.
     */
    const bool AddCourseTaken(int* CourseID){
        if (CourseID){
            PendCourse pend(*CourseID,NULL);
            _CoursesTaken.Insert(CourseID);
            if (_CoursesPending.IsIn(&pend)){
                _CoursesPending.Remove(&pend);
            }
            _NumberOfCoursesTaken++;
            return true;
        }
        return false;
    }
    
    const bool AddCoursePending (int* CourseID, LListNode<int>* QueueLocation){
        if (CourseID && QueueLocation != NULL){
            PendCourse pend(*CourseID,QueueLocation);
            if (!_CoursesTaken.IsIn(CourseID)){
                _CoursesPending.Insert(&pend);
                return true;
            }
        }
        return false;
    }
    
    const bool removeCourse(int* CourseID){
        if (CourseID){
            if (_CoursesTaken.IsIn(CourseID)){
                _CoursesTaken.Remove(CourseID);
                _NumberOfCoursesTaken--;
            }
            PendCourse pendRemoval(*CourseID,NULL);
            _CoursesPending.Remove(&pendRemoval);
            return true;
        }
        return false;
    }
    
    
    const bool operator< (Student& Comperator) const{
        return (_ID < Comperator.GetID());
    }
    
    const bool operator> (Student& Comperator) const{
        return (_ID > Comperator.GetID());
    }
    
    const bool operator== (Student& Comperator) const{
        return (_ID == Comperator.GetID());
    }
    
    const int GetNumberOfCoursesTaken() const{
        return _NumberOfCoursesTaken;
    }
    
    /*IsCourseTaken
     * Description: Returns a bool true/false according to wether a student is
     *              on a course's enrolled list or not.
     * @param CourseID: ID of the course to be checked.
     */
    const bool IsCourseTaken(int courseId){
        return _CoursesTaken.IsIn(&courseId);
    }
    
    /*IsCoursePending
     * Description: Returns a bool true/false according to wether a student is
     *              on a course's pending list or not.
     * @param CourseID: ID of the course to check.
     */
    const bool IsCoursePending(int courseID){
        PendCourse course(courseID);
    	return _CoursesPending.IsIn(&course);
    }
};

#endif
