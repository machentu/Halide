#include "HalideRuntime.h"
#include "HalideBuffer.h"

#include <math.h>
#include <stdio.h>

#include "configure.h"

using Halide::Runtime::Buffer;

const int kSize = 32;

int main(int argc, char **argv) {

    Buffer<int> input(kSize, kSize, 3);
    input.for_each_element([&](int x, int y, int c) {
        input(x, y, c) = (x * 3 + y * 5 + c * 7);
    });

    Buffer<int> output(kSize, kSize, 3);

    const int bias = 1;
    int result = configure(input, bias, output);
    if (result != 0) {
        fprintf(stderr, "Result: %d\n", result);
        exit(-1);
    }

    output.for_each_element([&](int x, int y, int c) {
        assert(output(x, y, c) == input(x, y, c) + bias);
    });

    printf("Success!\n");
    return 0;
}
