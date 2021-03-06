# Licensed to the Apache Software Foundation (ASF) under one
# or more contributor license agreements.  See the NOTICE file
# distributed with this work for additional information
# regarding copyright ownership.  The ASF licenses this file
# to you under the Apache License, Version 2.0 (the
# "License"); you may not use this file except in compliance
# with the License.  You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, either express or implied.  See the License for the
# specific language governing permissions and limitations
# under the License.


if (NOT PROJECT_SOURCE_DIR) 
    #If PROJECT_SOURCE_DIR is not defined, this CMakeLists will
    #act as a top level project. Making the etcdlib useable 
    #stand-alone

    cmake_minimum_required (VERSION 3.2)
    project(ETCDLIB 
        VERSION 1.0.0
        LANGUAGES C CXX
    )

    include(GNUInstallDirs)

    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
    set(CMAKE_C_FLAGS "-D_GNU_SOURCE -std=gnu99 ${CMAKE_C_FLAGS}")
    set(CMAKE_C_FLAGS_DEBUG "-g -DDEBUG")

    set(ETCDLIB_CMP ${CMAKE_INSTALL_DEFAULT_COMPONENT_NAME})
else()
    set(ETCDLIB_CMP framework)
endif ()

find_package(CURL REQUIRED)
find_package(Jansson REQUIRED)

include_directories(
        ${CURL_INCLUDE_DIRS}
        ${JANSSON_INCLUDE_DIRS}
        private/include
        public/include
)

add_library(etcdlib SHARED
    private/src/etcd.c
)

set_target_properties(etcdlib PROPERTIES SOVERSION 1)
set_target_properties(etcdlib PROPERTIES VERSION 1.0.0)
target_link_libraries(etcdlib ${CURL_LIBRARIES} ${JANSSON_LIBRARIES})

add_library(etcdlib_static STATIC
    private/src/etcd.c
)

set_target_properties(etcdlib_static PROPERTIES "SOVERSION" 1)
target_link_libraries(etcdlib_static ${CURL_LIBRARIES} ${JANSSON_LIBRARY})


install(TARGETS etcdlib etcdlib_static DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT ${ETCDLIB_CMP})
FILE(GLOB files "public/include/*.h")
INSTALL(FILES ${files} DESTINATION include/etcdlib COMPONENT framework)
