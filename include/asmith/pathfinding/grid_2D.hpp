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

#ifndef ASMITH_PATHFINDING_GRID_2D_HPP
#define ASMITH_PATHFINDING_GRID_2D_HPP

#include "map.hpp"
	
namespace asmith { namespace pathfinding {
	
	
	template<class K = uint64_t, class C = float, bool DIAGONALS = true>
	class grid_2D : public map<std::pair<K,K>, C> {
	private:
		enum {
			CONNECTION_COUNT = DIAGONALS ? 8 : 4
		};
		mutable connection_t mConnections[CONNECTION_COUNT];
	protected:
		virtual bool is_walkable(K, K) const throw() = 0;
		
		virtual cost_t get_cardinal_cost() const throw() {
			return 1;
		}
		
		virtual cost_t get_diagonal_cost() const throw() {
			return 1.4;
		}
	public:
		virtual ~grid_2D() {
			
		}
		
		// Inherited from map
		
		virtual const connection_t* get_connections(key_t aSrc, size_t& aCount) const throw() override {
			uint8_t count = 0;
			connection_t connection;
			
			connection.second = get_cardinal_cost();
			
			// Left
			connection.first.first = aSrc.first - 1;
			connection.first.second = aSrc.second;
			if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
			
			// Right
			connection.first.first = aSrc.first + 1;
			connection.first.second = aSrc.second;
			if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
			
			// Down
			connection.first.first = aSrc.first;
			connection.first.second = aSrc.second - 1;
			if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
			
			// Up
			connection.first.first = aSrc.first;
			connection.first.second = aSrc.second + 1;
			if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
			
			if(DIAGONALS) {
				connection.second = get_diagonal_cost();
			
				// Bottom left
				connection.first.first = aSrc.first - 1;
				connection.first.second = aSrc.second - 1;
				if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
				
				// Top left
				connection.first.first = aSrc.first - 1;
				connection.first.second = aSrc.second + 1;
				if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
				
				// Top left
				connection.first.first = aSrc.first + 1;
				connection.first.second = aSrc.second - 1;
				if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
				
				// Top right
				connection.first.first = aSrc.first + 1;
				connection.first.second = aSrc.second + 1;
				if(is_walkable(connection.first.first, connection.first.second)) mConnections[count++] = connection;
			}
			
			aCount = count;
			return mConnections;
		}
		
		//virtual bool is_connected(key_t aSrc, key_t aDst, cost_t& aCost) const throw() override {
		//	return is_connected(aSrc.first, aSrc.second, aDst.first, aDst.second, aCost);
		//}
	};
}}

#endif