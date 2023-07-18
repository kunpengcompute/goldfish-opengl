#!/bin/bash
# goldfish opengl build sh
# Copyright © Huawei Technologies Co., Ltd. 2021-2021. All rights reserved.

cur_file_path=$(cd $(dirname "${0}");pwd)
cd "${cur_file_path}"

error()
{
    echo -e  "\033[1;31m${*}\033[0m"
}

info()
{
    echo -e "\033[1;36m${*}\033[0m"
}

android_goldfish_opengl_source_dirs=$(basename ${cur_file_path})

goldfish_opengl_so_list=(
    vendor/lib/hw/gralloc.ranchu.so
    vendor/lib64/hw/gralloc.ranchu.so
    vendor/lib/egl/libEGL_emulation.so
    vendor/lib64/egl/libEGL_emulation.so
    vendor/lib/egl/libGLESv1_CM_emulation.so
    vendor/lib64/egl/libGLESv1_CM_emulation.so
    vendor/lib/egl/libGLESv2_emulation.so
    vendor/lib64/egl/libGLESv2_emulation.so
    vendor/lib/libOpenglSystemCommon.so
    vendor/lib64/libOpenglSystemCommon.so
    vendor/lib/libGLESv1_enc.so
    vendor/lib64/libGLESv1_enc.so
    vendor/lib/libGLESv2_enc.so
    vendor/lib64/libGLESv2_enc.so
    vendor/lib/libRenderControl_enc.so
    vendor/lib64/libRenderControl_enc.so
    vendor/lib/hw/vulkan.radv.so
    vendor/lib64/hw/vulkan.radv.so
    vendor/lib/libvulkan_enc.so
    vendor/lib64/libvulkan_enc.so
    vendor/lib/libandroidemu.so
    vendor/lib64/libandroidemu.so
)

android9_link()
{
    cd ..
    rm -rf ${AN_AOSPDIR}/${android_goldfish_opengl_source_dirs}
    [ ${?} != 0 ] && error "Failed to clean link ${android_goldfish_opengl_source_dirs}" && return -1
    ln -vs ${cur_file_path} ${AN_AOSPDIR}
    [ ${?} != 0 ] && error "Failed to link ${link_dir} to ${AN_AOSPDIR}" && return -1
    cd -
}

setup_env()
{
    export TOP=${AN_AOSPDIR}
    export OUT_DIR=${AN_AOSPDIR}/out
    export ANDROID_BUILD_TOP=${AN_AOSPDIR}
    if [ -z "${ANDROID_VERSION}" ];then
        android9_link
    else
        [ ! -d ${AN_AOSPDIR}/VMIEngine/unpack_open_source ] && mkdir -p ${AN_AOSPDIR}/VMIEngine/unpack_open_source
        rsync -azr --delete --exclude=".git" ${cur_file_path} ${AN_AOSPDIR}/VMIEngine/unpack_open_source
    fi
}

package()
{
    output_dir=${MODULE_OUTPUT_DIR}
    output_symbols_dir=${MODULE_SYMBOL_DIR}
    [ -z "${output_dir}" ] && output_dir=${cur_file_path}/output && rm -rf ${output_dir} && mkdir -p ${output_dir}
    [ -z "${output_symbols_dir}" ] && output_symbols_dir=${cur_file_path}/output/symbols && rm -rf ${output_symbols_dir} && mkdir -p ${output_symbols_dir}
    for so_name in ${goldfish_opengl_so_list[@]}
    do
        source_path=${AN_AOSPDIR}/out/target/product/generic_arm64/${so_name}
        source_symbol_path=${AN_AOSPDIR}/out/target/product/generic_arm64/symbols/${so_name}
        target_path=${output_dir}/${so_name%/*}
        [ ! -d "${target_path}" ] && mkdir -p ${target_path}
        symbol_target_path=${output_symbols_dir}/${so_name%/*}
        [ ! -d "${symbol_target_path}" ] && mkdir -p ${symbol_target_path}
        cp -d ${source_path} ${target_path}
        [ ${?} != 0 ] && error "Failed to copy ${so_name} to ${target_path}"
        [ -L ${source_path} ] && continue
        cp -d ${source_symbol_path} ${symbol_target_path}
        [ ${?} != 0 ] && error "Failed to copy ${so_name} to ${symbol_target_path}"
    done
    cd ${output_dir}/vendor/lib/egl/
    ln -s libEGL_emulation.so libEGL.so
    ln -s libGLESv1_CM_emulation.so libGLESv1_CM.so
    ln -s libGLESv2_emulation.so libGLESv2.so
    cd -
    if [ -z "${MODULE_OUTPUT_DIR}" ];then
        cd output
        tar zcvf GoldfishOpengl.tar.gz system vendor
        cd -
    fi
    if [ -z "${MODULE_SYMBOL_DIR}" ];then
        cd output/symbols
        tar zcvf ../GoldfishOpengl.tar.gz *
        cd -
    fi
}

clean()
{
    rm -rf output
}

inc()
{
    clean
    setup_env
    [ ${?} != 0 ] && error "Failed to setup env" && return -1
    cd ${AN_AOSPDIR}
    source build/envsetup.sh
    lunch aosp_arm64-eng
    if [ ! -z "${ANDROID_VERSION}" ];then
        cd VMIEngine/unpack_open_source
    fi
    mmm ${android_goldfish_opengl_source_dirs} -j
    [ ${?} != 0 ] && error "Failed to incremental compile ${android_mesa_source_dirs}" && return -1
    cd -
    package
}

build()
{
    inc
}

ACTION=$1; shift
case "$ACTION" in
    build) build "$@";;
    clean) clean "$@";;
	inc) inc "$@";;
    *) error "input command[$ACTION] not support.";;
esac
