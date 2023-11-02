/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/02 00:53:40 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer( void )
{
    
}

HTTPServer::~HTTPServer()
{
    
}

void HTTPServer::setPort(std::string const &port)
{
    if (port.size() > 5)
        throw HTTPCoreException("Port: is to long");
    for(size_t i = 0; i < port.size(); i++)
        if (!std::isdigit(port[i]))
            throw HTTPCoreException("Port: Non digit character");
    this->n_port = (uint16_t)std::atoi(port.c_str());
    this->port = port;
}

uint16_t HTTPServer::getNPort( void ) const
{
    return (this->n_port);
}

const char* HTTPServer::getPort( void ) const
{
    return (this->port.c_str());
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
    this->ip = ipv;
}

const char* HTTPServer::getIp( void ) const
{
    return (this->ip.c_str());
}

uint32_t HTTPServer::getNIp( void ) const
{
    return (this->n_ip);
}

void HTTPServer::push(std::string const &prefix, Location locationDirective)
{
    this->locations.insert(std::make_pair(prefix, locationDirective));
}

void HTTPServer::push(std::string const &srvName)
{
    std::vector<std::string>::iterator it = std::find(ServerName.begin(), ServerName.end(), srvName);
    if (it == ServerName.end())
        ServerName.push_back(srvName);
}

const Location* HTTPServer::find(std::string const &prefix) const
{
    std::map<std::string, Location>::const_iterator route = locations.find(prefix);
    if (route != locations.end())
        return (&route->second);
    return (NULL);
}

std::vector<std::string> const &HTTPServer::getServerNames( void ) const
{
    return (ServerName);
}

void HTTPServer::up( void )
{
    int addrinfo = 0;
    const char* givenIp = !ip.empty() ? ip.c_str() : "0.0.0.0";
    const char* givenPort = !port.empty() ? port.c_str() : "8080";
    Tcp::setup(givenIp, givenPort);
    Tcp::createSocket();
    Tcp::bindSocket();
    Tcp::listenSocket();
    std::cout << givenIp <<  ":" << givenPort << std::endl;
    std::cout << ServerName[0] << ": Up" << std::endl;
    freeaddrinfo(addrList);
}

void HTTPServer::push(sock_t clFd, Client &clt)
{
    clnt.insert(std::make_pair(clFd, clt));
}

bool HTTPServer::exist(sock_t fd)
{
    return (clnt.find(fd) != clnt.end());
}

// void HTTPServer::request(Client &cl)
// {
//     int buf = 0;
//     char http[READ_BUFFER];
//     while ((buf = recv(cl.getFd(), http, sizeof(http), 0)) > 0)
//     {
//         cl.append(http);
//     }
//     std::cout << "hasa" << std::endl;
//     std::cout << cl.getHttpRequest() << std::endl;   
// }