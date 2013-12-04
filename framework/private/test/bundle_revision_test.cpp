/**
 *Licensed to the Apache Software Foundation (ASF) under one
 *or more contributor license agreements.  See the NOTICE file
 *distributed with this work for additional information
 *regarding copyright ownership.  The ASF licenses this file
 *to you under the Apache License, Version 2.0 (the
 *"License"); you may not use this file except in compliance
 *with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *Unless required by applicable law or agreed to in writing,
 *software distributed under the License is distributed on an
 *"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 *specific language governing permissions and limitations
 *under the License.
 */
/*
 * bundle_revision_test.cpp
 *
 *  \date       Feb 11, 2013
 *  \author     <a href="mailto:celix-dev@incubator.apache.org">Apache Celix Project Team</a>
 *  \copyright  Apache License, Version 2.0
 */
#include <stdlib.h>
#include <stdio.h>

#include "CppUTest/TestHarness.h"
#include "CppUTest/TestHarness_c.h"
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTestExt/MockSupport.h"

extern "C" {
#include "bundle_revision_private.h"
}

int main(int argc, char** argv) {
	return RUN_ALL_TESTS(argc, argv);
}

TEST_GROUP(bundle_revision) {
	apr_pool_t *pool;

	void setup(void) {
		apr_initialize();
		apr_pool_create(&pool, NULL);
	}

	void teardown() {
		apr_pool_destroy(pool);
		mock().checkExpectations();
		mock().clear();
	}
};

TEST(bundle_revision, create) {
	char root[] = "bundle_revision_test";
	char location[] = "test_bundle.zip";
	char *inputFile = NULL;
	long revisionNr = 1l;

	mock().expectOneCall("extractBundle")
			.withParameter("bundleName", location)
			.withParameter("revisionRoot", root)
			.andReturnValue(CELIX_SUCCESS);

	bundle_revision_pt revision = NULL;
	celix_status_t status = bundleRevision_create(pool, root, location, revisionNr, inputFile, &revision);
	LONGS_EQUAL(CELIX_SUCCESS, status);
	LONGS_EQUAL(revisionNr, revision->revisionNr);
	STRCMP_EQUAL(root, revision->root);
	STRCMP_EQUAL(location, revision->location);
}

TEST(bundle_revision, createWithInput) {
	char root[] = "bundle_revision_test";
	char location[] = "test_bundle.zip";
	char inputFile[] = "from_somewhere.zip";
	long revisionNr = 1l;

	mock().expectOneCall("extractBundle")
			.withParameter("bundleName", inputFile)
			.withParameter("revisionRoot", root)
			.andReturnValue(CELIX_SUCCESS);

	bundle_revision_pt revision = NULL;
	celix_status_t status = bundleRevision_create(pool, root, location, revisionNr, inputFile, &revision);
	LONGS_EQUAL(CELIX_SUCCESS, status);
	LONGS_EQUAL(revisionNr, revision->revisionNr);
	STRCMP_EQUAL(root, revision->root);
	STRCMP_EQUAL(location, revision->location);
}

TEST(bundle_revision, getNumber) {
	bundle_revision_pt revision = (bundle_revision_pt) apr_palloc(pool, sizeof(*revision));
	char root[] = "bundle_revision_test";
	char location[] = "test_bundle.zip";
	long revisionNr = 1l;
	revision->root = root;
	revision->location = location;
	revision->revisionNr = revisionNr;

	char *actualRoot = NULL;
	char *actualLocation = NULL;
	long actualRevisionNr = 0l;
	celix_status_t status = CELIX_SUCCESS;

	status = bundleRevision_getNumber(revision, &actualRevisionNr);
	LONGS_EQUAL(CELIX_SUCCESS, status);
	LONGS_EQUAL(revisionNr, actualRevisionNr);

	status = bundleRevision_getLocation(revision, &actualLocation);
	LONGS_EQUAL(CELIX_SUCCESS, status);
	STRCMP_EQUAL(location, actualLocation);

	status = bundleRevision_getRoot(revision, &actualRoot);
	LONGS_EQUAL(CELIX_SUCCESS, status);
	STRCMP_EQUAL(root, actualRoot);

	status = bundleRevision_getNumber(NULL, &actualRevisionNr);
	LONGS_EQUAL(CELIX_ILLEGAL_ARGUMENT, status);

	status = bundleRevision_getLocation(NULL, &actualLocation);
	LONGS_EQUAL(CELIX_ILLEGAL_ARGUMENT, status);

	status = bundleRevision_getRoot(NULL, &actualRoot);
	LONGS_EQUAL(CELIX_ILLEGAL_ARGUMENT, status);
}
