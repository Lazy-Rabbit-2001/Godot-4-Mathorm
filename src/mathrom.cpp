#include "mathorm.h"

#include <functional>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


// Calculus
void Calculus::_bind_methods() {
    // Register constants
    BIND_CONSTANT(CALCULUS_SAMPLES);
    // Register methods
    ClassDB::bind_static_method("Calculus", D_METHOD("get_integral_definite", "from", "to", "function", "samples"), &Calculus::get_integral_definite, CALCULUS_SAMPLES);
    ClassDB::bind_static_method("Calculus", D_METHOD("get_derivative_at", "x", "function", "samples"), &Calculus::get_derivative_at, 1.0 / double(CALCULUS_SAMPLES));
    ClassDB::bind_static_method("Calculus", D_METHOD("get_legendre_elliptic_ii", "top", "k", "samples"), &Calculus::get_legendre_elliptic_ii, CALCULUS_SAMPLES);
}

// Constructor and Destructor
Calculus::Calculus() {}

Calculus::~Calculus() {}

// Methods
double Calculus::get_integral_definite(const double from, const double to, const Callable &function, const int samples) {
    if (samples < CALCULUS_SAMPLES) {
        UtilityFunctions::printerr("Sample amount ", samples, " is lower than ", CALCULUS_SAMPLES, ", integral will become more inaccurate!");
    }

    double ret = 0.0;
    double l = from;
    double r = l;

    for (int i = 0; i <= samples; i++) {
        // Moves the right edge
        r = Math::lerp(from, to, double(i) / double(samples));
        // Calculates the average height
        double aveH = function.call(((l + r) / 2));
        // Gets the "size" of rectangle
        ret += (r - l) * aveH;

        // Moves the left edge to the right one
        l = r;
    }

    return ret;
}

double Calculus::get_derivative_at(const double x, const Callable &function, const double samples) {
    if (samples > CALCULUS_SAMPLES) {
        UtilityFunctions::printerr("Sample amount ", samples, " is greater than ", 1.0 / CALCULUS_SAMPLES, ", derivative will become more inaccurate!");
    }

    return (double(function.call(x + samples)) - double(function.call(x))) / samples;
}

double Calculus::get_legendre_elliptic_ii(const double top, const double k, const int samples) {
    auto lambda = [](double x, double s) {
        return sqrt(1 - s * pow(sin(x), 2.0));
    };

    double (*p_lambda)(double x, double s) = lambda;
    Callable func = create_custom_callable_static_function_pointer<double>(p_lambda).bind(k);
    
    return get_integral_definite(0, top, func, samples);
}

    
// Transform2DAlgo
void Transform2DAlgo::_bind_methods() {
    // Register methods
    ClassDB::bind_static_method("Transform2DAlgo", D_METHOD("get_projection_limit", "vector", "onto", "length"), &Transform2DAlgo::get_projection_limit);
    ClassDB::bind_static_method("Transform2DAlgo", D_METHOD("get_direction_to_regardless_transform", "origin", "target", "trans", "index"), &Transform2DAlgo::get_direction_to_regardless_transform, 0);
}

Vector2 Transform2DAlgo::get_projection_limit(const Vector2 &vector, const Vector2 &onto, const double length) {
    double dot = vector.dot(onto);
    if (dot < 0 || UtilityFunctions::is_zero_approx(UtilityFunctions::snappedf(dot, 0.001))) {
        return vector;
    }

    Vector2 v = vector.project(onto);
    Vector2 d = v - v.limit_length(length);

    return double(v.length_squared()) > pow(length, 2.0) ? vector - d : vector;
}

int Transform2DAlgo::get_direction_to_regardless_transform(const Vector2 &origin, const Vector2 &target, const Transform2D &trans, int index) {
    Transform2D atr = trans.affine_inverse();
    
    index = UtilityFunctions::clampi(index, 0, 1);

    double ori = atr.basis_xform(origin)[index];
    double tgt = atr.basis_xform(target)[index];

    return UtilityFunctions::signi(tgt - ori);
}


// Geomentry
// Ellipse
void Ellipse::_bind_methods() {
    // Register properties
    // Vector2 center
    ClassDB::bind_method(D_METHOD("get_center"), &Ellipse::get_center);
    ClassDB::bind_method(D_METHOD("set_center", "p_center"), &Ellipse::set_center);
    ClassDB::add_property(
        "Ellipse", PropertyInfo(Variant::VECTOR2, "center"),
        "set_center", "get_center"
    );
    // Vector2 amplitude
    ClassDB::bind_method(D_METHOD("get_amplitude"), &Ellipse::get_amplitude);
    ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &Ellipse::set_amplitude);
    ClassDB::add_property(
        "Ellipse", PropertyInfo(Variant::VECTOR2, "amplitude"),
        "set_amplitude", "get_amplitude"
    );
    // double rotation
    ClassDB::bind_method(D_METHOD("get_rotation"), &Ellipse::get_rotation);
    ClassDB::bind_method(D_METHOD("set_rotation", "p_rotation"), &Ellipse::set_rotation);
    ClassDB::add_property(
        "Ellipse", PropertyInfo(Variant::VECTOR2, "rotation"),
        "set_rotation", "get_rotation"
    );

    // Register methods
    ClassDB::bind_method(D_METHOD("setup", "center", "amplitude", "rotation"), &Ellipse::setup, Vector2(), Vector2(1, 1), 0.0);
    ClassDB::bind_method(D_METHOD("get_long_axis"), &Ellipse::get_long_axis);
    ClassDB::bind_method(D_METHOD("get_short_axis"), &Ellipse::get_short_axis);
    ClassDB::bind_method(D_METHOD("get_half_focal_distance"), &Ellipse::get_half_focal_distance);
    ClassDB::bind_method(D_METHOD("get_eccentricity"), &Ellipse::get_eccentricity);
    ClassDB::bind_method(D_METHOD("get_ellipse_area"), &Ellipse::get_ellipse_area);
    ClassDB::bind_method(D_METHOD("get_circumference"), &Ellipse::get_circumference);
    ClassDB::bind_method(D_METHOD("get_circumference_accurate", "samples"), &Ellipse::get_circumference_accurate, Calculus::CALCULUS_SAMPLES);
}

// Constructor and Destructor
Ellipse::Ellipse(Vector2 center, Vector2 amplitude, double rotation) {
    this->center = center;
    this->amplitude = amplitude;
    this->rotation = rotation;
}

Ellipse::~Ellipse() {}

Ellipse* Ellipse::setup(const Vector2 &center, const Vector2 &amplitude, const double rotation) {
    this->center = center;
    this->amplitude = amplitude;
    this->rotation = rotation;
    
    return this;
}

// Methods
double Ellipse::get_long_axis() const {
    return amplitude[amplitude.max_axis_index()];
}

double Ellipse::get_short_axis() const {
    return amplitude[amplitude.min_axis_index()];
}

double Ellipse::get_half_focal_distance() const {
    double as = pow(get_long_axis(), 2.0);
    double bs = pow(get_short_axis(), 2.0);

    return sqrt(as - bs);
}

double Ellipse::get_eccentricity() const {
    return get_half_focal_distance() / get_long_axis();
}

double Ellipse::get_ellipse_area() const {
    return Math_PI * get_long_axis() * get_short_axis();
}

double Ellipse::get_circumference() const {
    double a = get_long_axis();
    double b = get_short_axis();

    if (a == b) {
        return Math_PI * (a + b);
    }

    double l = (a - b) / (a + b);
    double p = 3 * pow(l, 2.0);
    double q = 1 + p / (10 + double(sqrtf(4 - p)));

    return Math_PI * (a + b) * q;
}

double Ellipse::get_circumference_accurate(const int samples) const {
    double a = get_long_axis();
    double b = get_short_axis();
    double e = get_eccentricity();
    
    if (a == b) {
        return Math_PI * (a + b);
    }
    
    return 4 * a * Calculus::get_legendre_elliptic_ii(Math_PI / 2.0, pow(e, 2.0), samples);
}

Vector2 Ellipse::get_point(const double phase) const {
    return center + Vector2(amplitude.x * cos(phase), amplitude.y * sin(phase)).rotated(rotation);
}

// Properties' Setters & Getters
void Ellipse::set_center(const Vector2 &p_center) {
    center = p_center;
}

Vector2 Ellipse::get_center() const {
    return center;
}

void Ellipse::set_amplitude(const Vector2 &p_amplitude) {
    amplitude = p_amplitude;
}

Vector2 Ellipse::get_amplitude() const {
    return amplitude;
}

void Ellipse::set_rotation(const double p_rotation) {
    rotation = p_rotation;
}

double Ellipse::get_rotation() const {
    return rotation;
}
