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

#include "pathfinder.hpp"
	
namespace asmith { namespace pathfinding {
	
	template<class K, class C = float>
	class depth_first : public pathfinder<K,C> {
	public:
		typedef K key_t;
		typedef C cost_t;
		typedef std::pair<K,C> connection_t;

		// Inherited from pathfinder 

		std::vector<key_t> find_path(const map<key_t, C>& aMap, const key_t aBegin, const key_t aEnd) const throw() override {

			struct node {
				key_t key;
				key_t parent;
				bool discovered;
			};

			std::vector<key_t> s;
			std::map<key_t, node> nodes;

			nodes.emplace(aBegin, node({aBegin, aBegin, false}));
			s.push_back(aBegin);
			while(! s.empty()) {
				const key_t tmp = s.back();
				s.pop_back();
				node& n = nodes.find(tmp)->second;
				if(tmp == aEnd) {
					std::vector<key_t> path;
					node* n2 = &n;
					while(n2->key != aBegin) {
						path.push_back(n2->key);
						n2 = &nodes.find(n2->parent)->second;
					}
					path.push_back(aBegin);
					std::reverse(path.begin(), path.end());
					return path;
				}
				if(! n.discovered) {
					n.discovered = true;
					size_t count = 0;
					const connection_t* const connections = aMap.get_connections(tmp, count);
					for(size_t i = 0; i < count; ++i) {
						key_t k = connections[i].first;
						nodes.emplace(k, node({ k, tmp, false }));
						s.push_back(k);
					}
				}
			}
			return std::vector<key_t>();
		}
	};
}}

#endif