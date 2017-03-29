#ifndef ESPRESSO_GSLWRAPPERS_HH 
#define ESPRESSO_GSLWRAPPERS_HH 1

struct epm_gsl_block {
	size_t size;
	double *data; //[size]
};

struct epm_gsl_vector{
	size_t size;
	size_t stride;
	double *data; //[size]
	epm_gsl_block *block;
	int owner;
};

struct epm_gsl_matrix {
	size_t size1;
	size_t size2;
	size_t tda;
	double *data; //[size1][size2]
	epm_gsl_block *block;
	int owner;
};


#endif // ESPRESSO_GSLWRAPPERS_HH
