STATIC_THRIFT_TARGET="thrift/static_thrift_files/"

rm -r controller/thrift_api
mkdir -p controller/thrift_api
THRIFT_OPTS="-out controller/thrift_api/ --gen py:package_prefix=controller.thrift_api."
find "${STATIC_THRIFT_TARGET}" -name '*.thrift' -exec thrift ${THRIFT_OPTS} {} \;
