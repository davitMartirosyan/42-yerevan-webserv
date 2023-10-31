/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/11/01 00:53:07 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tcp.hpp"

Tcp::Tcp( void )
{
	memset(&this->rules, 0, sizeof(rules));
	memset(&this->Socket, 0, sizeof(Socket));
	memset(&this->SocketAddress, 0, sizeof(SocketAddress));
	memset(&this->SocketStorage, 0, sizeof(SocketStorage));
}

Tcp::~Tcp()
{
	
}

const char* Tcp::pton(uint32_t ipv) const
{
    char *ip = new char[16];
    std::stringstream ss;
    ss << ((int)(ipv >> 24) & 0XFF) << "." << ((int)(ipv >> 16) & 0XFF) << "." << ((int)(ipv >> 8) & 0XFF) << "." << ((int)(ipv) & 0XFF);
    int i = -1;
    while (++i < ss.str().size())
        ip[i] = ss.str().c_str()[i];
    ip[i] = '\0';
    return (ip);
}

void Tcp::setup(const char* ip, const char* port)
{
    int addrinfo = 0;
	rules.ai_family = PF_UNSPEC;
	rules.ai_flags = AI_PASSIVE;
	rules.ai_socktype = SOCK_STREAM;
	rules.ai_protocol = 0;
	rules.ai_canonname = NULL;
	if ((addrinfo = getaddrinfo(ip, port, &rules, &addrList)) < 0)
    {
        freeaddrinfo(addrList);
        throw HTTPCoreException(gai_strerror(addrinfo));
    }
    SocketAddress = addrList->ai_addr;
}

void Tcp::createSocket( void )
{
    fd = socket(addrList->ai_family, addrList->ai_socktype, addrList->ai_protocol);
    if (fd < 0)
        throw HTTPCoreException(strerror(errno)); 
}

void Tcp::bindSocket( void )
{
    if (bind(fd, SocketAddress, addrList->ai_addrlen) < 0)
        throw HTTPCoreException(strerror(errno));
}

void Tcp::listenSocket( void )
{
    if (listen(fd, 32) < 0)
        throw HTTPCoreException(strerror(errno));
}

