/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 06:37:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/01 00:53:07 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
#define LIBS_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <algorithm>
#include <limits.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdexcept>
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include <fstream>
#include <sys/select.h>
#include <map>
#include <vector>
#include "DefaultSetup.hpp"

typedef std::vector<std::string> methods_t;
typedef std::vector<std::string> indexes_t;
#endif