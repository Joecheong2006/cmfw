#include "primitive_shape_renderer.h"
#include <math.h>
#include "core/defines.h"

#if defined(_MSC_VER)
    // MSVC setup macro
    #pragma section(".CRT$XCU", read)
    #define INITIALIZER(f) \
        static void f(void); \
        __declspec(allocate(".CRT$XCU")) void (*f##_)(void) = f; \
        static void f(void)
#elif defined(__GNUC__) || defined(__clang__)
    // GCC/Clang setup macro (Priority 110)
    #define INITIALIZER(f) \
        static void f(void) __attribute__((constructor(110))); \
        static void f(void)
#else
    #define INITIALIZER(f) \
        #error "Unsupported compiler"
#endif

#define PI 3.14159265359
#define CIRCLE_POINT_COUNT 36

static vec2 circle_points[CIRCLE_POINT_COUNT];

INITIALIZER(init_circle_points) {
    f32 per_a = 360.0 / CIRCLE_POINT_COUNT;
    for (int i = 0; i < CIRCLE_POINT_COUNT; i++) {
        f32 a = (i + 1) * per_a;
        circle_points[i][0] = cos(a * PI / 180.0);
        circle_points[i][1] = sin(a * PI / 180.0);
    }
}

void draw_debug_circle(vec3 position, f32 radius, vec3 color) {
    vec3 p1, p2;
    for (int i = 0; i < CIRCLE_POINT_COUNT - 1; ++i) {
    	p1[0] = position[0] + circle_points[i][0] * radius;
    	p1[1] = position[1] + circle_points[i][1] * radius;
    	p1[2] = position[2];
    	p2[0] = position[0] + circle_points[i + 1][0] * radius;
    	p2[1] = position[1] + circle_points[i + 1][1] * radius;
    	p2[2] = position[2];
    	render_debug_line(p1, p2, color);
    }
	p1[0] = position[0] + circle_points[0][0] * radius;
	p1[1] = position[1] + circle_points[0][1] * radius;
	p1[2] = position[2];
	p2[0] = position[0] + circle_points[CIRCLE_POINT_COUNT - 1][0] * radius;
	p2[1] = position[1] + circle_points[CIRCLE_POINT_COUNT - 1][1] * radius;
	p2[2] = position[2];
	render_debug_line(p1, p2, color);
}

