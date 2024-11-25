#include <stdio.h>
#include <math.h>
#include "quaternion.h"

#define SQ(x) (x*x)

static void mult_sc_vec(const double sc, const double vector[3], double ret[3]) {
    for (int i = 0; i < 3; i++) {
        ret[i] = vector[i] * sc;
    }
}

static double scalar_product(const double v1[3], const double v2[3]) {
    double ret = 0;
    for (int i = 0; i < 3; i++) {
        ret += v1[i] * v2[i];
    }
    return ret;
}

static void vector_product(const double v1[3], const double v2[3], double ret[3]) {
    ret[0] = v1[1] * v2[2] - v1[2] * v2[1];
    ret[1] = v1[2] * v2[0] - v1[0] * v2[2];
    ret[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

static void add_vector(const double v1[3], const double v2[3], double ret[3]) {
    for (int i = 0; i < 3; i++) {
        ret[i] = v1[i] + v2[i];
    }
}

double vector_get_norm(const double v[3]) {
    return sqrt(SQ(v[0]) + SQ(v[1]) + SQ(v[2]));
}

double get_norm2(const Quaternion_t* const q) {
    return SQ(q->scalar) + SQ(q->i) + SQ(q->j) + SQ(q->k);
}

double get_norm(const Quaternion_t* const q) {
    return sqrt(get_norm2(q));
}

void mult_sc_quaternion(const double sc, const Quaternion_t* q, Quaternion_t* ret) {
    ret->scalar = sc * q->scalar;
    for (int i = 0; i < 3; i++) {
        ret->vector[i] = sc * q->vector[i];
    }
}

void invert_quaternion(const Quaternion_t* const q, Quaternion_t* ret) {
    Quaternion_t conj;
    get_conj(q, &conj);
    mult_sc_quaternion(1/get_norm2(q), &conj, ret);
}

void get_conj(const Quaternion_t* const q, Quaternion_t* r) {
    r->scalar = q->scalar;
    for (int i = 0; i < 3; i++) {
        r->vector[i] = -q->vector[i];
    }
}

void mult(const Quaternion_t* const q1, const Quaternion_t* const q2, Quaternion_t* ret) {
    ret->scalar = q1->scalar * q2->scalar - scalar_product(q1->vector, q2->vector);

    double m_vector[3];
    vector_product(q1->vector, q2->vector, m_vector);

    double a1v2[3];
    double a2v1[3];
    mult_sc_vec(q1->scalar, q2->vector, a1v2);
    mult_sc_vec(q2->scalar, q1->vector, a2v1);

    for (int i = 0; i < 3; i++) {
        ret->vector[i] = a1v2[i] + a2v1[i] + m_vector[i];
    }
}

void print_quaternion(const Quaternion_t* q) {
    printf("%f + %fi + %fj + %fk\n", q->scalar, q->i, q->j, q->k);
}

void rotate(const double vector[3], const double axis[3], const double angle, double ret[3]) {
    Quaternion_t q;
    q.scalar = cos(angle/2);
    mult_sc_vec(sin(angle/2)/vector_get_norm(axis), axis, q.vector);

    Quaternion_t q_inv;
    invert_quaternion(&q, &q_inv);

    Quaternion_t v_quaternion;
    v_quaternion.scalar = 0;

    for (int i = 0; i < 3; i++) {
        v_quaternion.vector[i] = vector[i];
    }

    Quaternion_t qv, qvq;
    mult(&q, &v_quaternion, &qv);
    mult(&qv, &q_inv, &qvq);

    for (int i = 0; i < 3; i++) {
        ret[i] = qvq.vector[i];
    }
}
