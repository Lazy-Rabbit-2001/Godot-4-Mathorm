#pragma once

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>

using namespace godot;

// Calculus 
class Calculus : public RefCounted {
    GDCLASS(Calculus, RefCounted)

protected:
    static void _bind_methods();

public:
    enum {
        CALCULUS_SAMPLES = 2400,
    };

    // Constructor and Destructor
    Calculus();
    ~Calculus();

    // Methods
    static double get_integral_definite(const double from, const double to, const Callable &function, const int samples = CALCULUS_SAMPLES);
    static double get_derivative_at(const double x, const Callable &function, const double samples = 1.0 / double(CALCULUS_SAMPLES));
    static double get_legendre_elliptic_ii(double top, const double k, const int samples = CALCULUS_SAMPLES);    
};


// Vector2D
class Vec2D : public RefCounted {
    GDCLASS(Vec2D, RefCounted)

protected:
    static void _bind_methods();

public:
    static Vector2 get_projection_limit(const Vector2 &vector, const Vector2 &onto, const double length);
};


// Geomentry
// Ellipse
class Ellipse : public RefCounted {
    GDCLASS(Ellipse, RefCounted)

private:
    Vector2 center;
    Vector2 amplitude;
    double rotation;

protected:
    static void _bind_methods();

public:
    // Constructor and Destructor
    Ellipse(const Vector2 center = Vector2(0, 0), const Vector2 amplitude = Vector2(1, 1), const double rotation = 0.0);
    ~Ellipse();

    // Methods
    Ellipse* Ellipse::setup(const Vector2 &center, const Vector2 &amplitude, double rotation);

    double get_long_axis() const;
    double get_short_axis() const;
    double get_half_focal_distance() const;
    double get_eccentricity() const;
    double get_ellipse_area() const;
    double get_circumference() const;
    double get_circumference_accurate(const int samples = 2400) const;

    Vector2 get_point(const double phase) const;

    // Properties' Setters & Getters
    void set_center(const Vector2 &p_center);
    Vector2 get_center() const;

    void set_amplitude(const Vector2 &p_amplitude);
    Vector2 get_amplitude() const;

    void set_rotation(const double p_rotation);
    double get_rotation() const;
};



