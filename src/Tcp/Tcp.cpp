/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:14 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/29 23:39:45 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Tcp.hpp"

Tcp::Tcp( void )
{
	memset(&this->saddr, 0, sizeof(saddr));
	memset(&this->Socket, 0, sizeof(Socket));
	memset(&this->SocketAddress, 0, sizeof(SocketAddress));
	memset(&this->SocketStorage, 0, sizeof(SocketStorage));
}

Tcp::~Tcp()
{
	
}


int Tcp::up(const char* ip, const char* port, int qLog)
{
	std::cout << ip << ":" << port << std::endl;
	saddr.ai_family = PF_UNSPEC;
	saddr.ai_flags = AI_PASSIVE;
	saddr.ai_socktype = SOCK_STREAM;
	saddr.ai_protocol = 0;
	saddr.ai_canonname = NULL;
	if ((addrinfo = getaddrinfo(ip, port, &saddr, &addrList)) < 0)
		return (addrinfo);
	else
	{
		Socket = (struct sockaddr_in*)addrList->ai_addr;
		Socket->sin_family = addrList->ai_family;
	}
	return (0);
}

// void Tcp::up(HTTPServer const &srv)
// {
// 	std::cout << srv.getIp() << ":" << srv.getPort() << std::endl;
// }

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

int Tcp::err( void )
{
	return (addrinfo);
}