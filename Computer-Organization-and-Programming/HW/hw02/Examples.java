/**
 * This class provides some worked examples of some methods which are similar
 * to some of those that you will have to implement in your assignment. If you
 * are having trouble, try looking at these to see how you could approach each
 * problem.
 */

public class Examples {
    int bitVector; // an int whose bits will be individually manipulated

    /**
     * This method clears the fourth bit (from the right) of the bit vector
     * declared above. This is very similar to the clear method you will have to
     * implement in the BitVector.java file, and the general approach should
     * help you to figure out some of the other problems.
     *
     * Example: If bitVector has the binary value 0000001101010111, then after
     *          calling this method it will be    0000001101000111.
     *
     */
    public void clearFourthBitOfBitVector() {
        int mask = 0x1; // mask is 000000000000000000000000000000001

        mask = mask << 4; // mask is now 00000000000000000000000000010000

        mask = ~mask; // mask is now 11111111111111111111111111101111

        /*
        Recall that a bitwise AND (&) of 1 and any other bit will be the
        other bit, and recall that a bitwise AND of 0 and any other bit will
        be 0.
        This means that when we AND a bit vector with our mask, wherever
        there is a 1 in the mask, the bit vector keeps its initial value, and
        wherever there is a 0 in the mask, the bit vector will become 0.
        */
        bitVector = bitVector & mask; // clears the fourth bit of the bit vector
    }

    /**
     * Note that many of the methods in this homework assignment need to be
     * implemented in one line. This can be very tricky to do all at once, so
     * we will demonstrate how you could do so after finding a multiline
     * solution.
     *
     * If we wanted to convert our above code into one line, we could make the
     * following changes:
     *
     *    1. Notice that we can replace the first use of mask with its literal
     *       value, giving us:
     *          short mask = 0x1;
     *          mask = 0x1 << 4; // was previously: mask = mask << 4
     *          mask = ~mask;
     *          bitVector = bitVector & mask;
     *
     *   2. Notice that we now assign mask the value 0x1 << 4 before we ever
     *      use its value of 0x1 from the first line. This means that we can
     *      combine the first and second line as follows:
     *          short mask = 0x1 << 4;
     *          mask = ~mask;
     *          bitVector = bitVector & mask;
     *
     *   3. Repeat the procedure in step 1 to get:
     *          short mask = 0x1 << 4;
     *          mask = ~(0x1 << 4);
     *          bitVector = bitVector & mask;
     *
     *   4. Again, notice that this makes the first assignment useless, so
     *      repeat the procedure in step 2:
     *          short mask = ~(0x1 << 4);
     *          bitVector = bitVector & mask;
     *
     *   5. Now we see that we can replace mask in the last line with the
     *      literal value of mask from the first line, yielding our final
     *      answer:
     *          bitVector = bitVector & ~(0x1 << 4);
     *
     * If your multiline solution can't be reduced to 1 line on this assignment,
     * there is probably a simpler way to approach the problem.
     */

    /**
     * This method does the same thing as the method above, but is implemented
     * more efficiently.
     */
    public void clearFourthBitOfBitVectorInOneLine() {
        bitVector = bitVector & ~(0x1 << 4);
    }


    /**
     * Converts the rightmost (least significant) two hex digits of an unsigned
     * int to a String. Remember that a hex digit, from 0 to F, is 4 bits long,
     * so our answer should always return 4 bits.
     * @param number an arbitrary unsigned int
     * @return a String corresponding to the hex value of the rightmost two
     *         hex digits of number
     *
     * Example: hexDigitToString(0x1234) -> "34"
     *          hexDigitToString(0xABCD) -> "CD"
     *          // Remember that all ints are actually represented as binary.
     *          // While we can write and display them as hex for convenience,
     *          // they are still binary, and we can write them as such.
     *          hexDigitToString(0b0001001000110100) -> "34"
     *          hexDigitToString(0b1010101111001101) -> "CD"
     *          // We could also write them with their decimal values, though
     *          // this hides what is actually going on and makes your code much
     *          // more difficult to read.
     *          hexDigitToString(4660) -> "34"
     *          hexDigitToString(43981) -> "CD"
     *
     */
    public String rightmostTwoHexDigitsToString(int number)
    {
        String result = ""; // empty String where we will store our answer

        /*
        In order to isolate the rightmost hex digit of our number, we must get
        the number's rightmost 4 bits. We can do this with the same AND
        technique that we showed above, but with the bitmask 0b1111 == 0xF
        instead. If we AND anything with 0b1111, all of the bits on the left
        side will become 0, but the rightmost 4 bits will not change.
        */
        int rightmostHexDigit = number & 0xF;

        /*
        Now, we need to get the ASCII character that corresponds to that
        rightmost hex digit.

        Remember that chars are also binary values, meaning that you can do
        arithmetic with them. Also, remember that the numbers in the ASCII
        table are in order from 0 to 9, and that the letters in the ASCII table
        are in order from A to Z.

        This means that an expression like '0' + 4 would result in the
        character '4', or '0' + 7 would result in the character '7'. Thus, for
        any single decimal digit (i.e., a hex digit less than or equal to 9),
        we can essentially add it to '0' to get the correct char.

        However, we also need to cast to a char in this case because Java will
        automatically promote char + int to be an int, which is too large
        to assign to a char. Casting will make sure that we only assign the
        portion of the int which will fit into a char, which will be its
        rightmost 8 bits.
        */
        if (rightmostHexDigit <= 9) {
            char decimalDigit = (char) ('0' + rightmostHexDigit);
            /*
            Since decimalDigit is a char, adding it to result will prepend its
            ASCII value to result (which is currently empty). If decimalDigit
            were an int, decimalDigit + result would instead yield the decimal
            value of decimalDigit as a String, which is not what we want.
            */
            result = decimalDigit + result;
        }

        /*
        Now we need to handle the case where a hex digit has a value greater
        than or equal to A, i.e., a value which will not fit within a single
        decimal digit. We can use a trick similar to the one we used before,
        where we can use our hex digit's value as an offset from some position
        in the ASCII table.

        Suppose our hex digit is 0xD, which has a decimal value of 13. It is
        also true that 0xD == 10 + 3 == 0xA + 3. Notice that if we change 0xA
        to be the character 'A', then the statement 'D' == 'A' + 3 is also true!
        We can manipulate these equations a little to show a direct way of
        obtaining 'D' from 0xD:
          0xD == 10 + 3 means that 0xD - 10 == 3.
          We can then replace the 3 in 'D' == 'A' + 3 with 0xD - 10 to find that
          'D' == 'A' + (0xD - 10)
        In fact, this pattern is true for any hex digit greater than 0xA, not
        just 0xD, and we can use it to get the correct char for our result.
        */
        else {
            char hexDigit = (char) ('A' + (rightmostHexDigit - 10));
            result = hexDigit + result;
        }

        /*
        At this point, result contains the first hexadecimal character of our
        answer, so we need to move on to the next hexadecimal digit to convert.
        To do this, we can shift our number to the right by 4 to move the next
        hex digit to the rightmost position. Then, we can mask with 0xF as we
        did earlier to just get the 4 bits at the end that we want.
        */
        number = number >> 4;
        rightmostHexDigit = number & 0xF;

        /*
        After isolating the correct 4 bits, we can convert them to a character
        in exactly the same way that we did before. Thinking about the fact that
        both conversions are the same should help you in constructing your loops
        in Bases.java.
        */
        if (rightmostHexDigit <= 9) {
            result = (char) ('0' + rightmostHexDigit) + result;
        }
        else {
            result = (char) ('A' + (rightmostHexDigit - 10)) + result;
        }

        // The result should now contain the rightmost two hex digits of the
        // original number.
        return result;
    }
}
