/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmartiro <dmartiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:32:40 by dmartiro          #+#    #+#             */
/*   Updated: 2023/10/28 13:09:51 by dmartiro         ###   ########.fr       */
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
		void up( void );
	public:
        const char* pton(uint32_t ipv) const;
	protected:
		int fd;
		int backlog;
	private:
		struct addrinfo ServerAddress;
		struct sockaddr_in SocketInfo;
		struct sockaddr SocketAddress;
		struct sockaddr_storage SocketStorage;
};

#endif