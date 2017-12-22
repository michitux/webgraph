/*               
 * Portions copyright (c) 2003-2007, Paolo Boldi and Sebastiano Vigna. Translation copyright (c) 2007, Jacob Ratkiewicz
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <iostream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>

#include "../webgraph/webgraph.hpp"

template <typename stream>
size_t PutVarint(stream& s, uint64_t v) {
	if (v < 128) {
		s << uint8_t(v);
                return 1;
	}
	else if (v < 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t((v >> 07) & 0x7F);
                return 2;
	}
	else if (v < 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t((v >> 14) & 0x7F);
                return 3;
	}
	else if (v < 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t((v >> 21) & 0x7F);
                return 4;
	}
	else if (v < 128llu * 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t((v >> 28) & 0x7F);
                return 5;
	}
	else if (v < 128llu * 128 * 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t(((v >> 28) & 0x7F) | 0x80);
		s << uint8_t((v >> 35) & 0x7F);
                return 6;
	}
	else if (v < 128llu * 128 * 128 * 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t(((v >> 28) & 0x7F) | 0x80);
		s << uint8_t(((v >> 35) & 0x7F) | 0x80);
		s << uint8_t((v >> 42) & 0x7F);
                return 7;
	}
	else if (v < 128llu * 128 * 128 * 128 * 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t(((v >> 28) & 0x7F) | 0x80);
		s << uint8_t(((v >> 35) & 0x7F) | 0x80);
		s << uint8_t(((v >> 42) & 0x7F) | 0x80);
		s << uint8_t((v >> 49) & 0x7F);
                return 8;
	}
	else if (v < 128llu * 128 * 128 * 128 * 128 * 128 * 128 * 128 * 128) {
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t(((v >> 28) & 0x7F) | 0x80);
		s << uint8_t(((v >> 35) & 0x7F) | 0x80);
		s << uint8_t(((v >> 42) & 0x7F) | 0x80);
		s << uint8_t(((v >> 49) & 0x7F) | 0x80);
		s << uint8_t((v >> 56) & 0x7F);
                return 9;
	}
		s << uint8_t(((v >> 00) & 0x7F) | 0x80);
		s << uint8_t(((v >> 07) & 0x7F) | 0x80);
		s << uint8_t(((v >> 14) & 0x7F) | 0x80);
		s << uint8_t(((v >> 21) & 0x7F) | 0x80);
		s << uint8_t(((v >> 28) & 0x7F) | 0x80);
		s << uint8_t(((v >> 35) & 0x7F) | 0x80);
		s << uint8_t(((v >> 42) & 0x7F) | 0x80);
		s << uint8_t(((v >> 49) & 0x7F) | 0x80);
		s << uint8_t(((v >> 56) & 0x7F) | 0x80);
		s << uint8_t((v >> 63) & 0x7F);
                return 10;
};



int main( int argc, char** argv ) {
   using namespace webgraph::bv_graph;

   if( argc < 3 ) {
      std::cerr << "You have to provide name of input and output graph file prefix.\n";
      return 1;
   }
   
   std::string name = argv[1];
   std::string out_name = argv[2];

   typedef boost::shared_ptr<graph> graph_ptr;

   graph_ptr graph_out = graph::load_offline( name );

   graph_ptr graph_in = graph::load_offline( name + "-t");
   
   graph::node_iterator u_out, u_in, u_out_end, u_in_end;
   
   boost::tie(u_out, u_out_end) = graph_out->get_node_iterator( 0 );
   boost::tie(u_in, u_in_end) = graph_in->get_node_iterator( 0 );
   
   std::cerr << graph_out->get_num_nodes() << std::endl;

   size_t part_id = 0;

   auto get_out_name = [&part_id,&out_name]() {
      std::stringstream ss;
      ss << std::setw(5) << std::setfill('0') << part_id;
      return out_name + ".part_" + ss.str();
   };
   
   std::ofstream out_stream(get_out_name(), std::ios::trunc | std::ios::binary);

   size_t bytes_written = 0;
   
   for (; u_out != u_out_end; ++u_out, ++u_in) {
      assert(u_in != u_in_end);

      if (bytes_written >= (1ull << 30)) {
         bytes_written = 0;
         ++part_id;
         out_stream.close();
         out_stream = std::ofstream(get_out_name(), std::ios::trunc | std::ios::binary);
      }

      std::vector<int> out_neighbors = successor_vector(u_out);
      std::vector<int> in_neigbors = successor_vector(u_in);

      if (!std::is_sorted(out_neighbors.begin(), out_neighbors.end())) {
         throw std::runtime_error("Error, out neighbors were assumed to be sorted but are not.");
      }
      
      if (!std::is_sorted(in_neigbors.begin(), in_neigbors.end())) {
         throw std::runtime_error("Error, in neighbors were assumed to be sorted but are not.");
      }

      std::vector<int> combined_neighbors;
      std::set_union(out_neighbors.begin(), out_neighbors.end(),
                     in_neigbors.begin(), in_neigbors.end(),
                     std::back_inserter(combined_neighbors));

      bytes_written += PutVarint(out_stream, combined_neighbors.size());

      for (int32_t v : combined_neighbors) {
         if (*u_out < v) {
            out_stream.write(reinterpret_cast<const char*>(&v), 4);
            bytes_written += 4;
         }
      }

      if (*u_out != 0 && *u_out % 100000 == 0) {
         std::cout << *u_out << std::endl;
      }
   }

   out_stream.close();

   return 0;  
}
