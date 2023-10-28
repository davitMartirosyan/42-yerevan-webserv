/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/28 15:44:09 by dmartiro         ###   ########.fr       */
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
    if (port.size() > 5)
        throw HTTPCoreException("Port: is to long");
    for(size_t i = 0; i < port.size(); i++)
        if (!std::isdigit(port[i]))
            throw HTTPCoreException("Port: Non digit character");
    this->port = (uint16_t)std::atoi(port.c_str());
    this->portNumber = port;
}

uint16_t HTTPServer::getPort( void ) const
{
    return (this->port);
}

const char* HTTPServer::getNPort( void ) const
{
    return (this->portNumber.c_str());
}

void HTTPServer::setIp(std::string const &ipv)
{
    size_t n = 0;
    size_t k = 0;
    std::string octet;
    
    if (ipv.size() > 15)
        throw HTTPCoreException("Ip: Syntax Error");
    for(size_t i = 0; i <= ipv.size(); i++)
    {
        if (std::isdigit(ipv[i]))
        {
            n++;
            octet += ipv[i];
        }
        else if (ipv[i] == '.' || i >= ipv.size())
        {
            if (ipv[i] == '.')
                k++;
            if (n > 3 || std::atoi(octet.c_str()) > 255)
                throw HTTPCoreException("Octet: > 255");
            octet.clear();
            n = 0;
        }
        else
            throw HTTPCoreException("Ip: Syntax Error");

    }
    if (k != 3)
        throw HTTPCoreException("Dots: syntax error");
    this->ipv4 = ipv;
}

const char* HTTPServer::getIp( void ) const
{
    return (this->ipv4.c_str());
}

void HTTPServer::pushLocation(std::string const &prefix, Location locationDirective)
{
    this->locations.insert(std::make_pair(prefix, locationDirective));
}

const Location* HTTPServer::find(std::string const &prefix) const
{
    std::map<std::string, Location>::const_iterator route = locations.find(prefix);
    if (route != locations.end())
        return (&route->second);
    return (NULL);
}

Location* HTTPServer::find(std::string const &prefix)
{
    std::map<std::string, Location>::iterator route = locations.find(prefix);
    if (route != locations.end())
        return (&route->second);
    return (NULL);
}