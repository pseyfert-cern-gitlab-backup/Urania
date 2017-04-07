#ifndef ESPRESSO_GSLWRAPPERS_HH 
#define ESPRESSO_GSLWRAPPERS_HH 1

#include <cstdint>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>

struct espresso_block {
  size_t size;
  double* data;
};

struct espresso_vector_io {
  uint32_t reflex_size;
};

struct espresso_vector_substruct {
  size_t size;
};

struct espresso_vector : public espresso_vector_io, espresso_vector_substruct {
  size_t stride;
  double* data; //[reflex_size]
  espresso_block* block;
  int owner;
};

struct espresso_matrix_io {
  uint32_t reflex_size;
};

struct espresso_matrix_substruct {
	size_t size1;
	size_t size2;
};

struct espresso_matrix : public espresso_matrix_io, espresso_matrix_substruct {
	size_t tda;
	double *data; //[reflex_size]
	espresso_block* block;
	int owner;
};

espresso_block* espresso_block_alloc (const size_t n);
espresso_block* espresso_block_calloc (const size_t n);
void espresso_block_free (espresso_block* b);

espresso_vector* espresso_vector_alloc (const size_t n);
espresso_vector* espresso_vector_calloc (const size_t n);
void espresso_vector_free (espresso_vector* b);

espresso_matrix* espresso_matrix_alloc (const size_t n1, const size_t n2);
espresso_matrix* espresso_matrix_calloc (const size_t n1, const size_t n2);
void espresso_matrix_free (espresso_matrix* m);

inline gsl_vector* GSL(espresso_vector* ev) {
  auto gv = reinterpret_cast<gsl_vector*>(static_cast<espresso_vector_substruct*>(ev));
  return gv;
}

inline espresso_vector* DeGSL(gsl_vector* gv) {
  auto ev = static_cast<espresso_vector*>(reinterpret_cast<espresso_vector_substruct*>(gv));
  return ev;
}

inline gsl_matrix* GSL(espresso_matrix* ev) {
  auto gv = reinterpret_cast<gsl_matrix*>(static_cast<espresso_matrix_substruct*>(ev));
  return gv;
}

inline espresso_matrix* DeGSL(gsl_matrix* gv) {
  auto ev = static_cast<espresso_matrix*>(reinterpret_cast<espresso_matrix_substruct*>(gv));
  return ev;
}

inline gsl_block* GSL(espresso_block* v) {
  return reinterpret_cast<gsl_block*>(v);
}

inline espresso_block* DeGSL(gsl_block* v) {
  return reinterpret_cast<espresso_block*>(v);
}

#endif // ESPRESSO_GSLWRAPPERS_HH
