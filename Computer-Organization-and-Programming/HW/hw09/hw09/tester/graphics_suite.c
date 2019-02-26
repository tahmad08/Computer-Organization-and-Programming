#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "../graphics.h"
#include "qdbmp.h"
#include "../images/azul.h"
#include "../images/austinbear.h"

#define RED ((Pixel) 0x1F)
#define GREEN ((Pixel) 0x3E0)
#define BLUE ((Pixel) 0x7C00)
#define YELLOW ((Pixel) 0x3FF)
#define BLACK ((Pixel) 0x0)
#define WHITE ((Pixel) 0x7FFF)

#define DARKRED ((Pixel) 0xF)
#define DARKGREEN ((Pixel) 0x1E0)
#define DARKBLUE ((Pixel) 0x3C00)

#define WIDTH 240
#define HEIGHT 160

#define MARGIN 10
#define BUFFER_WIDTH(w) (w)
#define BUFFER_HEIGHT(h) (h + (2 * MARGIN))
#define BUFFER_SIZE(w, h) (BUFFER_WIDTH(w) * BUFFER_HEIGHT(h))

#define ACTUAL_FILENAME(test) "tester/actual/"#test".bmp"
#define DIFF_FILENAME(test) "tester/diff/"#test".bmp"
#define EXPECTED_FILENAME(test) "tester/expected/"#test".bmp"

#define START_BUFFERED_TEST(test) \
START_TEST(test) {\
    char* actualFilename = ACTUAL_FILENAME(test);\
    char* diffFilename = DIFF_FILENAME(test);\
    char* expectedFilename = EXPECTED_FILENAME(test);

#define END_BUFFERED_TEST \
    save_buffer(actualFilename, paddedBuffer, BUFFER_WIDTH(screen->size.x), BUFFER_HEIGHT(screen->size.y));\
    load_buffer(expectedFilename, compareBuffer, BUFFER_WIDTH(screen->size.x), BUFFER_HEIGHT(screen->size.y));\
    create_diff(paddedBuffer, compareBuffer, BUFFER_WIDTH(screen->size.x), BUFFER_HEIGHT(screen->size.y));\
    save_buffer(diffFilename, diffBuffer, BUFFER_WIDTH(screen->size.x), BUFFER_HEIGHT(screen->size.y));\
    ck_assert_buffer_eq(compareBuffer, paddedBuffer);\
}\
END_TEST

#define ck_assert_buffer_eq(b1, b2) {\
    for (int r = BUFFER_HEIGHT(0); r < BUFFER_HEIGHT(HEIGHT); r++) {\
        for (int c = BUFFER_WIDTH(0); c < BUFFER_WIDTH(WIDTH); c++) {\
            int index = r * BUFFER_WIDTH(WIDTH) + c;\
    	    if(b1[index] != b2[index]) {\
                char* outmsg = malloc(200 * sizeof(char));\
                snprintf(outmsg, 200, "Pixel mismatch at row %d, column %d. Expected 0x%x, found 0x%x.", r, c, b1[index], b2[index]);\
                ck_abort_msg(outmsg);\
            }\
        }\
    }\
}

#define add_tcase(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(#func); \
    tcase_set_timeout(tc, 10); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}

static Pixel *paddedBuffer;
static Screen *screen;

static Pixel *compareBuffer;
static Pixel *diffBuffer;

void setup_screen(unsigned int width, unsigned int height) {
    paddedBuffer = malloc(BUFFER_WIDTH(width) * BUFFER_HEIGHT(height) * sizeof(Pixel));

    // Wipe the buffer
    for (unsigned int i = 0; i < BUFFER_SIZE(width, height); i++) {
        paddedBuffer[i] = WHITE;
    }

    // Draw a frame outside the actual display
    for (unsigned int i = 0; i < BUFFER_WIDTH(width); i++) {
        paddedBuffer[(MARGIN - 1) * BUFFER_WIDTH(width) + i] = BLACK;
        paddedBuffer[(MARGIN + height) * BUFFER_WIDTH(width) + i] = BLACK;
    }

    // Get a pointer to the actual location of the display
    Pixel* buffer = paddedBuffer + (MARGIN * BUFFER_WIDTH(width));
    screen = malloc(sizeof(Screen));
    screen->size = (Vector){width, height};
    screen->buffer = buffer;

    compareBuffer = malloc(BUFFER_WIDTH(width) * BUFFER_HEIGHT(height) * sizeof(Pixel));
    diffBuffer = malloc(BUFFER_WIDTH(width) * BUFFER_HEIGHT(height) * sizeof(Pixel));
}

void setup_default_screen(void) {
    setup_screen(WIDTH, HEIGHT);
}

void setup_larger_screen(void) {
    setup_screen(800, 600);
}

void teardown_screen(void) {
    free(paddedBuffer);
    free(screen);

    free(compareBuffer);
    free(diffBuffer);
}

void load_buffer(char* filename, Pixel *buffer, unsigned int width, unsigned int height) {
    BMP* bmp = BMP_ReadFile(filename);
    uint8_t r, g, b;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            BMP_GetPixelRGB(bmp, x, y, &r, &g, &b);
            buffer[y * width + x] = ((b >> 3) << 10) | ((g >> 3) << 5) | (r >> 3);
        }
    }

    BMP_Free(bmp);
}

void save_buffer(char* filename, Pixel *buffer, unsigned int width, unsigned int height) {
    BMP* bmp = BMP_Create(width, height, 24);
    Pixel pixel;
    uint8_t r, g, b;

    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            pixel = buffer[y * width + x];
            r = ((pixel) & 0x1F) * 255 / 31;
            g = ((pixel >> 5) & 0x1F) * 255 / 31;
            b = ((pixel >> 10) & 0x1F) * 255 / 31;
            BMP_SetPixelRGB(bmp, x, y, r, g, b);
        }
    }

    BMP_WriteFile(bmp, filename);
    BMP_Free(bmp);
}

void create_diff(Pixel *actual, Pixel *expected, unsigned int width, unsigned int height) {

    for (unsigned int y=0; y<height; y++){
      for (unsigned int x=0; x<width; x++){
	if (actual[y * width + x] == expected[y * width + x])
	  diffBuffer[y * width + x] = 0x1F << 5;	//GREEN
	else
	  diffBuffer[y * width + x] = 0x1F;		//RED;
      }
    }
}

START_TEST (noFilter_untouched)
{
  ck_assert_uint_eq(noFilter(WHITE), WHITE);
  ck_assert_uint_eq(noFilter(BLACK), BLACK);
  ck_assert_uint_eq(noFilter(GREEN), GREEN);
  ck_assert_uint_eq(noFilter(GREEN | BLUE), GREEN | BLUE);
  ck_assert_uint_eq(noFilter(DARKRED | DARKBLUE), DARKRED | DARKBLUE);
}
END_TEST

START_TEST (greyscaleFilter_white)
{
  ck_assert_uint_eq(greyscaleFilter(WHITE), WHITE);
}
END_TEST

START_TEST (greyscaleFilter_black)
{
  ck_assert_uint_eq(greyscaleFilter(BLACK), BLACK);
}
END_TEST

START_TEST (greyscaleFilter_green)
{
  ck_assert_uint_eq(greyscaleFilter(GREEN), 19026);
}
END_TEST

START_TEST (greyscaleFilter_cyan)
{
  ck_assert_uint_eq(greyscaleFilter(GREEN | BLUE), 22197);
}
END_TEST

START_TEST (greyscaleFilter_darkpurple)
{
  ck_assert_uint_eq(greyscaleFilter(DARKRED | DARKBLUE), 6342);
}
END_TEST

START_TEST (redOnlyFilter_white)
{
  ck_assert_uint_eq(redOnlyFilter(WHITE), RED);
}
END_TEST

START_TEST (redOnlyFilter_black)
{
  ck_assert_uint_eq(redOnlyFilter(BLACK), BLACK);
}
END_TEST

START_TEST (redOnlyFilter_green)
{
  ck_assert_uint_eq(redOnlyFilter(GREEN), 0);
}
END_TEST

START_TEST (redOnlyFilter_cyan)
{
  ck_assert_uint_eq(redOnlyFilter(GREEN | BLUE), 0);
}
END_TEST

START_TEST (redOnlyFilter_darkpurple)
{
  ck_assert_uint_eq(redOnlyFilter(DARKRED | DARKBLUE), 15);
}
END_TEST

START_TEST (brighterFilter_white)
{
  ck_assert_uint_eq(brighterFilter(WHITE), WHITE);
}
END_TEST

START_TEST (brighterFilter_black)
{
  ck_assert_uint_eq(brighterFilter(BLACK), 15855);
}
END_TEST

START_TEST (brighterFilter_green)
{
  ck_assert_uint_eq(brighterFilter(GREEN), 16367);
}
END_TEST

START_TEST (brighterFilter_darkgreen)
{
  ck_assert_uint_eq(brighterFilter(DARKGREEN), 16111);
}
END_TEST

START_TEST (brighterFilter_darkpurple)
{
  ck_assert_uint_eq(brighterFilter(DARKRED | DARKBLUE), 24055);
}
END_TEST

START_TEST (rotateImage_topleft)
    // Checks that the topleft coordinate is not modified in rotateImage
    Image image = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    for (int i = -360; i <= 720; i += 90) {
        Image rotated = rotateImage(&image, i);
        ck_assert_int_eq(image.top_left.x, rotated.top_left.x);
        ck_assert_int_eq(image.top_left.y, rotated.top_left.y);

        free(rotated.buffer);
    }
END_TEST

START_TEST (rotateImage_size)
    // Checks that the size is correctly edited
    Image image = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    for (int i = -360; i <= 720; i += 90) {
        Image rotated = rotateImage(&image, i);

        // This following line is obfuscated because it would give away the answer.
        int r = (!(i % (0x0000000000000168 + 0x00000000000002B4 + 0x00000000000008B4 - 0x0000000000000C1C) ^ 0x0000000000000000));
        int expected_rotated_x = r ? rotated.size.x : rotated.size.y;
        int expected_rotated_y = r ? rotated.size.y : rotated.size.x;
        ck_assert_int_eq(image.size.x, expected_rotated_x);
        ck_assert_int_eq(image.size.y, expected_rotated_y);

        free(rotated.buffer);
    }
END_TEST

START_BUFFERED_TEST (drawPixel_simple)
{
    drawPixel(screen, (Vector){10, 10}, RED);
    drawPixel(screen, (Vector){20, 10}, YELLOW);
    drawPixel(screen, (Vector){18, 27}, BLUE);
    drawPixel(screen, (Vector){190, 140}, GREEN);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawPixel_outofbounds)
{
    drawPixel(screen, (Vector){290, 0}, RED);
    drawPixel(screen, (Vector){290, 180}, GREEN);
    drawPixel(screen, (Vector){0, 180}, BLUE);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledRectangle_simple)
{
    drawFilledRectangle(screen, &(Rectangle){(Vector){0, 0}, (Vector){240, 160}, RED});
    drawFilledRectangle(screen, &(Rectangle){(Vector){15, 15}, (Vector){30, 90}, GREEN});
    drawFilledRectangle(screen, &(Rectangle){(Vector){110, 150}, (Vector){120, 10}, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledRectangle_outofbounds)
{
    drawFilledRectangle(screen, &(Rectangle){(Vector){10, 10}, (Vector){240, 20}, RED});
    drawFilledRectangle(screen, &(Rectangle){(Vector){15, 15}, (Vector){20, 200}, GREEN});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawLine_horizontal)
{
    drawLine(screen, &(Line){(Vector){10, 10}, (Vector){200, 10}, RED});
    drawLine(screen, &(Line){(Vector){200, 100}, (Vector){50, 100}, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawLine_vertical)
{
    drawLine(screen, &(Line){(Vector){50, 10}, (Vector){50, 120}, RED});
    drawLine(screen, &(Line){(Vector){190, 100}, (Vector){190, 50}, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawLine_positiveslope)
{
    drawLine(screen, &(Line){(Vector){10, 10}, (Vector){150, 150}, RED});
    drawLine(screen, &(Line){(Vector){200, 100}, (Vector){40, 50}, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawLine_negativeslope)
{
    drawLine(screen, &(Line){(Vector){10, 150}, (Vector){230, 10}, RED});
    drawLine(screen, &(Line){(Vector){50, 150}, (Vector){200, 120}, BLUE});
    drawLine(screen, &(Line){(Vector){50, 150}, (Vector){100, 10}, RED | BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawLine_outofbounds)
{
    drawLine(screen, &(Line){(Vector){290, 10}, (Vector){10, 150}, RED});
    drawLine(screen, &(Line){(Vector){50, 150}, (Vector){200, 300}, BLUE});
    drawLine(screen, &(Line){(Vector){10, 159}, (Vector){400, 159}, RED | BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawPolygon_triangle)
{
    Vector triangle[3];

    triangle[0] = (Vector){120, 20};
    triangle[1] = (Vector){10, 150};
    triangle[2] = (Vector){230, 150};

    Polygon p = {triangle, 3, BLACK};

    drawPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawPolygon_star)
{
    Vector v0 = {117, 80};
    Vector v01 = {130, 75};
    Vector v1 = {130, 61};
    Vector v12 = {139, 73};
    Vector v2 = {153, 68};
    Vector v23 = {145, 80};
    Vector v3 = {153, 92};
    Vector v34 = {139, 88};
    Vector v4 = {130, 99};
    Vector v40 = {130, 85};
    Vector star[10] = {v0, v01, v1, v12, v2, v23, v3, v34, v4, v40};

    Polygon p = {star, 10, RED | BLUE};
    drawPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawPolygon_outofbounds)
{
    Vector triangle[3];

    triangle[0] = (Vector){120, 20};
    triangle[1] = (Vector){10, 150};
    triangle[2] = (Vector){400, 190};

    Polygon p = {triangle, 3, BLUE};
    drawPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledPolygon_triangle)
{
    Vector triangle[3];

    triangle[0] = (Vector){120, 20};
    triangle[1] = (Vector){10, 150};
    triangle[2] = (Vector){230, 150};

    Polygon p = {triangle, 3, BLACK};

    drawFilledPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledPolygon_star)
{
    Vector v0 = {117, 80};
    Vector v01 = {130, 75};
    Vector v1 = {130, 61};
    Vector v12 = {139, 73};
    Vector v2 = {153, 68};
    Vector v23 = {145, 80};
    Vector v3 = {153, 92};
    Vector v34 = {139, 88};
    Vector v4 = {130, 99};
    Vector v40 = {130, 85};
    Vector star[10] = {v0, v01, v1, v12, v2, v23, v3, v34, v4, v40};

    Polygon p = {star, 10, RED | BLUE};
    drawFilledPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledPolygon_outofbounds)
{
    Vector triangle[3];

    triangle[0] = (Vector){120, 20};
    triangle[1] = (Vector){10, 150};
    triangle[2] = (Vector){400, 190};

    Polygon p = {triangle, 3, BLUE};
    drawFilledPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawRectangle_simple)
{
    drawRectangle(screen, &(Rectangle){(Vector){0, 0}, (Vector){240, 160}, RED});
    drawRectangle(screen, &(Rectangle){(Vector){15, 15}, (Vector){30, 90}, GREEN});
    drawRectangle(screen, &(Rectangle){(Vector){110, 150}, (Vector){120, 10}, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawRectangle_outofbounds)
{
    drawRectangle(screen, &(Rectangle){(Vector){10, 10}, (Vector){240, 20}, RED});
    drawRectangle(screen, &(Rectangle){(Vector){15, 15}, (Vector){20, 200}, GREEN});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawCircle_simple)
{
    drawCircle(screen, &(Circle){(Vector){145, 80}, 75, RED | BLUE});
    drawCircle(screen, &(Circle){(Vector){120, 80}, 50, BLACK});
    drawCircle(screen, &(Circle){(Vector){100, 80}, 30, RED});
    drawCircle(screen, &(Circle){(Vector){90, 80}, 20, BLUE});
    drawCircle(screen, &(Circle){(Vector){80, 80}, 10, GREEN});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawCircle_outofbounds)
{
    drawCircle(screen, &(Circle){(Vector){0, 0}, 75, RED | BLUE});
    drawCircle(screen, &(Circle){(Vector){0, 159}, 50, BLACK});
    drawCircle(screen, &(Circle){(Vector){239, 0}, 30, RED});
    drawCircle(screen, &(Circle){(Vector){239, 159}, 20, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledCircle_simple)
{
    drawFilledCircle(screen, &(Circle){(Vector){145, 80}, 75, RED | BLUE});
    drawFilledCircle(screen, &(Circle){(Vector){120, 80}, 50, BLACK});
    drawFilledCircle(screen, &(Circle){(Vector){100, 80}, 30, RED});
    drawFilledCircle(screen, &(Circle){(Vector){90, 80}, 20, BLUE});
    drawFilledCircle(screen, &(Circle){(Vector){80, 80}, 10, GREEN});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawFilledCircle_outofbounds)
{
    drawFilledCircle(screen, &(Circle){(Vector){0, 0}, 75, RED | BLUE});
    drawFilledCircle(screen, &(Circle){(Vector){0, 159}, 50, BLACK});
    drawFilledCircle(screen, &(Circle){(Vector){239, 0}, 30, RED});
    drawFilledCircle(screen, &(Circle){(Vector){239, 159}, 20, BLUE});
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_fullscreen_simple)
{
    Image i = {(Vector){0,0}, (Vector){AZUL_WIDTH, AZUL_HEIGHT}, azul};
    drawImage(screen, &i, noFilter);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_fullscreen_outofbounds)
{
    Image i = {(Vector){120, 80}, (Vector){AZUL_WIDTH, AZUL_HEIGHT}, azul};
    drawImage(screen, &i, noFilter);

}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_fullscreen_withfilter)
{
    Image i = {(Vector){0,0}, (Vector){AZUL_WIDTH, AZUL_HEIGHT}, azul};
    drawImage(screen, &i, greyscaleFilter);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_small_simple)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    drawImage(screen, &i, noFilter);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_small_outofbounds)
{
    Image i = {(Vector){-50,-20}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    drawImage(screen, &i, noFilter);

}
END_BUFFERED_TEST

START_BUFFERED_TEST (drawImage_small_withfilter)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    drawImage(screen, &i, redOnlyFilter);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_0)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, 0);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_90)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, 90);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_180)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, 180);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_270)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, 270);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_large_positive_angle)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, 630);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (rotateImage_large_negative_angle)
{
    Image i = {(Vector){5,5}, (Vector){AUSTINBEAR_WIDTH, AUSTINBEAR_HEIGHT}, austinbear};
    Image r = rotateImage(&i, -450);
    drawImage(screen, &r, noFilter);
    free(r.buffer);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (combination_cems_almost_turkish_flag)
{
    Pixel turkish_red = 0xC7A;
    drawFilledRectangle(screen, &(Rectangle){(Vector){0, 0}, (Vector){240, 160}, turkish_red});

    // Draw the crescent
    drawFilledCircle(screen, &(Circle){(Vector){85, 80}, 40, WHITE});
    drawFilledCircle(screen, &(Circle){(Vector){95, 80}, 32, turkish_red});

    Vector v0 = {117, 80};
    Vector v01 = {130, 75};
    Vector v1 = {130, 61};
    Vector v12 = {139, 73};
    Vector v2 = {153, 68};
    Vector v23 = {145, 80};
    Vector v3 = {153, 92};
    Vector v34 = {139, 88};
    Vector v4 = {130, 99};
    Vector v40 = {130, 85};

    Vector star[10] = {v0, v01, v1, v12, v2, v23, v3, v34, v4, v40};
    Polygon p = {star, 10, WHITE};
    drawFilledPolygon(screen, &p);
}
END_BUFFERED_TEST

START_BUFFERED_TEST (check_if_screen_size_was_used_correctly)
{
    drawFilledCircle(screen, &(Circle){(Vector){0, 0}, 75, RED | BLUE});
    drawFilledCircle(screen, &(Circle){(Vector){0, 159}, 50, BLACK});
    drawFilledCircle(screen, &(Circle){(Vector){239, 0}, 30, RED});
    drawFilledCircle(screen, &(Circle){(Vector){239, 159}, 20, BLUE});
}
END_BUFFERED_TEST

Suite *graphics_suite(void) {
    Suite *s = suite_create("graphics");

    add_tcase(s, NULL, NULL, noFilter_untouched);

    add_tcase(s, NULL, NULL, greyscaleFilter_white);
    add_tcase(s, NULL, NULL, greyscaleFilter_black);
    add_tcase(s, NULL, NULL, greyscaleFilter_green);
    add_tcase(s, NULL, NULL, greyscaleFilter_cyan);
    add_tcase(s, NULL, NULL, greyscaleFilter_darkpurple);

    add_tcase(s, NULL, NULL, redOnlyFilter_white);
    add_tcase(s, NULL, NULL, redOnlyFilter_black);
    add_tcase(s, NULL, NULL, redOnlyFilter_green);
    add_tcase(s, NULL, NULL, redOnlyFilter_cyan);
    add_tcase(s, NULL, NULL, redOnlyFilter_darkpurple);

    add_tcase(s, NULL, NULL, brighterFilter_white);
    add_tcase(s, NULL, NULL, brighterFilter_black);
    add_tcase(s, NULL, NULL, brighterFilter_green);
    add_tcase(s, NULL, NULL, brighterFilter_darkgreen);
    add_tcase(s, NULL, NULL, brighterFilter_darkpurple);

    add_tcase(s, NULL, NULL, rotateImage_topleft);
    add_tcase(s, NULL, NULL, rotateImage_size);

    add_tcase(s, setup_default_screen, teardown_screen, drawPixel_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawPixel_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawFilledRectangle_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawFilledRectangle_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawLine_horizontal);
    add_tcase(s, setup_default_screen, teardown_screen, drawLine_vertical);
    add_tcase(s, setup_default_screen, teardown_screen, drawLine_positiveslope);
    add_tcase(s, setup_default_screen, teardown_screen, drawLine_negativeslope);
    add_tcase(s, setup_default_screen, teardown_screen, drawLine_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawPolygon_triangle);
    add_tcase(s, setup_default_screen, teardown_screen, drawPolygon_star);
    add_tcase(s, setup_default_screen, teardown_screen, drawPolygon_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawFilledPolygon_triangle);
    add_tcase(s, setup_default_screen, teardown_screen, drawFilledPolygon_star);
    add_tcase(s, setup_default_screen, teardown_screen, drawFilledPolygon_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawRectangle_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawRectangle_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawCircle_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawCircle_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawFilledCircle_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawFilledCircle_outofbounds);

    add_tcase(s, setup_default_screen, teardown_screen, drawImage_fullscreen_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawImage_fullscreen_outofbounds);
    add_tcase(s, setup_default_screen, teardown_screen, drawImage_fullscreen_withfilter);

    add_tcase(s, setup_default_screen, teardown_screen, drawImage_small_simple);
    add_tcase(s, setup_default_screen, teardown_screen, drawImage_small_outofbounds);
    add_tcase(s, setup_default_screen, teardown_screen, drawImage_small_withfilter);

    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_0);
    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_90);
    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_180);
    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_270);
    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_large_positive_angle);
    add_tcase(s, setup_default_screen, teardown_screen, rotateImage_large_negative_angle);

    add_tcase(s, setup_default_screen, teardown_screen, combination_cems_almost_turkish_flag);

    add_tcase(s, setup_larger_screen, teardown_screen, check_if_screen_size_was_used_correctly);

    return s;
}
