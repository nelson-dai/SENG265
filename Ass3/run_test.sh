#This shell script uses merge.py to generate the example in the 
#assignment specification
python3 merge.py "Student Number" student_names.csv 265_a1_grades.csv 265_a2_grades.csv

python3 merge.py "Student" student_names.csv 265_a1_grades.csv 265_a2_grades.csv

python3 merge.py "A1 mark" student_names.csv 265_a1_grades.csv 265_a2_grades.csv
