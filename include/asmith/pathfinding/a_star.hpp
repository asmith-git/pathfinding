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

#ifndef ASMITH_PATHFINDING_A_STAR_HPP
#define ASMITH_PATHFINDING_A_STAR_HPP

#include "basic_pathfinder.hpp"
	
namespace asmith { namespace pathfinding {

	template<class K>
	struct a_star_node {
		K key;
		K parent;
		float g;
		float f;
		bool closed;
	};
	
	template<class K, class C = float>
	class a_star : public basic_pathfinder<K,C, a_star_node<K>> {
	private:
		float(*mHeuristic)(K, K);
		float(*mDistance)(K, K);
	public:
		a_star(float(*aHeuristic)(K, K), float(*aDistance)(K, K)) :
			mHeuristic(aHeuristic),
			mDistance(aDistance)
		{}

		// Inherited from pathfinder 

		std::vector<key_t> find_path(const map<key_t, C>& aMap, const key_t aBegin, const key_t aEnd) const throw() override {
			mStack.clear(); // Open set
			mNodes.clear(); // Closed set

			mNodes.emplace(aBegin, node({ aBegin, aBegin, 0.f, mHeuristic(aBegin, aEnd), false}));
			mStack.push_back(aBegin);

			while(! mStack.empty()) {
				node* n = &mNodes.find(mStack.front())->second;
				size_t index= 0;
				const size_t s = mStack.size();
				for(size_t i = 1; i < s; ++i) {
					node* const tmp = &mNodes.find(mStack[i])->second;
					if(tmp->f < n->f) {
						n = tmp;
						index = i;
					}
				}
				if(n->key == aEnd) return reconstruct_path(aBegin, *n);
				mStack.erase(mStack.begin() + index);
				n->closed = true;

				size_t count = 0;
				const connection_t* const connections = aMap.get_connections(n->key, count);
				for(size_t i = 0; i < count; ++i) {
					const key_t k = connections[i].first;

					const auto j = mNodes.find(k);
					node& n2 = j == mNodes.end() ?
						mNodes.emplace(k, node({ k, n->key, FLT_MAX, FLT_MAX, false })).first->second :
						j->second;

					if(n2.closed) continue;
					if(std::find(mStack.begin(), mStack.end(), k) == mStack.end()) mStack.push_back(k);

					const float g = n->g + mDistance(n->key, n2.key);
					if(g >= n2.g) continue;
					n2.parent = n->key;
					n2.g = g;
					n2.f = g + mHeuristic(n2.key, aEnd);
				}
			}
			return std::vector<key_t>();
		}
	};
}}

#endif