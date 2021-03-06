#-- GAUDI jobOptions generated on Sat Dec  1 09:51:04 2012
#-- Contains event types : 
#--   11144050 - 210 files - 2446491 events - 1119.50 GBytes


#--  Extra information about the data processing phases:

from Gaudi.Configuration import * 
from GaudiConf import IOHelper
IOHelper('ROOT').inputFiles(['LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000001_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000002_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000003_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000004_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000005_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000006_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000007_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000008_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000009_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000010_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000011_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000012_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000013_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000014_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000015_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000016_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000017_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000018_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000019_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000020_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000021_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000022_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000023_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000024_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000025_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000026_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000027_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000028_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000029_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000030_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000031_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000032_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000033_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000034_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000035_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000036_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000037_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000038_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000039_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000040_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000041_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000042_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000043_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000044_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000045_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000046_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000047_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000048_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000049_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000050_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000051_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000052_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000053_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000054_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000055_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000056_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000057_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000058_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000059_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000060_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000061_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000062_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000063_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000064_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000065_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000066_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000067_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000068_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000069_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000070_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000071_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000072_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000073_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000074_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000075_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000076_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000077_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000078_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000079_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000080_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000081_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000082_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000083_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000084_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000085_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000086_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000087_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000088_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000089_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000090_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000091_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000092_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000093_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000094_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000095_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000096_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000097_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000098_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000099_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000100_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000101_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000102_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000103_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000104_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000105_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000106_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000107_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000108_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000109_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000110_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000111_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000112_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000113_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000114_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000115_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000116_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000117_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000118_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000119_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000120_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000121_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000122_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000123_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000124_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000125_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000126_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000127_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000128_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000129_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000130_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000131_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000132_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000133_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000134_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000135_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000136_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000137_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000138_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000139_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000140_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000141_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000142_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000143_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000144_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000145_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000146_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000147_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000148_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000149_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000150_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000151_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000152_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000153_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000154_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000155_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000156_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000157_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000158_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000159_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000160_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000161_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000162_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000163_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000164_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000165_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000166_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000167_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000168_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000169_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000170_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000171_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000172_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000173_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000174_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000175_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000176_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000177_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000178_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000179_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000180_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000181_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000182_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000183_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000184_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000185_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000186_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000187_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000188_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000189_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000190_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000191_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000192_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000193_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000194_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000195_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000196_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000197_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000198_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000199_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000200_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000201_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000202_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000203_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000204_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000205_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000206_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000207_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000208_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000209_1.allstreams.dst',
'LFN:/lhcb/MC/MC11a/ALLSTREAMS.DST/00017392/0000/00017392_00000210_1.allstreams.dst'
], clear=True)
