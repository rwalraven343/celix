/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

#ifndef CELIX_PHASE3ACTIVATOR_H
#define CELIX_PHASE3ACTIVATOR_H

#include "Phase3BaseActivator.h"

using namespace celix::dm;

class Phase3Activator : public Phase3BaseActivator {
public:
    Phase3Activator(DependencyManager& mng) : Phase3BaseActivator(mng) {}
    virtual void init();
};

#endif //CELIX_PHASE2AACTIVATOR_H
