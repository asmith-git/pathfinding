//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
//	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.

#ifndef ASMITH_PATHFINDING_DEPTH_FIRST_HPP
#define ASMITH_PATHFINDING_DEPTH_FIRST_HPP

#include "basic_pathfinder.hpp"
	
namespace asmith { namespace pathfinding {
	
	template<class K, class C = float>
	class depth_first : public basic_pathfinder<K,C> {
	public:

		// Inherited from pathfinder 

		std::vector<key_t> find_path(const map<key_t, C>& aMap, const key_t aBegin, const key_t aEnd) const throw() override {
			mStack.clear();
			mNodes.clear();

			mNodes.emplace(aBegin, node({aBegin, aBegin, false}));
			mStack.push_back(aBegin);
			while(!mStack.empty()) {
				node& n = mNodes.find(mStack.back())->second;
				mStack.pop_back();
				if(n.key == aEnd) return reconstruct_path(aBegin, n);

				if(! n.discovered) {
					n.discovered = true;
					size_t count = 0;
					const connection_t* const connections = aMap.get_connections(n.key, count);
					for(size_t i = 0; i < count; ++i) {
						key_t k = connections[i].first;
						mNodes.emplace(k, node({ k, n.key, false }));
						mStack.push_back(k);
					}
				}
			}
			return std::vector<key_t>();
		}
	};
}}

#endif