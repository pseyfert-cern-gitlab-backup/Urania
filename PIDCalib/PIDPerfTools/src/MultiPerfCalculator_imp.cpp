// $Id: $
// Include file

#include "MultiPerfCalculator.icpp"
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/RICHTrackDataSet.h"
#include "PIDPerfTools/MUONTrackDataSet.h"

template class MultiPerfCalculator<TrackDataSet>;
template class MultiPerfCalculator<EvtTrackDataSet>;
template class MultiPerfCalculator<RICHTrackDataSet>;
template class MultiPerfCalculator<MUONTrackDataSet>;
