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

#ifndef ASMITH_PATHFINDING_PATHFINDER_HPP
#define ASMITH_PATHFINDING_PATHFINDER_HPP

#include <vector>
#include "map.hpp"
	
namespace asmith { namespace pathfinding {
	
	template<class K, class C>
	class pathfinder {
	public:
		typedef K key_t;
		typedef C cost_t;
		typedef std::pair<K,C> connection_t;

		virtual std::vector<key_t> find_path(const map<key_t, C>&, const key_t, const key_t) const throw() = 0;
	};
}}

#endif