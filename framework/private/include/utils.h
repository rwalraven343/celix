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
 * utils.h
 *
 *  Created on: Jul 27, 2010
 *      Author: alexanderb
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <ctype.h>

unsigned int string_hash(void * string);
int string_equals(void * string, void * toCompare);
char * string_ndup(const char *s, size_t n);
char * string_trim(char * string);

#endif /* UTILS_H_ */