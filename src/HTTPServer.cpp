/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HTTPServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 23:57:39 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/05 17:09:01 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HTTPServer.hpp"

HTTPServer::HTTPServer( void )
{
    //defualt initializations
    this->port = DEFAULT_HTTP_PORT;
    this->ip = DEFAULT_MASK;
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
    return (port.c_str());
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

void HTTPServer::up(ServerManager const &mgn)
{

    if (!mgn.used(this))
    {
        const char* givenIp = ip.c_str();
        const char* givenPort = port.c_str();
        Tcp::setup(givenIp, givenPort);
        Tcp::createSocket();
        Tcp::bindSocket();
        Tcp::listenSocket();
        std::cout << givenIp <<  ":" << givenPort << std::endl;
        freeaddrinfo(addrList);
    }
    else
        std::cout << "{Already:used}" << std::endl;
}

void HTTPServer::push(sock_t clFd, Client &clt)
{
    clnt.insert(std::make_pair(clFd, clt));
}

bool HTTPServer::exist(sock_t fd)
{
    return (clnt.find(fd) != clnt.end());
}

void HTTPServer::request(Client &cl)
{
    int buf = 0;
    char http[READ_BUFFER];
    buf = recv(cl.getFd(), http, sizeof(http), 0);
    http[buf] = '\0';
    std::cout << http << std::endl;
}

bool HTTPServer::operator==(HTTPServer const &sibling)
{
    if (std::strcmp(this->getIp(), sibling.getIp()) == 0 \
        && std::strcmp(this->getPort(),sibling.getPort()) == 0)
      return (true);  
    return (false);
}

//ServerCore////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
/***************************************************************** */

// int HTTPServer::getClientBodySize( void )
// {
// 	return (client_body_size);
// }

// void HTTPServer::pushIndex(std::string const &fileNameExample)
// {
// 	index.push_back(fileNameExample);
// }

// void HTTPServer::pushMethods(std::string const &method)
// {
// 	std::string capitalized = method;
// 	for(size_t i = 0; i < method.size(); i++)
// 		capitalized[i] = std::toupper(capitalized[i]);
// 	methods.push_back(capitalized);
// }

// std::vector<std::string> HTTPServer::getIndexFiles( void ) const
// {
// 	return (this->index);
// }

// std::vector<std::string> HTTPServer::getMethods( void ) const
// {
// 	return (this->methods);
// }

// void HTTPServer::setRoot(std::string const &root)
// {
// 	this->root = root;
// }

// std::string const &HTTPServer::getRoot( void ) const
// {
// 	return (this->root);
// }

// const char* HTTPServer::findIndex(std::string const &filename) const
// {
// 	size_t i = 0;
// 	for(; i < index.size(); i++)
// 		if (index[i] == filename)
// 			return (index[i].c_str());
// 	return (NULL);
// }

// const char* HTTPServer::findMethod(std::string const &method) const
// {
// 	size_t i = 0;
// 	for(; i < methods.size(); i++)
// 		if (methods[i] == method)
// 			return (methods[i].c_str());
// 	return (NULL);
// }

// const char* HTTPServer::findErrorPage(std::string const &status_code)
// {
// 	std::map<std::string, std::string>::iterator it = error_page.find(status_code);
// 	if (it != error_page.end())
// 		return (it->second.c_str());
// 	return (NULL);
// }

// void HTTPServer::setAutoindex(std::string const &sw)
// {
// 	(sw == "on") ? this->autoindex = 1 : this->autoindex = 0;
// }

// void HTTPServer::pushErrPage(std::string const &key, std::string const &errpage_filename)
// {
// 	error_page.insert(std::make_pair(key, errpage_filename));
// }

// void HTTPServer::setSize(std::string const &bodySize)
// {
// 	unsigned long long int toLong = std::strtoull(bodySize.c_str(), NULL, 10);
// 	if (errno == ERANGE && toLong == ULLONG_MAX)
// 		this->client_body_size = 200;
// 	else
// 		this->client_body_size = toLong * 1048576 / 1;
// }

// bool HTTPServer::getAutoindex( void ) const
// {
// 	return (autoindex);
// }