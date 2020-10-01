#include <bits/stdc++.h>
#include<iostream>
using namespace std;

class subject {
protected:
    int subID, credit{}, semester, attndCutoff{};
public:
    subject() {
        int x;
        x = rand() % 10000 + 10000;
        subID = x;
        x = rand() % 8 + 1;
        semester = x;
    }

    int returnCredit() { return credit; }

    // ADDED
    int returnSubId() { return subID; }

    void prntSubID() { cout << subID; }

    virtual int scoreMarks() = 0;

    virtual int debarStatus(int x) = 0;
};

class core : public subject {
public:
    core() = default;
};

class student {
protected:
    int stdID, semester, *attendance{}, *marks{};
    subject *sub[6]{};
    float CGPA;
public:
    student() {
        stdID = rand() % 100000 + 100000;
        semester = rand() % 8 + 1;
        CGPA = 0.0;
    }

    int getSemester() { return semester; }

    // ADDED
    int getStdId() { return stdID; }

    // ADDED
    float getCGPA() { return CGPA; }

    virtual void printDetails() = 0;

    virtual void computeCGPA() = 0;

    virtual void giveExam() = 0;

    virtual void registerSubject(subject *o) = 0;

    virtual int findAndReturnMarks(int subId) = 0;
};

class Theory : public core {
public:
    Theory() {
        credit = 4;
        attndCutoff = 70;
    }

    int debarStatus(int x) override {
        int tutorialAttnd;
        tutorialAttnd = rand() % 90 + 10;
        if ((x + tutorialAttnd) >= attndCutoff)
            return 1;
        else
            return 0;
    }

    int scoreMarks() override {
        int T1, T2, T3, TA, Tutorial;
        T1 = rand() % 21;
        T2 = rand() % 21;
        T3 = rand() % 36;
        TA = rand() % 16;
        Tutorial = rand() % 11;
        return T1 + T2 + T3 + TA + Tutorial;
    }
};

class Lab : public core {
public:
    Lab() {
        credit = 1;
        attndCutoff = 80;
    }

    int debarStatus(int x) override {
        if (x >= attndCutoff)
            return 1;
        else
            return 0;
    }

    int scoreMarks() override {
        int LT1, LT2, Assgn;
        int T, MiniPrj;
        LT1 = rand() % 21;
        LT2 = rand() % 21;
        MiniPrj = rand() % 11;
        Assgn = rand() % 51;
        T = LT1 + LT2 + Assgn + MiniPrj;
        return T;
    }
};

class Elective : public subject {
public:
    Elective() {
        credit = 3;
        attndCutoff = 70;
    }

    int debarStatus(int x) override {
        if (x >= attndCutoff)
            return 1;
        else { return 0; }
    }

    int scoreMarks() override {
        int T1, T2, T3, TA;
        T1 = rand() % 21;
        T2 = rand() % 21;
        T3 = rand() % 36;
        TA = rand() % 26;
        return T1 + T2 + T3 + TA;
    }
};

class UGStudent : public student {
public:
    UGStudent() {
        if (semester % 2 == 0) {
            marks = new int[6];
            attendance = new int[6];
            for (int i = 0; i < 6; i++) { sub[i] = NULL; }
        }
        else {
            marks = new int[5];
            attendance = new int[5];
            for (int i = 0; i < 6; i++) { sub[i] = NULL; }
        }
    }

    void registerSubject(subject *o) override {
        int j, i = 0;
        if (semester % 2 == 0) { j = 6; }
        else { j = 5; }
        while (sub[i] != NULL && i < j) { i++; }
        if (i == j) { cout << "\nCan not register more than " << j << " subjects"; }
        else { sub[i] = o; }
    }

    void giveExam() override {
        int j, i;
        if (semester % 2 == 0) { j = 6; }
        else { j = 5; }
        for (i = 0; i < j; i++) {
            attendance[i] = rand() % 101;
        }
        for (i = 0; i < j; i++)
            if (sub[i]->debarStatus(attendance[i])) { marks[i] = sub[i]->scoreMarks(); }
            else { marks[i] = 0; }
    }

    void computeCGPA() override {
        int j, i, credit, creditTotal = 0, gradePoint = 0;
        if (semester % 2 == 0) { j = 6; }
        else { j = 5; }
        for (i = 0; i < j; i++) {
            credit = sub[i]->returnCredit();
            creditTotal = creditTotal + credit;
            if (marks[i] >= 90) { gradePoint = gradePoint + credit * 10; }
            if (marks[i] >= 80 && marks[i] < 90) { gradePoint = gradePoint + credit * 9; }
            if (marks[i] >= 70 && marks[i] < 80) { gradePoint = gradePoint + credit * 8; }
            if (marks[i] >= 60 && marks[i] < 70) { gradePoint = gradePoint + credit * 7; }
            if (marks[i] >= 50 && marks[i] < 60) { gradePoint = gradePoint + credit * 6; }
            if (marks[i] >= 40 && marks[i] < 50) { gradePoint = gradePoint + credit * 5; }
            if (marks[i] >= 30 && marks[i] < 40) { gradePoint = gradePoint + credit * 4; }
            if (marks[i] < 30) { gradePoint = gradePoint + credit * 0; }
        }
        CGPA = gradePoint / creditTotal;
    }

    void printDetails() override {
        cout << "\nStudent ID: " << stdID;
        if (semester % 2 == 0) {
            for (int i = 0; i < 6; i++) {
                sub[i]->prntSubID();
                cout << " Attend = " << attendance[i] << " Marks = " << marks[i] << "\n";
            }
        }
        cout << "\nCGPA = " << CGPA;
    }

    // HELPER FUNTION TO FIND TOPPER WHEN SUBID IS GIVEN
    int findAndReturnMarks(int subId) override {
        int i, j;
        j = (semester % 2 == 0) ? 6 : 5;
        for (i = 0; i < j; ++i) {
            if (sub[i]->returnSubId() == subId)
                return marks[i];
        }
        return -1;
    }

};

// FUNCTION TO FIND TOPPER WHEM SUBID IS GIVEN
void findTopperSubject(int subId, student *stdu[], int size) {
    int Max = -1, student_id = -1;
    for (int i = 0; i < size; ++i) {
        int temp = stdu[i]->findAndReturnMarks(subId);
        if (temp != -1) {
            if (temp > Max) {
                Max = temp;
                student_id = stdu[i]->getStdId();
            }
        }
    }
    cout << "Topper of " << subId << " is " << student_id << " with marks " << Max << ".";
}

// FUNCTION TO FIND STUDENTS WHO ARE DEBARRED WHEM SUBID IS GIVEN
void findDebarred(int subId, student **stdu, int size) {
    vector<int> debarred;
    for (int i = 0; i < size; ++i) {
        int temp = stdu[i]->findAndReturnMarks(subId);
        if (temp == 0)
            debarred.emplace_back(stdu[i]->getStdId());
    }
    cout << "Students who have been debarred in " << subId << " are:\n";
    for (auto x: debarred)
        cout << x << '\n';
    cout << "--End of list--";
}

// FUNCTION TO FIND TOPPER WHEM SEMESETER IS GIVEN
void findTopperSemester(int semeseter, student *stdu[], int size) {
    if(semeseter < 1 or semeseter > 8) {
        cout<<"Please enter semester between 1 and 8\n";
    }
    int Max = -1, student_id = -1;
    for (int i = 0; i < size; ++i) {
        int temp = stdu[i]->getCGPA();
        int sem = stdu[i]->getSemester();
        if (temp > Max and sem == semeseter) {
            Max = temp;
            student_id = stdu[i]->getStdId();
        }
    }
    cout << "Semester topper for semeseter " << semeseter << " is " << student_id << " with cgpa of " << Max << ".";
}

int main() {
    subject *subj[50];
    student *stdu[200];
    int i, j, k, m;
    for (i = 0; i < 50; i++) {
        j = rand() % 3;
        if (j == 0) { subj[i] = new Theory; }
        if (j == 1) { subj[i] = new Lab; }
        if (j == 2) { subj[i] = new Elective; }
    }
    for (i = 0; i < 200; i++) {
        stdu[i] = new UGStudent;
        j = stdu[i]->getSemester();
        if (j % 2 == 0) {
            for (k = 0; k < 6; k++) {
                m = rand() % 50;
                stdu[i]->registerSubject(subj[m]);
            }
        }
        else {
            for (k = 0; k < 5; k++) {
                m = rand() % 50;
                stdu[i]->registerSubject(subj[m]);
            }
        }
    }
    for (i = 0; i < 200; i++) {
        stdu[i]->giveExam();
        stdu[i]->computeCGPA();
    }
    j = rand() % 200;

    // topper subject
    findTopperSubject(subj[0]->returnSubId(), stdu, 200);
    cout << "\n\n";

    // debarred subject
    findDebarred(subj[0]->returnSubId(), stdu, 200);
    cout << "\n\n";

    // topper semester
    findTopperSemester(1, stdu, 200);
    cout << "\n\n";
    return 0;
}
