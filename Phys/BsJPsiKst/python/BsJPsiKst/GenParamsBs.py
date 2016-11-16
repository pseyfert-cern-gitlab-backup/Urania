from SomeUtils.alyabar import TranslateHelicity
Hp = 0.685
Hz = 0.714
Hm = 0.143
pHp = 3.14
pHz = 0.0
pHm = -0.72

MCA02, MCApa2, MCdpa, MCdpe = TranslateHelicity(Hp, Hz, Hm, pHp, pHz, pHm)
MCApe2 = 1- MCApa2 - MCA02
