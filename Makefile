default: example

BUILD_TYPE ?= Release
BUILD_DIR := build/${BUILD_TYPE}
ROOT_DIR := $(shell pwd)

${BUILD_DIR}/Makefile: CMakeLists.txt
	@mkdir -p ${BUILD_DIR}
	@cd ${BUILD_DIR} && cmake ${ROOT_DIR} -DCMAKE_BUILD_TYPE=${BUILD_TYPE}

sdk: ${BUILD_DIR}/Makefile
	@cmake --build ${BUILD_DIR} --target sweep-sdk-cpp

example: sdk
	@cmake --build ${BUILD_DIR} --target sweep-sdk-cpp-example

install: sdk
	@cmake --build ${BUILD_DIR} --target install

clean:
	@${RM} -rf ${BUILD_DIR}

.PHONY: sdk example install clean
