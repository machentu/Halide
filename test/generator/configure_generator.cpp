#include "Halide.h"

namespace {

class Configure : public Halide::Generator<Configure> {
public:
    GeneratorParam<int> num_extra_inputs{"num_extra_inputs", 3};

    Input<Buffer<int>> input{"input", 3};
    Input<int> bias{"bias"};

    Output<Buffer<int>> output{ "output", 3 };

    void configure() {
        configure_calls++;

        // It's fine to examine GeneratorParams in the configure() method.
        assert(num_extra_inputs == 3);

        // Will fail: it is not legal to examine Inputs in the configure() method
        // assert(input.dimensions() == 3);

        // Will fail: it is not legal to examine Inputs in the configure() method
        // Expr b = bias;
        // assert(b.defined());

        // Will fail: it is not legal to examine Outputs in the configure() method
        // Func o = output;
        // assert(output.defined());
    }

    void generate() {
        assert(configure_calls == 1);
        Var x, y, c;
        output(x, y, c) = input(x, y, c) + bias;
    }

private:
    int configure_calls = 0;
};

}  // namespace

HALIDE_REGISTER_GENERATOR(Configure, configure)
