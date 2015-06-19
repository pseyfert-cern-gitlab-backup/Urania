// $Id: $
// Include file

#include "PerfCalculator.icpp"
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/RICHTrackDataSet.h"
#include "PIDPerfTools/MUONTrackDataSet.h"
#include "PIDPerfTools/PIDTrackDataSet.h"
#include "PIDPerfTools/LHCbPIDTrackDataSet.h"
#include "PIDPerfTools/GenericDataSet.h"

template class PerfCalculator<TrackDataSet>;
template class PerfCalculator<EvtTrackDataSet>;
template class PerfCalculator<RICHTrackDataSet>;
template class PerfCalculator<MUONTrackDataSet>;
template class PerfCalculator<PIDTrackDataSet>;
template class PerfCalculator<LHCbPIDTrackDataSet>;
template class PerfCalculator<GenericDataSet>;
