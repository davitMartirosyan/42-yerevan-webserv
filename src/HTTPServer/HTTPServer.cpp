/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/22 23:51:37 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer(std::string const &ip, std::string const &port)
{
    setListenerIpPort(ip, port);
    root = "www/server1/";
    autoindex = true;
    client_body_size = 2000;
    locations.insert(std::make_pair("/", Location()));
}

HTTPServer::~HTTPServer()
{
    
}

int HTTPServer::getServerSocket( void )
{
    return (fd);
}


std::string const &HTTPServer::getIp( void ) const
{
    return (ip);
}

std::string const &HTTPServer::getPort( void ) const
{
    return (port);
}

void HTTPServer::setListenerIpPort(std::string const &ip, std::string const &port)
{
    this->ip = ip;
    this->port = port;
}