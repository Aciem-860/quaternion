#ifndef QUATERNION_H
#define QUATERNION_H

typedef struct {
    double scalar;
    union {
        double vector[3];
        struct {
            double i;
            double j;
            double k;
        };
    };
} Quaternion_t;

double vector_get_norm(const double v[3]);
double get_norm2(const Quaternion_t* const q);
double get_norm(const Quaternion_t* const q);
void mult_sc_quaternion(const double sc, const Quaternion_t* q, Quaternion_t* ret);
void invert_quaternion(const Quaternion_t* const q, Quaternion_t* ret);
void get_conj(const Quaternion_t* const q, Quaternion_t* r);
void mult(const Quaternion_t* const q1, const Quaternion_t* const q2, Quaternion_t* ret);
void print_quaternion(const Quaternion_t* q);
void rotate(const double vector[3], const double axis[3], const double angle, double ret[3]);

#endif
