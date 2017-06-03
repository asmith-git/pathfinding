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

#ifndef ASMITH_PATHFINDING_MAP_HPP
#define ASMITH_PATHFINDING_MAP_HPP

#include <cstdint>
	
namespace asmith { namespace pathfinding {
	
	
	template<class K = uint64_t, class C = float>
	class map {
	public:
		typedef K key_t;
		typedef C cost_t;
		typedef std::pair<key_t, cost_t> connection_t;
		
		virtual ~map() {
			
		}
		
		virtual const connection_t* get_connections(key_t, size_t&) const throw() = 0;
		
		virtual bool is_connected(key_t aSrc, key_t aDst, cost_t& aCost) const throw() {
			size_t s;
			const connection_t* const connections = get_connections(aSrc, s);
			for(size_t i = 0; i < s; ++i) {
				if(connections[i].first == aDst) {
					aCost = connections[i].second;
					return true;
				}
			}
			return false;
		}
	};
}}

#endif