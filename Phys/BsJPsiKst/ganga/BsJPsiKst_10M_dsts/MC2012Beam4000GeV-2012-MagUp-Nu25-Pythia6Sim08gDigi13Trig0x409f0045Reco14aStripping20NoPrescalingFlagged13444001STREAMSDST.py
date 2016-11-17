#-- GAUDI jobOptions generated on Wed Mar  4 16:05:01 2015
#-- Contains event types : 
#--   13444001 - 110 files - 2452928 events - 663.99 GBytes


#--  Extra information about the data processing phases:

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000001_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000002_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000003_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000004_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000005_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000006_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000007_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000008_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000009_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000010_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000011_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000012_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000013_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000014_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000015_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000016_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000017_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000018_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000019_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000020_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000021_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000022_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000023_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000024_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000025_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000026_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000027_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000028_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000029_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000030_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000031_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000032_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000033_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000034_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000035_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000036_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000037_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000038_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000039_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000040_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000041_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000042_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000043_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000044_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000045_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000046_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000047_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000048_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000049_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000050_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000051_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000052_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000053_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000054_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000055_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000056_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000057_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000058_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000059_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000060_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000061_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000062_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000063_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000064_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000065_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000066_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000067_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000068_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000069_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000070_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000071_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000072_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000073_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000075_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000076_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000077_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000078_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000079_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000080_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000081_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000082_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000083_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000084_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000085_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000086_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000087_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000088_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000089_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000090_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000091_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000092_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000093_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000094_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000095_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000096_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000097_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000099_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000100_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000101_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000102_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000103_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000104_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000105_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000106_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000107_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000108_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000109_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000110_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000111_2.AllStreams.dst',
'LFN:/lhcb/MC/2012/ALLSTREAMS.DST/00042492/0000/00042492_00000112_2.AllStreams.dst'
], clear=True)