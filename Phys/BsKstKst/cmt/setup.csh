# echo "Setting BsKstKst v4r0 in /afs/cern.ch/project/lbcern/vol5/diegoms/URANIA/URANIA/URANIA_HEAD/Phys"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /afs/cern.ch/sw/contrib/CMT/v1r20p20090520
endif
source ${CMTROOT}/mgr/setup.csh

set tempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set tempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=BsKstKst -version=v4r0 -path=/afs/cern.ch/project/lbcern/vol5/diegoms/URANIA/URANIA/URANIA_HEAD/Phys  -no_cleanup $* >${tempfile}; source ${tempfile}
/bin/rm -f ${tempfile}

