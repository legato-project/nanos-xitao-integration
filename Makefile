##############################################################################################
#  This program is free software; you can redistribute it and/or modify                      #
#  it under the terms of the GNU General Public License as published by                      #
#  the Free Software Foundation; either version 2 of the License, or                         #
#  (at your option) any later version.                                                       #
#                                                                                            #
#  This program is distributed in the hope that it will be useful,                           #
#  but WITHOUT ANY WARRANTY; without even the implied warranty of                            #
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                             #
#  GNU General Public License for more details.                                              #
#                                                                                            #
#  You should have received a copy of the GNU General Public License                         #
#  along with this program; if not, write to the Free Software                               #
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA            #
##############################################################################################
include makefile.inc.sample

# Object files
_OBJS = src/interop.o src/ompss_dgemm.o src/xitao_dgemm.o src/nanos6_helpers.o src/xitao_tiled_gemm.o  nanos_xitao.o 

all: nanos_xitao

%.o : %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o : %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@	

nanos_xitao: $(_OBJS)
	$(CXX) $^ -o $@ ${LIBS} ${LDFLAGS}

run: nanos_xitao 
	./nanos_xitao 512 512 512

clean:
	rm -rf nanos_xitao $(_OBJS)
