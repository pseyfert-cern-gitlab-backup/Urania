// $Id: $
// Include file

#include "WeightDataSetTool.icpp"
#include "PIDPerfTools/TrackDataSet.h"
#include "PIDPerfTools/EvtTrackDataSet.h"
#include "PIDPerfTools/RICHTrackDataSet.h"
#include "PIDPerfTools/MUONTrackDataSet.h"
#include "PIDPerfTools/PIDTrackDataSet.h"
#include "PIDPerfTools/LHCbPIDTrackDataSet.h"

template class WeightDataSetTool<TrackDataSet>;
template class WeightDataSetTool<EvtTrackDataSet>;
template class WeightDataSetTool<RICHTrackDataSet>;
template class WeightDataSetTool<MUONTrackDataSet>;
template class WeightDataSetTool<PIDTrackDataSet>;
template class WeightDataSetTool<LHCbPIDTrackDataSet>;
