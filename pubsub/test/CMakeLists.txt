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

find_program(ETCD_CMD NAMES etcd)

find_package(CppUTest REQUIRED)
include_directories(${CPPUTEST_INCLUDE_DIR})

include_directories(
        ${CMAKE_SOURCE_DIR}/pubsub/api
        test
)

add_celix_bundle(pubsub_sut
    #"Vanilla" bundle which is under test
    SOURCES
        test/sut_activator.c
    VERSION 1.0.0
)
target_link_libraries(pubsub_sut celix_framework celix_utils)
celix_bundle_files(pubsub_sut
    msg_descriptors/msg.descriptor
    msg_descriptors/sync.descriptor
    DESTINATION "META-INF/descriptors/messages"
)
add_celix_container(pubsub_udpmc_sut
    NAME deploy_sut
    BUNDLES
        org.apache.celix.pubsub_serializer.PubSubSerializerJson
        org.apache.celix.pubsub_discovery.etcd.PubsubDiscovery
        org.apache.celix.pubsub_admin.PubSubAdminUdpMc
        org.apache.celix.pubsub_topology_manager.PubSubTopologyManager
        pubsub_sut
    DIR ${PROJECT_BINARY_DIR}/runtimes/test/pubsub/udpmc
)
add_celix_container(pubsub_zmq_sut
    NAME deploy_sut
    BUNDLES
        org.apache.celix.pubsub_serializer.PubSubSerializerJson
        org.apache.celix.pubsub_discovery.etcd.PubsubDiscovery
        org.apache.celix.pubsub_admin.PubSubAdminZmq
        org.apache.celix.pubsub_topology_manager.PubSubTopologyManager
        pubsub_sut
    DIR ${PROJECT_BINARY_DIR}/runtimes/test/pubsub/zmq
)

add_celix_bundle(pubsub_tst
    #Test bundle containing cpputests and uses celix_test_runner launcher instead of the celix launcher
    SOURCES
        test/tst_activator.cpp
    VERSION 1.0.0
)
if (APPLE)
    #Note that the launcher celix_test_runner is linked with CppuTest, not the bundle libs. Default libCppUTest.a is not compiled for relocation 
    target_link_libraries(pubsub_tst celix_framework celix_utils -Wl,-undefined -Wl,dynamic_lookup)
else ()
    target_link_libraries(pubsub_tst celix_framework celix_utils)
endif ()

celix_bundle_files(pubsub_tst
    msg_descriptors/msg.descriptor
    msg_descriptors/sync.descriptor
    DESTINATION "META-INF/descriptors/messages"
)
add_celix_container(pubsub_udpmc_tst
    NAME deploy_tst
    BUNDLES
        org.apache.celix.pubsub_serializer.PubSubSerializerJson
        org.apache.celix.pubsub_topology_manager.PubSubTopologyManager
        org.apache.celix.pubsub_discovery.etcd.PubsubDiscovery
        org.apache.celix.pubsub_admin.PubSubAdminUdpMc
        pubsub_tst
    #NOTE using $<TARGET_PROPERTY:pubsub_test_udpmc_runtime,RUNTIME_DIR> in DIR not (yet) possible
    DIR ${PROJECT_BINARY_DIR}/runtimes/test/pubsub/udpmc
    LAUNCHER celix_test_runner
)
add_celix_container(pubsub_zmq_tst
    NAME deploy_tst
    BUNDLES
        org.apache.celix.pubsub_serializer.PubSubSerializerJson
        org.apache.celix.pubsub_topology_manager.PubSubTopologyManager
        org.apache.celix.pubsub_discovery.etcd.PubsubDiscovery
        org.apache.celix.pubsub_admin.PubSubAdminZmq
        pubsub_tst
    DIR ${PROJECT_BINARY_DIR}/runtimes/test/pubsub/zmq
    LAUNCHER celix_test_runner
)

if (ETCD_CMD)
    add_runtime(pubsub_test_udpmc_runtime
        NAME udpmc
        GROUP test/pubsub
        DEPLOYMENTS
            pubsub_udpmc_sut
            pubsub_udpmc_tst
        COMMANDS
            etcd
        WAIT_FOR
            pubsub_udpmc_tst
        LOG_TO_FILES
        #USE_TERM
    )
    add_test(NAME pubsub_udpmc_test
	    COMMAND $<TARGET_PROPERTY:pubsub_test_udpmc_runtime,RUNTIME_LOC>/start.sh
    )

    add_runtime(pubsub_test_zmq_runtime
        NAME zmq
        GROUP test/pubsub
        DEPLOYMENTS
            pubsub_zmq_sut
            pubsub_zmq_tst
        COMMANDS
            etcd
        ARGUMENTS
            pubsub_zmq_tst "-o junit"
        WAIT_FOR
            pubsub_zmq_tst
        LOG_TO_FILES
        #USE_TERM
    )
    add_test(NAME pubsub_zmq_test
	    COMMAND $<TARGET_PROPERTY:pubsub_test_zmq_runtime,RUNTIME_LOC>/start.sh
    )
endif ()
