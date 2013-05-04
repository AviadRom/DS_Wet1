/*
 * DSTest.h
 *
 *  Created on: Apr 29, 2013
 *      Author: OHAD FIREMAN
 */

#ifndef DSTEST_H_
#define DSTEST_H_
#include "DS.h"
using namespace std;

void isCourseTaken(int courseID,AVLNode<Student>* root){
       	if (root == NULL){
       		return;
       	}
       	isCourseTaken(courseID,root->_Left);							////This function was not checked!
      	if (root->_Data.IsCourseTaken(courseID)){
   		cout << "Test failed, a student still takes the removed course.";
   		return;
       	}
      	if (root->_Data.IsCoursePending(courseID)){
      		cout << "Test failed, a student still pends to the removed course.";
       		return;
       	}
       	isCourseTaken(courseID,root->_Right);
    }

void AddCourseTest(){
	Statistics tester;
	int CourseID=56,Size=5;
	StatusType result=tester.AddCourse(CourseID,-1);
	if (result != INVALID_INPUT){
		cout << "Test failed,course with negative size was inserted.";
		return;
	}
	result=tester.AddCourse(CourseID,Size);
	if(!(tester.IsCourseExists(CourseID))){
		cout << "Test failed,course wasn't added to the system";
				return;
		}
	result=tester.AddCourse(CourseID,Size);
	if (result != FAILURE){
			cout << "Test failed, course was inserted twice to the system.";
			return;
		}
	cout << "AddCourseTest: Test Passed."<<endl;
}

void RemoveCourseTest(){
	Statistics tester;
	StatusType result=tester.AddCourse(1,50);
	result=tester.AddCourse(2,50);
	result=tester.AddCourse(3,55);
	result=tester.AddStudent(74);
	result=tester.AddStudent(47);
	result=tester.AddStudent(54);
	result=tester.TakeCourse(74,1);
	result=tester.TakeCourse(74,2);
	result=tester.TakeCourse(47,1);
	result=tester.RemoveCourse(4);
	if (result != FAILURE){
		cout << "Test failed,we removed a course that didn't exist";
		return;
	}
	result=tester.RemoveCourse(1);
	if (tester.IsCourseExists(1)){
		cout << "Test failed, the course was not removed";
		return;
	}
	if (!tester.IsCourseExists(2) || !tester.IsCourseExists(3)){
		cout << "Test failed, a wrong course was removed";
		return;
	}
	isCourseTaken(1,tester.GetStudentTreeRoot());
	cout << "RemoveCourseTest: Test Passed."<<endl;

}





#endif /* DSTEST_H_ */
