/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/25 23:39:54 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer( void )
{
    
}

HTTPServer::~HTTPServer()
{
    
}

int HTTPServer::getServerSocket( void )
{
    return (fd);
}

void HTTPServer::setPort(std::string const &port)
{
    std::cout << port.size() << std::endl;
    if (port.size() > 5)
        throw HTTPCoreException("Port: is to long");
    for(size_t i = 0; i < port.size(); i++)
        if (!std::isdigit(port[i]))
            throw HTTPCoreException("Port: Non digit character");
    this->port = (uint16_t)std::atoi(port.c_str());
}

uint16_t HTTPServer::getPort( void ) const
{
    return (this->port);
}

void HTTPServer::setIp(std::string const &ipv)
{
    if (ipv.size() > 15)
        throw HTTPCoreException("Ip: Syntax Error");
    for(size_t i = 0; i < ipv.size(); i++)
        if (ipv[i] != '.' || !std::isdigit(ipv[i]))
            throw HTTPCoreException("Ip: Non ip character [0-9][.][0-9][.][0.9][.][0-9]");
}

uint32_t HTTPServer::getIp( void ) const
{
    return (this->ip);
}