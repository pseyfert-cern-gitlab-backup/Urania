#include "GSLWrappers.hh"

#include <iostream>

#include <cstdlib>
#include <cstring>

#include <gsl/gsl_errno.h>
#define ATOMIC double
#define MULTIPLICITY 1
#define RETURN_IF_NULL(x) if (!x) { return ; }

espresso_block* espresso_block_alloc (const size_t n) {
  espresso_block* b;

  if (n == 0) {
    GSL_ERROR_VAL ("block length n must be positive integer",
		   GSL_EINVAL, 0);
  }

  b = (espresso_block*) std::malloc (sizeof (espresso_block));

  if (b == 0) {
    GSL_ERROR_VAL ("failed to allocate space for block struct",
		   GSL_ENOMEM, 0);
  }

  b->data = (ATOMIC *) std::malloc (MULTIPLICITY * n * sizeof (ATOMIC));

  if (b->data == 0)
    {
      free (b);         /* exception in constructor, avoid memory leak */

      GSL_ERROR_VAL ("failed to allocate space for block data",
		     GSL_ENOMEM, 0);
    }

  b->size = n;

  return b;
}

espresso_block* espresso_block_calloc(const size_t n) {
  size_t i;

  espresso_block* b = espresso_block_alloc(n);

  if (b == 0)
    return 0;

  /* initialize block to zero; the memset call takes care of padding bytes */
  std::memset(b->data, 0, MULTIPLICITY * n * sizeof(ATOMIC));

  for (i = 0; i < MULTIPLICITY * n; i++) {
    b->data[i] = 0;
  }

  return b;
}

void espresso_block_free(espresso_block* b) {
  RETURN_IF_NULL (b);
  // std::cout << b->size << std::endl;
  // std::cout << (void*)b->data << std::endl;
  free (b->data);
  // std::cout << "Freed b->data" << std::endl;
  free (b);
  // std::cout << "Freed b" << std::endl;
}

espresso_vector* espresso_vector_alloc (const size_t n) {
  espresso_block* block;
  espresso_vector* v;

  if (n == 0) {
    GSL_ERROR_VAL ("vector length n must be positive integer",
		   GSL_EINVAL, 0);
  }

  v = (espresso_vector*) std::malloc (sizeof (espresso_vector));

  if (v == 0) {
    GSL_ERROR_VAL ("failed to allocate space for vector struct",
		   GSL_ENOMEM, 0);
  }

  block = espresso_block_alloc (n);

  if (block == 0) {
    free (v) ;

    GSL_ERROR_VAL ("failed to allocate space for block",
		   GSL_ENOMEM, 0);
  }
      
  v->data = block->data;
  v->size = n;
  v->stride = 1;
  v->block = block;
  v->owner = 1;
  v->reflex_size = static_cast<uint32_t>(n);

  return v;
}

espresso_vector* espresso_vector_calloc (const size_t n) {
  size_t i;

  espresso_vector* v = espresso_vector_alloc(n);

  if (v == 0)
    return 0;

  /* initialize vector to zero; memset takes care of the padding bytes */
  std::memset(v->data, 0, MULTIPLICITY * n * sizeof(ATOMIC));

  for (i = 0; i < MULTIPLICITY * n; i++) {
    v->data[i] = 0;
  }

  return v;
}

void espresso_vector_free(espresso_vector* v) {
  RETURN_IF_NULL (v);
  
  // std::cout << "SIZE = " << v->reflex_size << " = " << v->size << std::endl;
  // std::cout << (void*)v->data << std::endl;
  // std::cout << (void*)v->block << std::endl;
  // std::cout << v->block->size << std::endl;
  // std::cout << (void*)v->block->data << std::endl;
  // for (size_t k = 0; k < v->size; ++k)
  //   std::cout << v->data[k] << ", ";
  // std::cout << std::endl;

  if (v->owner) {
    espresso_block_free(v->block) ;
  }
  free (v);
}

espresso_matrix* espresso_matrix_alloc(const size_t n1, const size_t n2) {
  espresso_block* block;
  espresso_matrix* m;

  if (n1 == 0) {
    GSL_ERROR_VAL ("matrix dimension n1 must be positive integer",
		   GSL_EINVAL, 0);
  } else if (n2 == 0) {
    GSL_ERROR_VAL ("matrix dimension n2 must be positive integer",
		   GSL_EINVAL, 0);
  }

  m = (espresso_matrix*) std::malloc (sizeof (espresso_matrix));

  if (m == 0) {
    GSL_ERROR_VAL ("failed to allocate space for matrix struct",
		   GSL_ENOMEM, 0);
  }

  /* FIXME: n1*n2 could overflow for large dimensions */

  block = espresso_block_alloc(n1 * n2) ;

  if (block == 0) {
    GSL_ERROR_VAL ("failed to allocate space for block",
		   GSL_ENOMEM, 0);
  }

  m->data = block->data;
  m->size1 = n1;
  m->size2 = n2;
  m->tda = n2; 
  m->block = block;
  m->owner = 1;
  m->reflex_size = static_cast<uint32_t>(n1 * n2);

  return m;
}

espresso_matrix* espresso_matrix_calloc(const size_t n1, const size_t n2) {
  size_t i;

  espresso_matrix* m = espresso_matrix_alloc(n1, n2);

  if (m == 0)
    return 0;

  /* initialize matrix to zero */
  std::memset(m->data, 0, MULTIPLICITY * n1 * n2 * sizeof(ATOMIC));

  for (i = 0; i < MULTIPLICITY * n1 * n2; i++) {
    m->data[i] = 0;
  }

  return m;
}

void espresso_matrix_free(espresso_matrix* m) {
  RETURN_IF_NULL (m);

  // std::cout << "SIZE = " << m->reflex_size << " = " << m->size1 << "x" << m->size2 << std::endl;
  // std::cout << (void*)m->data << std::endl;
  // std::cout << (void*)m->block << std::endl;
  // std::cout << m->block->size << std::endl;
  // std::cout << (void*)m->block->data << std::endl;
  // for (size_t k = 0; k < m->reflex_size; ++k)
  //   std::cout << m->data[k] << ", ";
  // std::cout << std::endl;

  if (m->owner) {
    espresso_block_free(m->block);
  }

  free (m);
}

