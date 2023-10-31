/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:32:40 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/31 00:13:51 by dmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_HPP
#define TCP_HPP
#include "Libs.hpp"

class Tcp
{
	public:
		Tcp( void );
		~Tcp();
	public:
		// int up(const char* ip, const char* port, int backlog);
        const char* pton(uint32_t ipv) const;
	protected:
		int fd;
		int backlog;
	protected:
		struct addrinfo rules;
		struct addrinfo* addrList;
		struct sockaddr_in *Socket;
		struct sockaddr SocketAddress;
		struct sockaddr_storage SocketStorage;
};

#endif