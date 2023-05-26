P4_THRIFT_SRC=${SDE}/build/p4-build/main/tofino/main/thrift
STATIC_THRIFT_SRC=${SDE}/pkgsrc/bf-drivers/pdfixed_thrift/thrift/
STATIC_THRIFT_TARGET="thrift/static_thrift_files/"
PLATFORM_THRIFT_SRC=${HOME}/bf-delta-ag9064v1-platforms/thrift/

mkdir -p ${STATIC_THRIFT_TARGET}
cp ${STATIC_THRIFT_SRC}/*.thrift ${STATIC_THRIFT_TARGET}/
cp ${PLATFORM_THRIFT_SRC}/*.thrift ${STATIC_THRIFT_TARGET}/
cp ${P4_THRIFT_SRC}/*.thrift ${STATIC_THRIFT_TARGET}/