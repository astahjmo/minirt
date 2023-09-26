#include "../../tester.h"

#define suite_name canvas
static void set_all_pixels_to_one_color(const t_canvas *c, t_tuple color);
int create_ppm_file(t_string ppm_string, const char filename[]);

//  =======================================================================  //
//                         Scenario: creating a canvas                       //
//  =======================================================================  //
#define scenario1                                                                        \
    CYAN "\n"                                                                            \
         "Given c ← canvas(20, 10)\n"                                                  \
         "Then c.width = 10 And c.height = 20\n"                                         \
         "And every pixel of c is color(0, 0, 0)" RESET

Test(suite_name, creating_a_canvas, .description = scenario1) {
    const t_canvas c = create_canvas(20, 10);
    cr_expect_eq(c.width, 10);
    cr_expect_eq(c.height, 20);
    for (int i = 0; i < c.width * c.height; i++) {
        int eq = cr_expect_tuple_eq(c.pixels[i / c.width][i % c.width],
                                    (t_tuple){0, 0, 0, COLOR});
        cr_assert_eq(eq, TRUE);
    }
}

//  =======================================================================  //
//                   Scenario: Writing a pixel to a canvas                   //
//  =======================================================================  //
#define scenario2                                                                        \
    CYAN "\n"                                                                            \
         "Given c ← canvas(20, 10)\n"                                                  \
         "When write_pixel(c, 2, 3, red)\n"                                              \
         "Then pixel_at(c, 2, 3) = red" RESET

Test(suite_name, writing_a_pixel_in_a_canvas, .description = scenario2) {
    t_canvas c = create_canvas(20, 10);
    write_pixel(&c, 3, 2, (t_tuple){1, 0, 0, COLOR});
    int eq = cr_expect_tuple_eq(c.pixels[3][2], (t_tuple){1, 0, 0, COLOR});
    cr_expect_eq(eq, TRUE);
}

//  =======================================================================  //
//               Scenario: Constructing the PPM header                       //
//  =======================================================================  //
#define scenario3                                                                        \
    CYAN "\n"                                                                            \
         "Given c ← canvas(3, 5)\n"                                                    \
         "When ppm ← canvas_to_ppm(c)\n"                                               \
         "Then lines 1-3 of ppm are:\n"                                                  \
         "P3\n"                                                                          \
         "5 3\n"                                                                         \
         "255\n" RESET

Test(suite_name, constructing_the_ppm_header, .description = scenario3) {
    const char expected[] = "P3\n5 3\n255\n"; // "P3\n" and "255\n" are fixed for all ppm
                                              // files in this project
    const t_canvas c = create_canvas(3, 5);
    const char *ppm_canvas_full = canvas_to_ppm(&c);
    char ppm_header[12];
    ft_strlcpy(ppm_header, ppm_canvas_full, 12);
    cr_expect_str_eq(ppm_header, expected);
}

//  =======================================================================  //
//               Scenario: Constructing the PPM pixel data                   //
//  =======================================================================  //
#define scenario4                                                                        \
    CYAN "\nGiven c ← canvas(3, 5)\n"                                                  \
         "And c1 ← color(1.5, 0, 0)\n"                                                 \
         "And c2 ← color(0, 0.5, 0)\n"                                                 \
         "And c3 ← color(-0.5, 0, 1)\n"                                                \
         "When write_pixel(c, 0, 0, c1)\n"                                               \
         "And write_pixel(c, 2, 1, c2)\n"                                                \
         "And write_pixel(c, 4, 2, c3)\n"                                                \
         "And ppm ← canvas_to_ppm(c)\n"                                                \
         "Then lines 4-6 of ppm are\n"                                                   \
         "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"                                             \
         "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"                                             \
         "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"

Test(suite_name, writing_the_whole_canvas_on_the_ppm_string, .description = scenario4) {
    t_canvas c = create_canvas(3, 5);
    const char expected[] = "P3\n5 3\n255\n"
                            "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                            "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    write_pixel(&c, 0, 0, (t_tuple){1.5, 0, 0, COLOR});
    write_pixel(&c, 1, 2, (t_tuple){0, 0.5, 0, COLOR});
    write_pixel(&c, 2, 4, (t_tuple){-0.5, 0, 1, COLOR});
    const char *res = canvas_to_ppm(&c);
    cr_expect_str_eq(res, expected);
	int fd = create_ppm_file(res, "output_scenario4.ppm");
    destroy_canvas(&c);
    close(fd);
}

#define scenario5                                                                        \
    CYAN "\nScenario: Splitting long lines in PPM files"                                 \
         "Given c ← canvas(2, 10)\n"                                                   \
         "When every pixel of c is set to color(1, 0.8, 0.6)\n"                          \
         "And ppm ← canvas_to_ppm(c)\n"                                                \
         "Then lines 4-7 of ppm are\n"                                                   \
         "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"         \
         "153 255 204 153 255 204 153 255 204 153 255 204 153\n"                         \
         "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"         \
         "153 255\n"


Test(suite_name, lines_longer_than_70_should_break, .description = scenario5) {
    const t_canvas c = create_canvas(2, 10);
	t_string ppm_string = canvas_to_ppm(&c);
	char *line;
	printf("%s\n", ppm_string);
	int fd = create_ppm_file(ppm_string, "scenario5.ppm");

	line = ft_gnl(fd);
	printf(GREEN"\n\n\n\n\n\n\nline: %s\n"RESET, line);
	// cr_expect_str_eq(line, "P3\n");
	free(line);
}

int create_ppm_file(t_string ppm_string, const char filename[]) {
	int fd = open(filename, O_CREAT | O_RDWR, 0666);
    if (fd < 0)
    	perror("Error opening file!\n");
    if (write(fd, ppm_string, strlen(ppm_string)) != strlen(ppm_string)) {
        perror("Error writing to file!\n");
    }
	return fd;
}

static void set_all_pixels_to_one_color(const t_canvas *c, t_tuple color) {
    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            write_pixel((t_canvas *)c, x, y, color);
        }
    }
}
