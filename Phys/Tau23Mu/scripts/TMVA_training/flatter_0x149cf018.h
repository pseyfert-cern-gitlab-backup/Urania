// Need to add use RichDet v* Det to requirements file

// Include
#include "RichDet/Rich1DTabFunc.h"

// Create object
template<>
TabulatedFunction1D* flatter<345829400>() {
TabulatedFunction1D* FlattenLookupTable;

// Initialisation (should do this just once, slow)
double input[300] = {-1, -0.993311, -0.986621, -0.979932, -0.973243, -0.966554, -0.959864, -0.953175, -0.946486, -0.939796, -0.933107, -0.926418, -0.919728, -0.913039, -0.90635, -0.899661, -0.892971, -0.886282, -0.879593, -0.872903, -0.866214, -0.859525, -0.852835, -0.846146, -0.839457, -0.832768, -0.826078, -0.819389, -0.8127, -0.80601, -0.799321, -0.792632, -0.785942, -0.779253, -0.772564, -0.765875, -0.759185, -0.752496, -0.745807, -0.739117, -0.732428, -0.725739, -0.719049, -0.71236, -0.705671, -0.698982, -0.692292, -0.685603, -0.678914, -0.672224, -0.665535, -0.658846, -0.652157, -0.645467, -0.638778, -0.632089, -0.625399, -0.61871, -0.612021, -0.605331, -0.598642, -0.591953, -0.585264, -0.578574, -0.571885, -0.565196, -0.558506, -0.551817, -0.545128, -0.538438, -0.531749, -0.52506, -0.518371, -0.511681, -0.504992, -0.498303, -0.491613, -0.484924, -0.478235, -0.471545, -0.464856, -0.458167, -0.451478, -0.444788, -0.438099, -0.43141, -0.42472, -0.418031, -0.411342, -0.404653, -0.397963, -0.391274, -0.384585, -0.377895, -0.371206, -0.364517, -0.357827, -0.351138, -0.344449, -0.33776, -0.33107, -0.324381, -0.317692, -0.311002, -0.304313, -0.297624, -0.290934, -0.284245, -0.277556, -0.270867, -0.264177, -0.257488, -0.250799, -0.244109, -0.23742, -0.230731, -0.224041, -0.217352, -0.210663, -0.203974, -0.197284, -0.190595, -0.183906, -0.177216, -0.170527, -0.163838, -0.157148, -0.150459, -0.14377, -0.137081, -0.130391, -0.123702, -0.117013, -0.110323, -0.103634, -0.0969448, -0.0902555, -0.0835662, -0.0768769, -0.0701876, -0.0634983, -0.056809, -0.0501197, -0.0434304, -0.0367411, -0.0300518, -0.0233625, -0.0166732, -0.00998395, -0.00329465, 0.00339465, 0.0100839, 0.0167732, 0.0234625, 0.0301518, 0.0368411, 0.0435304, 0.0502197, 0.056909, 0.0635983, 0.0702876, 0.0769769, 0.0836662, 0.0903555, 0.0970448, 0.103734, 0.110423, 0.117113, 0.123802, 0.130491, 0.137181, 0.14387, 0.150559, 0.157248, 0.163938, 0.170627, 0.177316, 0.184006, 0.190695, 0.197384, 0.204074, 0.210763, 0.217452, 0.224141, 0.230831, 0.23752, 0.244209, 0.250899, 0.257588, 0.264277, 0.270967, 0.277656, 0.284345, 0.291034, 0.297724, 0.304413, 0.311102, 0.317792, 0.324481, 0.33117, 0.33786, 0.344549, 0.351238, 0.357927, 0.364617, 0.371306, 0.377995, 0.384685, 0.391374, 0.398063, 0.404753, 0.411442, 0.418131, 0.42482, 0.43151, 0.438199, 0.444888, 0.451578, 0.458267, 0.464956, 0.471645, 0.478335, 0.485024, 0.491713, 0.498403, 0.505092, 0.511781, 0.518471, 0.52516, 0.531849, 0.538538, 0.545228, 0.551917, 0.558606, 0.565296, 0.571985, 0.578674, 0.585364, 0.592053, 0.598742, 0.605431, 0.612121, 0.61881, 0.625499, 0.632189, 0.638878, 0.645567, 0.652257, 0.658946, 0.665635, 0.672324, 0.679014, 0.685703, 0.692392, 0.699082, 0.705771, 0.71246, 0.719149, 0.725839, 0.732528, 0.739217, 0.745907, 0.752596, 0.759285, 0.765975, 0.772664, 0.779353, 0.786042, 0.792732, 0.799421, 0.80611, 0.8128, 0.819489, 0.826178, 0.832868, 0.839557, 0.846246, 0.852935, 0.859625, 0.866314, 0.873003, 0.879693, 0.886382, 0.893071, 0.899761, 0.90645, 0.913139, 0.919828, 0.926518, 0.933207, 0.939896, 0.946586, 0.953275, 0.959964, 0.966654, 0.973343, 0.980032, 0.986721, 0.993411, 1.0001};
double output[300] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 2.72695e-05, 5.4539e-05, 8.18085e-05, 0.000136348, 0.000245426, 0.000245426, 0.000327234, 0.000354504, 0.000381773, 0.000463582, 0.00054539, 0.000681738, 0.000790816, 0.000927163, 0.00103624, 0.00111805, 0.00130894, 0.00155436, 0.00166344, 0.00179979, 0.00209975, 0.00248152, 0.00289057, 0.00329961, 0.00373592, 0.0041995, 0.00458128, 0.00520848, 0.00586294, 0.00640833, 0.00722642, 0.00801723, 0.00869897, 0.00943525, 0.0103079, 0.0110714, 0.0119168, 0.0129257, 0.0139074, 0.0151073, 0.0162254, 0.0173434, 0.0186251, 0.0201249, 0.0220883, 0.0235609, 0.0256606, 0.027624, 0.0298874, 0.0316326, 0.0334051, 0.0353958, 0.0377137, 0.0400044, 0.043004, 0.0455401, 0.0483216, 0.050994, 0.0533937, 0.0565024, 0.0594475, 0.0630471, 0.0670012, 0.0703008, 0.0745276, 0.0785089, 0.0827357, 0.0871533, 0.0923891, 0.0974339, 0.102751, 0.107769, 0.113305, 0.118786, 0.12454, 0.130403, 0.135693, 0.141583, 0.148455, 0.1544, 0.160481, 0.166671, 0.17387, 0.180497, 0.187232, 0.192986, 0.200076, 0.20673, 0.214011, 0.221292, 0.227673, 0.235445, 0.242317, 0.250389, 0.258324, 0.265632, 0.273295, 0.281258, 0.289002, 0.29751, 0.305391, 0.313954, 0.321753, 0.328679, 0.336724, 0.344823, 0.352622, 0.361048, 0.369447, 0.377165, 0.385127, 0.393172, 0.401162, 0.408797, 0.416814, 0.425132, 0.433367, 0.441739, 0.449538, 0.458373, 0.466718, 0.475144, 0.482943, 0.491342, 0.499686, 0.507785, 0.51643, 0.524229, 0.533664, 0.541981, 0.551062, 0.560961, 0.570342, 0.580268, 0.589321, 0.599438, 0.609637, 0.620436, 0.630689, 0.641079, 0.650623, 0.660904, 0.671812, 0.682528, 0.693, 0.704617, 0.715497, 0.725778, 0.737586, 0.75013, 0.762346, 0.775163, 0.786643, 0.798724, 0.811322, 0.824439, 0.837201, 0.849145, 0.860953, 0.873715, 0.885741, 0.897167, 0.908402, 0.919664, 0.930681, 0.939625, 0.948788, 0.957105, 0.964004, 0.971067, 0.978266, 0.982738, 0.987292, 0.991901, 0.993919, 0.995419, 0.997846, 0.998637, 0.999155, 0.999755, 0.999918, 1};
FlattenLookupTable = new TabulatedFunction1D(input, output, 300, gsl_interp_linear);

return FlattenLookupTable;}
