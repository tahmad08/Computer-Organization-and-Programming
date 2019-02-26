;;===========================
;; Name: YOUR NAME HERE
;;===========================

;;Problem
;;-------
;;Calculate the sumtorial of the value stored at NUM and print the result
;; i.e, if 3 is stored at NUM then your assembly code should compute
;;3 + 2 + 1, and print the result, 6.

;;Pseudocode:
;;-----------

;; Sumtorial(n)
;; {
;;     int n = mem[NUM];
;;     int sum = 0;
;;     while (n > 0)
;;     {
;;        sum += n;
;;        n--;
;;     }
;;     return sum;
;; }

;;Hints
;;-----------
;;Look through the instruction set and think about which instruction you can use
;;to loop in your assembly code and evaluate your condition.


.orig x3000

;;Your Code Here

HALT

NUM     .FILL     #5
.end
