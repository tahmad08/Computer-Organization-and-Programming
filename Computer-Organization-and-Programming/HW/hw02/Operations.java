/**
 * CS 2110 Fall 2018 HW2
 * Part 3 - Coding with bitwise operators
 *
 * @author Tahirah Ahmad
 *
 * Global rules for this file:
 * - All of these functions must be completed in ONE statement. That means they should be
 *   of the form "return [...];", with a single semicolon. No partial credit will be
 *   awarded for any Method that isn't completed with one statement.
 *
 * - You may not use more than 2 conditionals per method, which for this file would
 *   just be ternary expressions. Boolean expressions outside of ternary expressions do
 *   not count toward this sum.
 * - You may not declare any variables.
 * - You may not use casting.
 * - You may not use the unsigned right shift operator (>>>)
 * - You may not write any helper methods, or call any other method from this or
 *   another file to implement any method.
 * - In functions where addition or subtraction is allowed, you may only do so
 *   with the number 1.
 *
 * Method-specific rules for this file:
 * - You may not use multiplication, division or modulus in any method.
 * - You may not use addition, subtraction, or conditionals in setShort,
 *   getByte, bitRange, pack, or xnor.
 * - You may not use bitshifting or the exclusive OR operator (^) in xnor.
 *
 * Finally, your code must be robust and concise. If we asked you to print out the values 1 through 100
 * and you wrote 100 separate print statements, then sure, it works, but no one's gonna hire a coder who does
 * that. Likewise, you will NOT get credit for verbose answers for which there is a much more concise
 * solution. For instance, if you need to shift a value by n*4 times, you may not write x << n << n << n << n
 * or you will get no credit, because there is a much more concise way to do this in only two operations by
 * first shifting n. Keep this in mind, ESPECIALLY in the first 2 functions in this file.
 *
 * Remember that for this assignment, All bit masks must be written in hexadecimal.
 * This is the convention for masks and makes it much easier for the programmer to
 * understand the code. If you write a mask in any other base you will lose points.
 *
 * All of these functions accept ints as parameters because if you pass in a number
 * (which is of type int by default) into a Method accepting a byte, then the Java
 * compiler will complain even if the number would fit into that type.
 *
 * Now, keep in mind the return value is also an int. Please read the comments about how
 * many significant bits to return and make sure that the other bits are not set or else
 * you will not get any points for that test case.
 * i.e if I say to return 6 bits and you return 0xFFFFFFFF, you will lose points.
 *
 * Definitions of types:
 * nibble - 4 bits
 * byte   - 8 bits
 * short  - 16 bits
 * int    - 32 bits
 */
public class Operations
{
    /**
     * Get an 8-bit byte from an int.
     *
     * Ints are made of 4 bytes, numbered like so:
     *   B3 | B2 | B1 | B0
     *
     * For a graphical representation of the bits:
     *   33222222222211111111110000000000
     *   10987654321098765432109876543210 <= starting with bit 0
     *   +--------------+---------------+
     *   |  3   |   2   |   1   |   0   |
     *
     * Examples:
     *     getByte(0x56781234, 0); // => 0x34
     *     getByte(0xFF254534, 1); // => 0x45
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int to get a byte from.
     * @param which Determines which byte gets returned - 0 for
     *              least-significant byte.
     *
     * @return A byte corresponding to the "which" parameter from num.
     */
    int getByte(int num, int which)
    {
        return ((num  >> (which << 3)) & 0xFF);
//        return (num & (0xFF << (which << 3)));

    }

    /**
     * Set a 16-bit short in an int.
     *
     * Ints are made of 2 shorts, numbered like so:
     *   S1 | S0
     *
     * For a graphical representation of the bits:
     *   33222222222211111111110000000000
     *   10987654321098765432109876543210 <= starting with bit 0
     *   ---------------+----------------
     *   |      1       |       0       |
     *
     * Examples:
     *     setShort(0xAAA5BBC6, 0x1234, 0); // => 0xAAA51234
     *     setShort(0x56B218F9, 0x8765, 1); // => 0x876518F9
     *
     * Note: Remember, no multiplication allowed!
     *
     * @param num The int that will be modified.
     * @param a_short The short to insert into the integer.
     * @param which Selects which short to modify - 0 for least-significant
     * short.
     *
     * @return The modified int.
     */
    int setShort(int num, int a_short, int which)
    {
        return (a_short <<(which << 4)) | num & ~(0xFFFF << (which << 4));
    }
    //((bits & (1 << index)) != 0) && (index <= 31)
    //!!!!!!!!!!!!

    /**
     * Packs 4 bytes into an int.
     *
     * The bytes should be placed consecutively in the 32-bit int in the order
     * that they appear in the parameters
     *
     * Example:
     *     pack(0x12, 0x34, 0x56, 0x78); // => 0x12345678
     *     pack(0xDE, 0xAD, 0xBE, 0xEF); // => 0xDEADBEEF
     *
     * @param b3 Most significant byte (will always be a 8-bit number).
     * @param b2 Second most significant byte (will always be a 8-bit number).
     * @param b1 Third most significant byte (will always be a 8-bit number).
     * @param b0 Least significant byte (will always be a 8-bit number).
     *
     * @return a 32-bit value formatted like so: b3b2b1b0
     */
    int pack(int b3, int b2, int b1, int b0)
    {
        return b3 <<(3 << 3) | b2 << (2 << 3) | b1 <<(1 << 3) |b0;
    }

    /**
     * Extract a range of bits from a number.
     *
     * Examples:
     *     bitRange(0x00001234, 0, 4);  // => 0x00000004
     *     bitRange(0x00001234, 4, 8);  // => 0x00000023
     *     bitRange(0x12345678, 0, 28); // => 0x02345678
     *     bitRange(0x55555555, 5, 7);  // => 0x0000002A
     *
     * Note: We will only pass in values 1 to 32 for n.
     * Second Note: In the examples above, the "num" parameter is in hex. Each
     *              digit of a hex number is 4 bits long!
     *
     * @param num An n-bit 2's complement number.
     * @param s The starting bit to grab
     * @param n The number of bits to return.
     * @return The n-bit number num[s:s+n-1].
     */
    int bitRange(int num, int s, int n)
    {
        return ~(0xFFFFFFFF << n) & (num >> s);
        //ur welcome idiot
    }

    /**
     * NOTE: For this method, you may only use &, |, and ~.
     *
     * Perform an exclusive-nor on two 32-bit ints.
     *
     * Examples:
     *     xnor(0xFF00FF00, 0x00FF00FF); // => 0x00000000
     *     xnor(0xAA00AA00, 0xAA00AA00); // => 0xFFFFFFFF
     *     xnor(0xF6683B06, 0xFD877726); // => 0xF410B3DF
     *
     * @param num1 An int
     * @param num2 Another int
     *
     * @return ~(num1 ^ num2)
     */
    int xnor(int num1, int num2)
    {
        return ~((num1 & ~num2) | (~num1 & num2));
    }

    /**
     * Return true if the given number is a power of 2.
     *
     * You may use addition, subtraction, and conditionals in this method.
     *
     * Examples:
     *     powerOf2(1024); // => true
     *     powerOf2(23);   // => false
     *
     * Note: Make sure you handle ALL the cases!
     * Note2: Remember: Robust and concise! Do not just return an OR of all the powers of 2.
     *
     * @param num a 32-bit int. Since this is an int, it is SIGNED!
     * @return true if num is a power of 2.
     */

    boolean powerOf2(int num)
    {
        return num >= 1 && (num & (num - 0x1)) == 0;
    }
}
