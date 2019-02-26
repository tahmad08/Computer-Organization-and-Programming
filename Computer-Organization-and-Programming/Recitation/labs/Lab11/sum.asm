;;===========================
;; Name: Tahirah AHmad
;;===========================

;;Problem
;;-------
;;Sum the values from the memory locations labelled X and Y, then print a message
;;and their sum to the user, in the console using printing traps. For example, if
;;the sum is 5, it should print: "The sum is: 5". For simplicity, the sum will
;;only be between 0 and 9, inclusive.

;;Pseudocode
;;----------
;;void sum() {
;;    int x = 2;
;;    int y = 3;
;;    int sum = x + y;
;;    const char *msg = "The sum is: ";
;;    printf(msg); // Uses the address of the first character to print msg
;;                 // Which LC3 instruction can you use to get the address of a
;;                 // label? Take a look at the ISA (appendix A)
;;    printf("%c", sum + 48); // The OUT trap prints the number as ASCII!
;;}
;;
;;
;;Hints
;;-----
;;You may find the PUTS trap to be helpful for printing strings. Read about the
;;PUTS trap in the ISA to see how it works!

;;You may find the OUT trap to be helpful for printing numbers. Read about the
;;OUT trap in the ISA to see how it works!

;;Note that OUT prints the number as an ASCII
;;value, so if your sum is 7 and you try to print it, you'll get garbage values
;;in your output. You must add the ASCII offset for '0' (which is 48).

;;The line const char *msg = "The sum is: "; declares a variable called "msg"
;;that contains the address of the first character of a null-terminated string
;;containing the characters "The sum is: ".

;;Strings in C and LC3 are null-terminated, meaning that there is a value of
;;zero at the end of the string. Printing functions like printf and PUTS know to
;;stop printing characters when they reach this value.


.ORIG x3000
LEA R0, THE_SUM_IS
PUTS

;;good habit is to clear registers before you fill them with values
AND R1, R1, 0
AND R2, R2, 0
AND R3, R3, 0


;;now load vars x and y
LD R1, X ; R1 <- X
LD R2, Y ; R2 <- Y
ADD R2, R1, R2
OUT




HALT

X .FILL 2
Y .FILL 3

;;need to print actual value, use OUT
;;looks at the offset and ASCII table
;;need to add 48 because in ASCII table, 48 is the start of smthn 
ASCII .FILL 48

THE_SUM_IS .STRINGZ "The sum is: " 
.END

;;to specify that x and y have certain cvalues, create labels


