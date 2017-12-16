// Need to add use RichDet v* Det to requirements file

// Include
#include "RichDet/Rich1DTabFunc.h"

// Create object
template<>
TabulatedFunction1D* flatter<345831448>() {
TabulatedFunction1D* FlattenLookupTable;

// Initialisation (should do this just once, slow)
double input[300] = {-1, -0.993311, -0.986621, -0.979932, -0.973243, -0.966554, -0.959864, -0.953175, -0.946486, -0.939796, -0.933107, -0.926418, -0.919728, -0.913039, -0.90635, -0.899661, -0.892971, -0.886282, -0.879593, -0.872903, -0.866214, -0.859525, -0.852835, -0.846146, -0.839457, -0.832768, -0.826078, -0.819389, -0.8127, -0.80601, -0.799321, -0.792632, -0.785942, -0.779253, -0.772564, -0.765875, -0.759185, -0.752496, -0.745807, -0.739117, -0.732428, -0.725739, -0.719049, -0.71236, -0.705671, -0.698982, -0.692292, -0.685603, -0.678914, -0.672224, -0.665535, -0.658846, -0.652157, -0.645467, -0.638778, -0.632089, -0.625399, -0.61871, -0.612021, -0.605331, -0.598642, -0.591953, -0.585264, -0.578574, -0.571885, -0.565196, -0.558506, -0.551817, -0.545128, -0.538438, -0.531749, -0.52506, -0.518371, -0.511681, -0.504992, -0.498303, -0.491613, -0.484924, -0.478235, -0.471545, -0.464856, -0.458167, -0.451478, -0.444788, -0.438099, -0.43141, -0.42472, -0.418031, -0.411342, -0.404653, -0.397963, -0.391274, -0.384585, -0.377895, -0.371206, -0.364517, -0.357827, -0.351138, -0.344449, -0.33776, -0.33107, -0.324381, -0.317692, -0.311002, -0.304313, -0.297624, -0.290934, -0.284245, -0.277556, -0.270867, -0.264177, -0.257488, -0.250799, -0.244109, -0.23742, -0.230731, -0.224041, -0.217352, -0.210663, -0.203974, -0.197284, -0.190595, -0.183906, -0.177216, -0.170527, -0.163838, -0.157148, -0.150459, -0.14377, -0.137081, -0.130391, -0.123702, -0.117013, -0.110323, -0.103634, -0.0969448, -0.0902555, -0.0835662, -0.0768769, -0.0701876, -0.0634983, -0.056809, -0.0501197, -0.0434304, -0.0367411, -0.0300518, -0.0233625, -0.0166732, -0.00998395, -0.00329465, 0.00339465, 0.0100839, 0.0167732, 0.0234625, 0.0301518, 0.0368411, 0.0435304, 0.0502197, 0.056909, 0.0635983, 0.0702876, 0.0769769, 0.0836662, 0.0903555, 0.0970448, 0.103734, 0.110423, 0.117113, 0.123802, 0.130491, 0.137181, 0.14387, 0.150559, 0.157248, 0.163938, 0.170627, 0.177316, 0.184006, 0.190695, 0.197384, 0.204074, 0.210763, 0.217452, 0.224141, 0.230831, 0.23752, 0.244209, 0.250899, 0.257588, 0.264277, 0.270967, 0.277656, 0.284345, 0.291034, 0.297724, 0.304413, 0.311102, 0.317792, 0.324481, 0.33117, 0.33786, 0.344549, 0.351238, 0.357927, 0.364617, 0.371306, 0.377995, 0.384685, 0.391374, 0.398063, 0.404753, 0.411442, 0.418131, 0.42482, 0.43151, 0.438199, 0.444888, 0.451578, 0.458267, 0.464956, 0.471645, 0.478335, 0.485024, 0.491713, 0.498403, 0.505092, 0.511781, 0.518471, 0.52516, 0.531849, 0.538538, 0.545228, 0.551917, 0.558606, 0.565296, 0.571985, 0.578674, 0.585364, 0.592053, 0.598742, 0.605431, 0.612121, 0.61881, 0.625499, 0.632189, 0.638878, 0.645567, 0.652257, 0.658946, 0.665635, 0.672324, 0.679014, 0.685703, 0.692392, 0.699082, 0.705771, 0.71246, 0.719149, 0.725839, 0.732528, 0.739217, 0.745907, 0.752596, 0.759285, 0.765975, 0.772664, 0.779353, 0.786042, 0.792732, 0.799421, 0.80611, 0.8128, 0.819489, 0.826178, 0.832868, 0.839557, 0.846246, 0.852935, 0.859625, 0.866314, 0.873003, 0.879693, 0.886382, 0.893071, 0.899761, 0.90645, 0.913139, 0.919828, 0.926518, 0.933207, 0.939896, 0.946586, 0.953275, 0.959964, 0.966654, 0.973343, 0.980032, 0.986721, 0.993411, 1.0001};
double output[300] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.7274e-05, 2.7274e-05, 2.7274e-05, 2.7274e-05, 2.7274e-05, 2.7274e-05, 2.7274e-05, 2.7274e-05, 5.45479e-05, 0.000109096, 0.000109096, 0.000109096, 0.000109096, 0.00013637, 0.00013637, 0.000218192, 0.00027274, 0.000327288, 0.000327288, 0.000381836, 0.00040911, 0.000518205, 0.000545479, 0.000600027, 0.000627301, 0.000763671, 0.000818219, 0.000900041, 0.00106368, 0.00109096, 0.00128188, 0.00144552, 0.00150007, 0.00169099, 0.0018819, 0.00212737, 0.00231829, 0.00267285, 0.00297286, 0.00338197, 0.00373653, 0.0040911, 0.00458203, 0.00496386, 0.00545479, 0.00594572, 0.0064912, 0.00706396, 0.00769126, 0.00864585, 0.0093277, 0.009955, 0.0103914, 0.011346, 0.011946, 0.0126824, 0.0136097, 0.0149734, 0.0162007, 0.017319, 0.0184645, 0.0199373, 0.0214373, 0.0228556, 0.0243557, 0.0265103, 0.0281195, 0.0299468, 0.0316651, 0.0340106, 0.0360562, 0.0383199, 0.0410746, 0.043802, 0.0467203, 0.0494204, 0.0524478, 0.0551752, 0.0586936, 0.0616392, 0.0648029, 0.0685395, 0.0722215, 0.0765035, 0.0805673, 0.0855039, 0.0906314, 0.0948589, 0.100177, 0.104759, 0.10956, 0.114251, 0.119733, 0.125706, 0.13097, 0.136861, 0.142779, 0.148889, 0.154207, 0.160725, 0.166589, 0.172562, 0.178726, 0.184945, 0.191709, 0.1976, 0.204391, 0.211619, 0.217646, 0.224356, 0.231447, 0.237747, 0.244702, 0.251684, 0.259239, 0.266903, 0.273749, 0.280622, 0.287713, 0.294613, 0.30225, 0.309369, 0.317333, 0.32546, 0.333342, 0.341606, 0.34908, 0.357344, 0.364953, 0.372808, 0.380581, 0.389418, 0.397354, 0.405755, 0.415273, 0.423647, 0.432183, 0.441266, 0.450757, 0.460221, 0.46963, 0.478604, 0.487631, 0.49685, 0.505196, 0.515205, 0.525051, 0.535115, 0.544361, 0.553962, 0.564271, 0.574172, 0.584754, 0.594545, 0.605046, 0.614428, 0.623265, 0.632456, 0.642329, 0.651875, 0.661285, 0.67064, 0.680649, 0.689813, 0.698432, 0.707678, 0.717851, 0.726742, 0.735633, 0.746052, 0.756198, 0.76528, 0.774499, 0.783608, 0.7931, 0.802864, 0.813064, 0.822992, 0.831883, 0.84252, 0.851657, 0.862048, 0.871567, 0.881413, 0.890004, 0.900177, 0.908714, 0.91916, 0.928297, 0.935333, 0.944034, 0.952025, 0.95838, 0.964707, 0.971662, 0.976081, 0.983281, 0.986418, 0.987181, 0.992963, 0.996427, 0.997654, 1};
FlattenLookupTable = new TabulatedFunction1D(input, output, 300, gsl_interp_linear);

return FlattenLookupTable;}