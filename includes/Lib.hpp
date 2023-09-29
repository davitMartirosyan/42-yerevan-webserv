/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:42:02 by dmartiro          #+#    #+#             */
/*   Updated: 2023/09/30 00:17:56 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_HPP
#define LIB_HPP
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include <map>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

//User-defined
#include "HttpMetaProvider.hpp"
#include "HttpRequest.hpp"
#endif