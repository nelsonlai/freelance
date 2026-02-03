-- =============================================================
-- COM641 Assignment 1 - Task 3: Procedures, Functions, Triggers and Active Rules
-- Student: [Your Name]
-- =============================================================

-- =============================================================
-- Schema Definition
-- =============================================================

CREATE TABLE Student (
    student_id     NUMBER PRIMARY KEY,
    student_name   VARCHAR2(100),
    state          VARCHAR2(50),
    city           VARCHAR2(50),
    postcode       VARCHAR2(10)
);

CREATE TABLE Course (
    course_id      NUMBER PRIMARY KEY,
    course_name    VARCHAR2(100),
    description    VARCHAR2(200)
);

CREATE TABLE Section (
    section_id     NUMBER PRIMARY KEY,
    course_id      NUMBER REFERENCES Course(course_id),
    instructor_id  NUMBER,
    start_date     DATE,
    capacity       NUMBER
);

CREATE TABLE Enrolment (
    enrol_id       NUMBER PRIMARY KEY,
    student_id     NUMBER REFERENCES Student(student_id),
    section_id     NUMBER REFERENCES Section(section_id)
);

CREATE TABLE Assessment (
    assess_id      NUMBER PRIMARY KEY,
    section_id     NUMBER REFERENCES Section(section_id),
    assess_type    VARCHAR2(20),
    weight_pct     NUMBER
);

CREATE TABLE Grade (
    assess_id      NUMBER REFERENCES Assessment(assess_id),
    student_id     NUMBER REFERENCES Student(student_id),
    mark           NUMBER
);

-- =============================================================
-- Sample Data
-- =============================================================
INSERT INTO Student VALUES (1001, 'Alice Brown', 'ON', 'Toronto', 'M2N1X1');
INSERT INTO Student VALUES (1002, 'Bob Smith', 'ON', 'Toronto', 'M3J1P3');
INSERT INTO Student VALUES (1003, 'Charlie Chen', 'BC', 'Vancouver', 'V5K0A1');

INSERT INTO Course VALUES (10, 'Database Systems', 'Study of databases and SQL');
INSERT INTO Course VALUES (11, 'Distributed Computing', 'Study of distributed systems');

INSERT INTO Section VALUES (501, 10, 9001, DATE '2025-09-01', 3);
INSERT INTO Section VALUES (502, 11, 9002, DATE '2025-09-05', 2);

INSERT INTO Enrolment VALUES (1, 1001, 501);
INSERT INTO Enrolment VALUES (2, 1002, 501);
INSERT INTO Enrolment VALUES (3, 1003, 502);

INSERT INTO Assessment VALUES (101, 501, 'Quiz', 20);
INSERT INTO Assessment VALUES (102, 501, 'Midterm', 30);
INSERT INTO Assessment VALUES (103, 501, 'Final', 50);
INSERT INTO Assessment VALUES (201, 502, 'Quiz', 30);
INSERT INTO Assessment VALUES (202, 502, 'Final', 70);

INSERT INTO Grade VALUES (101, 1001, 80);
INSERT INTO Grade VALUES (102, 1001, 75);
INSERT INTO Grade VALUES (103, 1001, 85);
INSERT INTO Grade VALUES (101, 1002, 90);
INSERT INTO Grade VALUES (102, 1002, 60);
INSERT INTO Grade VALUES (103, 1002, 70);
INSERT INTO Grade VALUES (201, 1003, 85);
INSERT INTO Grade VALUES (202, 1003, 80);

COMMIT;

-- =============================================================
-- Task 3a - Procedures
-- =============================================================

-- I. Final Mark Sheet Procedure
CREATE OR REPLACE PROCEDURE prc_final_mark_sheet (p_student_id IN NUMBER) IS
    CURSOR c_course IS
        SELECT c.course_name, s.section_id
        FROM Section s
        JOIN Course c ON s.course_id = c.course_id
        JOIN Enrolment e ON e.section_id = s.section_id
        WHERE e.student_id = p_student_id;
    v_final NUMBER;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Final Mark Sheet for Student ID: ' || p_student_id);
    FOR rec IN c_course LOOP
        SELECT SUM(g.mark * a.weight_pct/100)
          INTO v_final
          FROM Grade g
          JOIN Assessment a ON g.assess_id = a.assess_id
         WHERE g.student_id = p_student_id
           AND a.section_id  = rec.section_id;
        DBMS_OUTPUT.PUT_LINE('Course: ' || rec.course_name || '  Final Mark: ' || NVL(v_final,0));
    END LOOP;
END;
/

-- Test Procedure
SET SERVEROUTPUT ON;
EXEC prc_final_mark_sheet(1001);

-- II. Course Statistics Procedure
CREATE OR REPLACE PROCEDURE prc_course_statistics IS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Course Statistics Report');
    FOR rec IN (
        SELECT c.course_name,
               s.section_id,
               COUNT(e.student_id) AS num_students,
               ROUND(MAX(final_mark),2) AS max_mark,
               ROUND(MIN(final_mark),2) AS min_mark,
               ROUND(AVG(final_mark),2) AS avg_mark,
               ROUND(STDDEV(final_mark),2) AS stddev_mark,
               SUM(CASE WHEN final_mark BETWEEN 80 AND 100 THEN 1 ELSE 0 END) AS firsts,
               SUM(CASE WHEN final_mark BETWEEN 70 AND 79  THEN 1 ELSE 0 END) AS seconds,
               SUM(CASE WHEN final_mark BETWEEN 60 AND 69  THEN 1 ELSE 0 END) AS thirds,
               SUM(CASE WHEN final_mark < 60 THEN 1 ELSE 0 END) AS fails
        FROM (
            SELECT e.student_id, s.section_id,
                   SUM(g.mark * a.weight_pct/100) AS final_mark
            FROM Enrolment e
            JOIN Section s ON e.section_id = s.section_id
            JOIN Assessment a ON s.section_id = a.section_id
            JOIN Grade g ON a.assess_id = g.assess_id AND g.student_id = e.student_id
            GROUP BY e.student_id, s.section_id
        ) fm
        JOIN Section s ON s.section_id = fm.section_id
        JOIN Course c ON s.course_id = c.course_id
        JOIN Enrolment e ON e.section_id = s.section_id
        GROUP BY c.course_name, s.section_id
        ORDER BY c.course_name
    ) LOOP
        DBMS_OUTPUT.PUT_LINE('Course: '||rec.course_name||
            ' | Students: '||rec.num_students||
            ' | Avg: '||rec.avg_mark||
            ' | 1st:'||rec.firsts||' 2nd:'||rec.seconds||
            ' 3rd:'||rec.thirds||' Fails:'||rec.fails);
    END LOOP;
END;
/

EXEC prc_course_statistics;

-- III. Performance by Location
CREATE OR REPLACE PROCEDURE prc_perf_by_location IS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Performance by Location');
    FOR rec IN (
        SELECT st.state, st.city, st.postcode,
               c.course_name,
               ROUND(AVG(SUM(g.mark * a.weight_pct/100)) OVER
                     (PARTITION BY st.state, st.city, st.postcode, c.course_name),2) AS avg_mark
          FROM Student st
          JOIN Enrolment e ON st.student_id = e.student_id
          JOIN Section s ON e.section_id = s.section_id
          JOIN Course c ON s.course_id = c.course_id
          JOIN Assessment a ON s.section_id = a.section_id
          JOIN Grade g ON g.assess_id = a.assess_id AND g.student_id = st.student_id
      GROUP BY st.state, st.city, st.postcode, c.course_name
      ORDER BY avg_mark DESC
    ) LOOP
        DBMS_OUTPUT.PUT_LINE(rec.state||' - '||rec.city||' - '||rec.postcode||
            ' | '||rec.course_name||' | Avg:'||rec.avg_mark);
    END LOOP;
END;
/

EXEC prc_perf_by_location;

-- =============================================================
-- Task 3b - Active Rules Using Triggers
-- =============================================================

-- I. Restrict DML Outside Working Hours
CREATE OR REPLACE TRIGGER trg_office_hours_protect
BEFORE INSERT OR UPDATE OR DELETE ON Enrolment
DECLARE
    v_day  VARCHAR2(10);
    v_hour NUMBER;
BEGIN
    v_day  := TO_CHAR(SYSDATE, 'DY');
    v_hour := TO_NUMBER(TO_CHAR(SYSDATE, 'HH24'));

    IF (v_day IN ('SAT','SUN')) OR
       (v_day='FRI' AND v_hour>=17) OR
       (v_day='MON' AND v_hour<8) OR
       (v_day NOT IN ('SAT','SUN','FRI','MON') AND (v_hour<9 OR v_hour>=17)) THEN
        RAISE_APPLICATION_ERROR(-20001,'❌ Operation not allowed outside office hours (Mon 9 AM - Fri 5 PM).');
    END IF;
END;
/

-- II. Capacity Check Trigger
CREATE OR REPLACE TRIGGER trg_capacity_check
BEFORE INSERT ON Enrolment
FOR EACH ROW
DECLARE
    v_count NUMBER;
    v_capacity CONSTANT NUMBER := 60;
BEGIN
    SELECT COUNT(*) INTO v_count FROM Enrolment WHERE section_id = :NEW.section_id;
    SELECT capacity INTO v_capacity FROM Section WHERE section_id = :NEW.section_id;

    IF v_count >= v_capacity THEN
        RAISE_APPLICATION_ERROR(-20002,'❌ Capacity limit reached for this section.');
    ELSIF v_count >= v_capacity-2 THEN
        DBMS_OUTPUT.PUT_LINE('⚠️ Warning: Section is nearing capacity ('||v_count||'/'||v_capacity||')');
    END IF;
END;
/

-- =============================================================
-- End of Task 3 Script
-- =============================================================
