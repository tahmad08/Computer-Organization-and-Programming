/**
 * CS 2110 Fall 2018 HW2
 * Part 2 - Coding with bases
 *
 * @author Tahirah Ahmad
 *
 * Global rules for this file:
 * - You may not use more than 2 conditionals per method. Conditionals are
 *   if-statements, else-if statements, or ternary expressions. The else block
 *   associated with an if-statement does not count toward this sum. Boolean
 *   expressions outside of if-statements, else-if statements and ternary
 *   expressions do not count toward this sum either.
 * - You may not use more than 2 looping constructs per method. Looping
 *   constructs include for loops, while loops and do-while loops.
 * - You may not use nested loops.
 * - You may not declare any file-level variables.
 * - You may not declare any objects, other than String in select methods.
 * - You may not use switch statements.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - The only Java API methods you are allowed to invoke are:
 *     String.length()
 *     String.charAt()
 * - You may not invoke the above methods from string literals.
 *     Example: "12345".length()
 * - When concatenating numbers with Strings, you may only do so if the number
 *   is a single digit.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method, EXCEPT
 *   decimalStringToInt.
 * - You may declare exactly one String variable each in intToBinaryString and
 *   and intToHexString.
 */
public class Bases
{
    /**
     * Convert a string containing ASCII characters (in binary) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid binary numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: binaryStringToInt("111"); // => 7
     */
    public static int binaryStringToInt(String binary)
    {
        int count = 0;
        int newNum = 0;
        for ( int x = 0; x < binary.length(); x++) {
            count = count << 1; //this pushes the binary string one to the left and leaves a zero in the LSD
            //if a one needs to go here, it will be added in the first part of the if statement
            //otherwise it'll be a zero
            if (binary.charAt(x) == '1') {
                newNum = 1;
                count += newNum;//1 added in the LSD
            } else {
                newNum = 0;//doesn't really do anything here
            }
        }
        return count;
    }

    //!!!!!!!!!!!

    /**
     * Convert a string containing ASCII characters (in decimal) to an int.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid decimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: decimalStringToInt("123"); // => 123
     *
     * You may use multiplication, division, and modulus in this method.
     */
    public static int decimalStringToInt(String decimal)
    {
        int place = 1;//the 10s decimal place
        int curr = 0;//the total number to be returned 
        int num = 0;//the individual digit from the string we are looking at rn
        for (int x = decimal.length() - 1; x >= 0; x--) {
            //start from leftmost (MSD) to remain accurate
            num = decimal.charAt(x) - '0'; //converts the char to its correct decimal value. Look at the ASCII chart. for ex
            //the value of '1' is 49 and the val of '0' is 48. if you do '1'-'0', you get 1. 
            num *= place; //multiples whatever number you currently have by it's place (1's, 10's, 100's)
            curr += num; //adds the num from string to the overall number
            place *= 10;//increases the place
        }
        return curr;
    }

    /**
     * Convert a string containing ASCII characters (in hex) to an int.
     * The input string will only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers. The Strings we will pass in will be
     * valid hexadecimal numbers, and able to fit in a 32-bit signed integer.
     *
     * Example: hexStringToInt("A6"); // => 166
     */
    public static int hexStringToInt(String hex) {
        int place = 0; //16s place
        int answer = 0; //overall number to return
        int curr = 0;//number we are currently looking at from string
        for (int x = hex.length() - 1; x >= 0; x--) {
            //start form the MSD
            if (hex.charAt(x) > 64) {
                //that means the number is repped as a letter in the string (i.e., its >9)
                curr = hex.charAt(x) - '7';
                //converts hex letter to appropriate number value in 
            } else {
                curr = hex.charAt(x) - '0';
                //hex value is =< 9, converts to decimal
            }
            answer += curr << place;
            //the += happens first, then the <<. add the current decimal # to answer, then shift it to
            //its place
            place += 4;
            //increase place by 4, so in line 112, nxt # is multipled by 2^4, which is 16.
        }
        return answer;
    }



    /**
     * Convert a int into a String containing ASCII characters (in binary).
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToBinaryString(7); // => "111"
     *
     * You may declare one String variable in this method.
     */
    public static String intToBinaryString(int binary)
    {
        //main thing here is that the computer already reads numbers in binary. decimal 7 is seen as 111 already
        //so we just have to work like that
        String ans = "";
        if (binary == 0) {
            return "0";
        }
        while (binary > 0) {
            if ((binary & 1) != 0) {
                //if there's a one in the LSD
                ans = '1' + ans;
                //then add a 1 to the string
                binary = binary >> 1;
                //rightshift to shave off a number on the end that you just added to the string
            } else {
                ans = '0' + ans;
                //add 0 in not number in lsd
                binary = binary >> 1;
                //shift again
            }
        }
        return ans;

    }

    /**
     * Convert a int into a String containing ASCII characters (in hexadecimal).
     * The output string should only contain numbers and uppercase letters A-F.
     * You do not need to handle negative numbers.
     * The String returned should contain the minimum number of characters necessary to
     * represent the number that was passed in.
     *
     * Example: intToHexString(166); // => "A6"
     *
     * You may declare one String variable in this method.
     */
    public static String intToHexString(int hex)
    {
        String ans = "";
        int fours = 0;
        if (hex == 0) {
            return "0";
        }
        while (hex > 0) {
            fours = hex & 0b1111;//0b1111 is the binary rep of 31
            //SETS "fours" equal to ONLY the last 4 digits. recall that decimal #s are seen as binary in 
            //the computers eyes. so the input @hex is already in binary, and you look at each 4 binary bits and
            //convert individually. 
            if (fours > 9) {
                fours = (char)(fours + 55);
                ans = (char)(fours) + ans;
                //if the answer is supposed to be a letter val in hex, then this converts it
            } else {
                ans = (fours) + ans;
            }
            hex = hex >> 4;
        }
        return ans;
    }
}