m4_define(BUILD,m4_patsubst(m4_include(`vbuild.m4'),`
',`'))m4_dnl
m4_include(`tools.m4')m4_dnl
m4_define(FROMBIT,m4_ifelse(FARBIT,`64',`$2',`$1'))m4_dnl
m4_define(BUILDTYPE,`')m4_dnl
m4_define(MAJOR,3)m4_dnl
m4_define(MINOR,0)m4_dnl
m4_define(REVISION,0)m4_dnl
m4_define(STAGE,VS_RELEASE)m4_dnl
m4_define(BLD_DATE,m4_esyscmd(CMDAWK -f CMDDATE))m4_dnl
m4_define(BLD_YEAR,m4_substr(BLD_DATE,6,4))m4_dnl
m4_define(BLD_MONTH,m4_substr(BLD_DATE,3,2))m4_dnl
m4_define(BLD_DAY,m4_substr(BLD_DATE,0,2))m4_dnl
m4_define(COPYRIGHTYEAR,BLD_YEAR)m4_dnl
m4_define(MAKEFULLVERSION,`m4_ifelse(
`',$1,`MAJOR.MINOR (build BUILD) $2',
`RC',$1,`MAJOR.MINOR RC (build BUILD) $2',
`alpha',$1,`MAJOR.MINOR alpha (build BUILD) $2',
`beta',$1,`MAJOR.MINOR beta (build BUILD) $2',
`MAJOR.MINOR alpha ($1 based on build BUILD) $2')')m4_dnl
m4_define(FULLVERSION32,MAKEFULLVERSION(BUILDTYPE,`x86'))m4_dnl
m4_define(FULLVERSION64,MAKEFULLVERSION(BUILDTYPE,`x64'))m4_dnl
m4_define(FULLVERSION,FROMBIT(FULLVERSION32,FULLVERSION64))m4_dnl
m4_define(FULLVERSIONNOBRACES,`m4_patsubst(FULLVERSION,`[\(\)]',`')')m4_dnl
