// $Id: $
// Include file

#include "MultiPerfCalculator.icpp"
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/RICHTrackDataSet.h"
#include "PIDPerfTools/MUONTrackDataSet.h"
#include "PIDPerfTools/PIDTrackDataSet.h"
#include "PIDPerfTools/LHCbPIDTrackDataSet.h"
#include "PIDPerfTools/GenericDataSet.h"

template class MultiPerfCalculator<TrackDataSet>;
template class MultiPerfCalculator<EvtTrackDataSet>;
template class MultiPerfCalculator<RICHTrackDataSet>;
template class MultiPerfCalculator<MUONTrackDataSet>;
template class MultiPerfCalculator<PIDTrackDataSet>;
template class MultiPerfCalculator<LHCbPIDTrackDataSet>;
template class MultiPerfCalculator<GenericDataSet>;
