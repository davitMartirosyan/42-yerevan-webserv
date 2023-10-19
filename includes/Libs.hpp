/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Libs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 06:37:27 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/19 17:25:48 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_HPP
#define LIBS_HPP
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstring>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <poll.h>
#include <fstream>
#include <sys/select.h>
#include <map>
#include <vector>
#define CONFIGS "./conf/"
#define DFLT "./conf/webserv.conf"
#define READ_BUFFER     150000
#define WRITE_BUFFER    150000

struct Conf
{
    protected:
        std::string root;                                       // [root]           www/server1/
        std::vector<std::string> index;                         // [index]          index.html barev.html index.html ....
        std::vector<std::string> methods;                       // [allow_methods]  GET | POST | DELETE
        std::map<std::string, std::string> error_page;          // [error_page]     404 [root]/error_pages/404.html 
        int autoindex;                                          // [autoindex]      on (1) | off (0)
        unsigned long long int client_body_size; // 200000000byte -> 200mb 
};

#endif