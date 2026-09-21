# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/20 14:25:00 by cgajean           #+#    #+#              #
#    Updated: 2026/09/21 11:56:33 by cgajean          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# Compile                                                                      #
# **************************************************************************** #

FROM fedora:44

RUN dnf update && dnf install -y nasm g++ make && \
    rm -rf /var/cache/dnf

# Copy the project files
COPY libasm /libasm
COPY libcpp /libcpp
COPY tester_cpp /tester_cpp
COPY Makefile /

# Compile the project
RUN make bonus CXX=g++ ASM_CMP=nasm

ENTRYPOINT [ "/tester_cpp/libasm_tester" ]
