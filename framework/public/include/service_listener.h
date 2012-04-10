/*
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
/**
 *
 * @defgroup ServiceListener Service Listener
 * @ingroup framework
 * @{
 *
 *  \author    	Alexander Broekhuis
 *  \date      	January 11, 2012
 *  \copyright	Apache License, Version 2.0
 */
#ifndef SERVICE_LISTENER_H_
#define SERVICE_LISTENER_H_

#include <apr_general.h>

typedef struct serviceListener * SERVICE_LISTENER;

#include "celix_errno.h"
#include "service_event.h"

struct serviceListener {
	apr_pool_t *pool;
	void * handle;
	celix_status_t (*serviceChanged)(void * listener, SERVICE_EVENT event);
};



#endif /* SERVICE_LISTENER_H_ */

/**
 * @}
 */