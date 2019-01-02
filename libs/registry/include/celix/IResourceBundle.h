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

#ifndef CXX_CELIX_IRESOURCEBUNDLE_H
#define CXX_CELIX_IRESOURCEBUNDLE_H

namespace celix {

    class IResourceBundle {
    public:
        virtual ~IResourceBundle() = default;

        virtual long id() const noexcept  = 0;

        virtual const std::string& root() const noexcept = 0;

        virtual bool has(const std::string &path) const noexcept = 0;
        virtual bool isDir(const std::string &path) const noexcept = 0;
        virtual bool isFile(const std::string &path) const noexcept = 0;

        //virtual bool storeResource(const std::string &path, std::ostream content) noexcept = 0;
        //virtual std::istream open(const std::string &path) const noexcept = 0;
        //virtual std::fstream open(const std::string &path) noexcept = 0;
        virtual std::vector<std::string> readDir(const std::string &path) const noexcept = 0;
    };


    /*
     * void read_directory(const std::string& name, stringvec& v)
{
    DIR* dirp = opendir(name.c_str());
    struct dirent * dp;
    while ((dp = readdir(dirp)) != NULL) {
        v.push_back(dp->d_name);
    }
    closedir(dirp);
}
     */
}

#endif //CXX_CELIX_IRESOURCEBUNDLE_H