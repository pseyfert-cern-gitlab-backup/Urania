if test "${CMTROOT}" = ""; then
  CMTROOT=/afs/cern.ch/sw/contrib/CMT/v1r20p20090520; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then tempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=BsKstKst -version=v4r0 -path=/afs/cern.ch/project/lbcern/vol5/diegoms/URANIA/URANIA/URANIA_HEAD/Phys $* >${tempfile}; . ${tempfile}
/bin/rm -f ${tempfile}

